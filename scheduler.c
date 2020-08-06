#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "laneChangeWarning.h"
#include "systemStateMachine.h"
#include "CI_Defines.h"
#include "CommunicationInterface.h"
#include "RearCrossTrafficAlert.h"
#include "error_functions.h"
#include "error_constants.h"
#include <time.h>
//#include DEVELOPMENT
//#include "myDefines.h"

int main()
{
    int contor_teste=0;
    int x = 0;
    bool led_b = 0;
    bool audio_b = 0;
    int myTrigger_i = 500; /* 10ms task * 500 = 5s */
    unsigned char iterations_uc = 0;
    Warning_Feature lcwWarn_st;
    Warning_Feature rctaWarn_st;
    unsigned char msec_uc = 0, trigger_uc = 10; /* 10ms */
    clock_t before = clock();
    ErrStatus MYerr_e[2];
    ErrStatus myBatErr_e, myLostComErr_e;
    // MYerr_st[0].errQualTime_c=2; MYerr_st[0].errDequalTime_c =5; MYerr_st[0].errName_e=err_lostcom; MYerr_st[0].errStatus_e=passed;
    // MYerr_st[1].errQualTime_c=1; MYerr_st[1].errDequalTime_c =4; MYerr_st[1].errName_e=err_batvoltage; MYerr_st[1].errStatus_e=passed;
    // MYerr_st[2].errQualTime_c=3; MYerr_st[2].errDequalTime_c =7; MYerr_st[2].errName_e=err_lostcom; MYerr_st[2].errStatus_e=passed;
    int menu_decision_uc;
    int y = 0;
    bool under_b;
    bool over_b;
    bool valuesFromTest[NUMBER_OF_TEST];
    readTestFile(valuesFromTest);
    int ok = 1;
    printf("\n");
    for (int contor = 0; contor < sizeof(valuesFromTest); contor++)
    {
        printf("%d ", valuesFromTest[contor]);
    }
    printf("\n");
    // #ifdef DEVELOPMENT
    while (1)
    {
        printf("Introduce menu option:");
        scanf("%d", &menu_decision_uc);

        switch (menu_decision_uc)
        {
        case 1:
            CI_Read_data();
            break;

        case 2:
            x = 0;
            while (x < 1000)
            {
                iterations_uc = 0;
                do
                {
                    clock_t difference = clock() - before;
                    msec_uc = difference * 1000 / CLOCKS_PER_SEC;
                    iterations_uc++;
                } while (msec_uc < trigger_uc);
                printf("Iteratia curenta e: %d\n", x);
                errorHandler_BatteryVoltage_Check();
                errorHandler_Communication_Check();
                //CI_getGlobalErr_st(MYerr_st);
                errorHandler_GetError(err_batvoltage, &myBatErr_e);
                //Ssm crt_smm_state1 = systemStateMachine_change_state(MYerr_st,&myTrigger_i);
                errorHandler_GetError(err_lostcom, &myLostComErr_e);
                printf("Battery Voltage Error: %s and Lost Communication Error: %s\n", CI_getErrStatusChar(myBatErr_e), CI_getErrStatusChar(myLostComErr_e));
                MYerr_e[0] = myBatErr_e, MYerr_e[1] = myLostComErr_e;
                under_b = CI_getUndervoltage();
                over_b = CI_getOverVoltage();
                if (under_b == UNDERVOLTAGE_TRUE_B)
                {
                    printf("undervoltage\n");
                }
                if (over_b == OVERVOLTAGE_TRUE_B)
                {
                    printf("overvoltage\n");
                }
                Ssm crt_smm_state = systemStateMachine_change_state(MYerr_e, &myTrigger_i);
                CI_setCurrent_ssm_state(crt_smm_state);
                unsigned char mySpeed_uc = CI_getSpeed();
                Gear myGear_e = CI_getGear();
                char myAngle_c = CI_getAngle();
                float myDist_f = CI_getDistance();
                bool check_rez_b = 0;
                check_rez_b = laneChangeWarning_set_lcw_state(mySpeed_uc, myGear_e, myAngle_c, crt_smm_state);
                laneChangeWarning_check_colision(check_rez_b, myDist_f);
                RCTA_colisionRCTA();
                CI_getLCW_Warning(&lcwWarn_st);
                CI_getRCTA_Warning(&rctaWarn_st);
                led_b = lcwWarn_st.led_light_b || rctaWarn_st.led_light_b;
                audio_b = lcwWarn_st.audio_signal_b || rctaWarn_st.audio_signal_b;
                printf("Led LCW: %d and Audio LCW: %d\n",lcwWarn_st.led_light_b,lcwWarn_st.audio_signal_b);
                printf("Led RCTA: %d and Audio RCTA: %d\n", rctaWarn_st.led_light_b, rctaWarn_st.audio_signal_b);
                printf("Led Fin: %d and Audio Fin: %d\n", led_b, audio_b);
                x++;
            }
            break;

        case 3:
            return 0;
            //#ifdef Testing
        case 4: //testing
            //readTestFile(valuesFromTest);
            x=0;
            CI_Write_data(0,DVS);
            CI_Write_data(1,DVG);
            CI_Write_data(2,DVA);
            CI_Write_data(3,DVD);
            CI_Write_data(4,DVB);
            CI_Read_data();
            while(x<800)
            {
                iterations_uc = 0;
                do
                {
                    clock_t difference = clock() - before;
                    msec_uc = difference * 1000 / CLOCKS_PER_SEC;
                    iterations_uc++;
                } while (msec_uc < trigger_uc);
                if(x==0)
                {
                    CI_Write_data(1, 2);//gear=reverse
                    CI_Read_data();
                    contor_teste++;
                }
                if(x>=0 && x<100)
                {
                    //wait
                }
                if(x>=100 && x<200)
                {
                    
                    if (rctaWarn_st.led_light_b != valuesFromTest[contor_teste-1])
                    {                   
                        printf("fail1  %d\n",valuesFromTest[contor_teste-1]);
                        //printf("Led : %d and Audio : %d\n", lcwWarn_st.led_light_b, lcwWarn_st.audio_signal_b);
                    }
                    else
                    {
                        printf("passed\n");
                    }
                    
                }
                if(x==200)
                {
                    CI_Write_data(0,5);
                    CI_Read_data();
                    contor_teste++;
                }
                if(x>=200 && x<500)
                {
                    //wait
                }
                if(x>=500 && x<600)
                {                   
                    if (rctaWarn_st.led_light_b != valuesFromTest[contor_teste-1])
                    {                   
                        printf("fail2  %d\n",valuesFromTest[contor_teste-1]);
                        //printf("Led : %d and Audio : %d\n", lcwWarn_st.led_light_b, lcwWarn_st.audio_signal_b);
                    }
                    else
                    {
                        printf("passed\n");
                    }
                    
                }
                if(x==600)
                {
                    
                    CI_Write_data(3,3.9);
                    CI_Read_data();
                    contor_teste++;
                }
                
                if(x>=600 && x<650)
                {                   
                    if (rctaWarn_st.led_light_b != valuesFromTest[contor_teste-1])
                    {                   
                        printf("fail3  %d\n",valuesFromTest[contor_teste-1]);
                    }
                    else
                    {
                        printf("passed\n");
                    }
                    
                }
                if(x==650)
                {
                    CI_Write_data(4,7);                
                    CI_Read_data();
                    contor_teste++;
                }
                
                if(x>=650 && x<800)
                {   
                    //printf("Iteratia curenta e: %d\n", x);            
                    if (rctaWarn_st.led_light_b != valuesFromTest[contor_teste-1])
                    {                   
                        printf("fail4  %d\n",valuesFromTest[contor_teste-1]);
                        //printf("Led : %d and Audio : %d\n", rctaWarn_st.led_light_b, rctaWarn_st.audio_signal_b);
                    }
                    else
                    {
                        printf("passed\n");
                    }
                    
                }
                errorHandler_BatteryVoltage_Check();
                errorHandler_Communication_Check();
                errorHandler_GetError(err_batvoltage, &myBatErr_e);
                errorHandler_GetError(err_lostcom, &myLostComErr_e);
                //printf("Battery Voltage Error: %s and Lost Communication Error: %s\n", CI_getErrStatusChar(myBatErr_e), CI_getErrStatusChar(myLostComErr_e));
                MYerr_e[0] = myBatErr_e, MYerr_e[1] = myLostComErr_e;
                under_b = CI_getUndervoltage();
                over_b = CI_getOverVoltage();
                Ssm crt_smm_state = systemStateMachine_change_state(MYerr_e, &myTrigger_i);
                CI_setCurrent_ssm_state(crt_smm_state);
                unsigned char mySpeed_uc = CI_getSpeed();
                Gear myGear_e = CI_getGear();
                char myAngle_c = CI_getAngle();
                float myDist_f = CI_getDistance();
                bool check_rez_b = 0;
                check_rez_b = laneChangeWarning_set_lcw_state(mySpeed_uc, myGear_e, myAngle_c, crt_smm_state);
                laneChangeWarning_check_colision(check_rez_b, myDist_f);
                RCTA_colisionRCTA();
                CI_getLCW_Warning(&lcwWarn_st);
                CI_getRCTA_Warning(&rctaWarn_st);
                led_b = lcwWarn_st.led_light_b || rctaWarn_st.led_light_b;
                audio_b = lcwWarn_st.audio_signal_b || rctaWarn_st.audio_signal_b;
                x++;
            }
            
        
            break;

            //#endif
        default:
            printf("invalid");
        }
        y++;
    }

    //#endif

    return 0;
}
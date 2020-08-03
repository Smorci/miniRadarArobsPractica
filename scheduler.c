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
//#include "myDefines.h"


int main(){
    
    int x=0;
    bool led_b =0;
    bool audio_b=0;
    int myTrigger_i = 500; /* 10ms task * 500 = 5s */
    unsigned char iterations_uc =0;
    Warning_Feature lcwWarn_st;
    Warning_Feature rctaWarn_st;
    unsigned char msec_uc = 0, trigger_uc = 10; /* 10ms */
    clock_t before = clock();
    ErrStatus MYerr_e[2];
    ErrStatus myBatErr_e, myLostComErr_e;
    int menu_decision_uc;
    int y=0;
    bool under_b;
    bool over_b;
    while(1){
        printf("Introduce menu option:");
        scanf("%d",&menu_decision_uc);

            switch (menu_decision_uc)
            {
            case 1:
                CI_Read_data();
                break;
            
            case 2:
                x=0;
                while(x<1000){
                        iterations_uc=0;
                        do {
                            clock_t difference = clock() - before;
                            msec_uc = difference * 1000 / CLOCKS_PER_SEC;
                            iterations_uc++;
                        }while ( msec_uc < trigger_uc );  
                        printf("Iteratia curenta e: %d\n",x);
                        errorHandler_BatteryVoltage_Check();
                        errorHandler_Communication_Check();
                        errorHandler_GetError(err_batvoltage,&myBatErr_e);
                        errorHandler_GetError(err_lostcom,&myLostComErr_e);
                        printf("Battery Voltage Error: %s and Lost Communication Error: %s\n",CI_getErrStatusChar(myBatErr_e),CI_getErrStatusChar(myLostComErr_e));
                        MYerr_e[0] = myBatErr_e, MYerr_e[1]=myLostComErr_e;
                        under_b = CI_getUndervoltage();
                        over_b = CI_getOverVoltage();
                        if(under_b == UNDERVOLTAGE_TRUE_B){
                            printf("undervoltage\n");
                        }
                        if(over_b == OVERVOLTAGE_TRUE_B){
                            printf("overvoltage\n");
                        }
                        Ssm crt_smm_state = systemStateMachine_change_state(MYerr_e,&myTrigger_i);
                        CI_setCurrent_ssm_state(crt_smm_state);
                        unsigned char mySpeed_uc = CI_getSpeed();
                        Gear myGear_e = CI_getGear();
                        char myAngle_c = CI_getAngle();
                        unsigned char myDist_uc = CI_getDistance();
                        bool check_rez_b = 0;
                        check_rez_b = laneChangeWarning_set_lcw_state(mySpeed_uc,myGear_e,myAngle_c,crt_smm_state);
                        laneChangeWarning_check_colision(check_rez_b,myDist_uc);
                        RCTA_colisionRCTA();
                        CI_getLCW_Warning(&lcwWarn_st);
                        CI_getRCTA_Warning(&rctaWarn_st);
                        led_b = lcwWarn_st.led_light_b || rctaWarn_st.led_light_b;
                        audio_b = lcwWarn_st.audio_signal_b || rctaWarn_st.audio_signal_b;
                        printf("Led Fin: %d and Audio Fin: %d\n",led_b,audio_b);
                        x++;
                    }
                    break;
            
            case 3:
                return 0;
            
            default:
                break;
            }
            y++;
    }
    
    
   
    
    return 0;
}
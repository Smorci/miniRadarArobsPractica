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
    // MYerr_st[0].errQualTime_c=2; MYerr_st[0].errDequalTime_c =5; MYerr_st[0].errName_e=err_lostcom; MYerr_st[0].errStatus_e=passed;
    // MYerr_st[1].errQualTime_c=1; MYerr_st[1].errDequalTime_c =4; MYerr_st[1].errName_e=err_batvoltage; MYerr_st[1].errStatus_e=passed; 
    // MYerr_st[2].errQualTime_c=3; MYerr_st[2].errDequalTime_c =7; MYerr_st[2].errName_e=err_lostcom; MYerr_st[2].errStatus_e=passed; 
    while(x<550){
        iterations_uc=0;
        do {
            clock_t difference = clock() - before;
            msec_uc = difference * 1000 / CLOCKS_PER_SEC;
            iterations_uc++;
        }while ( msec_uc < trigger_uc );  
        printf("Iteratia curenta e: %d\n",x);
        CI_Read_data();
        errorHandler_BatteryVoltage_Check();
        errorHandler_Communication_Check();
        //CI_getGlobalErr_st(MYerr_st);
        errorHandler_GetError(err_batvoltage,&myBatErr_e);
        //Ssm crt_smm_state1 = systemStateMachine_change_state(MYerr_st,&myTrigger_i);
        errorHandler_GetError(err_lostcom,&myLostComErr_e);
        printf("BatErr: %d and CommErr: %d\n",myBatErr_e,myLostComErr_e);
        MYerr_e[0] = myBatErr_e, MYerr_e[1]=myLostComErr_e;
        Ssm crt_smm_state = systemStateMachine_change_state(MYerr_e,&myTrigger_i);
        // Ssm crt_smm_state;
        // if(myTrigger_i == 0){
        //     if(crt_smm_state1 == error || crt_smm_state2 == error){
        //         crt_smm_state =
        //     CI_setCurrent_ssm_state(error);
        //     }
        //     else{
        //         CI_setCurrent_ssm_state(active);
        //     }
        // } else CI_setCurrent_ssm_state(init);

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
    
    return 0;
}
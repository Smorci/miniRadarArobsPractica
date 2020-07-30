#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "definesLCW.h"
#include "CI_Defines.h"
#include "CommunicationInterface.h" 

bool laneChangeWarning_check_param(unsigned char speed_uc, Gear gear_e, char angle_c, Ssm current_ssm_state_e){
    bool param_passed_u = CONDITION_NOT_PASSED_U;
    if(speed_uc <= MIN_SPPED_U){
        param_passed_u = CONDITION_NOT_PASSED_U;
    }
    else if(gear_e != forward){
        param_passed_u = CONDITION_NOT_PASSED_U;
    }
    else if(angle_c <= MIN_ANGLE_C){
       param_passed_u = CONDITION_NOT_PASSED_U;
    }
    else if(current_ssm_state_e == active){
        param_passed_u = CONDITION_PASSED_U;
    }
    else if(current_ssm_state_e == error){
       param_passed_u = CONDITION_NOT_PASSED_U;
    }
    return param_passed_u;
}

bool laneChangeWarning_set_lcw_state(unsigned char speed_uc, Gear gear_e, char angle_c, Ssm current_ssm_state_e){
    bool current_lcw_state_b = LCW_PASSIVE_U;
    bool check_b = laneChangeWarning_check_param(speed_uc,gear_e,angle_c,current_ssm_state_e);
    //printf("chek_param returned: %d\n",check_b);

    if(check_b == CONDITION_NOT_PASSED_U){
        current_lcw_state_b = LCW_PASSIVE_U;
    }
    //do{
        //check_b= check_param(speed,gear,angle,current_ssm_state);
    if(check_b == CONDITION_PASSED_U){
        current_lcw_state_b = LCW_ACTIVE_U;
    }
        //return 1;
    //}while(check_b == 1);

   //current_lcw_state_b = LCW_PASSIVE;
   //printf("LCW state is: %d\n",current_lcw_state_b);
   return current_lcw_state_b;
    
}

void laneChangeWarning_check_colision(bool current_lcw_state_b, char distance_c){
    Warning_Feature *LCW_Warn_st = malloc(20);
    CI_getLCW_Warning(LCW_Warn_st);
    LCW_Warn_st->isActiv_b=current_lcw_state_b;
    if(current_lcw_state_b == LCW_PASSIVE_U){
        LCW_Warn_st->led_light_b=0;
        LCW_Warn_st->audio_signal_b=0;
    }
    if(current_lcw_state_b == LCW_ACTIVE_U){
        if(distance_c<=RANGE_LCW_U){
            LCW_Warn_st->led_light_b=1;
            LCW_Warn_st->audio_signal_b=1;
        }
    }
    CI_setLCW_Warning(LCW_Warn_st);
    printf("Led LCW: %d and Audio LCW: %d\n",LCW_Warn_st->led_light_b,LCW_Warn_st->audio_signal_b);
}




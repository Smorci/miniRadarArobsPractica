#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "myDefines.h"


bool laneChangeWarning_check_param(unsigned char speed_uc, enum gear_poz gear_e, char angle_c, enum ssm_states current_ssm_state_e){
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
    else if(current_ssm_state_e == ACTIVE){
        param_passed_u = CONDITION_PASSED_U;
    }
    else if(current_ssm_state_e == ERROR){
       param_passed_u = CONDITION_NOT_PASSED_U;
    }
    return param_passed_u;
}

bool laneChangeWarning_set_lcw_state(unsigned char speed_uc, enum gear_poz gear_e, char angle_c, enum ssm_states current_ssm_state_e){
    bool current_lcw_state_b = LCW_PASSIVE_U;
    bool check_b = laneChangeWarning_check_param(speed_uc,gear_e,angle_c,current_ssm_state_e);

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
   return current_lcw_state_b;
    
}

void laneChangeWarning_check_colision(bool current_lcw_state_b, char distance_c){
    if(current_lcw_state_b == LCW_PASSIVE_U){
        led_light_b=0;
        audio_signal_b=0;
    }
    if(current_lcw_state_b == LCW_ACTIVE_U){
        if(distance_c<=RANGE_LCW_U){
            led_light_b=1;
            audio_signal_b=1;
        }
    }
}




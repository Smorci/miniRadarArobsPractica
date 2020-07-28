#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "myDefines.h"


bool laneChangeWarning_check_param(unsigned char speed, enum gear_poz gear, char angle, enum ssm_states current_ssm_state){
    bool param_passed_u = CONDITION_NOT_PASSED;
    if(speed <= MIN_SPPED_U){
        param_passed_u = CONDITION_NOT_PASSED;
    }
    else if(gear != forward){
        param_passed_u = CONDITION_NOT_PASSED;
    }
    else if(angle <= MIN_ANGLE_C){
       param_passed_u = CONDITION_NOT_PASSED;
    }
    else if(current_ssm_state == ACTIVE){
        param_passed_u = CONDITION_PASSED;
    }
    else if(current_ssm_state == ERROR){
       param_passed_u = CONDITION_NOT_PASSED;
    }
    return param_passed_u;
}

bool laneChangeWarning_set_lcw_state(unsigned char speed, enum gear_poz gear, char angle, enum ssm_states current_ssm_state){
    bool current_lcw_state_b = LCW_PASSIVE;
    bool check_b = laneChangeWarning_check_param(speed,gear,angle,current_ssm_state);

    if(check_b == CONDITION_NOT_PASSED){
        current_lcw_state_b = LCW_PASSIVE;
    }
    //do{
        //check_b= check_param(speed,gear,angle,current_ssm_state);
    if(check_b == CONDITION_PASSED){
        current_lcw_state_b = LCW_ACTIVE;
    }
        //return 1;
    //}while(check_b == 1);

   //current_lcw_state_b = LCW_PASSIVE;
   return current_lcw_state_b;
    
}

void laneChangeWarning_check_colision(bool current_lcw_state, char distance){
    if(current_lcw_state == LCW_PASSIVE){
        return;
    }
    if(current_lcw_state == LCW_ACTIVE){
        if(distance<=RANGE){
            led_light_b=1;
            audio_signal_b=1;
        }
    }
}



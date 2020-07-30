#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "definesSSM.h"
#include "CI_Defines.h"

const char* getStateName(Ssm crt_state) 
{
   switch (crt_state) 
   {
      case init: return "INIT";
      case active: return "ACTIVE";
      case error: return "ERROR";
      /* etc... */
   }
}

bool systemStateMachine_check_err_val(ErrList err_vect_st[]){
    bool err_existence_b = NO_ERROR_OCURED_U;
    if (err_vect_st[0].errStatus_e==fail){
        err_existence_b = ERROR_OCURED_U;
    }
    else if(err_vect_st[1].errStatus_e==fail){
        err_existence_b =ERROR_OCURED_U;
    }
    else if(err_vect_st[2].errStatus_e==fail){
        err_existence_b =ERROR_OCURED_U;
    }
    else{
        err_existence_b=NO_ERROR_OCURED_U;
    }
    return err_existence_b;
}

Ssm systemStateMachine_change_state(ErrList err_vect_st[],int *myTrigger_i){
    Ssm current_state_e = init;
    bool err_exist_b = systemStateMachine_check_err_val(err_vect_st);

    //printf("Trrigger: %d\n",*myTrigger_i);
    if((*myTrigger_i) == 0){
        if(err_exist_b == ERROR_OCURED_U){
            current_state_e = error;
        }
        else{
            current_state_e = active;
        }
    }
    else{
        (*myTrigger_i)--;
        err_exist_b = systemStateMachine_check_err_val(err_vect_st);
    }
    
    printf("State is: %s\n", getStateName(current_state_e));
    return current_state_e;
}


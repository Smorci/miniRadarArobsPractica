#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "definesSSM.h"
#include "myDefines.h"

const char* getStateName(enum ssm_states crt_state) 
{
   switch (crt_state) 
   {
      case INIT: return "INIT";
      case ACTIVE: return "ACTIVE";
      case ERROR: return "ERROR";
      /* etc... */
   }
}

bool systemStateMachine_check_err_val(Errors err_vect_st[]){
    bool err_existence_b = NO_ERROR_OCURED_U;
    if (err_vect_st[0].err_val==fail){
        err_existence_b = ERROR_OCURED_U;
    }
    else if(err_vect_st[1].err_val==fail){
        err_existence_b =ERROR_OCURED_U;
    }
    else if(err_vect_st[2].err_val==fail){
        err_existence_b =ERROR_OCURED_U;
    }
    else{
        err_existence_b=NO_ERROR_OCURED_U;
    }
    return err_existence_b;
}

enum ssm_states systemStateMachine_change_state(Errors err_vect_st[],int *myTrigger_i){
    enum ssm_states current_state_e = INIT;
    bool err_exist_b = systemStateMachine_check_err_val(err_vect_st);

    printf("Trrigger: %d\n",*myTrigger_i);
    if((*myTrigger_i) == 0){
        if(err_exist_b == ERROR_OCURED_U){
            current_state_e = ERROR;
        }
        else{
            current_state_e = ACTIVE;
        }
    }
    else{
        (*myTrigger_i)--;
        err_exist_b = systemStateMachine_check_err_val(err_vect_st);
    }
    
    printf("State is: %s\n", getStateName(current_state_e));
    return current_state_e;
}


#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "definesSSM.h"
#include "CI_Defines.h"
#include "CommunicationInterface.h"

bool systemStateMachine_check_err_val(ErrStatus err_vect_e[]){
    bool err_existence_b = NO_ERROR_OCURED_U;
    if (err_vect_e[0]==fail){
        err_existence_b = ERROR_OCURED_U;
    }
    else if(err_vect_e[1]==fail){
        err_existence_b =ERROR_OCURED_U;
        #ifdef DEBUG
            printf("nu comunic\n");
        #endif
    }
    else{
        err_existence_b=NO_ERROR_OCURED_U;
    }
    return err_existence_b;
}

Ssm systemStateMachine_change_state(ErrStatus err_vect_e[],int *myTrigger_i){
    Ssm current_state_e = init;
    bool err_exist_b = systemStateMachine_check_err_val(err_vect_e);
    #ifdef DEBUG
        printf("err_exist_b: %d",err_exist_b);
        printf("Trrigger: %d\n",*myTrigger_i);
    #endif
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
        current_state_e = init;
    }
    
    //printf("State is: %s\n", CI_getStateName(current_state_e));
    return current_state_e;
}


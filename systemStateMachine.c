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

extern bool systemStateMachine_check_err_val(Errors err_vect[]){
    bool err_existence_b = NO_ERROR_OCURED_U;
    if (err_vect[0].err_val==fail){
        err_existence_b = ERROR_OCURED_U;
    }
    else if(err_vect[1].err_val==fail){
        err_existence_b =ERROR_OCURED_U;
    }
    else{
        err_existence_b=NO_ERROR_OCURED_U;
    }
    return err_existence_b;
}

extern enum ssm_states systemStateMachine_change_state(Errors err_vect[],int *myTrigger_i){
    enum ssm_states current_state_e = INIT;
    //enum ssm_states next_state_e = INIT;
    bool err_exist_b = systemStateMachine_check_err_val(err_vect);
    //int iterations_i =0;
    
    //iterations_i=0;
    //do {//fara do while - use counter
        //clock_t difference = clock() - startMoment;
        //mySec_i = difference * 1000 / CLOCKS_PER_SEC;
    //     mySec_i++;
    // }while ( mySec_i < myTrigger_i );
    printf("Trrigger: %d\n",*myTrigger_i);
    if((*myTrigger_i) == 0){
        if(err_exist_b == ERROR_OCURED_U){
            //next_state_e = ERROR;
            current_state_e = ERROR;
        }
        else{
            //next_state_e=ACTIVE;
            current_state_e = ACTIVE;
        }
    }
    else{
        (*myTrigger_i)--;
        err_exist_b = systemStateMachine_check_err_val(err_vect);
    }
    //bool err_exist_b = systemStateMachine_check_err_val(err_vect);
    // if(current_state_e == INIT && err_exist_b == ERROR_OCURED_U){
    //     next_state_e = ERROR;
    // }
    // else{
    //     next_state_e=ACTIVE;
    // } 
    /*if(current_state_e == ACTIVE && err_exist_b == ERROR_OCURED_U){
        next_state_e = ERROR;
    }
    else{
        next_state_e=ACTIVE;
    }
    if(current_state_e == ERROR && err_exist_b == ERROR_OCURED_U){
        next_state_e = ERROR;
    }
    else{
        next_state_e=ACTIVE;
    }*/
    printf("State is: %s\n", getStateName(current_state_e));
    return current_state_e;
}


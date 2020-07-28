#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "myDefines.h"

bool systemStateMachine_check_err_val(unsigned char err_val){
    bool err_existence_b = NO_ERROR_OCURED;
    if (err_val==fail){
        err_existence_b = ERROR_OCURED;
    }
    else{
        err_existence_b =NO_ERROR_OCURED;
    }
    return err_existence_b;
}

unsigned char systemStateMachine_change_state(unsigned char err_val){
    enum ssm_states current_state = INIT;
    enum ssm_states next_state = INIT;
    int iterations_i =0;
    int mySec_i = 0, myTrigger_i = 5000; /* 5s */
    clock_t startMoment = clock();
    iterations_i=0;
    do {
        clock_t difference = clock() - startMoment;
        mySec_i = difference * 1000 / CLOCKS_PER_SEC;
        iterations_i++;
    }while ( mySec_i < myTrigger_i );
    bool err_exist_b = systemStateMachine_check_err_val(err_val);
    if(current_state == INIT && err_exist_b == ERROR_OCURED){
        next_state = ERROR;
    }
    else{
        next_state=ACTIVE;
    } 
    if(current_state == ACTIVE && err_exist_b == ERROR_OCURED){
        next_state = ERROR;
    }
    else{
        next_state=ACTIVE;
    }
    if(current_state == ERROR && err_exist_b == ERROR_OCURED){
        next_state = ERROR;
    }
    else{
        next_state=ACTIVE;
    }
    return next_state;
}

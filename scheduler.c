#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "laneChangeWarning.h"
#include "systemStateMachine.h"
#include <time.h>
//#include "myDefines.h"


int main(){
    int x=0;
    bool led_light_b =0;
    bool audio_signal_b=0;
    int myTrigger_i = 500;; /* 10ms task * 500 = 5s */
    unsigned char iterations_uc =0;
    unsigned char msec_uc = 0, trigger_uc = 10; /* 10ms */
    clock_t before = clock();
    Errors err[2];
    err[0].q_time_i=2; err[0].err_val=passed;
    err[1].q_time_i=1;err[1].err_val=fail; 
    while(x<550){
        iterations_uc=0;
        do {
            clock_t difference = clock() - before;
            msec_uc = difference * 1000 / CLOCKS_PER_SEC;
            iterations_uc++;
        }while ( msec_uc < trigger_uc );  

        enum ssm_states current_smm_state = systemStateMachine_change_state(err,&myTrigger_i);
        bool check_rez_b = 0;
        check_rez_b = laneChangeWarning_set_lcw_state(21,1,10,current_smm_state);
        laneChangeWarning_check_colision(check_rez_b,10,&led_light_b,&audio_signal_b);
        printf("Led: %d and Audio: %d\n",led_light_b,audio_signal_b);
        x++;
    }
    
    return 0;
}
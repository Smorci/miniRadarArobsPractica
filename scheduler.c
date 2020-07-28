#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "laneChangeWarning.h"
#include "systemStateMachine.h"
#include <time.h>

int main(){
    int x=0;
    unsigned char iterations_uc =0;
    unsigned char msec_uc = 0, trigger_uc = 10; /* 10ms */
    clock_t before = clock();
    while(x<10){
        iterations_uc=0;
        do {
            clock_t difference = clock() - before;
            msec_uc = difference * 1000 / CLOCKS_PER_SEC;
            iterations_uc++;
        }while ( msec_uc < trigger_uc );  

        unsigned char current_smm_state = systemStateMachine_change_state(NO_ERROR_OCURED);
        bool check_rez_b = 0;
        check_rez_b = laneChangeWarning_set_lcw_state(21,1,8,ACTIVE);
        laneChangeWarning_check_colision(check_rez_b,10);
        printf("Led: %d and Audio: %d",led_light_b,audio_signal_b);
        x++;
    }
    
    return 0;
}
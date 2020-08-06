#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RCTA_Defines.h"
#include "CommunicationInterface.h"


void RCTA_isActivRCTA(Ssm current_ssm_state)
{
    Warning_Feature *RCTA_isActivWarning_st = malloc(20);
    CI_getRCTA_Warning(RCTA_isActivWarning_st);
    #ifdef DEBUG
        printf("%d %d %d\n", RCTA_isActivWarning_st->audio_signal_b, RCTA_isActivWarning_st->isActiv_b, RCTA_isActivWarning_st->led_light_b);
    #endif
    unsigned char RCTA_speed_uc=CI_getSpeed();
    Gear RCTA_gear_e=CI_getGear();
    if (RCTA_speed_uc <= ASL && RCTA_gear_e == AGS && current_ssm_state == ASS)
    {
        RCTA_isActivWarning_st->isActiv_b = true;
    }
    else
    {
        RCTA_isActivWarning_st->isActiv_b = false;
    }
    CI_setRCTA_Warning(RCTA_isActivWarning_st);
    #ifdef DEBUG
        printf("%d %d %d\n", RCTA_isActivWarning_st->audio_signal_b, RCTA_isActivWarning_st->isActiv_b, RCTA_isActivWarning_st->led_light_b);
    #endif
    //return RTCA_Warn.isActiv_b
}

void RCTA_colisionRCTA()
{
    Ssm RCTA_current_ssm_state =CI_getCurrent_ssm_state();
    RCTA_isActivRCTA(RCTA_current_ssm_state);
    Warning_Feature *RCTA_Warn = malloc(20);
    CI_getRCTA_Warning(RCTA_Warn);
    #ifdef DEBUG
        printf("%d %d %d\n", RCTA_Warn->audio_signal_b, RCTA_Warn->isActiv_b, RCTA_Warn->led_light_b);
    #endif
    float rctaDist_uc = CI_getDistance();

    if (rctaDist_uc <= CDL && RCTA_Warn->isActiv_b == true)
    {
        RCTA_Warn->audio_signal_b = true;
        RCTA_Warn->led_light_b = true;
    }
    else{
        RCTA_Warn->audio_signal_b = false;
        RCTA_Warn->led_light_b = false; 
    }
    CI_setRCTA_Warning(RCTA_Warn);
    //printf("Led RCTA: %d and Audio RCTA: %d\n", RCTA_Warn->led_light_b, RCTA_Warn->audio_signal_b);
}

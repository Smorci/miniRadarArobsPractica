#include "RCTA_Defines.h"
void RCTA_isActivRCTA(struct DataFromFile *data_struct, char current_ssm_state)
{
    Warning_Feature RCTA_Warn;
    getRCTA_Warning(RCTA_Warn);    
    printf("%d %d %d\n",RCTA_Warn.audio_signal_b,RCTA_Warn.isActiv_b,RCTA_Warn.led_light_b);
    if (data_struct->speed_uc <= ASL && data_struct->gear_e == AGS && current_ssm_state == ASS)
    {
        RCTA_Warn.isActiv_b = true;
    }else
    {
        
        RCTA_Warn.isActiv_b=false;
    }
    
    setRCTA_Warning(RCTA_Warn);
    printf("%d %d %d\n",RCTA_Warn.audio_signal_b,RCTA_Warn.isActiv_b,RCTA_Warn.led_light_b);

    //return RTCA_Warn.isActiv_b
}

void RCTA_colisionRCTA(DataFromFile *data_struct)
{
    char current_ssm_state = 1; //aici trebuie sa apelez ceva functie de la Claudia
    CI_Read_data(data_struct);
    RCTA_isActivRCTA(data_struct,current_ssm_state);
    Warning_Feature RCTA_Warn;
    //RCTA_Warn=RCTA_Warning_st;
    getRCTA_Warning(RCTA_Warn);
    printf("%d %d %d\n",RCTA_Warn.audio_signal_b,RCTA_Warn.isActiv_b,RCTA_Warn.led_light_b);

    if (data_struct->distance_uc <= CDL && RCTA_Warn.isActiv_b== true)
    {
        RCTA_Warn.audio_signal_b=true;
        RCTA_Warn.led_light_b=true;
    }
    setRCTA_Warning(RCTA_Warn);
    printf("Led: %d\nAudio: %d", RCTA_Warn.led_light_b, RCTA_Warn.audio_signal_b);
}

public bool isActivRCTA(unsigned char speed,char gear,char current_ssm_state[])
{
    if(speed<=10 && gear=2 && current_ssm_state="ACTIVE")
        return 1;
    return 0;
}

public void colisionRCTA(char distance)
{
    unsigned char speed=0;
    char gear=0;
    char current_ssm_state[]="INIT";
    
    if(distance<=4 && distance>=0 && isActivRCTA(speed,gear,current_ssm_state[]))
    {
        led_light=1;
        audio_signal=1;
    }
}

#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//defines for Com Interf
#define DS 5    //data size
#define ND 5    //number of data
#define LSL 0   //lower speed limit
#define USL 255 //upper speed limit
#define LGL 0   //lower gear limit
#define UGL 3   //upper gear limit
#define LAL -45 //lower angle limit
#define UAL 45  //upper angle limit
#define LDL 0   //lower distance limit
#define UDL 80  //upper distance limit
#define LBL 0   //lower battery_voltage limit
#define UBL 24  //upper battery_voltage limit
#define DVS 0   //default value for speed
#define DVG 0   //default value for gear
#define DVA 0   //default value for angle
#define DVD 50  //default value for distance
#define DVB 12  //default value for batery_voltage
#define DVU 1   //default value for undervoltage
#define DVO 1   //default value for overvoltage

//defines for RCTA
#define CDL 4  //colision distance limit
#define ASL 10 //RCTA activation speed limit
#define AGS 2  //RCTA activation gear state
#define ASS 1  //RCTA activation SSM state

typedef enum Gear
{
    neutral,
    forward,
    reveresed,
    parked
} Gear;

typedef struct DataFromFile
{
    unsigned char speed_uc;
    Gear gear_e;
    char angle_c;
    unsigned char distance_uc;
    unsigned char battery_voltage_uc;

} DataFromFile;

typedef enum Ssm
{
    init = 0,
    active = 1,
    error = 2
} Ssm;

typedef struct Warning_Feature
{
    bool isActiv_b;
    bool led_light_b;
    bool audio_signal_b;
} Warning_Feature;

typedef enum ErrName
{
    err_batvoltage = 0,
    err_lostcom = 1,
    err_delimiter = 2
} ErrName;

typedef enum ErrStatus
{
    notperformed = 0,
    fail = 1,
    passed = 2
} ErrStatus;

typedef struct ErrList
{
    ErrName errName_e;
    ErrStatus errStatus_e;
    char errQualTime_c;
    char errDequalTime_c;
} ErrList;

bool undervoltage_b;
bool overvoltage_b;
bool isFileOpen_b;
Warning_Feature RCTA_Warning_st;
Warning_Feature LCW_Warning_st;
ErrList globalErr_st;
Ssm current_ssm_state;
DataFromFile messageFromFile;

char lineFromFile[ND][DS];

bool CI_getUndervoltage()
{
    return undervoltage_b;
}
void CI_setUnderVoltage(bool undervoltageForSet_b)
{
    undervoltage_b = undervoltageForSet_b;
}
bool CI_getOverVoltage()
{
    return overvoltage_b;
}
void CI_serOverVoltage(bool overvoltageForSet_b)
{
    overvoltage_b = overvoltageForSet_b;
}
bool CI_getIsFileOpen()
{
    return isFileOpen_b;
}
void CI_setIsFileOpen(bool isFileOpenForSet_b)
{
    isFileOpen_b = isFileOpenForSet_b;
}
void CI_getRCTA_Warning(Warning_Feature *RCTA_Warning_ForSet_st)
{
    RCTA_Warning_ForSet_st->audio_signal_b = (&RCTA_Warning_st)->audio_signal_b;
    RCTA_Warning_ForSet_st->isActiv_b = (&RCTA_Warning_st)->isActiv_b;
    RCTA_Warning_ForSet_st->led_light_b = (&RCTA_Warning_st)->led_light_b;
}
void CI_setRCTA_Warning(Warning_Feature *RCTA_Warning_ForSet_st)
{
    (&RCTA_Warning_st)->audio_signal_b = RCTA_Warning_ForSet_st->audio_signal_b;
    (&RCTA_Warning_st)->isActiv_b = RCTA_Warning_ForSet_st->isActiv_b;
    (&RCTA_Warning_st)->led_light_b = RCTA_Warning_ForSet_st->led_light_b;
}
void CI_getLCW_Warning(Warning_Feature *LCW_Warning_ForSet_st)
{
    LCW_Warning_ForSet_st->audio_signal_b = (&LCW_Warning_st)->audio_signal_b;
    LCW_Warning_ForSet_st->isActiv_b = (&LCW_Warning_st)->isActiv_b;
    LCW_Warning_ForSet_st->led_light_b = (&LCW_Warning_st)->led_light_b;
}
void CI_setLCW_Warning(Warning_Feature *LCW_Warning_ForSet_st)
{
    (&LCW_Warning_st)->audio_signal_b = LCW_Warning_ForSet_st->audio_signal_b;
    (&LCW_Warning_st)->isActiv_b = LCW_Warning_ForSet_st->isActiv_b;
    (&LCW_Warning_st)->led_light_b = LCW_Warning_ForSet_st->led_light_b;
}

void CI_Read_data() //void si struct ca argum
{
    int i = 0;
    int buffer;
    bool isFileReadForSet = false;
    FILE *data_file = fopen("data.txt", "r");
    if (data_file == NULL)
        isFileReadForSet = true;
    CI_setIsFileOpen(isFileReadForSet);
    while (fgets(lineFromFile[i], DS, data_file))
    {
        lineFromFile[i][strlen(lineFromFile[i]) - 1] = '\0';
        switch (i)
        {
        case (int)0:
            buffer = atoi(lineFromFile[i]);
            if (buffer >= LSL && buffer <= USL)
                messageFromFile.speed_uc = buffer;
            else
                messageFromFile.speed_uc = DVS;
            printf("Viteza: %d\n", messageFromFile.speed_uc);
            break;
        case (int)1:
            buffer = atoi(lineFromFile[i]);
            if (buffer >= LGL && buffer <= UGL)
                messageFromFile.gear_e = buffer;
            else
                messageFromFile.gear_e = DVG;
            printf("Gear: %d\n", messageFromFile.gear_e);
            break;
        case (int)2:
            buffer = atoi(lineFromFile[i]);
            if (buffer >= LAL && buffer <= UAL)
                messageFromFile.angle_c = buffer;
            else
                messageFromFile.angle_c = DVA;
            printf("Angle: %d\n", messageFromFile.angle_c);
            break;
        case (int)3:
            buffer = atoi(lineFromFile[i]);
            if (buffer >= LDL && buffer <= UDL)
                messageFromFile.distance_uc = buffer;
            else
                messageFromFile.distance_uc = DVD;
            printf("Distance: %d\n", messageFromFile.distance_uc);
            break;
        case (int)4:
            buffer = atoi(lineFromFile[i]);
            if (buffer >= LBL && buffer <= UBL)
                messageFromFile.battery_voltage_uc = buffer;
            else
                messageFromFile.battery_voltage_uc = DVB;
            printf("Battery_voltage: %d\n", messageFromFile.battery_voltage_uc);
            break;
        }
        i++;
    }
    fclose(data_file);
    //return messageFromFile;
}

void CI_Write_data(int option_i, int data_i)
{
    FILE *data_file = fopen("data.txt", "w");
    int i = 0;
    switch (option_i)
    {
    case (int)0:
        itoa(data_i, lineFromFile[option_i], 10);
        break;
    case (int)1:
        itoa(data_i, lineFromFile[option_i], 10);
        break;
    case (int)2:
        itoa(data_i, lineFromFile[option_i], 10);
        ;
        break;
    case (int)3:
        itoa(data_i, lineFromFile[option_i], 10);
        break;
    case (int)4:
        itoa(data_i, lineFromFile[option_i], 10);
        break;
    case (int)5:
        itoa(data_i, lineFromFile[option_i], 10);
        break;
    case (int)6:
        itoa(data_i, lineFromFile[option_i], 10);
        break;
    default:
        printf("Invalid Option");
    }
    for (i = 0; i < ND; i++)
    {
        fprintf(data_file, "%s\n", lineFromFile[i]);
    }
    fclose(data_file);
}

unsigned char CI_getSpeed()
{
    return messageFromFile.speed_uc;
}
void CI_setSpeed(unsigned char speedForSet_uc)
{
    speedForSet_uc = messageFromFile.speed_uc;
}
Gear CI_getGear()
{
    return messageFromFile.gear_e;
}
void CI_setGear(Gear gearForSet_e)
{
    gearForSet_e = messageFromFile.gear_e;
}
unsigned char CI_getAngle()
{
    return messageFromFile.angle_c;
}
void CI_setAngle(unsigned char angleForSet_uc)
{
    angleForSet_uc = messageFromFile.angle_c;
}
unsigned char CI_getDistance()
{
    return messageFromFile.distance_uc;
}
void CI_setDistance(unsigned char distanceForSet_uc)
{
    distanceForSet_uc = messageFromFile.distance_uc;
}
unsigned char CI_getBatteryVoltage()
{
    return messageFromFile.battery_voltage_uc;
}
void CI_setBatteryVoltage(unsigned char battery_voltageForSet_uc)
{
    battery_voltageForSet_uc = messageFromFile.battery_voltage_uc;
}

void CI_getCurrent_ssm_state(Ssm current_ssm_stateForGet_e)
{
    current_ssm_stateForGet_e = current_ssm_state;
}
void CI_setCurrent_ssm_state(Ssm current_ssm_stateForSet_e)
{
    current_ssm_state = current_ssm_stateForSet_e;
}
void CI_getGlobalErr_st(ErrList *globalErrForGet_st)
{
    globalErrForGet_st = &globalErr_st;
}
void CI_setGlobalErr_st(ErrList *globalErrForSet_st)
{
    globalErr_st = *globalErrForSet_st;
}

void RCTA_isActivRCTA(Ssm current_ssm_state)
{
    Warning_Feature *RCTA_isActivWarning_st = malloc(20);
    CI_getRCTA_Warning(RCTA_isActivWarning_st);
    printf("%d %d %d\n", RCTA_isActivWarning_st->audio_signal_b, RCTA_isActivWarning_st->isActiv_b, RCTA_isActivWarning_st->led_light_b);
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
    printf("%d %d %d\n", RCTA_isActivWarning_st->audio_signal_b, RCTA_isActivWarning_st->isActiv_b, RCTA_isActivWarning_st->led_light_b);

    //return RTCA_Warn.isActiv_b
}

void RCTA_colisionRCTA()
{
    Ssm RCTA_current_ssm_state =1;//=CI_getCurrent_ssm_state();
    CI_Read_data();
    RCTA_isActivRCTA(RCTA_current_ssm_state);
    Warning_Feature *RCTA_Warn = malloc(20);
    CI_getRCTA_Warning(RCTA_Warn);
    printf("%d %d %d\n", RCTA_Warn->audio_signal_b, RCTA_Warn->isActiv_b, RCTA_Warn->led_light_b);

    if (messageFromFile.distance_uc <= CDL && RCTA_Warn->isActiv_b == true)
    {
        RCTA_Warn->audio_signal_b = true;
        RCTA_Warn->led_light_b = true;
    }
    CI_setRCTA_Warning(RCTA_Warn);
    printf("Led: %d\nAudio: %d", RCTA_Warn->led_light_b, RCTA_Warn->audio_signal_b);
}


int main()
{
    //DataFromFile *messageFromFile=malloc(1);
    //messageFromFile.speed_uc=1;
    CI_Read_data();
    CI_Write_data(1, 2);
    //CI_Read_data();
    RCTA_colisionRCTA();

    return 0;
}
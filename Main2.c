#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//defines for Com Interf
#define DS 5 //data size
#define ND 5//number of data
#define LSL 0//lower speed limit
#define USL 255//upper speed limit
#define LGL 0//lower gear limit
#define UGL 3//upper gear limit
#define LAL -45//lower angle limit
#define UAL 45//upper angle limit
#define LDL 0//lower distance limit
#define UDL 80//upper distance limit
#define LBL 0//lower battery_voltage limit
#define UBL 24//upper battery_voltage limit
#define DVS 0 //default value for speed
#define DVG 0 //default value for gear
#define DVA 0 //default value for angle
#define DVD 50 //default value for distance
#define DVB 12 //default value for batery_voltage
#define DVU 1 //default value for undervoltage
#define DVO 1 //default value for overvoltage

//defines for RCTA
#define CDL 4 //colision distance limit
#define ASL 10//RCTA activation speed limit
#define AGS 2//RCTA activation gear state
#define ASS 1//RCTA activation SSM state

enum Gear { 
    neutral,
    forward,
    reveresed,
    parked
};

typedef struct DataFromFile
{
    unsigned char speed_uc;
    enum Gear gear_e;
    char angle_c;
    unsigned char distance_uc;
    unsigned char battery_voltage_uc;
    
}DataFromFile;

enum Ssm{
    init=0,
    active=1,
    error=2
};

typedef struct Warning_Feature{
    bool isActiv_b;
    bool led_light_b;
    bool audio_signal_b;
}Warning_Feature;

enum ErrName{
	err_batvoltage=0,
	err_lostcom=1,
	err_delimiter=2
};

enum ErrStatus{
    notperformed=0,
    fail=1,
    passed=2
};

typedef struct ErrList{
	enum ErrName errName_e;
	enum ErrStatus errStatus_e;
	char errQualTime_c;
	char errDequalTime_c;
}ErrList;



bool undervoltage_b;
bool overvoltage_b;
struct Warning_Feature RCTA_Warning_st; 
struct Warning_Feature LCW_Warning_st;
struct ErrList globalErr_st;
enum Ssm current_ssm_state;
//struct DateFromFile *dataFromFile_struct;

char line[ND][DS];

bool getUndervoltage(){
    return undervoltage_b;
}
void setUnderVoltage(bool undervlt){
    undervoltage_b=undervlt;
}
bool getOverVoltage(){
    return overvoltage_b;
}
void serOverVoltage(bool overvlt){
    overvoltage_b=overvlt;
}
void getRCTA_Warning(Warning_Feature RCTA_Warn){
    RCTA_Warn=RCTA_Warning_st;
}
void setRCTA_Warning(Warning_Feature RCTA_Warn)
{
    RCTA_Warning_st=RCTA_Warn;
}
void getLCW_Warning(Warning_Feature LCW_Warn){
    LCW_Warn=LCW_Warning_st;
}
void setLCW_Warning(Warning_Feature LCW_Warn)
{
    LCW_Warning_st=LCW_Warn;
}

void CI_Read_data(struct DataFromFile *data_struct)//void si struct ca argum
{
    int i = 0;
    int buffer;
    FILE *data_file = fopen("data.txt", "r");
    if (data_file == NULL)
        printf("Fisier nedeschis");
    while (fgets(line[i], DS, data_file))
    {
        line[i][strlen(line[i]) - 1] = '\0';
        switch (i)
        {
        case (int)0:
            buffer = atoi(line[i]);
            if (buffer >= LSL && buffer <= USL)
                data_struct->speed_uc = buffer;
            else
                data_struct->speed_uc = DVS;
            printf("Viteza: %d\n", data_struct->speed_uc);
            break;
        case (int)1:
            buffer = atoi(line[i]);
            if (buffer >= LGL && buffer <= UGL)
                data_struct->gear_e = buffer;
            else
                data_struct->gear_e = DVG;
            printf("Gear: %d\n", data_struct->gear_e);
            break;
        case (int)2:
            buffer = atoi(line[i]);
            if (buffer >= LAL && buffer <= UAL)
                data_struct->angle_c = buffer;
            else
                data_struct->angle_c = DVA;
            printf("Angle: %d\n", data_struct->angle_c);
            break;
        case (int)3:
            buffer = atoi(line[i]);
            if (buffer >= LDL && buffer <= UDL)
                data_struct->distance_uc = buffer;
            else
                data_struct->distance_uc = DVD;
            printf("Distance: %d\n", data_struct->distance_uc);
            break;
        case (int)4:
            buffer = atoi(line[i]);
            if (buffer >= LBL && buffer <= UBL)
                data_struct->battery_voltage_uc = buffer;
            else
                data_struct->battery_voltage_uc = DVB;
            printf("Battery_voltage: %d\n", data_struct->battery_voltage_uc);
            break;
            default:printf("invalid");
        }
        i++;
    }

    fclose(data_file);
    //return data_struct;
}

void CI_Write_data(int option, int data)
{
    FILE *data_file = fopen("data.txt", "w");
    int i = 0;
    switch (option)
    {
    case (int)0:
        itoa(data, line[option], 10);
        break;
    case (int)1:
        itoa(data, line[option], 10);
        break;
    case (int)2:
        itoa(data, line[option], 10);
        ;
        break;
    case (int)3:
        itoa(data, line[option], 10);
        break;
    case (int)4:
        itoa(data, line[option], 10);
        break;
    case (int)5:
        itoa(data, line[option], 10);
        break;
    case (int)6:
        itoa(data, line[option], 10);
        break;
    default:
        printf("Invalid Option");
    }
    for (i = 0; i < ND; i++)
    {
        fprintf(data_file, "%s\n", line[i]);
    }
    fclose(data_file);
}

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


unsigned char getSpeed( DataFromFile *data_struct){
    return data_struct->speed_uc;
}
void setSpeed(unsigned char speed, DataFromFile *data_struct){
    speed=data_struct->speed_uc;
}
unsigned char getGear( DataFromFile *data_struct){
    return data_struct->gear_e;
}
void setGear(unsigned char gear, DataFromFile *data_struct){
    gear=data_struct->gear_e;
}
void getAngle(unsigned char gear, DataFromFile *data_struct){
    return data_struct->angle_c;
}
void setAngle(unsigned char angle, DataFromFile *data_struct){
    angle=data_struct->angle_c;
}
unsigned char getDistance( DataFromFile *data_struct){
    return data_struct->distance_uc;
}
void setDistance(unsigned char distance, DataFromFile *data_struct){
    distance=data_struct->distance_uc;
}
unsigned char getBatteryVoltage( DataFromFile *data_struct){
    return data_struct->battery_voltage_uc;
}
void setBatteryVoltage(unsigned char battery_voltage, DataFromFile *data_struct){
    battery_voltage=data_struct->battery_voltage_uc;
}

void getCurrent_ssm_state(enum Ssm current_ssm){
    current_ssm=current_ssm_state;
}
void setCurrent_ssm_state(enum Ssm current_ssm){
    current_ssm_state=current_ssm;
}
void getGlobalErr_st( ErrList GlobalErr){
    GlobalErr=globalErr_st;
}
void setGlobalErr_st( ErrList GlobalErr){
        globalErr_st=GlobalErr;
}
int main()
{
     DataFromFile *data_struct=malloc(1);
    CI_Read_data(data_struct);
    // for(int i=0;i<ND;i++)
    // {
    //     switch (i)
    //     {
    //     case (int)0:
    //         printf("Viteza: %d\n", data_struct->speed_uc);
    //         break;
    //     case (int)1:   
    //         printf("Gear: %d\n", data_struct->gear_e);
    //         break;
    //     case (int)2:
    //         printf("Angle: %d\n", data_struct->angle_c);
    //         break;
    //     case (int)3:
    //         printf("Distance: %d\n", data_struct->distance_uc);
    //         break;
    //     case (int)4:
    //         printf("Battery_voltage: %d\n", data_struct->battery_voltage_uc);
    //         break;
    //     }
    // }
    CI_Write_data(1, 2);
    CI_Read_data(data_struct);
    RCTA_colisionRCTA(data_struct);
    return 0;
}
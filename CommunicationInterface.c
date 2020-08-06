#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "CI_Defines.h"

bool undervoltage_b;
bool overvoltage_b;
bool isFileOpen_b;
Warning_Feature RCTA_Warning_st;
Warning_Feature LCW_Warning_st;
Ssm current_ssm_state;
DataFromFile messageFromFile;
char lineFromFile[ND][DS];
//bool valuesFromTestFile[NUMBER_OF_TEST];
char lineFromTestFile[NUMBER_OF_TEST][DS];

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
void CI_setOverVoltage(bool overvoltageForSet_b)
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
bool CI_isNumber(char line[DS])
{
    bool ok=1;
    for (int i = 0; i < strlen(line); i++)
    {
        if (!(isdigit(line[i])|| line[i]=='.'))
        {
            ok=0;
        }
    }
    return ok;
}
const char* CI_getGearName(Gear mGear_e) 
{
   switch (mGear_e) 
   {
      case neutral: return "neutral";
      case forward: return "forward";
      case reversed: return "reversed";
      case parked: return "parked";
      /* etc... */
   }
}

void readTestFile(bool valuesFromTestFile[NUMBER_OF_TEST]){
    FILE *test_file = fopen("testfile.txt", "r");
    int i=0;
    if(test_file==NULL)
        printf("fisier invalid");
    else
    {
        while (fgets(lineFromTestFile[i], DS, test_file))
            {
                lineFromTestFile[i][strlen(lineFromTestFile[i]) - 1] = '\0';
                valuesFromTestFile[i]=(bool)atoi(lineFromTestFile[i]);
                printf("%d ",valuesFromTestFile[i]);
                i++;
            }
    
    }
}
void CI_Read_data()
{
    bool isFileReadForSet;
    int i = 0;
    float buffer=0;
    isFileReadForSet = true;
    FILE *data_file = fopen("data.txt", "r");
    messageFromFile.speed_uc=DVS;
    messageFromFile.gear_e=DVG;
    messageFromFile.angle_c=DVA;
    messageFromFile.distance_f=DVD;
    messageFromFile.battery_voltage_uc=DVB;
    if (data_file == NULL)
    {
        isFileReadForSet = false;
        printf("File open: %d\n", isFileReadForSet);
        
    }
    else
    {
        while (fgets(lineFromFile[i], DS, data_file))
        {
            lineFromFile[i][strlen(lineFromFile[i]) - 1] = '\0';
            switch (i)
            {
            case (int)0:
                if (CI_isNumber(lineFromFile[i]))
                    buffer = atoi(lineFromFile[i]);
                else
                    buffer = DVS;
                if (buffer >= LSL && buffer <= USL)
                    messageFromFile.speed_uc = buffer;
                else
                    messageFromFile.speed_uc = DVS;
                printf("Viteza: %d\n", messageFromFile.speed_uc);
                break;
            case (int)1:
                if (CI_isNumber(lineFromFile[i]))
                    buffer = atoi(lineFromFile[i]);
                else
                    buffer = DVG;
                if (buffer >= LGL && buffer <= UGL)
                    messageFromFile.gear_e = buffer;
                else
                    messageFromFile.gear_e = DVG;
                printf("Gear: %s\n", CI_getGearName(messageFromFile.gear_e));
                break;
            case (int)2:
                if (CI_isNumber(lineFromFile[i]))
                    buffer = atoi(lineFromFile[i]);
                else
                    buffer = DVA;
                if (buffer >= LAL && buffer <= UAL)
                    messageFromFile.angle_c = buffer;
                else
                    messageFromFile.angle_c = DVA;
                printf("Angle: %d\n", messageFromFile.angle_c);
                break;
            case (int)3:
                if (CI_isNumber(lineFromFile[i]))
                    buffer =(float) atof(lineFromFile[i]);
                else
                    buffer = DVD;
                if (buffer >= LDL && buffer <= UDL)
                    messageFromFile.distance_f = buffer;
                else
                    messageFromFile.distance_f = DVD;
                printf("Distance: %4.2f\n", (float)messageFromFile.distance_f);
                break;
            case (int)4:
                if (CI_isNumber(lineFromFile[i]))
                    buffer = atoi(lineFromFile[i]);
                else
                    buffer = DVB;
                if (buffer >= LBL && buffer <= UBL)
                    messageFromFile.battery_voltage_uc = buffer;
                else
                    messageFromFile.battery_voltage_uc = DVB;
                printf("Battery_voltage: %d\n", messageFromFile.battery_voltage_uc);
                break;
            }
            //printf("buffer: %d  line: %s \n", buffer, lineFromFile[i]);
            i++;
        }
    }
    CI_setIsFileOpen(isFileReadForSet);
    fclose(data_file);
}

void CI_Write_data(int option_i, float data_i)
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
        break;
    case (int)3:
        gcvt(data_i,6, lineFromFile[option_i]);
        break;
    case (int)4:
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

const char* CI_getErrNameChar(ErrName myErrName_e) 
{
   switch (myErrName_e) 
   {
      case err_batvoltage: return "battery voltage error";
      case err_lostcom: return "lost communication error";
      case err_delimiter: return "delimiter";
   }
}

const char* CI_getErrStatusChar(ErrStatus myErrStatus_e) 
{
   switch (myErrStatus_e) 
   {
      case notperformed: return "not performed";
      case fail: return "fail";
      case passed: return "passed";
   }
}

const char* CI_getStateName(Ssm crt_state) 
{
   switch (crt_state) 
   {
      case init: return "INIT";
      case active: return "ACTIVE";
      case error: return "ERROR";
      /* etc... */
   }
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
float CI_getDistance()
{
    return messageFromFile.distance_f;
}
void CI_setDistance(float distanceForSet_f)
{
    distanceForSet_f = messageFromFile.distance_f;
}
unsigned char CI_getBatteryVoltage()
{
    return messageFromFile.battery_voltage_uc;
}
void CI_setBatteryVoltage(unsigned char battery_voltageForSet_uc)
{
    battery_voltageForSet_uc = messageFromFile.battery_voltage_uc;
}

Ssm CI_getCurrent_ssm_state()
{
    return current_ssm_state;
}
void CI_setCurrent_ssm_state(Ssm current_ssm_stateForSet_e)
{
    current_ssm_state = current_ssm_stateForSet_e;
}

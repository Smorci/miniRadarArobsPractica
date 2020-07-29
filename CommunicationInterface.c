#include "CI_Defines.h"

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
    // if (data_file == NULL)
    //     error_open_file = true;
    // else
    // {
    //     error_open_file = false;
    // }

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

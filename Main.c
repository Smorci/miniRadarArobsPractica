#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LSIZ 5
#define RSIZ 8
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

struct Data
{
    unsigned char speed_uc;
    unsigned char gear_uc;
    char angle_c;
    unsigned char distance_uc;
    unsigned char battery_voltage_uc;
    bool undervoltage_b;
    bool overvoltage_b;
};

bool led_light = false;
bool audio_signal = false;
char line[RSIZ][LSIZ];

struct Data Read_data()
{
    //char line[RSIZ][LSIZ];
    int i = 0;
    struct Data data_struct;
    FILE *data_file = fopen("data.txt", "r");
    while (fgets(line[i], LSIZ, data_file))
    {
        line[i][strlen(line[i]) - 1] = '\0';
        switch (i)
        {
        case (int)0:
            data_struct.speed_uc = atoi(line[i]);
            printf("Viteza: %s\n", line[i]);
            break;
        case (int)1:
            data_struct.gear_uc = atoi(line[i]);
            printf("Gear: %s\n", line[i]);
            break;
        case (int)2:
            data_struct.angle_c = atoi(line[i]);
            printf("Angle: %s\n", line[i]);
            break;
        case (int)3:
            data_struct.distance_uc = atoi(line[i]);
            printf("Distance: %s\n", line[i]);
            break;
        case (int)4:
            data_struct.battery_voltage_uc = atoi(line[i]);
            printf("Battery_voltage: %s\n", line[i]);
            break;
        case (int)5:
            data_struct.undervoltage_b = atoi(line[i]);
            printf("Undervoltage: %s\n", line[i]);
            break;
        case (int)6:
            data_struct.overvoltage_b = atoi(line[i]);
            printf("Overvoltage: %s\n", line[i]);
            break;
        default:
            printf("Invalid Option\n");
        }
        ++i;
    }

    // for (i = 0; i < RSIZ; ++i)
    // {
    //     switch (i)
    //     {
    //     case (int)0:
    //         data_struct.speed_uc = atoi(line[i]);
    //         printf("Viteza: %s\n", line[i]);
    //         break;
    //     case (int)1:
    //         data_struct.gear_uc = atoi(line[i]);
    //         printf("Gear: %s\n", line[i]);
    //         break;
    //     case (int)2:
    //         data_struct.angle_c = atoi(line[i]);
    //         printf("Angle: %s\n", line[i]);
    //         break;
    //     case (int)3:
    //         data_struct.distance_uc = atoi(line[i]);
    //         printf("Distance: %s\n", line[i]);
    //         break;
    //     case (int)4:
    //         data_struct.battery_voltage_uc = atoi(line[i]);
    //         printf("Battery_voltage: %s\n", line[i]);
    //         break;
    //     case (int)5:
    //         data_struct.undervoltage_b = atoi(line[i]);
    //         printf("Undervoltage: %s\n", line[i]);
    //         break;
    //     case (int)6:
    //         data_struct.overvoltage_b = atoi(line[i]);
    //         printf("Overvoltage: %s\n", line[i]);
    //         break;
    //     default:
    //         printf("Invalid Option");
    //     }
    // }
    fclose(data_file);
    return data_struct;
}

void Write_data(int option, int data)
{
    FILE *data_file = fopen("data.txt", "w");
    //char line[RSIZ][LSIZ];
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
    for(i = 0; i < RSIZ;++i)
    {
        fprintf(data_file,"%s\n",line[i]);
    }
    fclose(data_file);
}

bool isActivRCTA(unsigned char speed, char gear, char current_ssm_state[])
{
    if (speed <= 10 && gear == 2 && current_ssm_state == "ACTIVE")
        return true;
    return false;
}

void colisionRCTA()
{
    char current_ssm_state[] = "ACTIVE";
    struct Data data;
    data = Read_data();
    if (data.distance_uc <= 4 && data.distance_uc >= 0 && isActivRCTA(data.speed_uc, data.gear_uc, current_ssm_state))
    {
        led_light = true;
        audio_signal = true;
    }
}

int main()
{
    // Write_data('s',45);
    // Write_data('g',1);
    // Write_data('a',40);
    // Write_data('d',55);
    // Write_data('b',10);
    // printf("writing successfully\n");
    struct Data data;
    data = Read_data();
    Write_data(2,40);
    data=Read_data();

    return 0;
}
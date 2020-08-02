#ifndef CI_DEFINES
#define CI_DEFINES

#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

//#pragma once
typedef enum Gear
{
    neutral,
    forward,
    reversed,
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

// bool undervoltage_b;
// bool overvoltage_b;
// bool isFileOpen_b;
// Warning_Feature RCTA_Warning_st;
// Warning_Feature LCW_Warning_st;
// Ssm current_ssm_state;
// DataFromFile messageFromFile;
// char lineFromFile[ND][DS];
#endif
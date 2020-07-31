
#include "error_constants.h"
#include "error_functions.h"
#include <time.h>
#include "CommunicationInterface.h"
#include "CI_Defines.h"
#include <stdlib.h>

static unsigned int timer_u8 = RUNOUT_TIMER_UI;
static unsigned int underOverVoltageTimer_u8 = QUAL_TIME_UI;
static unsigned int lostCommTimer_u8 = LOSTCOMM_TIMER_UI;
unsigned char Battery_Voltage_UC;

ErrList err_st[2] = {
    {notperformed,
    err_batvoltage,
    QUAL_TIME_UI,
    DEQUAL_TIME_UI},
    {notperformed,
    err_lostcom,
    QUAL_TIME_UI,
    DEQUAL_TIME_UI}};


void errorHandler_SetError(ErrName name_e, ErrStatus stat_e)
{
    err_st[name_e].errStatus_e = stat_e;
    err_st[name_e].errName_e = name_e;
    err_st[name_e].errQualTime_c = QUAL_TIME_UI;
    err_st[name_e].errDequalTime_c = DEQUAL_TIME_UI;
   // CI_setGlobalErr_st(err_st);
}

void errorHandler_GetError(ErrName name_e, ErrStatus *status_e){
    *status_e = err_st[name_e].errStatus_e;
}

void errorHandler_BatteryVoltage_Check(){

    if(timer_u8 == RUNOUT_TIMER_UI)
    {
        Battery_Voltage_UC = CI_getBatteryVoltage();
        printf("Battery voltage from EH: %d\n",Battery_Voltage_UC);
        timer_u8 = BATTERY_CYCLE_TIMER_UI;
        printf("battery voltage read\n");
    }
    else
    {
        timer_u8--;
        printf("cnt for read\n");
    }
    
    // underV , overV detection
    printf("BV: %d\n",Battery_Voltage_UC);
    if(Battery_Voltage_UC < LOWER_VOLTAGE_LIMIT_C) {
        if(underOverVoltageTimer_u8 == RUNOUT_TIMER_UI)
        {
            underOverVoltageTimer_u8 = QUAL_TIME_UI;
            CI_setUnderVoltage(UNDERVOLTAGE_TRUE_B);
            CI_setOverVoltage(OVERVOLTAGE_FALSE_B);

            errorHandler_SetError(err_batvoltage,fail);// error qualified
            printf("undervoltage case\n");
        }
        else
        {
            underOverVoltageTimer_u8--;
            printf("still counting for undervoltage\n");
        }
    }
    else if(Battery_Voltage_UC > UPPER_VOLTAGE_LIMIT_C)
    {
        if(underOverVoltageTimer_u8 == RUNOUT_TIMER_UI)
        {
            underOverVoltageTimer_u8 = QUAL_TIME_UI;
            CI_setOverVoltage(OVERVOLTAGE_TRUE_B);
            CI_setUnderVoltage(UNDERVOLTAGE_FALSE_B);

            errorHandler_SetError(err_batvoltage,fail);// error qualified
            printf("overvoltage case\n");
        }
        else
        {
            underOverVoltageTimer_u8--;
            printf("still counting for overvoltage\n");
        }
    }
    else
    {
        if(underOverVoltageTimer_u8 == RUNOUT_TIMER_UI)
        {
            underOverVoltageTimer_u8 = DEQUAL_TIME_UI;
            CI_setOverVoltage(OVERVOLTAGE_FALSE_B);
            CI_setUnderVoltage(UNDERVOLTAGE_FALSE_B);            

            errorHandler_SetError(err_batvoltage,passed);

            printf("suntem unde trebe\n");
        }
        else
        {
            underOverVoltageTimer_u8--;
            printf("still cnt\n");
        }
        
    }
    
}

void errorHandler_Communication_Check(){ //struct from read_data
    
    bool isFileOpen = CI_getIsFileOpen();
    printf("isFileOpen: %d\n", isFileOpen);
    //printf("Suntem in lostCom\n");
    if(isFileOpen == FILE_NOT_OPEN_B)
    {
        if(lostCommTimer_u8 == RUNOUT_TIMER_UI)
        {
            lostCommTimer_u8 = LOSTCOMM_TIMER_UI;
            errorHandler_SetError(err_lostcom,fail);
            //printf("file did not open\n");
        } 
        else if(isFileOpen == FILE_OPEN_B)
        {
            lostCommTimer_u8 = LOSTCOMM_TIMER_UI;
            errorHandler_SetError(err_lostcom,passed);
           // printf("is in else if\n");
        }
        else 
        {
            lostCommTimer_u8--;
            //printf("timer lostComm: %d\n",lostCommTimer_u8);
            //printf("is in else\n");
        }
    }
    else{
        errorHandler_SetError(err_lostcom,passed);
        printf("file was opened\n");
    }

    

}




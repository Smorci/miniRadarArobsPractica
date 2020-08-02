
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
        #ifdef DEBUG
            printf("Battery voltage from EH: %d\n",Battery_Voltage_UC);
        #endif
        timer_u8 = BATTERY_CYCLE_TIMER_UI;
        #ifdef DEBUG
            printf("battery voltage read\n");
        #endif
    }
    else
    {
        timer_u8--;
        #ifdef DEBUG
            printf("cnt for read\n");
        #endif
    }
    
    // underV , overV detection
    #ifdef DEBUG
        printf("BV: %d\n",Battery_Voltage_UC);
    #endif
    if(Battery_Voltage_UC < LOWER_VOLTAGE_LIMIT_C) {
        if(underOverVoltageTimer_u8 == RUNOUT_TIMER_UI)
        {
            underOverVoltageTimer_u8 = QUAL_TIME_UI;
            CI_setUnderVoltage(UNDERVOLTAGE_TRUE_B);
            CI_setOverVoltage(OVERVOLTAGE_FALSE_B);

            errorHandler_SetError(err_batvoltage,fail);// error qualified
            #ifdef DEBUG
                printf("undervoltage case\n");
            #endif
        }
        else
        {
            underOverVoltageTimer_u8--;
            #ifdef DEBUG
                printf("still counting for undervoltage\n");
            #endif
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
            #ifdef DEBUG
                printf("overvoltage case\n");
            #endif
        }
        else
        {
            underOverVoltageTimer_u8--;
            #ifdef DEBUG
                printf("still counting for overvoltage\n");
            #endif
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
            #ifdef DEBUG
                printf("suntem unde trebe\n");
            #endif
        }
        else
        {
            underOverVoltageTimer_u8--;
            #ifdef DEBUG
                printf("still cnt\n");
            #endif
        }
        
    }
    
}

void errorHandler_Communication_Check(){ //struct from read_data
    
    bool isFileOpen = CI_getIsFileOpen();
    #ifdef DEBUG
        printf("isFileOpen: %d\n", isFileOpen);
        printf("Suntem in lostCom\n");
    #endif
    if(isFileOpen == FILE_NOT_OPEN_B)
    {
        if(lostCommTimer_u8 == RUNOUT_TIMER_UI)
        {
            lostCommTimer_u8 = LOSTCOMM_TIMER_UI;
            errorHandler_SetError(err_lostcom,fail);
            #ifdef DEBUG
                printf("file did not open\n");
            #endif
        } 
        else if(isFileOpen == FILE_OPEN_B)
        {
            lostCommTimer_u8 = LOSTCOMM_TIMER_UI;
            errorHandler_SetError(err_lostcom,passed);
            #ifdef DEBUG
                printf("is in else if\n");
            #endif
        }
        else 
        {
            lostCommTimer_u8--;
            #ifdef DEBUG
                printf("timer lostComm: %d\n",lostCommTimer_u8);
                printf("is in else\n");
            #endif
        }
    }
    else{
        errorHandler_SetError(err_lostcom,passed);
        #ifdef DEBUG
            printf("file was opened\n");
        #endif
    }

    

}




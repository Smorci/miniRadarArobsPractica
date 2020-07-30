
#include "error_constants.h"
#include "error_functions.h"
#include <time.h>
#include "CommunicationInterface.h"
#include "CI_Defines.h"
#include <stdlib.h>

static unsigned int timer_u8 = RUNOUT_TIMER_UI;
static unsigned int underOverVoltageTimer_u8 = QUAL_TIME_UI;
static unsigned int lostCommTimer_u8 = LOSTCOMM_TIMER_UI;


void errorHandler_SetError(ErrName name_e, ErrStatus status_e)
{
    ErrList err_st[3];// =(ErrList *)malloc(3 * sizeof(ErrList));
    CI_getGlobalErr_st(err_st);
    err_st[name_e].errStatus_e = status_e;
    err_st[name_e].errName_e = name_e;
    err_st[name_e].errQualTime_c = QUAL_TIME_UI;
    err_st[name_e].errDequalTime_c = DEQUAL_TIME_UI;
    CI_setGlobalErr_st(err_st);
}

void errorHandler_BatteryVoltage_Check(){

    unsigned char Battery_Voltage_UC;

    if(timer_u8 == RUNOUT_TIMER_UI)
    {
        Battery_Voltage_UC = CI_getBatteryVoltage();
        timer_u8 = BATTERY_CYCLE_TIMER_UI;
    }
    else
    {
        timer_u8--;
    }
    
    // underV , overV detection

    if(Battery_Voltage_UC < LOWER_VOLTAGE_LIMIT_C) {
        if(underOverVoltageTimer_u8 == RUNOUT_TIMER_UI)
        {
            underOverVoltageTimer_u8 = QUAL_TIME_UI;
            CI_setUnderVoltage(UNDERVOLTAGE_TRUE_B);
            CI_setOverVoltage(OVERVOLTAGE_FALSE_B);

            errorHandler_SetError(err_batvoltage,fail);// error qualified
        }
        else
        {
            underOverVoltageTimer_u8--;
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
        }
        else
        {
            underOverVoltageTimer_u8--;
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
        }
        else
        {
            underOverVoltageTimer_u8--;
        }
        
    }
    
}

void errorHandler_Communication_Check(){ //struct from read_data
    
    bool isFileOpen = CI_getIsFileOpen();

    if(isFileOpen == FILE_NOT_OPEN_B)
    {
        if(lostCommTimer_u8 == RUNOUT_TIMER_UI)
        {
            lostCommTimer_u8 = LOSTCOMM_TIMER_UI;
            errorHandler_SetError(err_lostcom,fail);
        } 
        else if(isFileOpen == FILE_OPEN_B)
        {
            lostCommTimer_u8 = LOSTCOMM_TIMER_UI;
            errorHandler_SetError(err_lostcom,passed);
        }
        else 
        {
            lostCommTimer_u8--;
        }
    }

    

}




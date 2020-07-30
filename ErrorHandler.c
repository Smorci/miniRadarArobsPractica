
#include "error_constants.h"
#include "error_functions.h"
#include <time.h>
// #include "CommunicationInterface.h"

static unsigned int timer_u8 = RUNOUT_TIMER_UI;
static unsigned int underOverVoltageTimer_u8 = QUAL_TIME_UI;
static unsigned int lostCommTimer_u8 = LOSTCOMM_TIMER_UI;


void errorHandler_SetError(enum error_Name name, enum error_Status status)
{
    globalErrors_ST[name]->errorStatus = status;
}

void errorHandler_BatteryVoltage_Check(struct DataFromFile *data){

    unsigned char Battery_Voltage_UC;

    if(timer_u8 == RUNOUT_TIMER_UI)
    {
        Battery_Voltage_UC = getBatteryVoltage(data);
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
            CI_serOverVoltage(OVERVOLTAGE_FALSE_B);

            errorHandler_SetError(ERR_BATTERYVOLTAGE,FAILED);// error qualified
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
            CI_serOverVoltage(OVERVOLTAGE_TRUE_B);
            CI_setUnderVoltage(UNDERVOLTAGE_FALSE_B);

            errorHandler_SetError(ERR_BATTERYVOLTAGE,FAILED);// error qualified
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
            CI_serOverVoltage(OVERVOLTAGE_FALSE_B);
            CI_setUnderVoltage(UNDERVOLTAGE_FALSE_B);            

            errorHandler_SetError(ERR_BATTERYVOLTAGE,PASSED);
        }
        else
        {
            underOverVoltageTimer_u8--;
        }
        
    }
    
}

void errorHandler_Communication_Check(struct DataFromFile *data){ //struct from read_data
    
    bool isFileOpen = CI_getIsFileOpen();

    if(isFileOpen == FILE_NOT_OPEN_B)
    {
        if(lostCommTimer_u8 == RUNOUT_TIMER_UI)
        {
            lostCommTimer_u8 = LOSTCOMM_TIMER_UI;
            errorHandler_SetError(ERR_LOSTCOMM,FAILED);
        } 
        else if(isFileOpen == FILE_OPEN_B)
        {
            lostCommTimer_u8 = LOSTCOMM_TIMER_UI;
        }
        else 
        {
            lostCommTimer_u8--;
        }
    }

    

}




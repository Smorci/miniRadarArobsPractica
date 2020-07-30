#include "CI_Defines.h"

bool CI_getUndervoltage();
void CI_setUnderVoltage(bool undervoltageForSet_b);
bool CI_getOverVoltage();
void CI_serOverVoltage(bool overvoltageForSet_b);
bool CI_getIsFileOpen();
void CI_setIsFileOpen(bool isFileOpenForSet_b);
void CI_getRCTA_Warning(Warning_Feature *RCTA_Warning_ForSet_st);
void CI_setRCTA_Warning(Warning_Feature *RCTA_Warning_ForSet_st);
void CI_getLCW_Warning(Warning_Feature *LCW_Warning_ForSet_st);
void CI_setLCW_Warning(Warning_Feature *LCW_Warning_ForSet_st);
void CI_Read_data();
void CI_Write_data(int option_i, int data_i);
unsigned char CI_getSpeed();
void CI_setSpeed(unsigned char speedForSet_uc);
Gear CI_getGear();
void CI_setGear(Gear gearForSet_e);
unsigned char CI_getAngle();
void CI_setAngle(unsigned char angleForSet_uc);
unsigned char CI_getDistance();
void CI_setDistance(unsigned char distanceForSet_uc);
unsigned char CI_getBatteryVoltage();
void CI_setBatteryVoltage(unsigned char battery_voltageForSet_uc);
Ssm CI_getCurrent_ssm_state();
void CI_setCurrent_ssm_state(Ssm current_ssm_stateForSet_e);
void CI_getGlobalErr_st(ErrList *globalErrForGet_st);
void CI_setGlobalErr_st(ErrList *globalErrForSet_st);

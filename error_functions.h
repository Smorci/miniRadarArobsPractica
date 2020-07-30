#include "error_constants.h"

void errorHandler_BatteryVoltage_Check(struct DataFromFile *data);

void errorHandler_Communication_Check(struct DataFromFile *data); //struct from read_data

void errorHandler_SetError(enum error_Name name, enum error_Status status);

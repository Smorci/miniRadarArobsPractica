#include "definesSSM.h"
extern bool systemStateMachine_check_err_val(Errors err_vect[]);

extern enum ssm_states systemStateMachine_change_state(Errors err_vect[],int *myTrigger_i);
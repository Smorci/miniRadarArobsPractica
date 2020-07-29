#include "definesSSM.h"
bool systemStateMachine_check_err_val(Errors err_vect_st[]);

extern enum ssm_states systemStateMachine_change_state(Errors err_vect_st[],int *myTrigger_i);
#include "definesLCW.h"
#include "CI_Defines.h"

bool laneChangeWarning_check_param(unsigned char speed_uc, Gear gear_e, char angle_c, Ssm current_ssm_state_e);

bool laneChangeWarning_set_lcw_state(unsigned char speed_uc, Gear gear_e, char angle_c, Ssm current_ssm_state_e);

void laneChangeWarning_check_colision(bool current_lcw_state_b, float distance_f);
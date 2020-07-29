#include "definesLCW.h"

extern bool laneChangeWarning_check_param(unsigned char speed_uc, gear_poz gear_e, char angle_c, ssm_states current_ssm_state_e);

bool laneChangeWarning_set_lcw_state(unsigned char speed_uc, gear_poz gear_e, char angle_c, ssm_states current_ssm_state_e);

void laneChangeWarning_check_colision(bool current_lcw_state_b, char distance_c, bool *led_light_b, bool *audio_signal_b);
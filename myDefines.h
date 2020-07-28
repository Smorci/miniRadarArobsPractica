#define ACTIVE_WARNING_U 1
#define NOT_ACTIVE_WARNING_U 0
#define MIN_SPPED_U 20
#define MIN_ANGLE_C 6
#define LCW_ACTIVE 1
#define LCW_PASSIVE 0
#define CONDITION_PASSED 1
#define CONDITION_NOT_PASSED 0
#define RANGE 20
#define ERROR_OCURED 1
#define NO_ERROR_OCURED 0

enum gear_poz{neutral, forward, reveresed, parked};
enum ssm_states{INIT,ACTIVE,ERROR};
enum err_values{notset,fail,passed};

bool led_light_b =0, audio_signal_b=0;

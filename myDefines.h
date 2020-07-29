#define ACTIVE_WARNING_U 1
#define NOT_ACTIVE_WARNING_U 0
#define MIN_SPPED_U 20
#define MIN_ANGLE_C 6
#define LCW_ACTIVE_U 1
#define LCW_PASSIVE_U 0
#define CONDITION_PASSED_U 1
#define CONDITION_NOT_PASSED_U 0
#define RANGE_LCW_U 20
#define ERROR_OCURED_U 1
#define NO_ERROR_OCURED_U 0

enum gear_poz{
    neutral,
    forward,
    reveresed,
    parked
};
enum ssm_states{
    INIT,
    ACTIVE,
    ERROR
};
enum err_values{
    notsetyet,
    fail,
    passed
};

typedef struct Errors{
    int q_time_i;
    enum err_values err_val;
}Errors;

bool led_light_b =0;
bool audio_signal_b=0;
int  myTrigger_i = 500; /* 10ms task * 500 = 5s */
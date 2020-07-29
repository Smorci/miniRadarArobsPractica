#define ACTIVE_WARNING_U 1
#define NOT_ACTIVE_WARNING_U 0
#define MIN_SPPED_U 20
#define MIN_ANGLE_C 6
#define LCW_ACTIVE_U 1
#define LCW_PASSIVE_U 0
#define CONDITION_PASSED_U 1
#define CONDITION_NOT_PASSED_U 0
#define RANGE_LCW_U 20

typedef enum gear_poz{
    neutral,
    forward,
    reveresed,
    parked
}gear_poz;
typedef enum ssm_states{
    INIT,
    ACTIVE,
    ERROR
}ssm_states;

#define ERROR_OCURED_U 1
#define NO_ERROR_OCURED_U 0


typedef enum err_values{
    notsetyet,
    fail,
    passed
}err_values;

typedef enum err_names{
    err_batVoltage,
    err_lostCom,
    err_delimiter
}err_names;

typedef struct Errors{
    int q_time_i;
    char dq_time_i;
    err_values err_val;
    err_names errName;
}Errors;
#define ERROR_OCURED_U 1
#define NO_ERROR_OCURED_U 0


enum err_values{
    notsetyet,
    fail,
    passed
};

typedef struct Errors{
    int q_time_i;
    enum err_values err_val;
}Errors;
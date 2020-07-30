#define QUAL_TIME_UI 150u  // to ms (dont work with float)
#define DEQUAL_TIME_UI 150u
#define LOSTCOMM_TIMER_UI 300u
#define RUNOUT_TIMER_UI 0u
#define BATTERY_CYCLE_TIMER_UI 50u
#define NUMBER_OF_ERRORS_C 3
#define LOWER_VOLTAGE_LIMIT_C 8
#define UPPER_VOLTAGE_LIMIT_C 16
#define FILE_NOT_OPEN_B false
#define FILE_OPEN_B true
#define UNDERVOLTAGE_FALSE_B false
#define UNDERVOLTAGE_TRUE_B true
#define OVERVOLTAGE_FALSE_B false
#define OVERVOLTAGE_TRUE_B true


typedef enum error_Status{
    NOT_YET_PERFORMED = 0,
    FAILED = 1,
    PASSED = 2
};

typedef enum error_Name{
    ERR_BATTERYVOLTAGE = 0,
    ERR_LOSTCOMM = 1,
    ERR_DELIMITER = 2
};

typedef struct error{
    enum error_Status errorStatus; 
    enum error_Name errorName;
} error;

struct error *globalErrors_ST[NUMBER_OF_ERRORS_C];

/* the following code will be deleted and included in ErrorHandler.c via CommunicationInterface.h*/


typedef struct DataFromFile         
{
    unsigned char speed_uc;
    enum Gear gear_e;      
    char angle_c;
    unsigned char distance_uc;
    unsigned char battery_voltage_uc;
    
}DataFromFile;
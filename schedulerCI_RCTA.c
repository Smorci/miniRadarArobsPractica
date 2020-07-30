#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CommunicationInterface.h"
#include "RearCrossTrafficAlert.h"

int main()
{
    //DataFromFile *messageFromFile=malloc(1);
    //messageFromFile.speed_uc=1;
    CI_Read_data();
    CI_Write_data(1, 2);
    //CI_Read_data();
    RCTA_colisionRCTA();

    return 0;
}
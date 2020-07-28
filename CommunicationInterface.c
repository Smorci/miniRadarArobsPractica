struct Data{
    unsigned char speed;
    char gear;
    char angle;
    char distance;
    char battery_voltage;
};

struct Data Read_data(){
    struct Data data;
    int buffer=0;
    FILE * speed_file;
    speed_file=fopen("speed.txt","r");
    if(speed_file)
    {
        fscanf(speed_file,"%d", &buffer);
        printf("%d\n",buffer);
        if(buffer>=0 && buffer<=255)
            data.speed=buffer;
        else
        data.speed=0;//default value for speed
    }

    FILE * gear_file;
    gear_file=fopen("gear.txt","r");
    if(gear_file)
    {
        fscanf(gear_file,"%d",&buffer);
        if(buffer>=0&&buffer<=2)
            data.gear=buffer;
        else
            data.gear=0;//default value for gear
    }

    FILE * angle_file;
    angle_file=fopen("angle.txt","r");
    if(angle_file)
    {
        fscanf(angle_file,"%d",&buffer);
        if(buffer>=-45&&buffer<=45)
            data.angle=buffer;
        else
            data.angle=0;//default value for angle
    }

    FILE * distance_file;
    distance_file=fopen("distance.txt","r");
    if(distance_file)
    {
        fscanf(distance_file,"%d",&buffer);
        if(buffer>=0&&buffer<=80)
            data.distance=buffer;
        else
            data.distance=-80;//default value for distance
    }
    FILE * battery_voltage_file;
    battery_voltage_file=fopen("battery_voltage.txt","r");
    if(battery_voltage_file)
    {
        fscanf(battery_voltage_file,"%d",&buffer);
        if(buffer>=8&&buffer<=16)
            data.distance=buffer;
        else
            data.distance=8;//default value for battery_voltage
    }
    return data;
}

void Write_data(char  option,int data)
{
    
    switch(option)
    {
        case 's': ;
            FILE * speed_file=fopen("speed.txt","w");
            fprintf(speed_file,"%d",data);
            break;
        case 'g': ;
            FILE *gear_file=fopen("gear.txt","w");
            fprintf(gear_file,"%d",data);
            break;
        case 'a': ;
            FILE *angle_file=fopen("angle.txt","w");
            fprintf(angle_file,"%d",data);
            break;
        case 'd': ;
            FILE *distance_file=fopen("distance.txt","w");
            fprintf(distance_file,"%d",data);
            break;
        case 'b': ;
            FILE *battery_voltage_file=fopen("battery_voltage.txt","w");
            fprintf(battery_voltage_file,"%d",data);
            break;
        default: printf("Invalid Option");

    }

}
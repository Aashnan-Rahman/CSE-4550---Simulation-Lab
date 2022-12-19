#include "vehicles.h"

int cnt = 0;

vehicles::vehicles()
{
    //ctor
}

int vehicles::rand_g(int n)
{
    return (rand())%n;
}

int vehicles::vehicle_sl()
{
    int temp = cnt;
    cnt++;

    return temp;
}

void vehicles::create_vehicles()
{
    int n = rand_g(3);
    serial_no = cnt;
    cnt++;

    if(n == 0)
    {
        type = "small";
        length = 7 + rand_g(3);
        speed =  40 + rand_g(15);
    }

    else if(n == 1)
    {
        type = "medium";
        length = 10 + rand_g(3);
        speed =  25 + rand_g(10);
    }

    else
    {
        type = "large";
        length = 20 + rand_g(2);
        speed =  10 + rand_g(5);
    }
}

void vehicles::create_vehic_csv()
{
    std::ofstream myfile;
    myfile.open("Vehicle Generator.csv");  //,std::ios::app
    myfile<<"Serial No , Queue No , Type , Length , Speed , Arrival , Depart \n";
    myfile.close();
}

void vehicles::write_vehic_csv()
{
    std::fstream myfile;
    myfile.open("Vehicle Generator.csv",ios::app);
    myfile << serial_no << "," << queue_no << "," << type <<","<< length <<","<< speed <<","<< arrival_t <<","<< depart_t <<"\n";
    myfile.close();
}

void vehicles::show_vehicles()
{
    create_vehic_csv();
    cout<<"Serial No :  "<<serial_no<<endl;
    cout<<"Queue No  :  "<<queue_no<<endl;
    cout<<"Type      :  "<<type<<endl;
    cout<<"Length    :  "<<length<<endl;
    cout<<"Speed     :  "<<speed<<endl;
    cout<<"Arrival   :  "<<arrival_t<<endl;
    cout<<"Depart    :  "<<depart_t<<endl;
    write_vehic_csv();
    serial_no++;
}



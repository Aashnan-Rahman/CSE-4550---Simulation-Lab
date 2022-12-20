#ifndef VEHICLES_H
#define VEHICLES_H

#include<bits/stdc++.h>
#include<ctime>

using namespace std;

class vehicles
{
    private:
        int serial_no;
        string type;
        int length;
        int speed;
        int queue_no;
        clock_t arrival_t;
        clock_t depart_t;
        clock_t waiting_t;


    public:
        vehicles();
        void create_vehicles(int no,int q);
        int rand_g(int n);
        int vehicle_sl();
        void show_vehicles();
        void write_vehic_csv();


    protected:


};


#endif // VEHICLES_H

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
        clock_t service_t;


    public:
        vehicles();
        void create_vehicles(int no,int q);
        int rand_g(int n);
        int vehicle_sl();
        void show_vehicles();
        void write_vehic_csv();
        void write_depart_csv(int turn_);
        void departing_info(int departing,int servicingTime);
        int can_pass(int remain, int length_to_be_covered);
        void fetch_info(int length_, int speed_, int arrival_, int depart_);
        int ret_id(){ return (serial_no); }


    protected:


};


#endif // VEHICLES_H

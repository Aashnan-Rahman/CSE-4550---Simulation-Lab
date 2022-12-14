#ifndef server_h
#define server_h

#include "event.h"
#include "queue.h"
#include "vehicles.h"
//#include "scheduler.h"

#include <math.h>
#include <iostream>
#include <fstream>
#include<bits/stdc++.h>
using namespace std;

class Server
{
	public:
		Server ();
		void initialize ();
		void arrivalHandler ();
		void departureHandler ();
		void junctionHandler () ;
		void terminationHandler () ;

		void createTraceFile ();
		void manage_junction_csv();
		void create_vehic_csv();
		void create_depart_csv();

		//inline int& status () { return (status_); }
		//inline int& itemArrived () { return (itemArrived_); }
		//inline double& arrivalMean () { return (arrivalMean_); }
		//inline double& departureMean () { return (departureMean_); }

		//inline double avgDelay() { return totalDelay_/itemArrived_; }
		//inline double avgQLength() { return qProduct_/lastEventTime_; }

		void show_result ();

		int add=3;
		int vehic = 5;

	private:
		Queue* queue_;
		ArrivalEvent a_;
		DepartureEvent d_;
		JunctionEvent j_;
		TerminationEvent t_;

		int itemArrived_;
		int vhc_cnt;
		int vhc_cnt_q1;
		int vhc_cnt_q2;
		int vhc_cnt_q3;
		Item* itemInService_;
		ofstream trace_;

        int status_;
        int remaining_time;
        int agg_length;
        int Junction_length=50;


		double arrivalMean_;
		double departureMean_;
		double exponential (double mean);
		int rand_g(int n);

		int signals_;
		int totalDepartures_;
		int totalWait_;
		double totalService_;

		vector<vehicles>v[4];
		int a[100500]={};


};
#endif




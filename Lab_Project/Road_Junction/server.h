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

		inline int& status () { return (status_); }
		inline int& itemArrived () { return (itemArrived_); }
		inline double& arrivalMean () { return (arrivalMean_); }
		inline double& departureMean () { return (departureMean_); }

		inline double avgDelay() { return totalDelay_/itemArrived_; }
		inline double avgQLength() { return qProduct_/lastEventTime_; }

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


		double arrivalMean_;
		double departureMean_;
		double exponential (double mean);
		int rand_g(int n);

		double qProduct_;
		double totalDelay_;
		double lastEventTime_;
		double lastArrivalTime_;

		vector<vehicles>v[4];
		void create_vehic_csv();

};
#endif





#ifndef server_h
#define server_h

#include "event.h"
#include "queue.h"
#include "scheduler.h"
#include "facility.h"

#include <math.h>
#include <iostream>
#include <fstream>

using namespace std;

class Server
{
	public:
		Server (int id, Facility* facility);
		void initialize ();
		static int itemArrived_;

		void facilityArrivalHandler ();
		void serverArrivalHandler ();
		//void facilityDepartureHandler ();

		void departureHandler ();

		//void createTraceFile ();
		void triggerArrival();
		void updateStat();
		void report();

		inline int& status () { return (status_); }
		inline int& itemArrived () { return (itemArrived_); }

		inline double& arrivalMean () { return (arrivalMean_); }
		inline double& departureMean () { return (departureMean_); }

		//inline double avgDelay() { return totalDelay_/itemArrived_; }
		//inline double avgQLength() { return qProduct_/lastEventTime_; }

        inline int queueLength() { return queue_->length(); }
		inline int getId() { return id_; }
		inline Facility* getFacility() { return facility_; }
		inline double& areaQueue() { return (areaQueue_); }

		inline double& totalQueueDelay() { return (totalQueueDelay_); }
		inline double& totalSystemDelay() { return (totalSystemDelay_); }

		inline int& totalCustomerServed() { return (totalCustomerServed_); }

		inline double trafficIntensity() { return arrivalMean()/departureMean(); }
		inline double averageQueueLength() { return (areaQueue()/Scheduler::now()); }
		inline double averageQueueDelay() { return (totalQueueDelay()/totalCustomerServed()); }
		inline double averageSystemDelay() { return (totalSystemDelay()/totalCustomerServed()); }

	private:
		Queue* queue_;
		ArrivalEvent a_;
		DepartureEvent d_;
		Facility* facility_;

        int id_;
		int status_;
		//int itemArrived_;
		Item* itemInService_;

		ofstream trace_;

		double arrivalMean_;
		double departureMean_;
		double exponential (double mean);

		double timeLastEvent_;
		double areaQueue_;

		double queueDelay_;
		double systemDelay_;

		double totalQueueDelay_;
		double totalSystemDelay_;

		int totalCustomerServed_;
};
#endif







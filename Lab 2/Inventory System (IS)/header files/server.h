#ifndef server_h
#define server_h

#include "event.h"

#include "scheduler.h"

#include <math.h>
#include <iostream>
#include <fstream>
using namespace std;

class Server
{
	public:
		Server();
		void initialize ();
		void supplyHandler ();
		void demandHandler ();
		void evaluationHandler ();
		void terminationHandler ();

		void displayReport();
		void updateStat();

        double avgOrderingCost;
		double avgHoldingCost ;
		double avgShortageCost;
		double avgCost;

		double t1=0,t2=0,t3=0,t4=0;
		double val=30;


	private:
		SupplyEvent s_;
		DemandEvent d_;
		EvaluationEvent e_;
        TerminationEvent t_;


        int ivLevel_;
        int n;

		int maxLevel_;
		int minLevel_;

		double maxLag_;
		double minLag_;

		double setupCost_ = 32;
		double itemCost_ = 3;

		double arrivalMean_ = 0.1;
		double demandMean_;

        double areaHolding_ ;
        double areaShortage_ = 0;
        double orderingCost_ = 0;

        double holdingCost_ = 1;
        double shortageCost_  = 5;


		double exponential (double mean);
		double uniformRand(double min_,double  max_);
		int discreteRand();

		double qProduct_;
		double totalDelay_;
		double lastEventTime_;
		double lastArrivalTime_;

		int orderAmount_;
		int timeLastEvent_;

		int evaluationID_;
		int supplyID_;
		int demandID_;

		ofstream trace_;






};
#endif









#include "server.h"
#include "scheduler.h"

#include <malloc.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;


Server::Server() : s_(this),e_(this),d_(this),t_(this)
{

}

double Server :: exponential(double mean)
{

	double r = (double)rand()/RAND_MAX;

	double ex = -mean * log (r);

	return ex;
}

int Server :: discreteRand()
{
    int d;
	double u = (double)rand()/RAND_MAX;

	if(u < 0.1667) d = 1;
	else if (u < 0.5001) d = 2;
	else if (u < 0.8335) d = 3;
	else  d = 4;

	return d;
}

double Server :: uniformRand(double min_,double max_)
{

	double u = (double)rand()/RAND_MAX;

	double ur = min_ + u * (max_ - min_);

	return ur;

}

void Server :: initialize ()
{
	ivLevel_ = 0;
	n = 120;
	demandMean_ = 0.1;

    maxLevel_ = 100;
    minLevel_ = 60;

	minLag_ = 0.5;
	maxLag_ = 1.0;

	qProduct_ = 0;
	totalDelay_ = 0;
	lastEventTime_ = 0;

    ivLevel_ = maxLevel_;

    evaluationID_ = 0;
    demandID_ = 0;
    supplyID_= 0;


    orderingCost_ = 0;
    areaHolding_ = 0;
    areaShortage_ = 0;

    timeLastEvent_ = 0 ;

    e_.activate(0);
    t_.activate(n);

	double tm = exponential (demandMean_);
	//trace_ << "interarrival time " << t << endl;
	d_.activate (tm);
}

void Server :: demandHandler()
{
    updateStat();
    demandID_++;
    int demand_ = discreteRand();
    ivLevel_ -= demand_;

    double tm = exponential(demandMean_);
    d_.activate(tm);
}

void Server :: evaluationHandler()
{

    updateStat();

    evaluationID_++;

    if(ivLevel_ < minLevel_)
    {
        orderAmount_ = maxLevel_ - ivLevel_;
        int cost_ = setupCost_ + (orderAmount_ * itemCost_);
        orderingCost_ += cost_;

        double tm = uniformRand(minLag_,maxLag_);
        s_.activate(tm);
    }
    e_.activate(1);
}

void Server :: supplyHandler()
{
    updateStat();
    supplyID_++;
    ivLevel_ += orderAmount_;
}

void Server :: terminationHandler()
{
//    s_.cancel();
//    d_.cancel();
//    e_.cancel();
    Scheduler::cancel();
    displayReport();
    //t_.cancel();
}


void Server :: updateStat()
{
    double t = Scheduler::now();
    int duration = t - timeLastEvent_;
    timeLastEvent_ = Scheduler::now();;

    if(ivLevel_ < 0)    areaShortage_ -= (ivLevel_ * duration);
    else areaHolding_ += (ivLevel_ * duration);
}

void Server :: displayReport()
{
    ofstream out("out.csv",ios_base::app);
    double avgOrderingCost = orderingCost_/120.0;
    double avgHoldingCost = (holdingCost_*areaHolding_)/120.0;
    double avgShortageCost = (shortageCost_*areaShortage_)/120.0;
    double avgCost = avgOrderingCost + avgHoldingCost + avgShortageCost;

    cout<<avgOrderingCost<<" "<<avgHoldingCost<<" "<<avgShortageCost<<" "<<avgCost<<endl;

    out << avgOrderingCost << ','  << avgHoldingCost << ',' << avgShortageCost << ',' << avgCost << endl;

    out.close();

}








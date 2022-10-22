#include "server.h"
#include <fstream>
using namespace std;

#ifndef facility_h
#define facility_h

class Facility
{
public:
    Facility(double arrivalMean, double serviceMean);
    void report();
    void initialize();
    void createTraceFile ();
    void arrivalHandler();
    void departureHandler(Server*);

    inline int queueLength() { return queue_ -> length(); }
    inline ofstream& trace() { return trace_; }

private:
    Server* server1;
    Server* server2;

    Queue* queue_;
    int itemArrived_;

    ofstream trace_;

};

#endif // facility_h

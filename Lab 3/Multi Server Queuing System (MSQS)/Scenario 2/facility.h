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
    void arrivalHandler();

    void createTraceFile();
    inline ofstream& trace() { return trace_; }

private:
    Server* server1;
    Server* server2;

    ofstream trace_;
};

#endif // facility_h


#ifndef TRAINTICKET_H
#define TRAINTICKET_H
#include <string>
#include <vector>

using std::string;
using std::vector;

#include "booking.h"
class TrainTicket  : virtual public Booking
{
    public:
        TrainTicket(const string& id, const double& price, const string& fromDate, const string& toDate,
                    const string &fromDestination, const string &toDestination,const string &departureTime,
                    const string &arrivalTime, const vector<string> connectingStations);
        string showDetails() override;


    private:
        string fromDestination;
        string toDestination;
        string departureTime;
        string arrivalTime;
        vector<string> connectingStations;
};

#endif // TRAINTICKET_H

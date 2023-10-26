#ifndef FLIGHTBOOKING_H
#define FLIGHTBOOKING_H
#include "booking.h"
#include <string>

using std::string;

class FlightBooking : virtual public Booking
{
    public:
        FlightBooking(const string& id, const double& price, const string& fromDate, const string& toDate, const string &fromDestination, const string &toDestination, const string &airline);
        string showDetails() override;
    private:
        string fromDestination;
        string toDestination;
        string airline;
};

#endif // FLIGHTBOOKING_H

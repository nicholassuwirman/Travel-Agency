#ifndef HOTELBOOKING_H
#define HOTELBOOKING_H
#include "booking.h"
#include <string>

using std::string;


class HotelBooking : virtual public Booking
{
    public:
        HotelBooking(const string& id, const double& price, const string& fromDate, const string& toDate, const string &hotel, const string &town );
        string showDetails() override;
    private:
        string hotel;
        string town;
};

#endif // HOTELBOOKING_H

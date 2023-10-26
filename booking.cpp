#include "booking.h"
#include <string>
using std::string;

Booking::Booking(const string& id, const double& price, const string& fromDate, const string& toDate)
    : id(id), price(price), fromDate(fromDate), toDate(toDate)
{

}

Booking::~Booking() //virtuell
{

}

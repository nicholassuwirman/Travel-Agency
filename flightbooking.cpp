#include "flightbooking.h"

FlightBooking::FlightBooking(const string &id, const double &price, const string &fromDate, const string &toDate, const string &fromDestination, const string &toDestination, const string &airline)
    : Booking(id, price, fromDate, toDate), fromDestination(fromDestination), toDestination(toDestination), airline(airline)
{

}

string FlightBooking::showDetails()
{
    return "Flugbuchung von " + fromDestination + " nach " + toDestination + " mit " + " am " + fromDate + ". Preis: " + std::to_string(price) + " Euro";
 }

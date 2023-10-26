#include "hotelbooking.h"

HotelBooking::HotelBooking(const string &id, const double &price, const string &fromDate, const string &toDate, const string &hotel, const string &town)
    :Booking(id, price, fromDate, toDate), hotel(hotel), town(town)
{

}

string HotelBooking::showDetails()
{
    return "Hotelreservierung im " + hotel + " in " + town + " vom " + fromDate + " bis zum " + toDate + ". Preis: " + std::to_string(price) + " Euro";
}

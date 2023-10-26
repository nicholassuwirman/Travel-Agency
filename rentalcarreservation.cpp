#include "rentalcarreservation.h"

RentalCarReservation::RentalCarReservation(const string& id, const double& price, const string& fromDate, const string& toDate, const string& pickupLocation, const string& returnLocation, const string& company)
    : Booking(id, price, fromDate, toDate), pickupLocation(pickupLocation), returnLocation(returnLocation), company{company} {}

string RentalCarReservation::showDetails()
{
    return "Mietwagenreservierung mit " + company + ". Abholung am " + fromDate + " in " + pickupLocation + ".  Rueckgabe am "
           + toDate + " in " + returnLocation + ". Preis: " + std::to_string(price);
}

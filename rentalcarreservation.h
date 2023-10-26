#ifndef RENTALCARRESERVATION_H
#define RENTALCARRESERVATION_H
#include "booking.h"

#include <string>

using std::string;

class RentalCarReservation : public Booking
{
public:
    RentalCarReservation(const string& id, const double& price, const string& fromDate, const string& toDate, const string& pickupLocation, const string& returnLocation, const string& company);
    string showDetails() override;
private:
    string pickupLocation;
    string returnLocation;
    string company;
};

#endif // RENTALCARRESERVATION_H

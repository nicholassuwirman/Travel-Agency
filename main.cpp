#include <iostream>
#include "travelagency.h"
#include "booking.h"

using namespace std;

int main()
{
    vector<Booking*> bookings;
    TravelAgency travelAgencyObject(bookings);

    travelAgencyObject.readFile();
    return 0;
}

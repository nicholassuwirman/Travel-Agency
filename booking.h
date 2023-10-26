#ifndef BOOKING_H
#define BOOKING_H
#include <string>
using std::string;

class Booking   // Abstract class
{
public:
    Booking(const string& id, const double& price, const string& fromDate, const string& toDate);
    virtual string showDetails() = 0;
    virtual ~Booking();
protected:
    string id;
    double price;
    string fromDate;
    string toDate;
};

#endif // BOOKING_H

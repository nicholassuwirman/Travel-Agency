#include "trainticket.h"

TrainTicket::TrainTicket(const string &id, const double &price, const string &fromDate, const string &toDate, const string &fromDestination, const string &toDestination, const string &departureTime, const string &arrivalTime, const vector<string> connectingStations)
    :Booking(id, price, fromDate, toDate), fromDestination(fromDestination), toDestination(toDestination), departureTime(departureTime), arrivalTime(arrivalTime),connectingStations(connectingStations)
{

}



string TrainTicket::showDetails()
{
    string toReturn = "Zugticket von " + fromDestination + " nach " + toDestination + " am "
                      + fromDate + " um " + departureTime;

    string checkStations{""};
    if(connectingStations.empty()) {
        checkStations  = "";    //noch empty
    } else {
        checkStations + " ueber ";
        for (auto &stations:connectingStations) {
            checkStations = checkStations + " " + stations;
        }
    }

    return toReturn + checkStations + ". Preis: " + std::to_string(price) + " Euro";
}

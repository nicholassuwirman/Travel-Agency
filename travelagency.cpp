#include "travelagency.h"
#include "flightbooking.h"
#include "hotelbooking.h"
#include "rentalcarreservation.h"
#include "trainticket.h"


TravelAgency::TravelAgency(const std::vector<Booking*> &bookings)
    : bookings(bookings)
{

}

TravelAgency::~TravelAgency()
{
    for (Booking* booking : bookings)
    {
        delete booking;
    }

    bookings.clear();
}

void TravelAgency::readFile()
{
    //Datei lesen
    QString dateiName = "bookings.json";
    QFile datei(dateiName);
    if ( !datei.open(QIODevice::ReadOnly) )
        cerr << "Datei konnte nicht geoeffnet werden";

    QString dateiInhalt = datei.readAll();
    datei.close();

    //um die JSON Datei in QJsonDocumentobjekt zu zerlegen
    QJsonDocument jsonDatei = QJsonDocument::fromJson(dateiInhalt.toUtf8());

    if (jsonDatei.isNull())
        cerr << "JSON-Datei ist ungueltig";

    if ( jsonDatei.isArray() )
    {
        QJsonArray jsonArray = jsonDatei.array();

        int flugBuchungen{0}, hotelReservierungen{0};

        for ( const QJsonValue &jsonValue : jsonArray )
        {
            if ( jsonValue.isObject() )      //bisa di clean hrsnya pake !jsonObject aja
            {
                QJsonObject jsonObject = jsonValue.toObject();

                //Umwandlung aller Variablen, die immer benutzen werden (fuer Booking object im Konstruktor)
                string id = jsonObject[ "id" ].toString().toStdString();
                double price = jsonObject[ "price" ].toDouble();
                string fromDate = jsonObject[ "fromDate" ].toString().toStdString();
                string toDate = jsonObject[ "toDate" ].toString().toStdString();

                //Zugriff auf den Type des jsonObjekts
                QString objectType = jsonObject[ "type" ].toString();

                if ( objectType == "RentalCar" )
                {
                    string pickupLocation = jsonObject[ "pickupLocation" ].toString().toStdString();
                    string returnLocation = jsonObject[ "returnLocation" ].toString().toStdString();
                    string company = jsonObject[ "company" ].toString().toStdString();

                    RentalCarReservation* rentalCarReservation = new RentalCarReservation(id, price, fromDate, toDate, pickupLocation, returnLocation, company);

                    bookings.push_back( rentalCarReservation );
                }
                else if ( objectType == "Hotel" )
                {
                    string hotel = jsonObject[ "hotel" ].toString().toStdString();
                    string town = jsonObject[ "town" ].toString().toStdString();

                    HotelBooking* hotelBooking = new HotelBooking(id, price, fromDate, toDate, hotel, town);

                    bookings.push_back( hotelBooking );
                    hotelReservierungen++;
                }
                else if ( objectType == "Flight" )
                {
                    string fromDestination = jsonObject[ "fromDest" ].toString().toStdString();
                    string toDestination = jsonObject[ "toDate" ].toString().toStdString();
                    string airline = jsonObject[ "airline "].toString().toStdString();

                    FlightBooking* flightBooking = new FlightBooking(id, price, fromDate, toDate, fromDestination, toDestination, airline);

                    bookings.push_back( flightBooking );

                    flugBuchungen++;
                }
                else if( objectType == "Train" )
                {
                    string fromDestination = jsonObject[ "fromDate" ].toString().toStdString();
                    string toDestination = jsonObject[ "toDate" ].toString().toStdString();
                    string departureTime = jsonObject[ "departureTime" ].toString().toStdString();
                    string arrivalTime = " ";   //es gibt keine arrivalTime Objektattribute im jsonfile.
                    vector<string> connectingStations;

                    if (jsonObject.contains("connectingStations") && jsonObject[ "connectingStations" ].isArray() )
                    {
                        QJsonArray stationsArray = jsonObject[ "connectingStations" ].toArray();

                        for ( const QJsonValue &station : stationsArray )
                        {
                            connectingStations.push_back( station.toString().toStdString() );
                        }
                    }

                    TrainTicket* trainObject = new TrainTicket(id, price, fromDate, toDate, fromDestination, toDestination, departureTime, arrivalTime, connectingStations);

                    bookings.push_back( trainObject );
                }

            }
        }
        cout << "sucessful, TODO AUFGABE 4" << flugBuchungen << hotelReservierungen;
    }
}
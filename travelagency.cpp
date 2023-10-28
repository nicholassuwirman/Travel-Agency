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


void TravelAgency::readBinaryFile()
{
    ifstream binaryDatei;
    binaryDatei.open("bookingsBinary.bin", ios::in | ios::binary);

    if ( !binaryDatei.is_open() )
        cerr << "Binaerdatei kann nicht geoeffnet werden" <<endl;

    //countvariablen fuer die Ausgabe
    int flight{}, flightTotalPrice{};       //TODO Countnya

    //8+1 fuer Nullterminator
    char type{}; char id[39]; double price{}; char fromDate[9]; char toDate[9];
    //Flight
    char fromDestination[4]; char toDestination[4]; char airline[16];

    if ( !binaryDatei )
        cerr << "Binaerdatei error" << endl;

    while ( !binaryDatei.eof() )
    {
        //Zugriff auf die Bookingvariablen von der Binaerdatei
        binaryDatei.read( reinterpret_cast<char*>(&type), sizeof (type) );
        binaryDatei.read( reinterpret_cast<char*>(&id), sizeof (id)-1 );
        binaryDatei.read( reinterpret_cast<char*>(&price), sizeof (price) );
        binaryDatei.read( reinterpret_cast<char*>(&fromDate), sizeof (fromDate)-1 );
        binaryDatei.read( reinterpret_cast<char*>(&toDate), sizeof (toDate)-1 );

        //um das Chararray zu terminieren (also Chararray braucht null terminator)
        id[38] = '\0';
        fromDate[8] = '\0';
        toDate[8] = '\0';


        if ( type == 'F')
        {
            binaryDatei.read( reinterpret_cast<char*>(&fromDestination), sizeof (fromDestination) );
            binaryDatei.read( reinterpret_cast<char*>(&toDestination), sizeof (toDestination) );
            binaryDatei.read( reinterpret_cast<char*>(&airline), sizeof (airline) );

            fromDestination[3] = '\0';
            toDestination[3] = '\0';

            // Trim trailing spaces from the airline name
            for (int i = 15; i >= 0; i--) {
                if (airline[i] != ' ') {
                    airline[i + 1] = '\0'; // Null-terminate at the first non-space character
                    break;
                }
            }

            FlightBooking* flightBooking = new FlightBooking(id, price, fromDate, toDate, fromDestination, toDestination, airline);

            bookings.push_back(flightBooking);

            flight++;
            flightTotalPrice+=price;
        }
        else if( type == 'R')
        {

        }
    }

    cout << fromDestination << " Flights and total price: " << toDestination << "   " <<  airline;
    binaryDatei.close();
}


void TravelAgency::readFile()
{
    //Datei lesen
    QString dateiName = "bookings.json";
    QFile datei(dateiName);
    if ( !datei.open(QIODevice::ReadOnly) )
        cerr << "Datei kann nicht geoeffnet werden" << endl;

    QString dateiInhalt = datei.readAll();
    datei.close();

    //um die JSON Datei in QJsonDocumentobjekt zu zerlegen
    QJsonDocument jsonDatei = QJsonDocument::fromJson(dateiInhalt.toUtf8());


    //Weitere Checks
    if ( jsonDatei.isNull() )
        cerr << "JSON-Datei ist ungueltig";


    if( !jsonDatei.isArray() )
        cerr << "JSON-Datei ist kein Array";

    QJsonArray jsonArray = jsonDatei.array();

    int flugBuchungen{0}, flugBuchungenWert{0}, mietwagenBuchungen{0}, mietwagenBuchungenWert{0},
        hotelReservierungen{0}, hotelReservierungenWert{0}, zugBuchungen{0}, zugBuchungenWert{0};

    for ( const QJsonValue &jsonValue : jsonArray )
    {
        if( !jsonValue.isObject() )
            cerr << "Invalid JSON-Value";

        QJsonObject jsonObject = jsonValue.toObject();

        //Umwandlung des Types aller Variablen, die immer benutzen werden (fuer Booking object im Konstruktor)
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

            mietwagenBuchungen++;
            mietwagenBuchungenWert+=price;
        }
        else if ( objectType == "Hotel" )
        {
            string hotel = jsonObject[ "hotel" ].toString().toStdString();
            string town = jsonObject[ "town" ].toString().toStdString();

            HotelBooking* hotelBooking = new HotelBooking(id, price, fromDate, toDate, hotel, town);

            bookings.push_back( hotelBooking );

            hotelReservierungen++;
            hotelReservierungenWert+=price;
        }
        else if ( objectType == "Flight" )
        {
            string fromDestination = jsonObject[ "fromDest" ].toString().toStdString();
            string toDestination = jsonObject[ "toDate" ].toString().toStdString();
            string airline = jsonObject[ "airline "].toString().toStdString();

            FlightBooking* flightBooking = new FlightBooking(id, price, fromDate, toDate, fromDestination, toDestination, airline);

            bookings.push_back( flightBooking );

            flugBuchungen++;
            flugBuchungenWert+=price;
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

            zugBuchungen++;
            zugBuchungenWert+=price;
        }
    }

    cout << "Es Wurden " << flugBuchungen << " Flugbuchungen im Wert von " << flugBuchungenWert << " Euro, " << mietwagenBuchungen << " Mietwagenbuchungen im Wert von "
         << mietwagenBuchungenWert << " Euro, " << hotelReservierungen << " Hotelreservierungen im Wert von " << hotelReservierungenWert << " Euro, "
         << zugBuchungen << " Zugbuchungen im Wert von " << zugBuchungenWert << " Euro, angelegt" << endl << endl;

}

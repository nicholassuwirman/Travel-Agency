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

//TODO: 50/49 Flugbuchungen ist richtig?
void TravelAgency::readBinaryFile()
{
    ifstream binaryDatei;
    binaryDatei.open("bookingsBinary.bin", ios::in | ios::binary);

    if ( !binaryDatei.is_open() )
        cerr << "Binaerdatei kann nicht geoeffnet werden" <<endl;

    //countvariablen fuer die Ausgabe
    double flightCount{}, flightTotalPrice{}, rentalCarCount{}, rentalCarTotalPrice{}, hotelBookingsCount{}, hotelTotalPrice{}, trainCount{}, trainTotalPrice{};

    //8+1 fuer Nullterminator
    char type{}; char id[39]; double price{}; char fromDate[9]; char toDate[9];
    //Flight
    char fromDestination[4]; char toDestination[4]; char airline[16];
    //RentalCar
    char pickupLocation[16]; char returnLocation[16]; char company[16];
    //Hotel
    char hotelName[16]; char hotelTown[16];
    //Train  fromDestination, toDestination, departureTime, arrivalTime, connectingStations
    char trainFromDestination[16]; char trainToDestination[16]; char departureTime[6]; char arrivalTime[6];


    if ( !binaryDatei )
        cerr << "Binaerdatei error" << endl;

    while ( !binaryDatei.eof() )
    {
        //um das Chararray zu terminieren (also Chararray braucht null terminator)
        id[38] = '\0';
        fromDate[8] = '\0';
        toDate[8] = '\0';

        //Zugriff auf die Bookingvariablen von der Binaerdatei
        binaryDatei.read( reinterpret_cast<char*>(&type), sizeof (type) );
        binaryDatei.read( reinterpret_cast<char*>(&id), sizeof (id) - 1 );
        binaryDatei.read( reinterpret_cast<char*>(&price), sizeof (price) );
        binaryDatei.read( reinterpret_cast<char*>(&fromDate), sizeof (fromDate) - 1 );
        binaryDatei.read( reinterpret_cast<char*>(&toDate), sizeof (toDate) - 1 );

        switch ( type ) {
        case 'F':
        {
            fromDestination[3] = '\0';
            toDestination[3] = '\0';
            airline[15] = '\0';

            binaryDatei.read( reinterpret_cast<char*>(&fromDestination), sizeof (fromDestination) - 1 );
            binaryDatei.read( reinterpret_cast<char*>(&toDestination), sizeof (toDestination) - 1 );
            binaryDatei.read( reinterpret_cast<char*>(&airline), sizeof (airline) - 1 );

            FlightBooking* flightBooking = new FlightBooking(id, price, fromDate, toDate, fromDestination, toDestination, airline);

            bookings.push_back(flightBooking);

            flightCount++;
            flightTotalPrice+=price;
            break;
        }
        case 'R':
        {
            pickupLocation[15] = '\0';
            returnLocation[15] = '\0';
            company[15] = '\0';

            binaryDatei.read( reinterpret_cast<char*>(&pickupLocation), sizeof (pickupLocation) - 1 );
            binaryDatei.read( reinterpret_cast<char*>(&returnLocation), sizeof (returnLocation) - 1 );
            binaryDatei.read( reinterpret_cast<char*>(&company), sizeof (company) - 1 );

            RentalCarReservation* rentalCar = new RentalCarReservation(id, price, fromDate, toDate, pickupLocation, returnLocation, company);

            bookings.push_back(rentalCar);

            rentalCarCount++;
            rentalCarTotalPrice+=price;
            break;
        }
        case 'H':
        {
            hotelName[15] = '\0';
            hotelTown[15] = '\0';

            binaryDatei.read( reinterpret_cast<char*>(&hotelName), sizeof (hotelName) - 1 );
            binaryDatei.read( reinterpret_cast<char*>(&hotelTown), sizeof (hotelTown) - 1 );

            HotelBooking* hotelBooking = new HotelBooking(id, price, fromDate, toDate, hotelName, hotelTown);

            bookings.push_back(hotelBooking);

            hotelBookingsCount++;
            hotelTotalPrice+=price;
            break;
        }
        case 'T':
        {
            trainFromDestination[15] = '\0';
            trainToDestination[15] = '\0';
            departureTime[5] = '\0';
            arrivalTime[5] = '\0';
            vector<string> connectingStations;
            int connectingStationsSize;

            binaryDatei.read( reinterpret_cast<char*>(&trainFromDestination), sizeof (trainFromDestination) - 1 );
            binaryDatei.read( reinterpret_cast<char*>(&trainToDestination), sizeof (trainToDestination) - 1 );
            binaryDatei.read( reinterpret_cast<char*>(&departureTime), sizeof (arrivalTime) - 1 );
            binaryDatei.read( reinterpret_cast<char*>(&arrivalTime), sizeof (arrivalTime) - 1 );
            binaryDatei.read( reinterpret_cast<char*>(&connectingStationsSize), sizeof (connectingStationsSize));

            char station[16];
            station[15] = '\0';

            for (int i = 0; i < connectingStationsSize; i++)
            {
                binaryDatei.read( reinterpret_cast<char*>(&station), sizeof (station) - 1 );
                connectingStations.push_back(station);
            }

            TrainTicket* trainBooking = new TrainTicket(id, price, fromDate, toDate, trainFromDestination, trainToDestination, departureTime, arrivalTime, connectingStations);

            bookings.push_back(trainBooking);

            trainCount++;
            trainTotalPrice+=price;
            break;
        }
        default:
        {
            cout << "Unbekannt Typ";
        }


        }
    }

    cout << "Es Wurden " << flightCount << " Flugbuchungen im Wert von " << flightTotalPrice << " Euro, " << rentalCarCount << " Mietwagenbuchungen im Wert von "
         << rentalCarTotalPrice << " Euro, " << hotelBookingsCount << " Hotelreservierungen im Wert von " << hotelTotalPrice << " Euro, "
         << trainCount << " Zugbuchungen im Wert von " << trainTotalPrice << " Euro, angelegt" << endl << endl;

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

    double flugBuchungen{0}, flugBuchungenWert{0}, mietwagenBuchungen{0}, mietwagenBuchungenWert{0},
           hotelReservierungen{0}, hotelReservierungenWert{0}, zugBuchungen{0}, zugBuchungenWert{0};
    int itemNumber{};

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
        itemNumber++;

        if ( id.empty() || fromDate.empty() || toDate.empty() )
            throw invalid_argument( "Leeres Attribut in Itemnummer: "  + to_string(itemNumber));

        if ( price < 0 )
            throw invalid_argument( "Price in Itemnummer "+ to_string(itemNumber) +" ist kleiner als 0" );

        //Zugriff auf den Type des jsonObjekts
        QString objectType = jsonObject[ "type" ].toString();

        if ( objectType == "RentalCar" )
        {
            string pickupLocation = jsonObject[ "pickupLocation" ].toString().toStdString();
            string returnLocation = jsonObject[ "returnLocation" ].toString().toStdString();
            string company = jsonObject[ "company" ].toString().toStdString();

            if ( pickupLocation.empty() || returnLocation.empty() || company.empty() )
                throw invalid_argument( "Leeres Attribut in Itemnummer: "  + to_string(itemNumber));

            RentalCarReservation* rentalCarReservation = new RentalCarReservation(id, price, fromDate, toDate, pickupLocation, returnLocation, company);

            bookings.push_back( rentalCarReservation );

            mietwagenBuchungen++;
            mietwagenBuchungenWert+=price;
        }
        else if ( objectType == "Hotel" )
        {
            string hotel = jsonObject[ "hotel" ].toString().toStdString();
            string town = jsonObject[ "town" ].toString().toStdString();

            if ( hotel.empty() || town.empty() )
                throw invalid_argument( "Leeres Attribut in Itemnummer: "  + to_string(itemNumber));

            HotelBooking* hotelBooking = new HotelBooking(id, price, fromDate, toDate, hotel, town);

            bookings.push_back( hotelBooking );

            hotelReservierungen++;
            hotelReservierungenWert+=price;
        }
        else if ( objectType == "Flight" )
        {
            string fromDestination = jsonObject[ "fromDest" ].toString().toStdString();
            string toDestination = jsonObject[ "toDest" ].toString().toStdString();
            string airline = jsonObject[ "airline"].toString().toStdString();

            if ( fromDestination.empty() || toDestination.empty() || airline.empty() )
                throw invalid_argument( "Leeres Attribut in Itemnummer: "  + to_string(itemNumber));

            if ( fromDestination.length() > 3 )
                throw invalid_argument("Das Zeichen des fromDestination in" + to_string(itemNumber) + "ist groesser als 3");

            if ( toDestination.length() > 3 )
                throw invalid_argument("Das Zeichen des toDestination in" + to_string(itemNumber) + "ist groesser als 3");

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
            string arrivalTime = jsonObject[ "arrivalTime" ].toString().toStdString();;
            vector<string> connectingStations;

            if ( fromDestination.empty() || toDestination.empty() || departureTime.empty() || arrivalTime.empty() )
                throw invalid_argument( "Leeres Attribut in Itemnummer: "  + to_string(itemNumber));

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

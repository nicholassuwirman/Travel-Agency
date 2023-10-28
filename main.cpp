#include <iostream>
#include "travelagency.h"
#include "Booking.h"

using namespace std;

int main()
{
    vector<Booking*> bookings;
    TravelAgency travelAgencyObject(bookings);
    string antwort;

    //travelAgencyObject.readBinaryFile();




    try {

        while ( true )
        {
            cout << "JSON- oder Binaerdatei lesen?" << endl;
            cout << "j eingeben fuer JSON-Datei" << endl;
            cout << "b eingeben fuer Binaerdatei" << endl << endl;
            cin >> antwort;
            cout << endl;
            if( antwort == "j" ) travelAgencyObject.readFile();
            else if ( antwort == "b" )
                travelAgencyObject.readBinaryFile();
            else
                cout << "Falsche Eingabe." << endl << endl;
        }

    }
    catch (invalid_argument& e)
    {
        cout << e.what() << endl;
    } catch (exception& e)
    {
        cout << e.what() << endl;
    }catch(...)
    {
        cout << "Unbekannter Fehler";
    }

    return 0;
}

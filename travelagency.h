#ifndef TRAVELAGENCY_H
#define TRAVELAGENCY_H
#include <vector>
#include "Booking.h"
#include <iostream>

#include <fstream>
#include <QVector>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QCoreApplication>
#include <QDebug>
#include <Qstring>
#include <QJsonArray>

using namespace std;

class TravelAgency
{
public:
    TravelAgency(const std::vector<Booking*> &bookings); //todo
    void readFile();
    ~TravelAgency();
    void readBinaryFile();

private:
    std::vector<Booking*> bookings;
};

#endif // TRAVELAGENCY_H

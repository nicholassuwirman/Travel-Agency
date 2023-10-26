TEMPLATE = app
CONFIG += console c++17
CONFIG += app_bundle
CONFIG += qt
QT += widgets


SOURCES += \
        booking.cpp \
        flightbooking.cpp \
        hotelbooking.cpp \
        main.cpp \
        rentalcarreservation.cpp \
        trainticket.cpp \
        travelagency.cpp

HEADERS += \
    booking.h \
    flightbooking.h \
    hotelbooking.h \
    rentalcarreservation.h \
    trainticket.h \
    travelagency.h

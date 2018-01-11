#-------------------------------------------------
#
# Project created by QtCreator 2017-07-06T11:33:26
#
#-------------------------------------------------

QT       += core gui serialport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmartHome
TEMPLATE = app


SOURCES += main.cpp\
        homepagewidget.cpp \
    showpage.cpp \
    areaclickable.cpp \
    myserialport.cpp \
    dht11page.cpp \
    videothread.cpp \
    videowidget.cpp

HEADERS  += homepagewidget.h \
    showpage.h \
    areaclickable.h \
    myserialport.h \
    dht11page.h \
    videothread.h \
    videowidget.h

FORMS    += homepagewidget.ui

RESOURCES += \
    images.qrc

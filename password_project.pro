TEMPLATE = app
CONFIG += c++17
CONFIG -= app_bundle
CONFIG += qt

QT += core widgets
QT += sql

SOURCES += \
        Controleur/passwordcontroleur.cpp \
        Vue/mainwindow.cpp \
        main.cpp

HEADERS += \
    Controleur/passwordcontroleur.h \
    Vue/mainwindow.h \
    main.h

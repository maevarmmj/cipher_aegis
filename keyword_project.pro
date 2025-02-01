TEMPLATE = app
CONFIG += c++17
CONFIG -= app_bundle
CONFIG += qt

QT += core widgets
QT += sql

SOURCES += \
        Controleur/keywordcontroleur.cpp \
        Vue/mainwindow.cpp \
        main.cpp

HEADERS += \
    Controleur/keywordcontroleur.h \
    Vue/mainwindow.h \
    main.h

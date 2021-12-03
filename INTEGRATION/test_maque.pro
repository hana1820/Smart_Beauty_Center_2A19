QT += core gui
QT += sql
QT += printsupport
QT += serialport
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
TEMPLATE = app
DEPENDPATH += .
INCLUDEPATH += .
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Arduino.cpp \
    client.cpp \
    connection.cpp \
    exportexcelobject.cpp \
    mailing.cpp \
    main.cpp \
    mainwindow.cpp \
    rendez_vous.cpp

HEADERS += \
    Arduino.h \
    client.h \
    connection.h \
    exportexcelobject.h \
    mailing.h \
    mainwindow.h \
    rendez_vous.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    Rendez_Vous_fr_FR.ts \
    Rendez_Vous_an_AN.ts \
    Rendez_Vous_tu_TU.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Image.qrc \
    Traduction.qrc

DISTFILES += \
    Rendez_Vous_an_AN.ts \
    Rendez_Vous_tu_TU.ts

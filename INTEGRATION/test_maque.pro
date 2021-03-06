QT += core gui
QT += sql
QT += printsupport
QT += serialport
QT += network charts

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
    carte_fidelite.cpp \
    client.cpp \
    connection.cpp \
    employe.cpp \
    exportexcelobject.cpp \
    mailing.cpp \
    main.cpp \
    mainwindow.cpp \
    produit.cpp \
    rendez_vous.cpp \
    stat_combo.cpp

HEADERS += \
    Arduino.h \
    carte_fidelite.h \
    client.h \
    connection.h \
    employe.h \
    exportexcelobject.h \
    mailing.h \
    mainwindow.h \
    produit.h \
    rendez_vous.h \
    stat_combo.h

FORMS += \
    mainwindow.ui \
    stat_combo.ui

TRANSLATIONS += \
    Français.ts \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Image.qrc \
    Traduction.qrc

DISTFILES += \
    Anglais.ts \
    Espagnol.ts \
    map .png \
    map .png \
    map .png \
    map.qml \
    test.xls

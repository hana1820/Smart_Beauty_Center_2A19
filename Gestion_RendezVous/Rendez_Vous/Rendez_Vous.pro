CONFIG += console

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


# SOURCES : Listes des fichiers sources (*.cpp) du projet.
# HEADERS : Listes des fichiers d'en-tête (*.h) du projet.
# FORMS : Listes des formulaires Qt Designer (*.ui) du projet.
# DEFINES : Listes des symboles définis lors de la compilation du projet.

SOURCES += \
    connection.cpp \
    main.cpp \
    mainwindow.cpp \
    rendez_vous.cpp

HEADERS += \
    connection.h \
    mainwindow.h \
    rendez_vous.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Translations.qrc

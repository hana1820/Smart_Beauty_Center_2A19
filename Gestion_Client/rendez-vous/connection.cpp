#include "connection.h"

bool Connection::createConnection()
{
    bool test=false;

    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("system");
    db.setPassword("QToracle");

    if (db.open())
        test=true;
    return  test;
}

void Connection::closeConnection()
{
    db.close();
}

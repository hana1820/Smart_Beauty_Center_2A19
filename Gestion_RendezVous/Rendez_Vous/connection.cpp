#include "connection.h"

/*
{
    QSqlQuery query(db);
    QString select = "SELECT login from account where login=? and password=?";
    qDebug() << select;
    query.prepare(select);
    query.addBindValue(ui->lelogin->text());
    query.addBindValue(ui->lepassword->text());
    query.exec();
}
*/

bool Connection::createconnection()
{

bool test=false;

db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_Projet2A"); //inverser le nom de la source de données ODBC
db.setUserName("system");//inserer nom de l'utilisateur
db.setPassword("QToracle");//inserer mot de passe de cet utilisateur

if (db.open())
    test=true;
return  test;
}

void Connection::closeConnection()
{
    db.close();
}


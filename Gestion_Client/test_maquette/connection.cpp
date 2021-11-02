#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnection()
{
   bool test=false;
db = QSqlDatabase::addDatabase("QODBC"); //initialisation de l'attribut de db qui sera utilisé dans la méthode create connection;
db.setDatabaseName("test4");//inserer le nom de la source de données ODBC
db.setUserName("system");//inserer nom de l'utilisateur
db.setPassword("@Tampon2001");//inserer mot de passe de cet utilisateur

if (db.open()) test=true;

return  test;
}

void Connection::closeconnection()
{
    db.close();
}

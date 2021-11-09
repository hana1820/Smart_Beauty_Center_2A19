#ifndef CONNEXION_H
#define CONNEXION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery> //The QSqlQuery class provides a means of executing and manipulating SQL statements
class connexion
{
    QSqlDatabase db ;
public:
    connexion();

    bool ouvrirconnexion();
    void fermerconnexion();


};

#endif // CONNEXION_H

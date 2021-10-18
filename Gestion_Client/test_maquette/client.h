#ifndef CLIENT_H
#define CLIENT_H

#include <QString>

class Client
{
public:
    Client();
    void setIdentifiant(QString identifiant);
    void setprenom(QString prenom);
    void setnom(QString nom);
    void setville(QString ville);
    void setadresse(QString ville);


    QString get_Identifiant();
    QString get_Prenom();
    QString get_Nom();
    QString get_Ville();
    QString get_Adresse();

private:
    QString identifiant;
    QString prenom;
    QString nom;
    QString ville;
    QString adresse;
};

#endif // CLIENT_H

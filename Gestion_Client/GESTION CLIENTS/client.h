#ifndef CLIENT_H
#define CLIENT_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>

class Client
{
public:
    //Constructeurs
    Client();
    Client(int,QString, QString,QString,int,int,QString,QString,int);

    //Les Setteurs
    int set_Identifiant(int);
    void set_prenom(QString);
    void set_nom(QString);
    void set_adresse(QString);
    void set_telephone(int);
    void set_email(QString);
    void set_sexe(QString);
    void set_age(int);

    //Les getteurs
    int get_Identifiant();
    QString get_Prenom();
    QString get_Nom();
    QString get_Adresse();
    int get_Telephone();
    int get_Age();
    QString get_Email();
    QString get_Sexe();
    int get_Achat();

    //Les fonctionnalités de base
    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(int);
    bool modifier(int,QString, QString,QString,int,int,QString,QString,int);
    //Les fonctionnalités avancées
    QSqlQueryModel *rechercher(int);
    QSqlQueryModel* Trier(QString );

    int recetteTotale();
    void genereExcel();
    void genererPdf();
    void chat();

private:
    QString prenom,nom,adresse,email,sexe;
   int telephone,age,identifiant,achat;

};

#endif // CLIENT_H

#ifndef CLIENT_H
#define CLIENT_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include <QTableView>
#include <QDate>



class Client
{
public:
    //Constructeurs
    Client();
    Client(int,QString, QString,QString,int,int,QString,QString,int,QDate);
    Client (int,QString,QString,int,QString,int);


    //Les Setteurs : On utilisera que les nécessaires
    void set_Identifiant(int);
    void set_prenom(QString);
    void set_nom(QString);
    void set_adresse(QString);
    void set_id_employe(int);
    void set_email(QString);
    void set_sexe(QString);
    void set_age(int);

    //Les getteurs : On utilisera que les nécessaires
    int get_Identifiant();
    QString get_Prenom();
    QString get_Nom();
    QString get_Adresse();
    int get_id_employe();
    int get_Age();
    QString get_Email();
    QString get_Sexe();
    int get_Achat();

    //Les fonctionnalités de base
    bool ajouter();
    QSqlQueryModel *afficher();
    bool supprimer(int);
    bool modifier();
    //Les fonctionnalités avancées
    QSqlQueryModel *rechercher_id(int);
    QSqlQueryModel *rechercher_nom(QString);
    QSqlQueryModel *rechercher_prenom(QString);
    QSqlQueryModel *rechercher_ville(QString);
    QSqlQueryModel* Trier(QString);
    int recetteTotale(QDate);
    int recetteTotale2(QDate);
    void genereExcel(QTableView *);
    void genererPdf();
    void chat();
    //Les controles de saisie;
    bool testmail(QString);
    bool testNom_prenom_adresse(QString);



private:
   QString prenom,nom,adresse,email,sexe;
   int id_employe,age,identifiant,achat;
   QDate date;


};

#endif // CLIENT_H

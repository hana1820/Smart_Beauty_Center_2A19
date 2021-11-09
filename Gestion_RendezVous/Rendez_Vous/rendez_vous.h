#ifndef RENDEZ_VOUS_H
#define RENDEZ_VOUS_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel> // lire seulement // todkhol lel base de donnee w t affichih
#include <QApplication>
#include <QTranslator>
#include <QInputDialog>

class Rendez_vous
{
private:
    QString date_rdv, heure, periode, salle_rdv, designation;
    int num_rdv,id_client;

public:

    //Constructeurs
    Rendez_vous();
    Rendez_vous(int, int, QString, QString, QString, QString, QString);

    //Getters
    QString getDate(){return date_rdv;}
    QString getHeure(){return heure;}
    QString getPeriode(){return periode;}
    QString getSalle(){return salle_rdv;}
    QString getDesignation(){return designation;}
    int getNumRDV(){return num_rdv;}
    int getIdClient(){return id_client;}

    //Setters
    void setDate(QString d){date_rdv=d;}
    void setHeure(QString h){heure=h;}
    void setPeriode(QString p){periode=p;}
    void setSalle(QString s){salle_rdv=s;}
    void setDesignation(QString des){designation=des;}
    void setNumRDV(int num_rdv){this->num_rdv=num_rdv;}

    // Fonctionnalités de Base relatives à l'entité Rendez_Vous
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int, int, QString, QString, QString, QString, QString);

    // Les Métiers
    QSqlQueryModel * trierParNum_RDV();
    QSqlQueryModel * trierParDate();
    QSqlQueryModel * rechercher(int);
    //void translate();

    /* void mailing(); */
    /* void Excel(); */
    /* void Notifications(); */

};

#endif // RENDEZ_VOUS_H

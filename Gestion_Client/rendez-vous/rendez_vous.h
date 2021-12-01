#ifndef RENDEZ_VOUS_H
#define RENDEZ_VOUS_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QApplication>
#include <QTranslator>
#include <QInputDialog>
#include <QSystemTrayIcon>
#include <QString>
#include <QDate>

class Rendez_Vous
{
private:
    int num_rdv,id_client;
    QString date_rdv, heure, periode, salle_rdv, designation;
public:
    Rendez_Vous();
    Rendez_Vous(int, int, QString, QString, QString, QString, QString);

    //Getters
    int getNumRDV(){return num_rdv;}
    int getIdClient(){return id_client;}
    QString getDate(){return date_rdv;}
    QString getHeure(){return heure;}
    QString getPeriode(){return periode;}
    QString getSalle(){return salle_rdv;}
    QString getDesignation(){return designation;}

    //Setters
    void setNumRDV(int num_rdv){this->num_rdv=num_rdv;}
    void setDate(QString d){date_rdv=d;}
    void setHeure(QString h){heure=h;}
    void setPeriode(QString p){periode=p;}
    void setSalle(QString s){salle_rdv=s;}
    void setDesignation(QString des){designation=des;}

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int, int, QString, QString, QString, QString, QString);

    QSqlQueryModel * trierNum_RDV();
    //QSqlQueryModel * trierDate();
    QSqlQueryModel * rechercher(int);
    void notifications(QString, QString);

    int nb_total_rdv();

};

#endif // RENDEZ_VOUS_H

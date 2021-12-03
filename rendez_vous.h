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
    int getNumRDV();
    int getIdClient();
    QString getDate();
    QString getHeure();
    QString getPeriode();
    QString getSalle();
    QString getDesignation();

    //Setters
    void setNumRDV(int);
    void setDate(QString);
    void setHeure(QString);
    void setPeriode(QString);
    void setSalle(QString);
    void setDesignation(QString);

    bool ajouter_rdv();
    QSqlQueryModel * afficher_rdv();
    bool supprimer_rdv(int);
    bool modifier_rdv(int, int, QString, QString, QString, QString, QString);

    QSqlQueryModel * trierNum_RDV();
    //QSqlQueryModel * trierDate();
    QSqlQueryModel * rechercher_rdv(int);
    void notifications(QString, QString);

    int nb_total_rdv();

};

#endif // RENDEZ_VOUS_H

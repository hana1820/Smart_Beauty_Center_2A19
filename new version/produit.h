#ifndef PRODUIT_H
#define PRODUIT_H

#include <QSqlQuery>
#include <QSqlQueryModel>

class produit
{
public:
    produit();
    produit (QString,QString,QString,QString,int,double);

    bool ajouter();
    bool modifier(QString);
     QSqlQueryModel * afficher();
      bool supprimer(QString);



    QString reference,nom,type,nature;
    int quantite;
    double prix;
};

#endif // PRODUIT_H

#ifndef CARTE_FIDELITE_H
#define CARTE_FIDELITE_H

#include <QSqlQuery>
#include <QSqlQueryModel>

class carte_fidelite
{
public:
    carte_fidelite();

    carte_fidelite (QString,QString,int);

    bool ajouter();
    bool modifier(QString, double);
     QSqlQueryModel * afficher();
      bool supprimer(QString);
      int calcul_point(double);
      int get_old_fid(QString);




    QString id,id_client;
    int point;
};

#endif // CARTE_FIDELITE_H

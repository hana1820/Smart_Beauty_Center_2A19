#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QSqlQueryModel>
#include <QString>
#include <QDate>
//test
//test
class Employe
{

public:
    Employe();
    Employe(int,int,QString,QString,QString,QString,QString,QString);
         int getid();
         int gettelephone();
         QString getnom();
         QString getprenom();
         QString getadresse();
         QString getposte();
         QString getemail();
         void setid(int);
         void settelephone(int);
         void setnom(QString);
         void setprenom(QString);
         void setadresse(QString);
         void setposte(QString);
         void setemail(QString);
         bool ajouter();
         QSqlQueryModel *afficher();
         bool supprimer(int);
         bool modifier(int id,int telephone,QString nom,QString prenom,QString adresse,QString poste,QString email);
         QSqlQueryModel * sort;
             QSqlQueryModel *rechercher(int) ;
             QSqlQueryModel *sort_employe();
             QSqlQueryModel *fusion();
             double Statistique(QString) ;
             double Statistiquee(QString  , QString) ;

private:
         int id,telephone;
         QString nom,prenom,adresse,poste,email,sr;
         QDate datedebut ,datefin ;


};
#endif // EXPORTEXCELOBJECT_H

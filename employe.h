#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QSqlQueryModel> //provides a read-only data model for SQL result sets
#include <QString>

class Employe
{
public://méthode disponible à partir de n'importe où, d'autres classes et instances de l'objet.
    Employe();
    Employe(int,int,QString,QString,QString,QString,QString);
         int getid();//acceder aux donnees
         int gettelephone();
         QString getnom();
         QString getprenom();
         QString getadresse();
         QString getposte();
         QString getemail();
         void setid(int);//modifier les donnees
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
         QSqlQueryModel * sort_employe() ;
             QSqlQueryModel *rechercher(int) ;
private: //méthode soit visible dans sa propre classe uniquement.
         int id,telephone;
         QString nom,prenom,adresse,poste,email;


};


#endif // EMPLOYE_H

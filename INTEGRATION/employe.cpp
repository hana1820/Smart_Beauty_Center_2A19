#include "employe.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>


Employe::Employe()
{
    id=0;
    telephone=0;
    nom=" ";
    prenom=" ";
    adresse=" ";
    poste=" ";
    email=" ";


}
Employe::Employe(int id,int telephone,QString nom,QString prenom,QString adresse,QString poste,QString email,QString sr)
 {this->id=id;
    this->telephone=telephone;
    this->nom=nom ;
    this->prenom=prenom;
    this->adresse=adresse ;
    this->poste=poste;
    this->email=email;}
 int Employe::getid() {return id ;}
 int Employe::gettelephone() {return telephone ;}
 QString Employe::getnom() {return nom ;}
 QString Employe::getprenom() {return prenom ;}
 QString Employe::getadresse() {return adresse ;}
 QString Employe::getposte() {return poste;}
 QString Employe::getemail() {return email ;}
 void Employe::setid(int id) {this->id=id;}
 void Employe::settelephone(int telephone) {this->telephone=telephone;}
 void Employe::setnom(QString nom) {this->nom=nom;}
 void Employe::setprenom(QString prenom) {this->prenom=prenom;}
 void Employe::setadresse(QString adresse) {this->adresse=adresse;}
 void Employe::setposte(QString poste) {this->poste=poste;}
 void Employe::setemail(QString email) {this->email=email;}

 bool Employe::ajouter()
 {

     QString id_string=QString::number(id);
     QString telephone_string=QString::number(telephone);
      QSqlQuery query;
query.prepare("INSERT INTO a_sbc_employe (id_emp,nom,prenom,adresse,poste,email,telephone) "
                         "VALUES (:id, :nom, :prenom, :adresse, :poste, :email, :telephone)");


           query.bindValue(0,id_string);
           query.bindValue(1,nom);
           query.bindValue(2,prenom);
           query.bindValue(3,adresse);
           query.bindValue(4,poste);
           query.bindValue(5,email);
           query.bindValue(6,telephone_string);
           return query.exec();
 }
 bool Employe::supprimer(int id )
 {

      QSqlQuery query;
           query.prepare("Delete from a_sbc_employe where id_emp=:id");
           query.bindValue(0,id);

           return query.exec();

 }
 QSqlQueryModel* Employe::afficher()
 {
    QSqlQueryModel* model=new QSqlQueryModel();
         model->setQuery("SELECT* FROM a_sbc_employe");

         model->setHeaderData(0, Qt::Horizontal,QObject:: tr("ID_EMP"));
         model->setHeaderData(1, Qt::Horizontal,QObject:: tr("NOM"));
         model->setHeaderData(2, Qt::Horizontal,QObject:: tr("PRENOM"));
         model->setHeaderData(3, Qt::Horizontal,QObject:: tr("ADRESSE"));
         model->setHeaderData(4, Qt::Horizontal,QObject:: tr("POSTE"));
         model->setHeaderData(5, Qt::Horizontal,QObject:: tr("EMAIL"));
         model->setHeaderData(6, Qt::Horizontal,QObject:: tr("TELEPHONE"));
 return model   ;
 }

 bool Employe::modifier(int id,int telephone,QString nom,QString prenom,QString adresse,QString poste,QString email)

 {

      QString id_string=QString::number(id);
      QString telephone_string=QString::number(telephone);

      QSqlQuery query;
         query.prepare("update a_sbc_employe set nom=:nom,prenom=:prenom,adresse=:adresse,poste=:poste,email=:email,telephone=:telephone where id_emp=:id");

         query.bindValue(":id",id_string); /*bind value : passer la valeur et la variable */
         query.bindValue(":nom",nom);      /* query : error branche vide */
         query.bindValue(":prenom",prenom);
         query.bindValue(":adresse",adresse);
         query.bindValue(":poste",poste);
         query.bindValue(":email",email);
         query.bindValue(":telephone",telephone_string);

 return query.exec();
 }
 //
 QSqlQueryModel *Employe::sort_employe()
 {
     QSqlQueryModel * model=new QSqlQueryModel();

     model->setQuery("select * from  a_sbc_employe ORDER BY id_emp");

     model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID_EMP"));
     model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM"));
     model->setHeaderData(2, Qt::Horizontal,QObject::tr("PRENOM"));
     model->setHeaderData(3, Qt::Horizontal,QObject::tr("ADRESSE"));
     model->setHeaderData(4, Qt::Horizontal,QObject::tr("POSTE"));
     model->setHeaderData(5, Qt::Horizontal,QObject::tr("EMAIL"));
     model->setHeaderData(6, Qt::Horizontal,QObject::tr("TELEPHONE"));


     return model;
 }
 QSqlQueryModel * Employe::rechercher(int ide)
 {
 QSqlQueryModel * model= new QSqlQueryModel();
 QSqlQuery query;
 query.prepare("SELECT * from a_sbc_employe where ID_EMP= :id");
 query.bindValue(":id",ide);

     query.exec();
 model->setQuery(query);
 model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID_EMP"));
 model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM"));
 model->setHeaderData(2, Qt::Horizontal,QObject::tr("PRENOM"));
 model->setHeaderData(3, Qt::Horizontal,QObject::tr("ADRESSE"));
 model->setHeaderData(4, Qt::Horizontal,QObject::tr("POSTE"));
 model->setHeaderData(5, Qt::Horizontal,QObject::tr("EMAIL"));
 model->setHeaderData(6, Qt::Horizontal,QObject::tr("TELEPHONE"));


 return model ;
 }


  QSqlQueryModel *Employe::fusion()
  { QSqlQueryModel *model=new QSqlQueryModel();
      model->setQuery("select SALLE_RDV from A_SBC_RENDEZVOUS");
      return model ;
}
  double Employe::Statistiquee(QString db , QString ds)
  {
      QSqlQuery query;
          int s=0 ;
             query.prepare("SELECT SUM (salaire) from a_sbc_employe where datedebut >=TO_DATE(:db,'YYYY-MM-DD')  and datefin <= TO_DATE(:ds,'YYYY-MM-DD')");
            // query.bindValue(":id_emp",id);
             query.bindValue(":db",db) ;
             query.bindValue(":ds",ds) ;
             if(query.exec())
              {
                  while(query.next())
                      s=query.value(0).toInt();

              }
              else
                 return 0;

          return s;

  }

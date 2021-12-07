#include "produit.h"

produit::produit()
{

}

produit::produit(QString s1,QString s2,QString s3,QString s4,int x1, double x2){

    reference=s1;
    nom=s2;
    type=s3;
    nature = s4;
    quantite=x1;
    prix=x2;

}


bool produit::ajouter(){

    QSqlQuery query;


    query.prepare("INSERT INTO A_SBC_PRODUIT (reference,nom,type,nature,quantite,prix,prix_fid)" "VALUES (:reference,:nom,:type,:nature,:quantite,:prix,:prix_fid)");

    query.bindValue(":reference", reference);
    query.bindValue(":nom",nom);
    query.bindValue(":type",type);
    query.bindValue(":nature",nature);
    query.bindValue(":quantite",quantite);
    query.bindValue(":prix",prix);
    query.bindValue(":prix_fid",prix*100);


    return    query.exec();

}

bool produit::modifier(QString selected){

    QSqlQuery query;


    query.prepare(" UPDATE A_SBC_PRODUITS SET  nom=:nom, type=:type, nature=:nature, quantite=:quantite, prix=:prix, prix_fid=:prix_fid"
                  " where reference= :reference");
    query.bindValue(":reference", selected);
    query.bindValue(":nom",nom);
    query.bindValue(":type",type);
    query.bindValue(":nature",nature);
    query.bindValue(":quantite",quantite);
    query.bindValue(":prix",prix);
    query.bindValue(":prix_fid",prix*100);



    return    query.exec();

}

 QSqlQueryModel * produit::afficher(){

     QSqlQueryModel * modal=new QSqlQueryModel();
     modal->setQuery("SELECT * FROM A_SBC_PRODUITS");

     return modal;

 }
  bool produit::supprimer(QString selected){

      QSqlQuery query;
      query.prepare("Delete from A_SBC_PRODUITS where reference = :reference ");
      query.bindValue(":reference", selected);
      return    query.exec();


  }

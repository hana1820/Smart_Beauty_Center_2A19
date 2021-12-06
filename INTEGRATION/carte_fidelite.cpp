#include "carte_fidelite.h"


carte_fidelite::carte_fidelite()
{

}

carte_fidelite::carte_fidelite(QString s1,QString s2, int x1){

    id=s1;
    id_client=s2;
    point=x1;

}

//dans la fonction ajout client -> si on a un nouveau client lors de la creation il aura une carte
bool carte_fidelite::ajouter(){

    QSqlQuery query;


    query.prepare("INSERT INTO carte_fidelite (id,id_client,point) VALUES (:reference,:nom,:point)");

    query.bindValue(":id", id);
    query.bindValue(":id_client",id_client);
    query.bindValue(":point",0);

    return    query.exec();

}


//dans la fonction modifier client -> si le montant achat est modifié le nombre de points de fid dans la carte sera modifier aussi
// selected ici , c'est l'id_client selectionné
// achat ici , c'est le montant ajouté au montant total apres l'operation

bool carte_fidelite::modifier(QString selected, double achat){

    QSqlQuery query;


    query.prepare(" UPDATE carte_fidelite SET point=:point"
                  " where id_client= :id_client");
    query.bindValue(":id_client",selected);
    query.bindValue(":point",get_old_fid(selected)+calcul_point(achat));


    return    query.exec();

}

 QSqlQueryModel * carte_fidelite::afficher(){

     QSqlQueryModel * modal=new QSqlQueryModel();
     modal->setQuery("SELECT * FROM carte_fidelite");

     return modal;

 }
  bool carte_fidelite::supprimer(QString selected){

      QSqlQuery query;
      query.prepare("Delete from carte_fidelite where id = :id ");
      query.bindValue(":id", selected);
      return    query.exec();


  }


  // recupere le montant d'achat du client et le transforme en points fid
  int carte_fidelite::calcul_point(double achat){

      int p=0;

      p= static_cast<int>(achat);

      return  p;


  }


  //  recupere les points existants du client selectionne
  int carte_fidelite::get_old_fid(QString selected){

      QSqlQuery query;
      int r=0;

      query.prepare("select point from carte_fidelite where id_client = :id_client ");

      query.bindValue(":id_client",selected);
        query.exec();

      while (query.next())
          query.value(0).toInt();

      return  r;
  }




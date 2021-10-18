#include "client.h"

Client::Client()
{
identifiant="";
prenom="";
nom="";
ville="";
adresse="";
}

//Les setteurs
 void Client::setIdentifiant(QString identifiant)
 {
     this->identifiant=identifiant;
 }

 void Client::setprenom(QString prenom)
 {
     this->prenom=prenom;
 }

 void Client::setnom(QString nom)
 {
     this->nom=nom;
 }

 void Client::setville(QString ville)
 {
     this->ville=ville;
 }

 void Client::setadresse(QString adresse)
 {
     this->adresse=adresse;
 }
//Les getters

 QString Client::get_Identifiant()
 {
     return identifiant;
 }

 QString Client::get_Prenom()
 {
     return prenom;
 }

 QString Client::get_Nom()
 {
     return nom;
 }

 QString Client::get_Ville()
 {
     return ville;
 }

 QString Client::get_Adresse()
 {
     return adresse;
 }

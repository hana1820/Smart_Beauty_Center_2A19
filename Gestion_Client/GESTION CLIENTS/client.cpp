 #include "client.h"
#include <QSqlQuery>
#include <QtDebug>



Client::Client()
{
    identifiant=0;
    prenom="";
    nom="";
    adresse="";
    telephone=0;
    age=0;
    email="";
    sexe="";
    achat=0;
}
Client:: Client(int identifiant,QString prenom, QString nom, QString adresse,int telephone, int age,QString email,QString sexe,int achat)
{
    this->identifiant=identifiant;
    this->prenom=prenom;
    this->nom=nom;
    this->adresse=adresse;
    this->telephone=telephone;
    this->age=age;
    this->email=email;
    this->sexe=sexe;
    this->achat=achat;
}

/*n LES SETTEURS
int set_Identifiant(int);
void set_prenom(QString prenom);
void set_nom(QString nom);
void set_adresse(QString adresse);
void set_telephone(int  telephone);
void set_email(QString email);
void set_sexe(QString sexe);
void set_age(int );
*/

int Client::get_Identifiant(){return identifiant;}
QString Client::get_Prenom(){return prenom;}
QString Client::get_Nom(){return nom;}
QString Client::get_Adresse(){return adresse;}
int Client::get_Telephone(){return telephone;}
int Client::get_Age(){return age;}
QString Client::get_Email(){return email;}
QString Client::get_Sexe(){return sexe;}
int Client::get_Achat(){return achat;}

bool Client::ajouter()
{

    QSqlQuery query;
    QString identifiant_string = QString::number(identifiant);
    QString telephone_string=QString::number(telephone);
    QString age_string=QString::number(age);
    QString achat_string=QString::number(achat);


    //prepare() prend la requete ne paramètre pour la préparer à l'éxécution

    query.prepare("insert into CLIENT (IDENTIFIANT, NOM, PRENOM, ADRESSE, TELEPHONE, AGE, EMAIL, SEXE, ACHAT)"
            "values(:identifiant, :nom, :prenom, :adresse, :telephone, :age, :email, :sexe, :achat)");

    //Creatino des variables liees

    query.bindValue(":identifiant",identifiant_string);
    query.bindValue(":prenom",prenom);
    query.bindValue(":nom",nom);
    query.bindValue(":adresse",adresse);
    query.bindValue(":telephone",telephone_string);
    query.bindValue(":age",age_string);
    query.bindValue(":email",email);
    query.bindValue(":sexe",sexe);
    query.bindValue(":achat",achat_string);

  return query.exec(); //exec() envoie la requete pour l'exécuter.
}

QSqlQueryModel *Client::afficher()
{
QSqlQueryModel *model=new QSqlQueryModel();

model->setQuery("select * from client");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("ADRESSE"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("TEL"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("AGE"));
model->setHeaderData(6,Qt::Horizontal,QObject::tr("EMAIL"));
model->setHeaderData(7,Qt::Horizontal,QObject::tr("SEXE"));
return model;
}


bool ::Client::supprimer(int id)
{
    QSqlQuery query;
    QString id_string=QString::number(id);

    query.prepare("Delete from client where identifiant= :id");
    query.bindValue(":id",id_string);

    return query.exec();

}



bool Client::modifier(int identifiant, QString nom, QString prenom, QString adresse,int telephone,int age, QString email, QString sexe,int achat)
{
    QSqlQuery query;


    QString identifiant_string = QString::number(identifiant);
    QString telephone_string=QString::number(telephone);
    QString age_string=QString::number(age);
    QString achat_string=QString::number(achat);


    query.prepare("update CLIENT set IDENTIFIANT=:identifiant ,NOM=:nom ,PRENOM=:prenom ,ADRESSE=:adresse,TELEPHONE=:telephone,AGE=:age,EMAIL=:email,SEXE=:sexe,ACHAT=:achat where IDENTIFIANT= :identifiant ");
    query.bindValue(":identifiant",identifiant_string);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":adresse", adresse);
    query.bindValue(":telephone",telephone_string);
    query.bindValue(":age",age_string);
    query.bindValue(":email",email);
    query.bindValue(":sexe",sexe);
    query.bindValue(":achat",achat_string);

    return    query.exec();


}

QSqlQueryModel * Client::rechercher(int id)   //OK
{

    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery query;

    QString id_string=QString::number(id);


    query.prepare("Select * from client where identifiant=:id");
    query.bindValue(":id",id_string);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));

    return model;
}

QSqlQueryModel* Client::Trier(QString critere)
{
    QSqlQueryModel* model=new QSqlQueryModel() ;
    QSqlQuery *query=new QSqlQuery;
    query->prepare(critere) ;
    query->exec() ;
    model->setQuery(*query) ;

 return model;
}



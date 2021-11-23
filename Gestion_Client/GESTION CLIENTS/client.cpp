#include "client.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QtDebug>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextStream>
#include <QPainter>

//DEVELOPPEMENT DES CONSTRUCTEURS ::::: @KEITA CODE
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
Client:: Client(int identifiant,QString prenom, QString nom, QString adresse,int telephone, int age,QString email,QString sexe,int achat,QDate date)
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
    this->date=date;
}
Client:: Client (int identifiant,QString prenom,QString nom,int telephone,QString adresse,int montant)
{
    this->identifiant=identifiant;
    this->prenom=prenom;
    this->nom=nom;
    this->telephone=telephone;
    this->adresse=adresse;
    this->achat=montant;
}

//DEVELOPPEMENT DES SETTEURS ::::: @KEITA CODE
void Client::set_Identifiant(int identifiant)
{
    this->identifiant=identifiant;
}
void Client::set_prenom(QString prenom)
{this->prenom=prenom;}
void Client::set_nom(QString nom)
{this->nom=nom;}
void Client::set_adresse(QString adresse)
{this->adresse=adresse;}
void Client::set_telephone(int  telephone)
{this->telephone=telephone;}
void Client::set_email(QString email)
{this->email=email;}
void Client::set_sexe(QString sexe)
{this->sexe=sexe;}
void Client::set_age(int age)
{this->age=age;}

//DEVELOPPEMENT DES GETTEURS ::::: @KEITA CODE
int Client::get_Identifiant()
{return identifiant;}
QString Client::get_Prenom()
{return prenom;}
QString Client::get_Nom()
{return nom;}
QString Client::get_Adresse()
{return adresse;}
int Client::get_Telephone()
{return telephone;}
int Client::get_Age()
{return age;}
QString Client::get_Email()
{return email;}
QString Client::get_Sexe()
{return sexe;}
int Client::get_Achat()
{return achat;}

//LES FONCTIONNALITES DE BASE ( CONTROLE DE SAISIE ET CRUDS) ::::: @KEITA CODE
bool Client::testmail(QString mail)
{
    int test=0;
    int position=0;

    if(mail[0]=='@') //le premier caractère est un @
    {
        return false;
    }
    for(int i = 1; i < mail.size(); i++)
    {
        if(mail[i]=='@')
        {
            test++;
            position=i; //recupérer la position du @

        }
    }
    if(test!=1) //il y'a plusieurs @ ou il n'ya pas de @
    {
        return false;
    }

    if(mail[position+1]=='.') //on a le piont juste après le @
    {
        return false;
    }
    for(int i = position+1; i < mail.size(); i++)
    {

        if(mail[i]=='.')
        {
            if(mail.size()>i+1) //S'il y'a des caractère après le point
                return true;
        }
    }
    return false;
}
bool Client::testNom_prenom_adresse(QString a)
{
    for(int i=0;i<a.size();i++)
    {
        if(a.at(i)=='&'||a.at(i)=='~'||a.at(i)=='#'||a.at(i)=='{'||a.at(i)=='['||a.at(i)=='|'||a.at(i)=='@'
                ||a.at(i)==']'||a.at(i)=='}'||a.at(i)=='!'||a.at(i)=='?'||a.at(i)=='*'||a.at(i)=='%'||a.at(i)=='$'
               )
        {
            return false;
        }

    }

    return true;
}
bool Client::ajouter()
{

    QSqlQuery query;
    QString identifiant_string = QString::number(identifiant);
    QString telephone_string=QString::number(telephone);
    QString age_string=QString::number(age);
    QString achat_string=QString::number(achat);

    //prepare() prend la requete en paramètre pour la préparer à l'éxécution

    query.prepare("insert into A_SBC_CLIENT (IDENTIFIANT, NOM, PRENOM, ADRESSE, TELEPHONE, AGE, MAIL, SEXE, ACHAT, DATEC)"
            "values(:identifiant, :nom, :prenom, :adresse, :telephone, :age, :email, :sexe, :achat, :date)");


    query.bindValue(":identifiant",identifiant_string);
    query.bindValue(":prenom",prenom);
    query.bindValue(":nom",nom);
    query.bindValue(":adresse",adresse);
    query.bindValue(":telephone",telephone_string);
    query.bindValue(":age",age_string);
    query.bindValue(":email",email);
    query.bindValue(":sexe",sexe);
    query.bindValue(":achat",achat_string);
    query.bindValue(":date",date);

  return query.exec(); //exec() envoie la requete pour l'exécuter.
}
QSqlQueryModel *Client::afficher()
{

QSqlQueryModel *model=new QSqlQueryModel();

model->setQuery("select * from A_SBC_CLIENT");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("ADRESSE"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("TEL"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("AGE"));
model->setHeaderData(6,Qt::Horizontal,QObject::tr("MAIL"));
model->setHeaderData(7,Qt::Horizontal,QObject::tr("SEXE"));
model->setHeaderData(8,Qt::Horizontal,QObject::tr("DATE"));
return model;
}
bool ::Client::supprimer(int id)
{
    QSqlQuery query;
    QString id_string=QString::number(id);
    query.prepare("Delete from A_SBC_CLIENT where identifiant= :id");
    query.bindValue(":id",id_string);

    return query.exec();

}
bool Client::modifier()
{
    QSqlQuery query;


    QString identifiant_string = QString::number(identifiant);
    QString telephone_string=QString::number(telephone);
    QString age_string=QString::number(age);
    QString achat_string=QString::number(achat);


    query.prepare("update A_SBC_CLIENT set IDENTIFIANT=:identifiant ,NOM=:nom ,PRENOM=:prenom ,ADRESSE=:adresse,TELEPHONE=:telephone,AGE=:age,MAIL=:email,SEXE=:sexe,ACHAT=:achat, DATEC=:date where IDENTIFIANT= :identifiant ");

    query.bindValue(":identifiant",identifiant_string);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":adresse", adresse);
    query.bindValue(":telephone",telephone_string);
    query.bindValue(":age",age_string);
    query.bindValue(":email",email);
    query.bindValue(":sexe",sexe);
    query.bindValue(":achat",achat_string);
    query.bindValue(":date",date);

    return    query.exec();


}

//LES FONCTIONNALITES AVANCEES ::::: @KEITA CODE
QSqlQueryModel * Client::rechercher_id(int id)
{

    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery query;

    QString id_string=QString::number(id);

    query.prepare("Select * from A_SBC_CLIENT where identifiant=:id");
    query.bindValue(":id",id_string);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));

    return model;
}
QSqlQueryModel * Client::rechercher_nom(QString nom)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery query;

    query.prepare("Select * from A_SBC_CLIENT where nom=:nom");
    query.bindValue(":nom",nom);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));

    return model;
}
QSqlQueryModel * Client::rechercher_prenom(QString prenom)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery query;

    query.prepare("Select * from A_SBC_CLIENT where prenom=:prenom");
    query.bindValue(":prenom",prenom);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));

    return model;
}
QSqlQueryModel * Client::rechercher_ville(QString ville)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    QSqlQuery query;

    query.prepare("Select * from A_SBC_CLIENT where adresse=:ville");
    query.bindValue(":ville",ville);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));

    return model;
}
QSqlQueryModel * Client::Trier(QString critere)
{
    //Pour Optimisation, On mettra  critere de tri dans la chaine 'critere'::::: @KEITA CODE
    QSqlQueryModel* model=new QSqlQueryModel() ;
    QSqlQuery *query=new QSqlQuery;
    query->prepare(critere) ;
    query->exec() ;
    model->setQuery(*query) ;

    return model;
}
int Client::recetteTotale(QDate date)
{
    QSqlQuery query;

    int somme = 0;
    query.prepare("select * from A_SBC_CLIENT");

    if (query.exec())
    {
        while (query.next())
            if(query.value(9)==date)
            somme +=query.value(8).toInt();
        //8 representre la colonne qui contient le montant des achats ::::: @KEITA CODE
    }

    return somme;

}
int Client::recetteTotale2(QDate date)
{
            QSqlQuery query;

            int somme = 0;
            query.prepare("select * from A_SBC_CLIENT");

            if (query.exec())
            {
                while (query.next())
                    if(query.value(9)==date)
                    somme +=query.value(8).toInt();
                //8 representre la colonne qui contient le montant des achats ::::: @KEITA CODE
            }

            return somme;
}
void Client::genereExcel(QTableView *table)
{

         QString filters("CSV files (.csv);;All files (.*)");
         QString defaultFilter("CSV files (*.csv)");
         QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                                  filters, &defaultFilter);
               QFile file(fileName);

               QAbstractItemModel *model =  table->model();
               if (file.open(QFile::WriteOnly | QFile::Truncate)) {
                   QTextStream data(&file);
                   QStringList strList;
                   for (int i = 0; i < model->columnCount(); i++) {
                       if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                           strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                       else
                           strList.append("");
                   }
                   data << strList.join(";") << "\n";
                   for (int i = 0; i < model->rowCount(); i++) {
                       strList.clear();
                       for (int j = 0; j < model->columnCount(); j++) {

                           if (model->data(model->index(i, j)).toString().length() > 0)
                               strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                           else
                               strList.append("");
                       }
                       data << strList.join(";") + "\n";
                   }
                   file.close();
                   QMessageBox::information(nullptr, QObject::tr("GENERATION EXCEL"),
                                             QObject::tr("GENERATION REALISEE AVEC SUCCES\n"
                                                         "Click OK to exit."), QMessageBox::Ok);
               }

}
void Client::genererPdf()
{
    QPdfWriter pdf("C:/Users/balla/Desktop/TRAVAIL C++/Pdf.pdf");
    QPainter painter(&pdf);

    painter.setPen(Qt::black);
    painter.setFont(QFont("Gabriola", 50));
    painter.drawText(1600,4000,"RECU DE PAIEMENT");
    painter.setFont(QFont("Gabriola", 16));
    painter.drawText(200,400,"AVENUE BOURGUIBA");
    painter.drawText(200,900,"BP:005");
    painter.drawText(200,1400,"Mail:magictouch@gmail.com");
    painter.drawText(200,1900,"TEL:51010101");
    painter.drawText(200,2400,"BEAUTY CENTER MAGIC TOUCH");

    painter.setPen(Qt::black);

    painter.setFont(QFont("Cambria", 50));
    //painter.drawText(1100,2000,afficheDC);
    painter.drawRect(100,100,7300,2600);

    painter.drawPixmap(QRect(7500,70,2000,2600),QPixmap("C:/Users/balla/Desktop/TRAVAIL C++/logo2.png"));
    painter.drawRect(0,3000,9600,500);
    painter.setFont(QFont("Cambria", 17));
    painter.drawText(200,5000,"Je soussigné Mr Balla moussa Keita,Responsable des clients"
                              " Certifie avoir");
    painter.drawText(200,5500,"reçu un paiement en DT de la part du client dont les infomations"
                              " suivent:");
    painter.drawText(200,6300,"ID:");
    painter.drawText(200,7100,"NOM:");
    painter.drawText(200,7900,"PRENOM:");
    painter.drawText(6000,6300,"CONTACT:");
    painter.drawText(6000,7100,"ADRESSE:");
    painter.drawText(6000,7900,"MONTANT:");



   QString id_string=QString::number(identifiant);
   QString telephone_string=QString::number(telephone);
   QString montant_string=QString::number(achat);
    painter.setFont(QFont("Courier New", 18));
        painter.drawText(2400,6300,id_string);
        painter.drawText(2400,7100,nom);
        painter.drawText(2400,7900,prenom);
        painter.drawText(7500,6300,telephone_string);
        painter.drawText(7500,7100,adresse);
        painter.drawText(7500,7900,montant_string);
        painter.setPen(Qt::red);

        painter.setFont(QFont("Cambria", 30));

         painter.setFont(QFont("Cambria", 14));
        painter.setPen(Qt::green);
        painter.drawText(1300,12800,"LA DIRECTION DE MAGIC TOUCH VOUS REMERCIE DE VOTRE FIDELITE");
         painter.setPen(Qt::black);
         painter.drawText(6000,10500,"RESPONSABLE DES CLIENTS");

// QMessageBox:: question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
    if (1)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/balla/Desktop/TRAVAIL C++/Pdf.pdf"));
        painter.end();
    }
   else
    {
        painter.end();
    }
}

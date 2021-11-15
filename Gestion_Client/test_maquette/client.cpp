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

bool Client::testmail(QString mail){
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

    if(mail[position+1]=='.') //on a le pont juste après le @
    {
        return false;
    }
    for(int i = position+1; i < mail.size(); i++)
    {

        if(mail[i]=='.')
        {
            if(mail.size()>i+1)
                return true;
        }
    }
    return false;
}

bool Client::testNom_prenom_adresse(QString a) //Pour éviter les caracètre spéciaux
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


    //prepare() prend la requete ne paramètre pour la préparer à l'éxécution

    query.prepare("insert into A_SBC_CLIENT (IDENTIFIANT, NOM, PRENOM, ADRESSE, TELEPHONE, AGE, MAIL, SEXE, ACHAT)"
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

model->setQuery("select * from A_SBC_CLIENT");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("ADRESSE"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("TEL"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("AGE"));
model->setHeaderData(6,Qt::Horizontal,QObject::tr("MAIL"));
model->setHeaderData(7,Qt::Horizontal,QObject::tr("SEXE"));
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


    query.prepare("update A_SBC_CLIENT set IDENTIFIANT=:identifiant ,NOM=:nom ,PRENOM=:prenom ,ADRESSE=:adresse,TELEPHONE=:telephone,AGE=:age,MAIL=:email,SEXE=:sexe,ACHAT=:achat where IDENTIFIANT= :identifiant ");
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


    query.prepare("Select * from A_SBC_CLIENT where identifiant=:id");
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

int Client::recetteTotale()
{
    QSqlQuery query;

    int somme = 0;
    query.prepare("select * from A_SBC_CLIENT");

    if (query.exec())
    {
        while (query.next())
            somme +=query.value(8).toInt();
    }

    return somme;

}

//ENCOURS
void Client::genereExcel()
{
    /*
    QTableView *table;
             //  table = ui->tableView_2;

               QString filters("XLSX files (.xlsx);;All files (.*)");
               QString defaultFilter("XLSX files (*.xlsx)");
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
                   QMessageBox::information(nullptr, QObject::tr("Export excel"),
                                             QObject::tr("Export avec succes .\n"
                                                         "Click OK to exit."), QMessageBox::Ok);
               }
               */
}
//ENCOURS
void Client::genererPdf(int identifiant,QString nom,QString prenom,int telephone,QString adresse, int montant)
{
    /*QString nomFichier = QFileDialog::getSaveFileName(0, QString::fromUtf8("Générer PDF"), QCoreApplication::applicationDirPath(), "*.pdf");

    int id(20);
    if (!nomFichier.isEmpty())
    {
        if (QFileInfo(nomFichier).suffix().isEmpty())
            nomFichier.append(".pdf");

        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(nomFichier);
        printer.setOrientation(QPrinter::Portrait);
        printer.setPaperSize(QPrinter::A4);
        printer.setPageSize(QPrinter::A4);
        printer.setPageMargins(15,15,15,15,QPrinter::Millimeter);

        qDebug() << "Page px :" << printer.pageRect() << printer.paperRect();
        qDebug() << "Page mm :" << printer.pageRect(QPrinter::Millimeter) << printer.paperRect(QPrinter::Millimeter);
        qreal left, top, right, bottom;
        printer.getPageMargins(&left, &top, &right, &bottom, QPrinter::DevicePixel);
        qDebug() << "Marges px :" << left << top << right << bottom;
        printer.getPageMargins(&left, &top, &right, &bottom, QPrinter::Millimeter);
        qDebug() << "Marges mm :" << left << top << right << bottom;

        QPainter painter(&printer);


            painter.drawText(0, printer.pageRect().y()*2, QString::fromUtf8("FACTURE N001"));
            painter.drawText(1, printer.pageRect().y()*3, QString::fromUtf8("IDENTIFIANT:"));
            painter.drawText(3, printer.pageRect().y()*4, QString::fromUtf8("NOM:"));
            painter.drawText(4, printer.pageRect().y()*5, QString::fromUtf8("PRENOM"));


            // Une nouvelle page
            printer.newPage();
            painter.drawText(0, printer.pageRect().y()*3, QString::fromUtf8("Ligne 2"));
    }*/

    //QDateTime datecreation = date.currentDateTime();
    //QString afficheDC = "Date de Creation PDF : " + datecreation.toString() ;

    QPdfWriter pdf("C:/Users/balla/Desktop/TRAVAIL C++/Pdf.pdf");
    QPainter painter(&pdf);
    int i = 4000;
    painter.setPen(Qt::black);
    painter.setFont(QFont("Gabriola", 50));
    painter.drawText(1600,4000,"RECU DE PAIEMENT");
    painter.setFont(QFont("Gabriola", 16));
    painter.drawText(200,400,"AVENUE BOURGUIBA");
    painter.drawText(200,900,"BP:005");
    painter.drawText(200,1400,"Mail:magictouch@gmail.com");
    painter.drawText(200,1900,"TEL:51010101");
    painter.drawText(200,2400,"BS MAGIC TOUCH");

    painter.setPen(Qt::black);

    painter.setFont(QFont("Cambria", 50));
    //painter.drawText(1100,2000,afficheDC);
    painter.drawRect(100,100,7300,2600);

    painter.drawPixmap(QRect(7500,70,2000,2600),QPixmap("C:/Users/balla/Desktop/TRAVAIL C++/logo2.png"));
    painter.drawRect(0,3000,9600,500);
    painter.setFont(QFont("Cambria", 17));
    painter.drawText(200,5000,"Je soussigné Mr Balla moussa Keita,Responsable des clients"
                              " Ceritifie avoir");
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
   QString montant_string=QString::number(montant);
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


    int reponse;// QMessageBox:: question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextStream>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setTabEnabled(1, false);
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(DONNEESRecues()));
    connect(socket, SIGNAL(connected()), this, SLOT(CONNECTE()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(DECONNECTE()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this,
    SLOT(ERREURSOCKET(QAbstractSocket::SocketError)));
    tailleMessage = 0;
    #define NOM_RX "^([a-z]+[,.]?[ ]?|[A-Z]+['-]?)+$"

    QRegExp rxNom(NOM_RX);
    QRegExpValidator*valiNom= new QRegExpValidator(rxNom,this);

    ui->lineEdit_nom->setValidator(valiNom);
    ui->lineEdit_prenom->setValidator(valiNom);
    ui->lineEdit_adresse->setValidator(valiNom);

    ui->lineEdit_id->setValidator(new QIntValidator(0,99999999,this));
    ui->lineEdit_telephone->setValidator(new QIntValidator(0,99999999,this));
    ui->lineEdit_age->setValidator(new QIntValidator(0,99,this));
    ui->lineEdit_achat->setValidator(new QIntValidator(0,999999999,this));
    ui->tableView_2->setModel(Ctmp.afficher());
    setFixedSize(size()); //empecher le redimensionnement de l'écran

    //

    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).
    //
}

MainWindow::~MainWindow()
{
    delete ui;
}

//SLOTS ARDUNINO
void MainWindow::update_label()
{
    data=A.read_from_arduino();

  if(data=="1")
  {
      QMessageBox::StandardButton reply = QMessageBox::question(this,"ARDUINO","ATTENTION! MOUVEMENT DETECTE", QMessageBox::Yes | QMessageBox::No);
      data="0";

  }
}

//SLOTS VERS LES FONCTIONNALITES DE BASE ::::: @KEITA CODE
void MainWindow::on_pb_ajouter_clicked()
{

    //On recupère les élements présents dans les lineEdits

    int identifiant=ui->lineEdit_id->text().toInt();
    QString prenom=ui->lineEdit_prenom->text();
    QString nom=ui->lineEdit_nom->text();
    QString adresse=ui->lineEdit_adresse->text();
    int telephone=ui->lineEdit_telephone->text().toInt();
    int age=ui->lineEdit_age->text().toInt();
    QString email=ui->lineEdit_mail->text();
    QString sexe=ui->lineEdit_sexe->currentText();
    int achat=ui->lineEdit_achat->text().toInt();
    QDate date=ui->dateEdit->date();

    if(Ctmp.testNom_prenom_adresse(adresse))
    {
        //verifiier la validité du mail;
        Client C(identifiant,prenom,nom,adresse,telephone,age,email,sexe,achat,date);
        ui->lineEdit_mail->setStyleSheet("color: black");
        ui->lineEdit_id->setStyleSheet("color: black");
        ui->lineEdit_prenom->setStyleSheet("color : black");
        ui->lineEdit_nom->setStyleSheet("color: black");
        ui->lineEdit_adresse->setStyleSheet("color: black");
        ui->lineEdit_telephone->setStyleSheet("color: black");
        bool test=C.ajouter();

        if(test) //si la requete est bien exécutée;
        {
            //actualisation Sur la table_View
            QString id_string=QString::number(identifiant);
            ui->tableView_2->setModel(Ctmp.afficher());

            QMessageBox::information(nullptr,QObject::tr("OK"),
            QObject::tr("AJOUT EFFECTUE...\n"
              "Click Cancel to quit"),QMessageBox::Cancel);
        }
        else
        {

            QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
            QObject::tr("AJOUT NON EFFECTUE...\n"
              "Click Cancel to quit"),QMessageBox::Cancel);
        }

    }
    else
    {
           QMessageBox::critical(nullptr,QObject::tr("ERROR"),
           QObject::tr("VERIFIER LES INFORMATIONS...\n"
           "Click Cancel to quit"),QMessageBox::Cancel);

    }
    if(!Ctmp.testmail(email)) //essayer de réper l'erreur pour pemettre à l'utilisateur de corriger rapidement
    {
        ui->lineEdit_mail->setStyleSheet("color: red");

    }
    if(!Ctmp.testNom_prenom_adresse(prenom))
    {
        ui->lineEdit_prenom->setStyleSheet("color: red");
    }
    if(!Ctmp.testNom_prenom_adresse(nom))
    {
        ui->lineEdit_nom->setStyleSheet("color: red");
    }
    if(!Ctmp.testNom_prenom_adresse(adresse))
    {
        ui->lineEdit_adresse->setStyleSheet("color : red");
    }


}
void MainWindow::on_pb_supprimer_clicked()
{
    int id=ui->lineEdit_id->text().toInt();

    QMessageBox::StandardButton reply = QMessageBox::question(this,"SUPPRESSION","ATTENTION!\nVOULEZ-VOUS VRAIMENT SUPPRIMER CE CLIENT DE LA BD?", QMessageBox::Yes | QMessageBox::No);

    if(reply==QMessageBox::Yes)
    {
       bool test=Ctmp.supprimer(id);

       if(test)
       {
           ui->tableView_2->setModel(Ctmp.afficher());

           //on remet a vide le conteu des  labael
           ui->lineEdit_id->setText(0);
           ui->lineEdit_nom->setText(0);
           ui->lineEdit_prenom->setText(0);
           ui->lineEdit_adresse->setText(0);
           ui->lineEdit_telephone->setText(0);
           ui->lineEdit_age->setText(0);
           ui->lineEdit_mail->setText(0);
           ui->lineEdit_achat->setText(0);

           QMessageBox::information(nullptr,QObject::tr("OK"),
           QObject::tr("SUPPRESSION EFFECTUEE...\n"
           "Click Cancel to quit"),QMessageBox::Cancel);
       }
        else//si la requete non executer ==>QMessageBox::critical
        {
            QMessageBox::critical(nullptr,QObject::tr("Not OK"),
            QObject::tr("SUPPRESION NON EFFECTUEE.\n""Click Cancel to quit."),QMessageBox::Cancel);
        }
    }

    else
    {
       qDebug()<<"Suppresion annulée!!";
    }
}
void MainWindow::on_pb_modifier_clicked()
{


    int identifiant=ui->lineEdit_id->text().toInt();

    QString prenom=ui->lineEdit_prenom->text();
    QString adresse=ui->lineEdit_adresse->text();
    QString nom=ui->lineEdit_nom->text();
    int telephone=ui->lineEdit_telephone->text().toInt();
    QString email=ui->lineEdit_mail->text();
    int age=ui->lineEdit_age->text().toInt();
    QString sexe=ui->lineEdit_sexe->currentText();
    int achat=ui->lineEdit_achat->text().toInt();
    QDate date=ui->dateEdit->date();
    Client C(identifiant,prenom,nom,adresse,telephone,age,email,sexe,achat,date);
    QMessageBox::StandardButton reply = QMessageBox::question(this,"UPDATE","ATTENTION!\nVOULEZ-VOUS VRAIMENT MODIFIER CES INFORMATIONS?", QMessageBox::Yes | QMessageBox::No);

    if(reply==QMessageBox::Yes)
    {
        bool test=C.modifier();
        if(test)
        {
             ui->tableView_2->setModel(Ctmp.afficher());
            QMessageBox::information(nullptr,QObject::tr("OK"),
            QObject::tr("MODIFICATION EFFECTUEE...\n"
              "Click Cancel to quit"),QMessageBox::Cancel);
        }
        else
        {
            QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
            QObject::tr("MODIFICATION NON EFFECTUEE...\n"
              "Click Cancel to quit"),QMessageBox::Cancel);
        }
    }
    else
    {
       qDebug()<<"MODIFICATION ANNULEE!!";
    }

}
void MainWindow::on_pb_annuler_clicked()
{
    //REMETTRE LES CHAMPS A VIDE
    ui->lineEdit_id->setText(0);
    ui->lineEdit_nom->setText(0);
    ui->lineEdit_prenom->setText(0);
    ui->lineEdit_adresse->setText(0);
    ui->lineEdit_telephone->setText(0);
    ui->lineEdit_age->setText(0);
    ui->lineEdit_mail->setText(0);
    ui->lineEdit_sexe->setCurrentText(0);
    ui->lineEdit_achat->setText(0);
}

//SLOTS VERS LES FONCTIONNALITES AVANCEES ::::: @KEITA CODE
void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    QString critere;
    if(index==2)
    {
        critere="select * from A_SBC_CLIENT ORDER BY SEXE";
    ui->tableView_2->setModel(Ctmp.Trier(critere));
    }

    if(index==1)
    {
         critere="select * from A_SBC_CLIENT ORDER BY AGE";
    ui->tableView_2->setModel(Ctmp.Trier(critere));
    }

    if(index==0)
    {
         critere="select * from A_SBC_CLIENT ORDER BY NOM";
    ui->tableView_2->setModel(Ctmp.Trier(critere));
    }
}
void MainWindow::on_tableView_2_activated(const QModelIndex &index)
{
    QSqlQuery query;
    QString val=ui->tableView_2->model()->data(index).toString();
    query.prepare("SELECT * from A_SBC_CLIENT where IDENTIFIANT= :identifiant");
    query.bindValue(":identifiant",val);
    if(query.exec())
    {
        while(query.next())
        {

            ui->lineEdit_id->setText(query.value(0).toString());
            ui->lineEdit_nom->setText(query.value(1).toString());
            ui->lineEdit_prenom->setText(query.value(2).toString());
            ui->lineEdit_adresse->setText(query.value(3).toString());
            ui->lineEdit_telephone->setText(query.value(4).toString());
            ui->lineEdit_age->setText(query.value(5).toString());
            ui->lineEdit_mail->setText(query.value(6).toString());
            ui->lineEdit_sexe->setCurrentText(query.value(7).toString());
            ui->lineEdit_achat->setText(query.value(8).toString());

        }
    }
    else
    {
            QMessageBox::critical(nullptr, QObject::tr("Transferer données"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
    }
}
void MainWindow::on_pb_rechercher_clicked()
{
    int id=ui->lineEdit_IDS->text().toInt();
    if(ui->comboBox_rechercher->currentText()=="ID")
    {
        ui->tableView_2->setModel(Ctmp.rechercher_id(id));
     }

    if(ui->comboBox_rechercher->currentText()=="NOM")
    {
        QString nom=ui->lineEdit_IDS->text();
        ui->tableView_2->setModel(Ctmp.rechercher_nom(nom));
    }

    if(ui->comboBox_rechercher->currentText()=="PRENOM")
    {
        QString nom=ui->lineEdit_IDS->text();
        ui->tableView_2->setModel(Ctmp.rechercher_prenom(nom));
    }

    if(ui->comboBox_rechercher->currentText()=="VILLE")
    {
        QString nom=ui->lineEdit_IDS->text();
        ui->tableView_2->setModel(Ctmp.rechercher_ville(nom));
    }
}


void MainWindow::on_pb_recette_clicked()
{
     ui->stackedWidget->setCurrentIndex(4);
     QDate date=ui->dateEdit_recette->date();
     QDate dateprec=date.addDays(-1);
    int somme=Ctmp.recetteTotale(date);
    int sommeprec=Ctmp.recetteTotale2(dateprec);
    QString somme_string=QString::number(somme);
    QString sommeprec_string=QString::number(sommeprec);
    float progression;

if(sommeprec!=0)
{
        progression=((somme-sommeprec)*100)/sommeprec;
        QString progression_string=QString::number(progression);

        ui->lineEdit_pourcentage->setText(progression_string);

   ui->lineEdit_recette->setText(somme_string);
}




}

//ENSEMBLE DES SLOTS POUR LA GESTION CHAT TENTATIVE DE CONNEXION AU SERVEUR (PARTIE CHAT)
void MainWindow::on_pb_connexion_clicked()
{
    ui->textEdit->append(tr("TRAITEMENT EN COURS..."));
    ui->pb_connexion->setEnabled(false);
    socket->abort(); // On désactive les connexions précédentes s'il y en a
    // On se connecte au serveur demandé
    socket->connectToHost(ui->lineEdit_3->text(), ui->lineEdit_4->text().toInt());
}
void MainWindow::on_pb_envoyer_clicked()
{
    MainWindow c;
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);
    // On prépare le paquet à envoyer
    QString messageAEnvoyer = tr("<strong>") + ui->lineEdit_6->text() +tr("</strong> : ") + ui->lineEdit_5->text();
    out << (quint16) 0;
    out << messageAEnvoyer;
    out.device()->seek(0);
    out << (quint16) (paquet.size() - sizeof(quint16));
    socket->write(paquet); // On envoie le paquet
    ui->lineEdit_5->clear(); // On vide la zone d'écriture du message
    ui->lineEdit_5->setFocus(); // Et on remet le curseur à l'intérieur

}
void MainWindow::DONNEESRecues()
{
/* Même principe que lorsque le serveur reçoit un paquet :
On essaie de récupérer la taille du message
Une fois qu'on l'a, on attend d'avoir reçu le message entier
(en se basant sur la taille annoncée tailleMessage)
*/
QDataStream in(socket);
if ( tailleMessage == 0 )
{
if (socket->bytesAvailable() < (int)sizeof(quint16))
return;
in >> tailleMessage;
}
if (socket->bytesAvailable() < tailleMessage)
return;
// Si on arrive jusqu'à cette ligne, on peut récupérer le message entier
QString messageRecu;
in >> messageRecu;
// On affiche le message sur la zone de Chat
ui->textEdit->append(messageRecu);
// On remet la taille du message à 0 pour pouvoir recevoir de futurs messages
tailleMessage = 0;
}
void MainWindow::CONNECTE()
{
ui->textEdit->append(tr("Connexion réussie !"));
ui->pb_connexion->setEnabled(true);
}
void MainWindow::DECONNECTE()
{
ui->textEdit->append(tr("Déconnecté du serveur"));
}
void MainWindow::ERREURSOCKET(QAbstractSocket::SocketError erreur)
{
switch(erreur) // On affiche un message différent selon l'erreur qu'on nous indique
{
case QAbstractSocket::HostNotFoundError:
ui->textEdit->append(tr("ERREUR : le serveur n'a pas pu être trouvé. Vérifiez l'IP et le port."));
break;
case QAbstractSocket::ConnectionRefusedError:
ui->textEdit->append(tr("ERREUR : le serveur a refusé la connexion. Vérifiez si le programme \"serveur\" a bien été lancé. Vérifiez aussi l'IP et le port."));
break;
case QAbstractSocket::RemoteHostClosedError:
ui->textEdit->append(tr("ERREUR : le serveur a coupé la connexion."));
break;
default:
ui->textEdit->append(tr("ERREUR : ") + socket->errorString() +tr(""));
}
ui->pb_connexion->setEnabled(true);
}

//GENRERATION DE LA FACTURE EN PDF (EN COURS)
void MainWindow::on_pb_pdf_clicked()
{


     ui->stackedWidget->setCurrentIndex(3);
     ui->label_id->setText(ui->lineEdit_id->text());
     ui->label_nom->setText(ui->lineEdit_nom->text());
     ui->label_prenom->setText(ui->lineEdit_prenom->text());
     ui->label_contact->setText(ui->lineEdit_telephone->text());
     ui->label_adresse->setText(ui->lineEdit_adresse->text());
     ui->label_montant->setText(ui->lineEdit_achat->text());

}
void MainWindow::on_pb_excel_clicked()
{
     ui->stackedWidget->setCurrentIndex(2);
     ui->tableView_excel->setModel(Ctmp.afficher());

}
void MainWindow::on_pb_chat_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
void MainWindow::on_pb_accueil_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}
void MainWindow::on_pushButton_2_clicked()
{
    /*QString id_connexion=ui->lineEdit_id_connexion->text();
    QString password_connexion=ui->lineEdit_connexion_password->text();


    ui->lineEdit_connexion_password->setStyleSheet("color: black");
    ui->lineEdit_id_connexion->setStyleSheet("color: black");

    if(id_connexion=="administrateur"&&password_connexion=="admin")
    {
        ui->label_username->setText(ui->lineEdit_id_connexion->text());
        ui->tabWidget->setCurrentIndex(1);
        ui->tabWidget->setTabEnabled(1, true);
    }
    else if(id_connexion!="admin"&&password_connexion=="admin")
    {
        ui->lineEdit_id_connexion->setStyleSheet("color: red");

    }
    else if(id_connexion=="admin"&&password_connexion!="admin")
    {
        ui->lineEdit_connexion_password->setStyleSheet("color: red");
    }
    else
    {
         ui->lineEdit_connexion_password->setStyleSheet("color: red");
         ui->lineEdit_id_connexion->setStyleSheet("color: red");

    }*/

    ui->label_username->setText(ui->lineEdit_id_connexion->text());

    ui->tabWidget->setCurrentIndex(1);
    ui->tabWidget->setTabEnabled(1, true);
    ui->tabWidget->setTabEnabled(0,false);



}
void MainWindow::on_pb_generer_excel_clicked()
{
     QTableView * table;
    table = ui->tableView_2;
      Ctmp.genereExcel(table);


}
void MainWindow::on_pb_generer_pdf_clicked()
{
    int identifiant=ui->lineEdit_id->text().toInt();
    QString nom=ui->lineEdit_nom->text();
    QString prenom=ui->lineEdit_prenom->text();
    int telephone=ui->lineEdit_telephone->text().toInt();
    QString adresse=ui->lineEdit_adresse->text();
    int montant=ui->lineEdit_achat->text().toInt();
    Client C(identifiant,prenom,nom,telephone,adresse,montant);
    C.genererPdf();
}


void MainWindow::on_pushButton_clicked()
{
    QDesktopServices::openUrl(QUrl("http://www.facebook.com", QUrl::TolerantMode));
}

void MainWindow::on_pushButton_retourInscription_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}

void MainWindow::on_pb_quitter_clicked()
{
    close();
}

void MainWindow::on_pushButton_deconnexion_clicked()
{
    ui->tabWidget->setTabEnabled(0,true);
    ui->tabWidget->setTabEnabled(1,false);
}

void MainWindow::on_pushButton_passwordforgot_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);

}

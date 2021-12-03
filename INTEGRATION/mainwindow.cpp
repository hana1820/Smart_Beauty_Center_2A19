#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include "rendez_vous.h"

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

    Connection c;
    c.createconnection();

    //setWindowIcon(QIcon(":logo 0.png"));
    //Désactiver les pages pour les gestion avant la connexion.
    ui->tabWidget->setTabEnabled(1, false);
     ui->tabWidget->setTabEnabled(2, false);
      ui->tabWidget->setTabEnabled(3, false);
       ui->tabWidget->setTabEnabled(4, false);
       ui->tabWidget->setTabEnabled(5, false);
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

     // PARTIE CITATION ALEATOIRE

     srand(time(NULL)); // Initialisation de la donnée seed
     nombre = rand() % (10);
     if(nombre==0)
     ui->label_citation->setText("NOTRE VIE VAUT CE QU'ELLE NOUS A COUTE.");
     else if(nombre==1)
         ui->label_citation->setText("VOUS TROUVEREZ LA CLE DU SUCCES SOUS LE REVEILLE-MATIN.");
     else if(nombre==2)
         ui->label_citation->setText("Là OU SE TROUVE UNE VOLONTE, IL EXISTE UN CHEMIN.");
     else if(nombre==3)
         ui->label_citation->setText("LE FRUIT DU TRAVAIL EST LE PLUS DOUX DES PLAISIRS.");
     else if(nombre==4)
         ui->label_citation->setText("C'EST MAINTENANT LE TEMPS DE TRAVAILLER ENCORE PLUS DUR.");
     else if(nombre==5)
         ui->label_citation->setText("NE RÊVE PAS, FAIS-LE.");
     else if(nombre==6)
         ui->label_citation->setText("LES GAGNANTS TROUVENT LES MOYENS, LES PERDANTS DES EXCUSES.");
     else if(nombre==7)
         ui->label_citation->setText("LA MOTIVATION ET LE TRAVAIL SONT LA CLE DU SUCCES.");
     else if(nombre==8)
         ui->label_citation->setText("PRENEZ SOINS DE NOS CLIENTS.");
     else if(nombre==9)
         ui->label_citation->setText("LES PORTES DE L'AVENIR SONT OUVERTES A CEUX QUI SAVENT LES POUSSER.");

     Rendez_Vous R;
     ui->TableView->setModel(Etmp.afficher_rdv());
     ui->spinBox->setValue(R.nb_total_rdv());

     for(int i=0; i<13; i++)
     {
         for(int j=0; j<60; j+=30)
         {
             ui->PeriodeComboBox->addItem(QString::number(i) + " heures et " + QString::number(j) + " minutes");
         }
     }

     ui->NumLine->setValidator(new QIntValidator(0,99999999,this));
     ui->IdLine->setValidator(new QIntValidator(0,99999999,this));

     QPixmap logog("C:/Users/USER/Desktop/GESTION CLIENTS METIERS/logog.png");
     ui->logog->setPixmap(logog);

     QPixmap logop("C:/Users/USER/Desktop/GESTION CLIENTS METIERS/logop.png");
     ui->logop->setPixmap(logop);

     QIcon ajout("C:/Users/USER/Desktop/GESTION CLIENTS METIERS/ajout.png");
     ui->AjouterRDV->setIcon(ajout);

     QIcon annuler("C:/Users/USER/Desktop/GESTION CLIENTS METIERS/annuler.png");
     ui->QuitterRDV->setIcon(annuler);

     QIcon email("C:/Users/USER/Desktop/GESTION CLIENTS METIERS/email.png");
     ui->MailRDV->setIcon(email);

     QIcon entrer("C:/Users/USER/Desktop/GESTION CLIENTS METIERS/entrer.png");
     ui->Connecter->setIcon(entrer);

     QIcon excel("C:/Users/USER/Desktop/GESTION CLIENTS METIERS/excel.png");
     ui->ExcelRDV->setIcon(excel);

     QIcon modifier("C:/Users/USER/Desktop/GESTION CLIENTS METIERS/modifier.png");
     ui->ModifierRDV->setIcon(modifier);

     QIcon recherche("C:/Users/USER/Desktop//GESTION CLIENTS METIERS/recherche.png");
     ui->RechercherRDV->setIcon(recherche);

     QIcon supprimer("C:/Users/USER/Desktop/GESTION CLIENTS METIERS/supprimer.png");
     ui->SupprimerRDV->setIcon(supprimer);

     connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
     connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));

     /*ui->tabWidget->setTabEnabled(1,false);
     ui->tabWidget->setTabEnabled(2,false);
     ui->tabWidget->setTabEnabled(3,false);
     */
}

MainWindow::~MainWindow()
{
    delete ui;
}

//SLOTS ARDUINO
void MainWindow::update_label()
{
   data=A.read_from_arduino();

   if(data=="\x13"||data=="\x03"||data=="s")
    {
         A.write_to_arduino("1");
         QMessageBox::StandardButton reply = QMessageBox::question(this,"MAGASIN STOCK","UNE PERSONNE VIENT D'ACCEDER\nAU MAGASIN DE STOCK", QMessageBox::Yes | QMessageBox::No);
         if(reply==QMessageBox::Yes)
         {

         }


    }

    else
    {
        A.write_to_arduino("0");
    }
    qDebug() << "data:" << data;

   /* int test=0;
    QSqlQuery query;
    query.prepare("select *from A_SBC_CLIENT");
    if(query.exec())
    {
        while(query.next())
            if(query.value(3)==data)
                test++;
    }



    if(test!=0) //code retrouve
    {
        A.write_to_arduino("1");
         QMessageBox::StandardButton reply = QMessageBox::question(this,"ARDUINO","ATTENTION! MOUVEMENT DETECTE", QMessageBox::Yes | QMessageBox::No);
         if(reply==QMessageBox::Yes)
         {

         }
         else
         {
            // A.write_to_arduino("0");
         }
    }
    else
    {
         A.write_to_arduino("0");
    }*/



 /* if(data=="1")
  {
      QMessageBox::StandardButton reply = QMessageBox::question(this,"ARDUINO","ATTENTION! MOUVEMENT DETECTE", QMessageBox::Yes | QMessageBox::No);
      data="0";

  }*/
}

//SLOTS VERS LES FONCTIONNALITES DE BASE ::::: @KEITA CODE
void MainWindow::on_pb_ajouter_clicked()
{

A.write_to_arduino("1");


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

void MainWindow::on_Connecter_clicked()
{
    QString id_connexion=ui->lineEdit_id_connexion->text();
    QString password_connexion=ui->lineEdit_connexion_password->text();

    ui->lineEdit_connexion_password->setStyleSheet("color: black");
    ui->lineEdit_id_connexion->setStyleSheet("color: black");

    if(id_connexion == "admin" && password_connexion == "admin")
    {
        Etmp.notifications("Connexion", "Le nom d'utilisateur et le mot de passe sont corrects");
        //ui->label_username->setText(ui->lineEdit_id_connexion->text());
        ui->tabWidget->setCurrentIndex(2);
        ui->tabWidget->setTabEnabled(2, true);
        ui->tabWidget->setTabEnabled(0,false);
        /*ui->tabWidget->setCurrentIndex(1);
        ui->tabWidget->setTabEnabled(1, true);
        */
    }
    else if(id_connexion != "admin" && password_connexion == "admin")
    {
        ui->lineEdit_id_connexion->setStyleSheet("color: red");
        Etmp.notifications("Connexion", "Username is not correct");
    }
    else if(id_connexion == "admin" && password_connexion != "admin")
    {
        ui->lineEdit_connexion_password->setStyleSheet("color: red");
        Etmp.notifications("Connexion", "Password is not correct");
    }
    else
    {
         ui->lineEdit_connexion_password->setStyleSheet("color: red");
         ui->lineEdit_id_connexion->setStyleSheet("color: red");
         Etmp.notifications("Connexion", "Username or password is not correct");
    }
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

    //MODE NUIT

   /* ui->tabWidget->setStyleSheet("background-color: rgb(40,40,40)");
    ui->stackedWidget->setStyleSheet("background-color: rgb(40,40,40)");
    ui->stackedWidget_2->setStyleSheet("background-color: rgb(40,40,40)");*/
}
void MainWindow::on_pushButton_passwordforgot_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);

}
void MainWindow::on_pb_configuration_clicked()
{
     ui->stackedWidget->setCurrentIndex(5);

   /* ui->tabWidget->setStyleSheet("background-color: rgb(245,172,162);");
    ui->stackedWidget->setStyleSheet("background-color: rgb(245,172,162);");
    ui->stackedWidget_2->setStyleSheet("background-color: rgb(245,172,162);");*/

   // color: rgb(121, 79, 29);
}
void MainWindow::on_pushButton_APPLIQUER_clicked()
{


    if(ui->lineEdit_mode->currentText()=="         JOUR")
    {

            ui->tabWidget->setStyleSheet("background-color: rgb(245,172,162);color: rgb(121, 79, 29) ;");
            ui->stackedWidget->setStyleSheet("background-color: rgb(245,172,162);color: rgb(121, 79, 29);");
            ui->stackedWidget_2->setStyleSheet("background-color: rgb(245,172,162);color: rgb(121, 79, 29);");

            ui->widget->setStyleSheet("background-color: rgb(197, 131, 98);");

    }
    else if(ui->lineEdit_mode->currentText()=="         NUIT")
    {
            ui->tabWidget->setStyleSheet("background-color: rgb(40,40,40)");
            ui->stackedWidget->setStyleSheet("background-color: rgb(40,40,40)");
            ui->stackedWidget_2->setStyleSheet("background-color: rgb(40,40,40)");
            ui->widget->setStyleSheet("background-color: rgb(80,40,40)");
            ui->frame_2->setStyleSheet("background-color: rgb(60,40,40);");


    }


}





//-------------------------------------------------------------------------------------------------//
//-----------------------------------------------RDV-----------------------------------------------//

void MainWindow::on_QuitterRDV_clicked()
{
    close();
}

//----------------------------------------------------------CRUDS----------------------------------------------------------//

void MainWindow::on_AjouterRDV_clicked()
{
    int num_rdv = ui->NumLine->text().toInt();
    int id_client = ui->IdLine->text().toInt();
    QString date_rdv = ui->dateEdit_RDV->date().toString();
    QString heure = ui->timeEdit->time().toString();
    QString periode = ui->PeriodeComboBox->currentText();
    QString salle_rdv = ui->SalleComboBox->currentText();
    QString designation = ui->DesComboBox->currentText();

    qDebug()<<num_rdv;
    qDebug()<<id_client;
    qDebug()<<date_rdv;
    qDebug()<<heure;
    qDebug()<<periode;
    qDebug()<<salle_rdv;
    qDebug()<<designation;

    Rendez_Vous R(num_rdv, id_client, date_rdv, heure, periode, salle_rdv, designation);

    bool test=R.ajouter_rdv();

    if(test)
    {
        ui->TableView->setModel(Etmp.afficher_rdv());
        ui->spinBox->setValue(R.nb_total_rdv());

        Etmp.notifications("Success", "ajout avec success");
    }
    else
        Etmp.notifications("Failed", "ajout echoué");
}

void MainWindow::on_ModifierRDV_clicked()
{
    int num_rdv = ui->NumLine->text().toInt();
    int id_client = ui->IdLine->text().toInt();
    QString date_rdv = ui->dateEdit_RDV->date().toString();
    QString heure = ui->timeEdit->time().toString();
    QString periode = ui->PeriodeComboBox->currentText();
    QString salle_rdv = ui->SalleComboBox->currentText();
    QString designation = ui->DesComboBox->currentText();

    Rendez_Vous R(num_rdv, id_client, date_rdv, heure, periode, salle_rdv, designation);

    bool test=R.modifier_rdv(num_rdv, id_client, date_rdv, heure, periode, salle_rdv, designation);

    if(test)
    {
        ui->TableView->setModel(Etmp.afficher_rdv());

        Etmp.notifications("Succès","Modification avec success");
    }
    else
        Etmp.notifications("échoué","Modification echouee");
}

void MainWindow::on_SupprimerRDV_clicked()
{
    int num_rdv =ui->NumLine->text().toInt();
    bool test=Etmp.supprimer_rdv(num_rdv);
    Rendez_Vous R;

    if(test)
    {
        ui->TableView->setModel(Etmp.afficher_rdv());
        ui->spinBox->setValue(R.nb_total_rdv());

        Etmp.notifications("Succès","Suppression avec success");
    }
    else
        Etmp.notifications("échoué","Suppression echoué");
}

//----------------------------------------------------------METIERS----------------------------------------------------------//

void MainWindow::on_TrierComboBox_currentIndexChanged(int test)
{
    if (test==1)
    {
        ui->TableView->setModel(Etmp.trierNum_RDV());

        Etmp.notifications("Succès","Trie effectuée");
    }
    else
        Etmp.notifications("échoué","Trie non effectuée");
}

void MainWindow::on_RechercherRDV_clicked()
{
    int num_rdv =ui->RechercherLine->text().toInt();
    bool test=Etmp.rechercher_rdv(num_rdv);

    if(test)
    {
        ui->TableView->setModel(Etmp.rechercher_rdv(num_rdv));

        Etmp.notifications("Succès","Recherche effectuée");
    }
    else
        Etmp.notifications("échoué","Recherche non effectuée");
}

void MainWindow::on_ExcelRDV_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                    tr("Excel Files (*.xls)"));
    if (fileName.isEmpty())
        return;

    ExportExcelObject obj(fileName, "mydata", ui->TableView);

    obj.addField(0, "NUM_RDV", "char(50)");
    obj.addField(1, "ID_Client", "char(50)");
    obj.addField(2, "ID_EMPLOYEE", "char(50)");
    obj.addField(3, "DATE_RDV", "char(50)");
    obj.addField(4, "HEURE", "char(50)");
    obj.addField(5, "PERIODE", "char(50)");
    obj.addField(6, "SALLE_RDV", "char(50)");
    obj.addField(7, "DESIGNATION", "char(50)");

    int retVal = obj.export2Excel();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"), QString(tr("%1 records exported!")).arg(retVal));
    }
}

//mailing
void MainWindow::on_MailRDV_clicked()
{
    ui->Gestion_des_Rendez_Vous->setCurrentIndex(1);
}

void MainWindow::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );
}

void MainWindow::sendMail()
{
    Mailing* mailing = new Mailing("hana.mejdoub@esprit.tn", ui->mail_pass->text(), "smtp.gmail.com");
    connect(mailing, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        mailing->sendMail("hana.mejdoub@esprit.tn", ui->rcpt->text(), ui->subject->text(), ui->msg->toPlainText(), files );
    else
        mailing->sendMail("hana.mejdoub@esprit.tn", ui->rcpt->text(), ui->subject->text(), ui->msg->toPlainText());
}

void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
    {
        Etmp.notifications("reussie","Envoie avec success");
        ui->rcpt->clear();
        ui->subject->clear();
        ui->file->clear();
        ui->msg->clear();
        ui->mail_pass->clear();
    }
}

void MainWindow::on_QuitterRDV_2_clicked()
{
    close();
}

//-------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------//


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
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(DONNEESRecues()));
    connect(socket, SIGNAL(connected()), this, SLOT(CONNECTE()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(DECONNECTE()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this,
    SLOT(ERREURSOCKET(QAbstractSocket::SocketError)));
    tailleMessage = 0;
    ui->lineEdit_id->setValidator(new QIntValidator(0,99999999,this));
    ui->tableView_2->setModel(Ctmp.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_ajouter_clicked()
{

    int identifiant=ui->lineEdit_id->text().toInt();
    QString prenom=ui->lineEdit_prenom->text();
    QString nom=ui->lineEdit_nom->text();
    QString adresse=ui->lineEdit_adresse->text();
   int telephone=ui->lineEdit_telephone->text().toInt();
   int age=ui->lineEdit_age->text().toInt();
   QString email=ui->lineEdit_mail->text();
    QString sexe=ui->lineEdit_sexe->text();
    int achat=ui->lineEdit_achat->text().toInt();

    Client C(identifiant,prenom,nom,adresse,telephone,age,email,sexe,achat);

    bool test=C.ajouter();

    if(test) //si la requete est bien exécutée;
    {
        //actualisation
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


void MainWindow::on_pb_supprimer_clicked()
{
    int id=ui->lineEdit_id->text().toInt();
    bool test=Ctmp.supprimer(id);

    if(test)
    {
        ui->tableView_2->setModel(Ctmp.afficher());

        ui->lineEdit_id->setText(0);
        ui->lineEdit_nom->setText(0);
        ui->lineEdit_prenom->setText(0);
        ui->lineEdit_adresse->setText(0);
        ui->lineEdit_telephone->setText(0);
         ui->lineEdit_age->setText(0);
         ui->lineEdit_mail->setText(0);
          ui->lineEdit_sexe->setText(0);
          ui->lineEdit_achat->setText(0);//on remet a vide le conteu des  labael

        QMessageBox::information(nullptr,QObject::tr("OK"),
        QObject::tr("SUPPRESSION EFFECTUEE...\n"
          "Click Cnacel to quit"),QMessageBox::Cancel);

    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
        QObject::tr("SUPPRESSION NON EFFECTUEE...\n"
          "Click Cancel to quit"),QMessageBox::Cancel);
    }
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    QString critere;
    if(index==2)
    {
        critere="select * from CLIENT_TEST ORDER BY SEXE";
    ui->tableView_2->setModel(Ctmp.Trier(critere));
    }

    if(index==1)
    {
         critere="select * from CLIENT_TEST ORDER BY AGE";
    ui->tableView_2->setModel(Ctmp.Trier(critere));
    }

    if(index==0)
    {
         critere="select * from CLIENT_TEST ORDER BY NOM";
    ui->tableView_2->setModel(Ctmp.Trier(critere));
    }
}

void MainWindow::on_pb_valider_clicked()
{
    int identifiant=ui->lineEdit_id->text().toInt();

    QString prenom=ui->lineEdit_prenom->text();
    QString adresse=ui->lineEdit_adresse->text();
    QString nom=ui->lineEdit_nom->text();
    int telephone=ui->lineEdit_telephone->text().toInt();
    QString email=ui->lineEdit_mail->text();
    int age=ui->lineEdit_age->text().toInt();
    QString sexe=ui->lineEdit_sexe->text();
    int achat=ui->lineEdit_achat->text().toInt();

    bool test=Ctmp.modifier(identifiant,nom,prenom,adresse,telephone,age,email,sexe,achat);
    if(test)
    {
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
    ui->tableView_2->setModel(Ctmp.afficher());

}

void MainWindow::on_tableView_2_activated(const QModelIndex &index)
{
    QSqlQuery query;
    QString val=ui->tableView_2->model()->data(index).toString();
    query.prepare("SELECT * from CLIENT_TEST where IDENTIFIANT= :identifiant");
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
              ui->lineEdit_sexe->setText(query.value(7).toString());
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

void MainWindow::on_pb_annuler_clicked()
{
    ui->lineEdit_id->setText(0);
    ui->lineEdit_nom->setText(0);
    ui->lineEdit_prenom->setText(0);
    ui->lineEdit_adresse->setText(0);
    ui->lineEdit_telephone->setText(0);
     ui->lineEdit_age->setText(0);
     ui->lineEdit_mail->setText(0);
      ui->lineEdit_sexe->setText(0);
      ui->lineEdit_achat->setText(0);
}

void MainWindow::on_pb_rechercher_clicked()
{
    int id=ui->lineEdit_IDS->text().toInt();
       ui->tableView_2->setModel(Ctmp.rechercher(id));
}

void MainWindow::on_pb_recette_clicked()
{
    int somme=Ctmp.recetteTotale();
    QString somme_string=QString::number(somme);

   ui->lineEdit_recette->setText(somme_string);

}

//TENTATIVE DE CONNEXION AU SERVEUR
void MainWindow::on_pushButton_clicked()
{
    ui->textEdit->append(tr("TRAITEMENT EN COURS..."));
    ui->pushButton->setEnabled(false);
    socket->abort(); // On désactive les connexions précédentes s'il y en a
    // On se connecte au serveur demandé
    socket->connectToHost(ui->lineEdit_3->text(), ui->lineEdit_4->text().toInt());
}

void MainWindow::on_pushButton_3_clicked()
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
    //listeMessages->append(tr("bonjour"));
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
ui->pushButton->setEnabled(true);
}

void MainWindow::DECONNECTE()
{
ui->textEdit->append(tr("Déconnecté du serveur"));
}

// Ce slot est appelé lorsqu'il y a une erreur
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
ui->pushButton->setEnabled(true);
}

//GENRERATION DE LA FACTURE EN PDF (EN COURS)


//GENERATION DE FIC EXCEL (EN COURS)
void MainWindow::on_pb_excel_clicked()
{
   Ctmp.genereExcel();

}

void MainWindow::on_pb_pdf_clicked()
{
    Ctmp.genererPdf();
}

void MainWindow::on_pushButton_11_clicked()
{
    close();
}

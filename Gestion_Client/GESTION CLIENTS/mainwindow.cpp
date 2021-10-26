#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
/*
void MainWindow::on_pb_modifier_clicked()
{
   // int id=ui->lineEdit_IDS->text().toInt();
   /*ui->tableView_2->setModel(Ctmp.rechercher(id)); //permetrra de recherhcer

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
        QObject::tr("SUPPRESSION EFFECTUEE...\n"
          "Click Cancel to quit"),QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
        QObject::tr("SUPPRESSION NON EFFECTUEE...\n"
          "Click Cancel to quit"),QMessageBox::Cancel);
    }
    ui->tableView_2->setModel(Ctmp.afficher());

}

*/

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    QString critere;
    if(index==2)
    {
        critere="select * from client ORDER BY SEXE";
    ui->tableView_2->setModel(Ctmp.Trier(critere));
    }

    if(index==1)
    {
         critere="select * from client ORDER BY AGE";
    ui->tableView_2->setModel(Ctmp.Trier(critere));
    }

    if(index==0)
    {
         critere="select * from client ORDER BY NOM";
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
    query.prepare("SELECT * from client where IDENTIFIANT= :identifiant");
    /*or nomAgence= :nomAgence or adresse= :adresse "
                  "or nbr_Employes= :nbr_Employes or email= :email or gain= :gain");*/

    query.bindValue(":identifiant",val);
   /* SELECT WHOLE ROW
    * query.bindValue(":nomAgence",val);
    query.bindValue(":adresse",val);
    query.bindValue(":nbr_Employes",val);
    query.bindValue(":email",val);
    query.bindValue(":gain",val);*/

    if(query.exec())
    {
        while(query.next())
        {
            //ui->lineEdit_Supression->setText(query.value(0).toString());
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

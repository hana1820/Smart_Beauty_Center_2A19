#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rendez_vous.h"
#include <QApplication>
#include <QMessageBox>
#include <iostream>
#include <QDebug>

/* include <QApplication>
On inclue la création des fenêtres*/

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->TableView->setModel(Etmp.afficher());

    /*
    for(int i=1; i<13; i++)
    {
        ui->comboBox->addItem(QString::number(i) + " heures");
    }

    for(int j=0; j<60; j++)
    {
        ui->comboBox->addItem(QString::number(j) + " minutes");
    }*/

    for(int i=0; i<13; i++)
    {
        for(int j=0; j<60; j+=30)
        {
            ui->PeriodeComboBox->addItem(QString::number(i) + " hour et " + QString::number(j) + " minutes");
        }
    }

    QPixmap logog("C:/Users/USER/Desktop/Projet C++/Rendez_Vous/logog.png");
    ui->logog->setPixmap(logog);

    QPixmap logop("C:/Users/USER/Desktop/Projet C++/Rendez_Vous/logop.png");
    ui->logop->setPixmap(logop);
}

MainWindow::~MainWindow()
{
    delete ui;


    int num_rdv =ui->NumLine->text().toInt();
    bool test=Etmp.rechercher(num_rdv);

    if(test)
    {
        ui->TableView->setModel(Etmp.rechercher(num_rdv));
        /*QtableViewItem * item = ui->TableView->currentItem();
          item->setTextColor(QT::red);
          item->setBackgroundColor(QT::black);*/

        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Recherche effectuée\n" "Click Cancel to exit"), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("Recherche non effectuée\n" "Click Cancel to exit"), QMessageBox::Cancel);
}


void MainWindow::on_Ajouter_clicked()
{
    //Récupération des informations saisies dans les 3 champs
    int num_rdv = ui->NumLine->text().toInt();
    //ui->lineEdit->text()="";  //tfaragh leblasa eli bch tekteb fyha baad ajout
    int id_client = ui->IdLine->text().toInt();
    QString date_rdv = ui->dateEdit->date().toString();
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

    Rendez_vous R(num_rdv, id_client, date_rdv, heure, periode, salle_rdv, designation);

    bool test=R.ajouter();

    if(test) // Si requete executée
    {
        //Refresh (Actualiser)

        ui->TableView->setModel(Etmp.afficher());

        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Ajout effectuée\n" "Click Cancel to exit"), QMessageBox::Cancel);
    }
    else // Si requete non executée
        QMessageBox::critical(nullptr, QObject::tr("Not OK"), QObject::tr("Ajout non effectuée\n" "Click Cancel to exit"), QMessageBox::Cancel);
}

void MainWindow::on_Quitter_clicked()
{
    close();
}

void MainWindow::on_Modifier_clicked()
{
    int num_rdv = ui->NumLine->text().toInt();
    int id_client = ui->IdLine->text().toInt();
    QString date_rdv = ui->dateEdit->date().toString();
    QString heure = ui->timeEdit->time().toString();
    QString periode = ui->PeriodeComboBox->currentText();
    QString salle_rdv = ui->SalleComboBox->currentText();
    QString designation = ui->DesComboBox->currentText();

    Rendez_vous R(num_rdv, id_client, date_rdv, heure, periode, salle_rdv, designation);

    bool test=R.modifier(num_rdv, id_client, date_rdv, heure, periode, salle_rdv, designation);

    if(test)
    {
        ui->TableView->setModel(Etmp.afficher());   //refresh

        QMessageBox::information(nullptr, QObject::tr("OK"),
                  QObject::tr("Modification effectuée\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                  QObject::tr("Modification non effectuée\n" "Click Cancel to exit."), QMessageBox::Cancel);
}


void MainWindow::on_Supprimer_clicked()
{
    int num_rdv =ui->NumLine->text().toInt();
    bool test=Etmp.supprimer(num_rdv);

    if(test)
    {
        //Refresh (Actualiser)

        ui->TableView->setModel(Etmp.afficher());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Suppression effectuée\n" "Click Cancel to exit"), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("Suppression non effectuée.\n" "Click Cancel to exit"), QMessageBox::Cancel);
}

void MainWindow::on_Rechercher_clicked()
{
    int num_rdv =ui->RechercherLine->text().toInt();
    bool test=Etmp.rechercher(num_rdv);

    if(test)
    {
        ui->TableView->setModel(Etmp.rechercher(num_rdv));
        /*QtableViewItem * item = ui->tableView->currentItem();
          item->setTextColor(QT::red);
          item->setBackgroundColor(QT::black);*/

        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Recherche effectuée\n" "Click Cancel to exit"), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("Recherche non effectuée\n" "Click Cancel to exit"), QMessageBox::Cancel);
}

void MainWindow::on_TrierComboBox_currentIndexChanged(int index)
{
    if (index==1)
    {
        ui->TableView->setModel(Etmp.trierParNum_RDV());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Trie effectuée\n" "Click Cancel to exit"), QMessageBox::Cancel);
    }
    else
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Trie non effectuée\n" "Click Cancel to exit"), QMessageBox::Cancel);

}

void MainWindow::on_TrierComboBox_currentIndexChanged(const QString &arg1)
{
    if (arg1=="")
    {
        ui->TableView->setModel(Etmp.trierParDate());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Trie effectuée\n" "Click Cancel to exit"), QMessageBox::Cancel);
    }
    else
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Trie non effectuée\n" "Click Cancel to exit"), QMessageBox::Cancel);

}

/*
void MainWindow::on_pushButton_clicked()
{
    Connection c;
    QSqlQueryModel * model=new QSqlQueryModel();

    c.createconnection();
    QSqlQuery* qry=new QSqlQuery(c.db);

    qry->prepare("select * from a_sbc_rendezvous");

    qry->exec();
    model->setQuery(*qry);

    c.closeConnection();

    QDebug() <<(model->rowcount());
}*/

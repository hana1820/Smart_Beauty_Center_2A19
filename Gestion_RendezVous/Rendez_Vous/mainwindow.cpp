#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rendez_vous.h"
#include <QApplication>
#include <QMessageBox>
#include <iostream>
#include <QDebug>
#include <QtGui>

/* include <QApplication>
On inclue la création des fenêtres*/

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(Etmp.afficher());

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
            ui->comboBox->addItem(QString::number(i) + " h et " + QString::number(j) + " m ");
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ajouter_clicked()
{
    //Récupération des informations saisies dans les 3 champs
    int num_rdv = ui->lineEdit->text().toInt();
    //ui->lineEdit->text()="";  //tfaragh leblasa eli bch tekteb fyha baad ajout
    int id_client = ui->lineEdit_3->text().toInt();
    QString date_rdv = ui->dateEdit->date().toString();
    QString heure = ui->timeEdit->time().toString();
    QString periode = ui->comboBox->currentText();
    QString salle_rdv = ui->comboBox_2->currentText();
    QString designation = ui->comboBox_3->currentText();

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

        ui->tableView->setModel(Etmp.afficher());

        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Ajout effectuée\n" "Click Cancel to exit"), QMessageBox::Cancel);
    }
    else // Si requete non executée
        QMessageBox::critical(nullptr, QObject::tr("Not OK"), QObject::tr("Ajout non effectuée\n" "Click Cancel to exit"), QMessageBox::Cancel);
}

void MainWindow::on_Modifier_clicked()
{
    int num_rdv =ui->lineEdit->text().toInt();
    int id_client =ui->lineEdit_3->text().toInt();
    QString date_rdv=ui->dateEdit->date().toString();
    QString heure = ui->timeEdit->time().toString();
    QString periode = ui->comboBox->currentText();
    QString salle_rdv=ui->comboBox_2->currentText();
    QString designation=ui->comboBox_3->currentText();

    Rendez_vous R(num_rdv, id_client, date_rdv, heure, periode, salle_rdv, designation);

    bool test=R.modifier(num_rdv, id_client, date_rdv, heure, periode, salle_rdv, designation);

    if(test)
    {
        ui->tableView->setModel(Etmp.afficher());   //refresh

        QMessageBox::information(nullptr, QObject::tr("OK"),
                  QObject::tr("Modification effectuée\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                  QObject::tr("Modification non effectuée\n" "Click Cancel to exit."), QMessageBox::Cancel);

}

void MainWindow::on_supprimer_clicked()
{
    int num_rdv =ui->lineEdit->text().toInt();
    bool test=Etmp.supprimer(num_rdv);

    if(test)
    {
        //Refresh (Actualiser)

        ui->tableView->setModel(Etmp.afficher());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Suppression effectuée\n" "Click Cancel to exit"), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("Suppression non effectuée.\n" "Click Cancel to exit"), QMessageBox::Cancel);
}

void MainWindow::on_recherhcer_clicked()
{
    int num_rdv =ui->lineEdit_6->text().toInt();
    bool test=Etmp.rechercher(num_rdv);

    if(test)
    {
        ui->tableView->setModel(Etmp.rechercher(num_rdv));
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

void MainWindow::on_comboBox_5_currentIndexChanged(int index)
{
    if (index==1)
    {
        ui->tableView->setModel(Etmp.trierParNum_RDV());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Trie effectuée\n" "Click Cancel to exit"), QMessageBox::Cancel);
    }
    else
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Trie non effectuée\n" "Click Cancel to exit"), QMessageBox::Cancel);

}

void MainWindow::on_comboBox_5_currentIndexChanged(const QString &arg1)
{
    if (arg1=="")
    {
        ui->tableView->setModel(Etmp.trierParDate());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Trie effectuée\n" "Click Cancel to exit"), QMessageBox::Cancel);
    }
    else
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Trie non effectuée\n" "Click Cancel to exit"), QMessageBox::Cancel);

}

void MainWindow::on_pushButton_3_clicked()
{
    close();
}

/*
void Rendez_vous::translate(QEvent *event)
 {
     if (e->type() == QEvent::LanguageChange) {
         ui->lineEdit->setText(tr("Titre du document"));
         ui->comboBox_4->setText(tr("&OK"));
     } else
         QWidget::translate(event);
 }

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

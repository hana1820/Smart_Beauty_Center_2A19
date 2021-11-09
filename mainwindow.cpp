#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include <QMessageBox>
#include <QIntValidator>
MainWindow::MainWindow(QWidget *parent):
     QMainWindow(parent),
     ui(new Ui::MainWindow)
{
    ui->setupUi(this);
ui->le_id->setValidator(new QIntValidator(100,999,this));
ui->tab_employes->setModel(E.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pb_ajouter_clicked()
{
    int id=ui->le_id->text().toInt(); // conversion en int
    int telephone=ui->le_tel->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    QString adresse=ui->le_adresse->text();
    QString poste=ui->le_poste->text();
    QString email=ui->le_email->text();
    Employe E(id,telephone,nom,prenom,adresse,poste,email);
    bool test=E.ajouter();
    if(test)
    {

        QMessageBox::information(nullptr,QObject::tr("OK"),
        QObject::tr("Ajout effectué\n"
        "click Cancel to exit"),QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
        QObject::tr("Ajout not effectué.\n"
        "Click Cancel to exit"), QMessageBox::Cancel);
    }

void MainWindow::on_pb_supprimer_clicked()
{
Employe E1;
E1.setid(ui->le_id->text().toInt());
bool test=E1.supprimer(E1.getid());
if(test)
{

    QMessageBox::information(nullptr,QObject::tr("OK"),
    QObject::tr("Suppression effectué\n"
    "click Cancel to exit"),QMessageBox::Cancel);
    ui->tab_employes->setModel(E.afficher());

}
else
    QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
    QObject::tr("Suppression not effectué.\n"
    "Click Cancel to exit"), QMessageBox::Cancel);


}

void MainWindow::on_pb_modifier_employe_clicked()
{
    int id=ui->le_id->text().toInt();
        int telephone=ui->le_tel->text().toInt();

        QString nom=ui->le_nom->text();
        QString prenom=ui->le_prenom->text();
        QString adresse=ui->le_adresse->text();
       QString poste=ui->le_poste->text();
        QString email=ui->le_email->text();


        Employe E;
               bool test;
               test=E.modifier(id,telephone,nom,prenom,adresse,poste,email);
               if(test)
               {
                  ui->tab_employes->setModel(E.afficher());

                  QMessageBox::information(nullptr,QObject::tr("modifier employe"),
                    QObject::tr(" employe modifé") ,QMessageBox::Ok);

                 }else

                     QMessageBox::critical(nullptr,QObject::tr("modifier employe"),
                       QObject::tr("Erreur !.\n""Click Ok to exit."), QMessageBox::Ok);
        }



void MainWindow::on_pb_recherche_employe_clicked()
{
    Employe E;

    int ide=ui->lineEdit_18->text().toInt() ;
    ui->tab_employes->setModel(E.rechercher(ide)) ;
    QMessageBox::information(nullptr, QObject::tr("succes"),
                QObject::tr(" affiche  dans le tableau !.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}




void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if(index==1)
      {
          ui->tab_employes->setModel(E.sort_employe());
      }else
          ui->tab_employes->setModel(E.sort_employe());
}

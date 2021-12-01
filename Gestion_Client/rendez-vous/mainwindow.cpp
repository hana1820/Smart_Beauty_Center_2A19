#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rendez_vous.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Connection c;
    c.createConnection();

    Rendez_Vous R;
    ui->TableView->setModel(Etmp.afficher());
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

    QPixmap logog("C:/Users/USER/Desktop/Rendez_Vous/logog.png");
    ui->logog->setPixmap(logog);

    QPixmap logop("C:/Users/USER/Desktop/Rendez_Vous/logop.png");
    ui->logop->setPixmap(logop);

    QIcon ajout("C:/Users/USER/Desktop/Rendez_Vous/ajout.png");
    ui->Ajouter->setIcon(ajout);

    QIcon annuler("C:/Users/USER/Desktop/Rendez_Vous/annuler.png");
    ui->Quitter->setIcon(annuler);

    QIcon email("C:/Users/USER/Desktop/Rendez_Vous/email.png");
    ui->Mail->setIcon(email);

    QIcon entrer("C:/Users/USER/Desktop/Rendez_Vous/entrer.png");
    ui->Connecter->setIcon(entrer);

    QIcon excel("C:/Users/USER/Desktop/Rendez_Vous/excel.png");
    ui->Excel->setIcon(excel);

    QIcon modifier("C:/Users/USER/Desktop/Rendez_Vous/modifier.png");
    ui->Modifier->setIcon(modifier);

    QIcon recherche("C:/Users/USER/Desktop/Rendez_Vous/recherche.png");
    ui->Rechercher->setIcon(recherche);

    QIcon supprimer("C:/Users/USER/Desktop/Rendez_Vous/supprimer.png");
    ui->Supprimer->setIcon(supprimer);

    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));

    ui->tabWidget->setTabEnabled(1,false);
    ui->tabWidget->setTabEnabled(2,false);
    ui->tabWidget->setTabEnabled(3,false);

    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
       break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
      break;
    case(-1):qDebug() << "arduino is not available";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Connecter_clicked()
{
    QString username = ui->IdentifiantLine->text();
    QString password = ui->MdpLine->text();

    if(username ==  "test" && password == "test")
    {
        Etmp.notifications("Connexion", "Le nom d'utilisateur et le mot de passe sont corrects");
        ui->tabWidget->setCurrentIndex(1);
        ui->tabWidget->setTabEnabled(1,true);
        ui->tabWidget->setTabEnabled(2,true);
        ui->tabWidget->setTabEnabled(3,true);
    }
    else
        Etmp.notifications("Connexion", "Username or password is not correct");
}

void MainWindow::on_Quitter_clicked()
{
    close();
}

//----------------------------------------------------------CRUDS----------------------------------------------------------//

void MainWindow::on_Ajouter_clicked()
{
    int num_rdv = ui->NumLine->text().toInt();
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

    Rendez_Vous R(num_rdv, id_client, date_rdv, heure, periode, salle_rdv, designation);

    bool test=R.ajouter();

    if(test)
    {
        ui->TableView->setModel(Etmp.afficher());
        ui->spinBox->setValue(R.nb_total_rdv());

        Etmp.notifications("Success", "ajout avec success");
    }
    else
        Etmp.notifications("Failed", "ajout echoué");
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

    Rendez_Vous R(num_rdv, id_client, date_rdv, heure, periode, salle_rdv, designation);

    bool test=R.modifier(num_rdv, id_client, date_rdv, heure, periode, salle_rdv, designation);

    if(test)
    {
        ui->TableView->setModel(Etmp.afficher());

        Etmp.notifications("Succès","Modification avec success");
    }
    else
        Etmp.notifications("échoué","Modification echouee");
}

void MainWindow::on_Supprimer_clicked()
{
    int num_rdv =ui->NumLine->text().toInt();
    bool test=Etmp.supprimer(num_rdv);
    Rendez_Vous R;

    if(test)
    {
        ui->TableView->setModel(Etmp.afficher());
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

void MainWindow::on_Rechercher_clicked()
{
    int num_rdv =ui->RechercherLine->text().toInt();
    bool test=Etmp.rechercher(num_rdv);

    if(test)
    {
        ui->TableView->setModel(Etmp.rechercher(num_rdv));

        Etmp.notifications("Succès","Recherche effectuée");
    }
    else
        Etmp.notifications("échoué","Recherche non effectuée");
}

void MainWindow::on_Excel_clicked()
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
void MainWindow::on_Mail_clicked()
{
    ui->tabWidget->setCurrentIndex(2);
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
    Mailing* mailing = new Mailing("hana.mejdoub@esprit.tn",ui->mail_pass->text(), "smtp.gmail.com");
    connect(mailing, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        mailing->sendMail("hana.mejdoub@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        mailing->sendMail("hana.mejdoub@esprit.tn",ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}

void MainWindow::mailSent(QString status)
{
    if(status == "Message sent"){
        Etmp.notifications("reussie","Envoie avec success");
        ui->rcpt->clear();
        ui->subject->clear();
        ui->file->clear();
        ui->msg->clear();
        ui->mail_pass->clear();
    }
    else
        Etmp.notifications("echec","Non envoyé");
}

//----------------------------------------------------------ARDUINO----------------------------------------------------------//

void MainWindow::on_pushButton_aa_clicked()
{
    A.write_to_arduino("0");
    Etmp.notifications("Alarme","Active");
    //msgbox aal cap de fumee
}

void MainWindow::on_pushButton_da_clicked()
{
    A.write_to_arduino("1");
    Etmp.notifications("Alarme","Desactive");
}



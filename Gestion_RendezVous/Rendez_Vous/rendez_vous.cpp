#include "rendez_vous.h"

//Les requettes aana selection ajout suppression update creationdutableau
Rendez_vous::Rendez_vous()
{
    num_rdv=0;
    id_client=0;
    date_rdv="";
    heure="";
    periode="";
    salle_rdv="";
    designation="";
}

Rendez_vous::Rendez_vous(int num_rdv, int id_client, QString date_rdv, QString heure, QString periode, QString salle_rdv, QString designation)
{
    this->num_rdv=num_rdv;
    this->id_client=id_client;
    this->date_rdv=date_rdv;
    this->heure=heure;
    this->periode=periode;
    this->salle_rdv=salle_rdv;
    this->designation=designation;
}

bool Rendez_vous::ajouter()
{
    QSqlQuery query;

    QString n = QString::number(num_rdv);
    QString Id = QString::number(id_client);

    //prepare() prend la requete en parametre pour la preparer a l'execution.

    query.prepare("insert into a_sbc_rendezvous (num_rdv, id_client, date_rdv, heure, periode, salle_rdv, designation)" "values (:num_rdv, :id_client, :date_rdv, :heure, :periode, :salle_rdv, :designation)");

    //Création des variables liées
    // transmettre les valeurs et les variables
    query.bindValue(":num_rdv",n);
    query.bindValue(":id_client",Id);
    query.bindValue(":date_rdv",date_rdv);
    query.bindValue(":heure",heure);
    query.bindValue(":periode",periode);
    query.bindValue(":salle_rdv",salle_rdv);
    query.bindValue(":designation",designation);

    return query.exec(); //exec() envoie la requete pour l'executer

}

QSqlQueryModel * Rendez_vous::afficher()
{
    QSqlQueryModel * model = new QSqlQueryModel(); // Création de l'objet
    model->setQuery("select * from a_sbc_rendezvous");

    //setHeaderData taamel l affichage ml base de donnees
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("num_rdv"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("id_client"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("id_employe"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("date_rdv"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("heure"));
    model->setHeaderData(5,Qt::Horizontal, QObject::tr("periode"));
    model->setHeaderData(6,Qt::Horizontal, QObject::tr("salle_rdv"));
    model->setHeaderData(7,Qt::Horizontal, QObject::tr("designation"));

    return model;
}

bool Rendez_vous::supprimer(int num_rdv)
{
    QSqlQuery query;
    QString n = QString::number(num_rdv);

    query.prepare("Delete from a_sbc_rendezvous where num_rdv= :num_rdv");

    query.bindValue(":num_rdv",n);

    return query.exec();
}

bool Rendez_vous::modifier(int num_rdv, int id_client, QString date_rdv, QString heure, QString periode, QString salle_rdv, QString designation)
{
    QSqlQuery query;

    QString n = QString::number(num_rdv);
    QString Id = QString::number(id_client);

    query.prepare("Update a_sbc_rendezvous set id_client = :id_client, date_rdv = :date_rdv, heure = :heure, periode = :periode, salle_rdv = :salle_rdv, designation = :designation where num_rdv = :num_rdv ");

    query.bindValue(":num_rdv", n);
    query.bindValue(":id_client", Id);
    query.bindValue(":date_rdv", date_rdv);
    query.bindValue(":heure", heure);
    query.bindValue(":periode", periode);
    query.bindValue(":salle_rdv", salle_rdv);
    query.bindValue(":designation", designation);

    return query.exec();
}

QSqlQueryModel * Rendez_vous:: trierParNum_RDV()
{
    QSqlQueryModel * model = new QSqlQueryModel();

    model->setQuery("select * from a_sbc_rendezvous order by NUM_RDV");

    model->setHeaderData(0,Qt::Horizontal, QObject::tr("num_rdv"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("id_client"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("id_employe"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("date_rdv"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("heure"));
    model->setHeaderData(5,Qt::Horizontal, QObject::tr("periode"));
    model->setHeaderData(6,Qt::Horizontal, QObject::tr("salle_rdv"));
    model->setHeaderData(7,Qt::Horizontal, QObject::tr("designation"));

    return model;
}

QSqlQueryModel * Rendez_vous::trierParDate()
{
    QSqlQueryModel * model = new QSqlQueryModel();

    model->setQuery("select * from a_sbc_rendezvous order by DATE_RDV");

    model->setHeaderData(0,Qt::Horizontal, QObject::tr("num_rdv"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("id_client"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("id_employe"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("date_rdv"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("heure"));
    model->setHeaderData(5,Qt::Horizontal, QObject::tr("periode"));
    model->setHeaderData(6,Qt::Horizontal, QObject::tr("salle_rdv"));
    model->setHeaderData(7,Qt::Horizontal, QObject::tr("designation"));

    return model;
}

QSqlQueryModel * Rendez_vous::rechercher(int num_rdv)
{

    QSqlQueryModel * model = new QSqlQueryModel();

    QSqlQuery query;

    QString n = QString::number(num_rdv);

    query.prepare("Select * from a_sbc_rendezvous where num_rdv=:num_rdv");

    query.bindValue(":num_rdv", n);
    query.exec();
    model->setQuery(query);

    model->setHeaderData(0,Qt::Horizontal, QObject::tr("num_rdv"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("id_client"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("id_employe"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("date_rdv"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("heure"));
    model->setHeaderData(5,Qt::Horizontal, QObject::tr("periode"));
    model->setHeaderData(6,Qt::Horizontal, QObject::tr("salle_rdv"));
    model->setHeaderData(7,Qt::Horizontal, QObject::tr("designation"));

    return model;
}
/*
void Rendez_vous::translate()
 {
    QApplication app(argc, argv);

    QTranslator t;

    QStringList languages;
    languages << "French" << "English" << "Turc" ;

    QString lang = QInputDialog::getItem(NULL,"Select Language", "Languge" , languages);

    if ( lang == "English")
    {
        t.load(":/english.qm");
    }
    else
        if ( lang == "Turc")
        {
            t.load(":/Turc.qm");
        }

    if ( lang != "French")
    {
        app.installTranslator(&t);
    }
         //ui->TraductionComboBox->setText(t());
 }*/

/*
//mailing
void  MainWindow::browse()
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
void   MainWindow::sendMail()
{
    Smtp* smtp = new Smtp("mohamedaziz.benhaha@esprit.tn",ui->mail_pass->text(), "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("mohamedaziz.benhaha@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail("mohamedaziz.benhaha@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}
void   MainWindow::mailSent(QString status)
{

    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    ui->rcpt->clear();
    ui->subject->clear();
    ui->file->clear();
    ui->msg->clear();
    ui->mail_pass->clear();
}
*/


/* //export excel
void MainWindow::on_export_excel_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                    tr("Excel Files (*.xls)"));
    if (fileName.isEmpty())
        return;

    ExportExcelObject obj(fileName, "mydata", ui->tableau);

    //colums to export
    obj.addField(0, "entier", "char(20)");
    obj.addField(1, "reel", "char(20)");
    obj.addField(2, "combobox", "char(20)");
    obj.addField(3, "lineedit", "char(20)");
    obj.addField(4, "textedit", "char(20)");
    obj.addField(5, "dateedit", "char(20)");
    obj.addField(5, "timeedit", "char(20)");


    int retVal = obj.export2Excel();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"),
                                 QString(tr("%1 records exported!")).arg(retVal)
                                 );
    }
}
*/


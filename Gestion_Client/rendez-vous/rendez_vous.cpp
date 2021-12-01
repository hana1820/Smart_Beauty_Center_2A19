#include "rendez_vous.h"

Rendez_Vous::Rendez_Vous()
{
    num_rdv=0;
    id_client=0;
    date_rdv="";
    heure="";
    periode="";
    salle_rdv="";
    designation="";
}

Rendez_Vous::Rendez_Vous(int num_rdv, int id_client, QString date_rdv, QString heure, QString periode, QString salle_rdv, QString designation)
{
    this->num_rdv=num_rdv;
    this->id_client=id_client;
    this->date_rdv=date_rdv;
    this->heure=heure;
    this->periode=periode;
    this->salle_rdv=salle_rdv;
    this->designation=designation;
}

int Rendez_Vous::nb_total_rdv()
{
    QSqlQuery q;
    int tot=0;
    q.prepare("select * from a_sbc_rendezvous");
    q.exec();

    while (q.next()) tot++;

    return tot;
}

//----------------------------------------------------------CRUDS----------------------------------------------------------//

bool Rendez_Vous::ajouter()
{
    QSqlQuery query;

    QString n = QString::number(num_rdv);
    QString Id = QString::number(id_client);
    query.prepare("insert into a_sbc_rendezvous (num_rdv, id_client, date_rdv, heure, periode, salle_rdv, designation)" "values (:num_rdv, :id_client, :date_rdv, :heure, :periode, :salle_rdv, :designation)");
    query.bindValue(":num_rdv",n);
    query.bindValue(":id_client",Id);
    query.bindValue(":date_rdv",date_rdv);
    query.bindValue(":heure",heure);
    query.bindValue(":periode",periode);
    query.bindValue(":salle_rdv",salle_rdv);
    query.bindValue(":designation",designation);

    return query.exec();
}

QSqlQueryModel * Rendez_Vous::afficher()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from a_sbc_rendezvous");

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

bool Rendez_Vous::supprimer(int num_rdv)
{
    QSqlQuery query;
    QString n = QString::number(num_rdv);

    query.prepare("Delete from a_sbc_rendezvous where num_rdv= :num_rdv");

    query.bindValue(":num_rdv",n);

    return query.exec();
}

bool Rendez_Vous::modifier(int num_rdv, int id_client, QString date_rdv, QString heure, QString periode, QString salle_rdv, QString designation)
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

//----------------------------------------------------------METIERS----------------------------------------------------------//

QSqlQueryModel * Rendez_Vous:: trierNum_RDV()
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

/*
QSqlQueryModel * Rendez_Vous::trierDate()
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
*/

QSqlQueryModel * Rendez_Vous::rechercher(int num_rdv)
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

void Rendez_Vous::notifications(QString title, QString text)
{
    QSystemTrayIcon * notifyIcon = new QSystemTrayIcon;

    notifyIcon->show();
    notifyIcon->showMessage(title,text,QSystemTrayIcon::Information,10000);
}

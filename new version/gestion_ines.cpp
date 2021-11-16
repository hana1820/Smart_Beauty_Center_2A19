#include "gestion_ines.h"
#include "ui_gestion_ines.h"

gestion_ines::gestion_ines(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gestion_ines)
{
    ui->setupUi(this);

    //affichage contenu de la base
    show_table();
}

gestion_ines::~gestion_ines()
{
    delete ui;
}

//get variables

QString gestion_ines::get_nature() const { //combo box

    return ui->nature->currentText();
}

QString gestion_ines::get_type() const { //combo box

    return ui->type->currentText();
}

QString gestion_ines::get_reference() const { //line edit

    return ui->reference->text();
}

QString gestion_ines::get_nom() const { //line edit

    return ui->nom->text();
}

int gestion_ines::get_quantite() const{ //int

    return ui->quantite->value();
}

double gestion_ines::get_prix() const{ //float

    return ui->prix->value();
}


//fill form


void gestion_ines::fill_form(QString selected ) {
    QSqlQuery query;
    query.prepare("select * from produit where reference= :reference");
    query.bindValue(":reference", selected);
    query.exec();
    while(query.next()){

  ui->reference->setText(query.value(0).toString()); //line edit
  ui->nom->setText(query.value(1).toString()); //line edit
   ui->type->setCurrentText(query.value(2).toString()); //combobox
   ui->nature->setCurrentText(query.value(3).toString()); //combobox
     ui->quantite->setValue(query.value(4).toInt()); // int
     ui->prix->setValue(query.value(5).toReal()); // reel

    }

}

void gestion_ines::clear_form( ) {

    ui->reference->clear();
    ui->nom->clear();
    ui->type->setCurrentIndex(0);
    ui->nature->setCurrentIndex(0);
    ui->prix->setValue(0);
    ui->quantite->setValue(0);

}



//************************ crud ****************************

//ajout

void gestion_ines::on_actionajout_produit_triggered()
{
    //recuperation des donnees
      QString s1=get_reference();
      QString s2=get_nom();
      QString s3=get_type();
      QString s4=get_nature();
      double x2=get_prix();
      int x1=get_quantite();


      //ajout
      produit s(s1,s2,s3,s4,x1,x2);
      s.ajouter();

      clear_form( );

      //refresh du tableau (affichage)
        show_table();
}

//get selected id

void gestion_ines::on_tableau_produit_clicked(const QModelIndex &index)
{
selected=ui->tableau_produit->model()->data(index).toString();
}

//suppression

void gestion_ines::on_actionsuppression_produit_triggered()
{
    produit s;
  s.supprimer(selected);

 //refresh du tableau (affichage)
   show_table();
}

//modification

void gestion_ines::on_tableau_produit_doubleClicked(const QModelIndex &index)
{
    fill_form(selected);
}

void gestion_ines::on_actionmodification_produit_triggered()
{
    //recuperation des donnees
    QString s1=selected;
    QString s2=get_nom();
    QString s3=get_type();
    QString s4=get_nature();
    double x2=get_prix();
    int x1=get_quantite();

      //mofication
      produit s(selected,s2,s3,s4,x1,x2);
      s.modifier(selected);

clear_form( );

    //refresh du tableau (affichage)
     show_table();
}

//affichage
void gestion_ines::show_table(){
//creation model (masque du tableau) : permet recherche et tri
    proxy = new QSortFilterProxyModel();

 //definir la source (tableau original)
    proxy->setSourceModel(tmp.afficher());

 //pour la recherche
    proxy->setFilterCaseSensitivity(Qt::CaseSensitive); // S=/=s (difference entre majiscule et miniscule)
    proxy->setFilterKeyColumn(-1); // chercher dans tout le tableau (-1) ou donner le numero de la colone
   //remplissage tableau avec le masque
    ui->tableau_produit->setModel(proxy);

}


//*******************  metiers ************************

//stat

void gestion_ines::on_actionstat_prix_triggered()
{
    s = new stat_combo();

  s->setWindowTitle("statistique Prix");
  s->choix_pie();
  s->show();
}

void gestion_ines::on_actionstat_type_triggered()
{
    s = new stat_combo();

  s->setWindowTitle("statistique Type");
  s->choix_bar();
  s->show();
}

//recherche

void gestion_ines::on_rech_textChanged(const QString &arg1)
{
    proxy->setFilterFixedString(arg1);

}

void gestion_ines::on_sel_col_currentIndexChanged(const QString &arg1)
{
    sel_col=ui->sel_col->currentIndex()-1;
    proxy->setFilterKeyColumn(sel_col); // chercher dans tout le tableau (-1) ou donner le numero de la colone
}

//Excel
void gestion_ines::on_export_excel_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                    tr("Excel Files (*.xls)"));
    if (fileName.isEmpty())
        return;

    ExportExcelObject obj(fileName, "mydata", ui->tableau_produit);

    //colums to export
    obj.addField(0, "Reference", "char(20)");
    obj.addField(1, "Nom", "char(20)");
    obj.addField(2, "Type", "char(20)");
    obj.addField(3, "Nature", "char(20)");
    obj.addField(4, "Quantite", "char(20)");
    obj.addField(5, "Prix", "char(20)");





    int retVal = obj.export2Excel();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"),
                                 QString(tr("%1 records exported!")).arg(retVal)
                                 );
    }
}

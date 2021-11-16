#ifndef GESTION_INES_H
#define GESTION_INES_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>

#include "produit.h"
#include "exportexcelobject.h"
#include "stat_combo.h"

namespace Ui {
class gestion_ines;
}

class gestion_ines : public QMainWindow
{
    Q_OBJECT

public:
    explicit gestion_ines(QWidget *parent = nullptr);
    ~gestion_ines();

    produit tmp;
    QSortFilterProxyModel *proxy;

    //produit
    QString get_reference () const ;
    QString get_nom () const ;
    QString get_nature() const;
    QString get_type() const;
    double get_prix() const ;
    int get_quantite() const;

    void fill_form(QString);
    void show_table();
    void clear_form();

private slots:
    void on_actionajout_produit_triggered();

    void on_actionsuppression_produit_triggered();

    void on_actionmodification_produit_triggered();

    void on_actionstat_prix_triggered();

    void on_actionstat_type_triggered();

    void on_rech_textChanged(const QString &arg1);

    void on_sel_col_currentIndexChanged(const QString &arg1);

    void on_tableau_produit_clicked(const QModelIndex &index);

    void on_tableau_produit_doubleClicked(const QModelIndex &index);

    void on_export_excel_clicked();

private:
    Ui::gestion_ines *ui;
    QString selected="";
    int sel_col=-1;
    stat_combo *s;
};

#endif // GESTION_INES_H

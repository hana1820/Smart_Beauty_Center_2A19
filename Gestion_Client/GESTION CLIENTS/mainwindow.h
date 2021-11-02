#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "client.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:


    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_pb_valider_clicked();

    void on_tableView_2_activated(const QModelIndex &index);

    void on_pb_annuler_clicked();

    void on_pb_rechercher_clicked();

    void on_pb_recette_clicked();

private:
    Ui::MainWindow *ui;
    Client Ctmp;
};

#endif // MAINWINDOW_H

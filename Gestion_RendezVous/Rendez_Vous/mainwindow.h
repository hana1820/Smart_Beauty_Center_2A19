#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "connection.h"
#include "rendez_vous.h"
#include "mailing.h"
#include "exportexcelobject.h"
#include "arduino.h"

#include <QMainWindow>
#include <QApplication>
#include <QMessageBox>
#include <iostream>
#include <QDebug>
#include <QPixmap>
#include <QDate>
#include <QFileDialog>

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
    void on_Connecter_clicked();

    void on_AjouterRDV_clicked();

    void on_QuitterRDV_clicked();

    void on_ModifierRDV_clicked();

    void on_SupprimerRDV_clicked();

    void on_TrierComboBox_currentIndexChanged(int index);

    void on_RechercherRDV_clicked();

    void on_ExcelRDV_clicked();

    void on_MailRDV_clicked();
    void sendMail();
    void mailSent(QString);
    void browse();
    void on_Quitter_2_clicked();

    void on_pushButton_aa_clicked();

    void on_pushButton_da_clicked();

    void update();

private:
    Ui::MainWindow *ui;
    Rendez_Vous Etmp;

    QStringList files;

    QByteArray data; // variable contenant les données reçues
    Arduino A; // objet temporaire
};
#endif // MAINWINDOW_H

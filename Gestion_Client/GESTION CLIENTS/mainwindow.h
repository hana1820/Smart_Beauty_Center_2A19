#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QtWidgets>
#include <QtNetwork>
#include "client.h"
#include "Arduino.h"

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

    void on_pb_modifier_clicked();

    void on_tableView_2_activated(const QModelIndex &index);

    void on_pb_annuler_clicked();

    void on_pb_rechercher_clicked();

    void on_pb_recette_clicked();

    void on_pb_connexion_clicked();
    void DONNEESRecues();

    void CONNECTE();
    void DECONNECTE();
    void ERREURSOCKET(QAbstractSocket::SocketError erreur);


    void on_pb_envoyer_clicked();



    void on_pb_excel_clicked();

    void on_pb_pdf_clicked();

    void on_pb_chat_clicked();

    void on_pb_accueil_clicked();

    void on_pushButton_2_clicked();

    void on_pb_generer_excel_clicked();

    void on_pb_generer_pdf_clicked();

void update_label();

    void on_pushButton_clicked();





    void on_pushButton_retourInscription_clicked();

    void on_pb_quitter_clicked();

    void on_pushButton_deconnexion_clicked();

    void on_pushButton_passwordforgot_clicked();

private:
    Ui::MainWindow *ui;

    QTcpSocket *socket; // Représente le serveur
    quint16 tailleMessage;
    Client Ctmp;
    QByteArray data; // variable contenant les données reçues
    Arduino A; // objet temporaire
};

#endif // MAINWINDOW_H

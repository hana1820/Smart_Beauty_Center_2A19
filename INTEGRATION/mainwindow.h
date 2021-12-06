#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QtWidgets>
#include <QtNetwork>
#include <QApplication>
#include <QMessageBox>
#include <iostream>
#include <QDebug>
#include <QPixmap>
#include <QDate>
#include <QFileDialog>
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>

#include "produit.h"
#include "exportexcelobject.h"
#include "stat_combo.h"
#include "carte_fidelite.h"

#include "client.h"
#include "Arduino.h"
#include "connection.h"
#include "rendez_vous.h"
#include "mailing.h"
#include "exportexcelobject.h"
#include "employe.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();
    produit tmp;
    carte_fidelite tmp_fid;
    QSortFilterProxyModel *proxy, *proxy_fid;
     int pt_dispo=9999999;

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

    void get_prod_dispo();
    void get_clients();

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

    void on_Connecter_clicked();

    void on_pb_generer_excel_clicked();

    void on_pb_generer_pdf_clicked();

void update_label();

    void on_pushButton_clicked();





    void on_pushButton_retourInscription_clicked();

    void on_pb_quitter_clicked();

    void on_pushButton_deconnexion_clicked();

    void on_pushButton_passwordforgot_clicked();

    void on_pb_configuration_clicked();

    void on_pushButton_APPLIQUER_clicked();



//------------------------------------------------//

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
    void on_QuitterRDV_2_clicked();

    void update();
    void on_pushButton_aa_clicked();
    void on_pushButton_da_clicked();
//----------------------------------------------//

    void on_pb_ajouter_2_clicked();

    void on_pb_supprimer_2_clicked();

    void on_pb_modifier_employe_clicked();

    void on_pb_recherche_employe_clicked();

    void on_comboBox_2_currentIndexChanged(int index);

    //void on_lineEdit_id_connexion_cursorPositionChanged(int arg1, int arg2);

   // void on_pb_ajouter_3_clicked();

    void on_statistique_2_clicked();

    void on_statistique_clicked();

    void on_pushButton_2_clicked();

    void on_localisation_clicked();

    void on_retour_clicked();

    void on_retour_2_clicked();


    void on_ajout_produit_clicked();

    void on_suppression_produit_clicked();

    void on_modification_produit_clicked();

    void on_stat_prix_clicked();

    void on_stat_type_clicked();

    void on_rech_textChanged(const QString &arg1);

    void on_sel_col_currentIndexChanged(const QString &arg1);

    void on_tableau_produit_clicked(const QModelIndex &index);

    void on_tableau_produit_doubleClicked(const QModelIndex &index);

    void on_export_excel_clicked();


    void on_rech_carte_textChanged(const QString &arg1);

    void on_sel_col_carte_currentIndexChanged(const QString &arg1);

    void on_id_client_fid_currentTextChanged(const QString &arg1);

    void on_cartefid_clicked();

    void on_retour_ines_clicked();

    void on_pushButton_aa_2_clicked();

    void on_pushButton_da_2_clicked();

private:
    Ui::MainWindow *ui;
    QString selected="";
    int sel_col=-1,sel_col_fid=-1;
    stat_combo *s;
    QTcpSocket *socket; // Représente le serveur
    quint16 tailleMessage;
    Client Ctmp;
    QByteArray data; // variable contenant les données reçues
    Arduino A; // objet temporaire
    int nombre;
//----------------------------------------------//
    Rendez_Vous Etmp;
    QStringList files;
//----------------------------------------------//
Employe E ;
void refrech() ;
   signals:
void setCenter(QVariant,QVariant);// localisation


};

#endif // MAINWINDOW_H

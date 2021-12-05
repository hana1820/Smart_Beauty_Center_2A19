#include "mainwindow.h"
#include "connection.h"

#include <QApplication>
#include <QMessageBox>
#include <QTranslator>
#include <QInputDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //-----------------------------------------TRADUCTION-----------------------------------------//

    QTranslator t;
    QStringList languages;
    languages << "Français" << "Anglais" << "Turc" ;
    QString lang = QInputDialog::getItem(NULL,QObject::tr("Veuillez choisir la langue"),QObject::tr("Langue"), languages);

    if (lang != "Français")
    {
        a.installTranslator(&t);
    }

    if (lang == "Anglais")
    {
        t.load(":/Rendez_Vous_an_AN.qm");
    }
    else
        if(lang == "Turc")
        {
            t.load(":/Rendez_Vous_tu_TU.qm");
        }

    //--------------------------------------------------------------------------------------------//

    MainWindow w;
    w.setWindowTitle("Magic Touch Application");
    w.setWindowIcon(QIcon(":/img/logo.png"));
    w.setGeometry(100, 60, 1280, 780);
    w.show();

/*  Connection c;
    bool test=c.createConnection();
    if(test)
    {
        w.show();
        QMessageBox::information(nullptr, QObject::tr("la base de données est ouverte"), QObject::tr("Connexion réussie\n" "Cliquez sur Annuler pour quitter"), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("la base de données n est pas ouverte"), QObject::tr("La connexion a échoué \n" "Cliquez sur Annuler pour quitter"), QMessageBox::Cancel);
*/
    return a.exec();
}

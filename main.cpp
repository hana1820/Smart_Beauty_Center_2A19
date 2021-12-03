#include "mainwindow.h"
#include "connection.h"

#include <QApplication>
#include <QMessageBox>
#include <QTranslator>
#include <QInputDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*
    Connection c; //une seule instance de la classe connection;
    bool test=c.createconnection();//etablir la connection
    */


    //-----------------------------------------TRADUCTION-----------------------------------------//

    QTranslator t;
    QStringList languages;
    languages << "Français" << "Anglais" << "Turc" ;
    QString lang = QInputDialog::getItem(NULL,"Veuillez choisir la langue", "Langue", languages);

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
    w.setWindowIcon(QIcon("C:/Users/USER/Desktop/GESTION CLIENTS METIERS/logo.png"));
    w.show();

    /*
    if(test)
    {
        w.show();

        QMessageBox::information(nullptr,QObject::tr("YOUPI, DateBase is Open"),
        QObject::tr("Connection succesful.\n"
          "Click Cancel to quit"),QMessageBox::Cancel);
    }

   else //C'est à dire if connection failed;
    {
        QMessageBox::information(nullptr,QObject::tr("OUPS, DateBase is not Open"),
        QObject::tr("Connection failed.\n"
                    "Click Cancel to quit"),QMessageBox::Cancel);

    }
    */

    return a.exec();
}

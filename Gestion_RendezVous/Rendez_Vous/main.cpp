#include "mainwindow.h"
#include "connection.h"
#include <QApplication>
#include <QMessageBox>
#include <QTranslator>
#include <QInputDialog>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv); //On créé l'application.

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

    Connection c; //Une seule instance de la classe connection

    bool test=c.createconnection(); //Etablir la connexion

    MainWindow w; //appelle lel fenetre

    //w.setWindowIcon(QIcon("logop.png"));

    w.setWindowTitle("Smart Beauty Center Application");

    if(test) //Si la connexion est établie
    {
        w.show(); //afficher fenetre
        /*w.resize(1250,700);*/

        QMessageBox::information(nullptr, QObject::tr("database is open"), QObject::tr("Connection successful\n" "Click Cancel to exit"), QMessageBox::Cancel);
    }
    else //Si la connexion a échoué

        QMessageBox::critical(nullptr, QObject::tr("database is not open"), QObject::tr("Connection failed \n" "Click Cancel to exit"), QMessageBox::Cancel);

    return app.exec(); //execution de l'application
}

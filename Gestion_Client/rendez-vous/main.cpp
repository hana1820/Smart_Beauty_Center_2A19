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
    languages << "Francais" << "Anglais" << "Turc" ;
    QString lang = QInputDialog::getItem(NULL,"Veuillez choisir la langue", "Langue", languages); //QlistDialog
    if (lang != "Francais")
    {
        a.installTranslator(&t);
    }
    if (lang == "Anglais")
    {
        t.load(":/anglais.qm");
    }
    else
        if(lang == "Turc")
        {
            t.load(":/turc.qm");
        }

    MainWindow w;
    w.setWindowTitle("Smart Beauty Center Application");
    w.setWindowIcon(QIcon(":/img/logo.png"));
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

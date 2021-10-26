#include "mainwindow.h"

#include <QApplication>
#include <QMessageBox>
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c; //une seule instance de la classe connection;
    bool test=c.createconnection();//etablir la connection

    MainWindow w;
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



    return a.exec();
}

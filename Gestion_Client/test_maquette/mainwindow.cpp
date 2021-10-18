#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    Client C;
    C.setIdentifiant(ui->lineEdit_id->text());
    C.setprenom(ui->lineEdit_prenom->text());
    C.setnom(ui->lineEdit_nom->text());
    C.setville(ui->lineEdit_ville->text());
    C.setadresse(ui->lineEdit_telephone->text());
}

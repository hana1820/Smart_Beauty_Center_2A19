#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "connection.h"
#include "rendez_vous.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Modifier_clicked();
    void on_supprimer_clicked();
    void on_ajouter_clicked();

    void on_pushButton_3_clicked();

    void on_recherhcer_clicked();

    void on_comboBox_5_currentIndexChanged(int index);

    void on_comboBox_5_currentIndexChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;

    Rendez_vous Etmp;
};
#endif // MAINWINDOW_H

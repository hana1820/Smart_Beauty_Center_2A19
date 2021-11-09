#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QPixmap>
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

    void on_Ajouter_clicked();

    void on_Quitter_clicked();

    void on_Modifier_clicked();

    void on_Supprimer_clicked();

    void on_Rechercher_clicked();

    void on_TrierComboBox_currentIndexChanged(int index);

    void on_TrierComboBox_currentIndexChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;

    Rendez_vous Etmp;
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_cre_paquet_clicked();

    void on_del_paquet_clicked();

    void on_select_paquet_clicked();

    void on_aff_qst_clicked();

    void on_add_cm_clicked();

    void on_aff_rep_clicked();

    void on_mod_qst_clicked();

    void on_mod_rep_clicked();

    void on_del_cm_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

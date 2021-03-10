#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qfile.h"
#include "qtextstream.h"
#include "qfiledialog.h"
#include <qinputdialog.h>
#include <qmessagebox.h>
QDir dirpaquet;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if(QDir("Paquet").exists()==false)
    {
        QDir().mkdir("Paquet");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_cre_paquet_clicked()
{
    QMessageBox Existe;
    bool okpressed;
    Existe.setText("Une erreur s'est produite !");
    QString Nom=QInputDialog::getText(this, "Créer un paquet","Nom du paquet", QLineEdit::Normal,0,&okpressed);
    if(okpressed==true)
    {
        if(QDir("Paquet/"+Nom).exists()==false)
        {
            QDir().mkdir("Paquet/"+Nom);
        }
        else
        {
            Existe.exec();
        }
    }
}

void MainWindow::on_del_paquet_clicked()
{
    QDir Lieu("Paquet");
    QStringList lescm = Lieu.entryList(QDir::AllEntries|QDir::NoDotAndDotDot);
    bool ok;
    QString asupprm= QInputDialog::getItem(this,tr("suppression"),tr("Selectionnez un paquet à supprimer:"),lescm,0,0,&ok);
    if(ok)
    {
        QDir("Paquet/"+asupprm).removeRecursively();
    }
}

void MainWindow::on_select_paquet_clicked()
{
    QDir selpqt = QFileDialog::getExistingDirectory(0, ("Choissisez le paquet"), "Paquet/");
    dirpaquet=selpqt;
    QStringList lescm = selpqt.entryList(QDir::AllEntries|QDir::NoDotAndDotDot);
    ui->select_cm->clear();
    if(selpqt!=QDir().currentPath()&&selpqt.path()!=QDir().currentPath()+"/Paquet") // si on annule
    {
        foreach (const QString &str, lescm) {
            ui->select_cm->addItem(str);
        }
    }
}

void MainWindow::on_aff_qst_clicked()
{
    QMessageBox erreur;
    erreur.setText("Une erreur s'est produite lors de la lecture de la question");
    QMessageBox qst;
    QString paquet=dirpaquet.path();
    QString nom_cm=ui->select_cm->currentText();
    QFile cm(paquet+"/"+nom_cm);
    QString ligne;
    if (cm.open(QIODevice::ReadOnly| QIODevice::Text))
    {
        QTextStream flux(&cm);
        flux.setCodec("UTF-8");
        qst.setText(flux.readLine());
        qst.exec();
    }
    else
    {
        erreur.exec();
    }
}

void MainWindow::on_add_cm_clicked()
{
    bool okappuye;
    QString Acreer=QInputDialog::getText(this,"Ajout","Nom de la carte mémoire:", QLineEdit::Normal,0,&okappuye);
    if(okappuye==true)
    {
        QString paquet=dirpaquet.path();
        QFile fait(paquet+"/"+Acreer+".txt");
        fait.open(QIODevice::WriteOnly|QIODevice::Text);
        fait.close();
        ui->select_cm->addItem(Acreer+".txt");
    }
}


void MainWindow::on_aff_rep_clicked()
{
    QMessageBox erreur;
    erreur.setText("Une erreur s'est produite lors de la lecture de la réponse");
    QMessageBox rep;
    QString paquet=dirpaquet.path();
    QString nom_cm=ui->select_cm->currentText();
    QFile cm(paquet+"/"+nom_cm);

    if (cm.open(QIODevice::ReadOnly| QIODevice::Text))
    {
        QTextStream flux(&cm);
        flux.setCodec("UTF-8");
        flux.readLine();
        rep.setText(flux.readLine());
        rep.exec();
    }
    else
    {
        erreur.exec();
    }
}

void MainWindow::on_mod_qst_clicked()
{
    QString paquet=dirpaquet.path();
    QMessageBox erreur;
    erreur.setText("Une erreur s'est produite lors de la modification de la question");
    QString nom_cm=ui->select_cm->currentText();
    QFile cm(paquet+"/"+nom_cm);
    QString Rep;
    if (cm.open(QIODevice::ReadWrite| QIODevice::Text))
    {
        QTextStream flux(&cm);
        flux.setCodec("UTF-8");
        flux.readLine(); // pour passer 2 eme ligne
        Rep=flux.readLine();
        cm.close();
        QString newqst=QInputDialog::getText(this, tr("QInputDialog::getText()"),tr("Quelle est la nouvelle question?"), QLineEdit::Normal);
        if(cm.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            QTextStream flux(&cm);
            flux.setCodec("UTF-8");
            flux << newqst << endl << Rep << endl;
            cm.close();
        }
    }
    else
    {
        erreur.exec();
    }
}

void MainWindow::on_mod_rep_clicked()
{
    QString paquet=dirpaquet.path();
    QString nom_cm=ui->select_cm->currentText();
    QFile cm(paquet+"/"+nom_cm);
    QString qst;
    QMessageBox erreur;
    erreur.setText("Une erreur s'est produite lors de la modification de la réponse");
    if (cm.open(QIODevice::ReadWrite| QIODevice::Text))
    {
        QTextStream flux(&cm);
        flux.setCodec("UTF-8");
        qst=flux.readLine();
        cm.close();
        QString newrep=QInputDialog::getText(this, tr("QInputDialog::getText()"),tr("Quelle est la nouvelle question?"), QLineEdit::Normal);
        if(cm.open(QIODevice::WriteOnly|QIODevice::Text)){
            QTextStream flux(&cm);
            flux.setCodec("UTF-8");
            flux << qst << endl << newrep << endl;
            cm.close();
        }
    }
    else
    {
        erreur.exec();
    }
}

void MainWindow::on_del_cm_clicked()
{
    int indexdusuppr=ui->select_cm->currentIndex();
    QString paquet =dirpaquet.path();
    QFile asupprm(paquet+"/"+ui->select_cm->currentText());
    asupprm.remove();
    ui->select_cm->removeItem(indexdusuppr);
}


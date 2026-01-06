#include "mainwindow.h"
#include "loaddialog.h"
#include "ui_mainwindow.h"
#include <QFile>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , enabled(true)
    , enabled_edit(false)
    , current(0)
{
    ui->setupUi(this);
    ui->button_forward->setEnabled(false);
    ui->button_back->setEnabled(false);
    ui->button_edit->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_add_clicked()
{
    if(enabled)
    {
        contact c;
        c.first_name = ui->lineEdit_first_name->text();
        c.last_name = ui->lineEdit_last_name->text();
        contact_list.push_back(c);
        enabled = false;
        ui->label_3->setText(QString::number(contact_list.size()) + "/" + QString::number(contact_list.size()));
        current = contact_list.size() - 1;

        if(contact_list.size()>1)
            ui->button_back->setEnabled(true);
        ui->button_edit->setEnabled(true);
    } else {
        enabled = true;
        ui->lineEdit_first_name->setText("");
        ui->lineEdit_last_name->setText("");
        ui->button_forward->setEnabled(false);
        ui->button_back->setEnabled(false);
    }
    ui->button_edit->setEnabled(!enabled);
    ui->lineEdit_first_name->setEnabled(enabled);
    ui->lineEdit_last_name->setEnabled(enabled);
}


void MainWindow::on_button_back_clicked()
{
    --current;
    updateUI();
}


void MainWindow::on_button_forward_clicked()
{
    ++current;
    updateUI();
}

void MainWindow::updateUI()
{
    contact c = contact_list[current];
    ui->lineEdit_first_name->setText(c.first_name);
    ui->lineEdit_last_name->setText(c.last_name);

    // gestire abilitazione/disabilitazione tasti backward e forward
    if(current == 0)
    {
        ui->button_back->setEnabled(false);
        ui->button_forward->setEnabled(true);
    }
    else if(current == (contact_list.size() - 1))
    {
        ui->button_back->setEnabled(true);
        ui->button_forward->setEnabled(false);
    }
    else
    {
        ui->button_forward->setEnabled(true);
        ui->button_back->setEnabled(true);
    }

    // aggiornare label contatore
    ui->label_3->setText(QString::number(current+1) + "/" + QString::number(contact_list.size()));

}


void MainWindow::on_button_edit_clicked()
{
    if(enabled_edit)
    {
        contact c;
        c.first_name = ui->lineEdit_first_name->text();
        c.last_name = ui->lineEdit_last_name->text();
        contact_list[current] = c;
        enabled_edit = false;
    } else {
        enabled_edit = true;
        ui->button_forward->setEnabled(false);
        ui->button_back->setEnabled(false);
    }

    ui->button_add->setEnabled(!enabled_edit);
    ui->lineEdit_first_name->setEnabled(enabled_edit);
    ui->lineEdit_last_name->setEnabled(enabled_edit);

    updateUI();
}


void MainWindow::on_button_sort_clicked()
{
    std::sort(contact_list.begin(), contact_list.end(), sort_concact());
    current = contact_list.size() - 1;
    updateUI();
}


void MainWindow::on_button_load_clicked()
{
    LoadDialog dlg(this);

    if(dlg.exec() == QDialog::Accepted)
    {
        QFile file("contact_list.csv");
        file.open(QIODevice::ReadOnly);
        QTextStream tstream(&file);

        contact_list.clear();
        while(!tstream.atEnd())
        {
            QString str = tstream.readLine();
            QStringList str_list = str.split(",");
            contact c;
            c.last_name = str_list[0];
            c.first_name = str_list[1];
            contact_list.push_back(c);
        }

        file.close();

        current = contact_list.size() - 1;
        updateUI();
    }
}


void MainWindow::on_button_save_clicked()
{
    QFile file("contact_list.csv");
    file.open(QIODevice::WriteOnly);
    QTextStream tstream(&file);

    for(unsigned int i=0 ; i<contact_list.size() ; ++i )
    {
        contact c = contact_list[i];
        tstream << c.last_name << "," << c.first_name << "\n";
    }

    file.close();
}


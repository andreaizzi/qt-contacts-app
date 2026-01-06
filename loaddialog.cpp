#include "loaddialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>

LoadDialog::LoadDialog(QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout *layout = new QVBoxLayout();
    QHBoxLayout *h_layout = new QHBoxLayout();

    label = new QLabel("Il caricamento dei dati dal file comporterà la perdita di quelli non salvati. Procedere?");
    button_accept = new QPushButton("OK");
    button_deny = new QPushButton("Cancel");

    h_layout->addWidget(button_deny);
    h_layout->addWidget(button_accept);
    layout->addWidget(label);
    layout->addLayout(h_layout);
    this->setLayout(layout);

    connect(button_accept, SIGNAL(clicked()), this, SLOT(accept()));
    connect(button_deny, SIGNAL(clicked()), this, SLOT(close()));
}


LoadDialog::~LoadDialog()
{}

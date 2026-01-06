#ifndef LOADDIALOG_H
#define LOADDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class LoadDialog;
}
QT_END_NAMESPACE


class LoadDialog : public QDialog
{
public:
    LoadDialog(QWidget *parent = nullptr);
    ~LoadDialog();

private:
    QLabel *label;
    QPushButton *button_accept;
    QPushButton *button_deny;
};

#endif // LOADDIALOG_H

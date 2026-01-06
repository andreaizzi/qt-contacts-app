#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

struct contact{
    QString first_name;
    QString last_name;
};

struct sort_concact {
    bool operator()(const contact &ln1, const contact &ln2) {
        return ln1.last_name < ln2.last_name;
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_button_add_clicked();
    void on_button_back_clicked();
    void on_button_forward_clicked();

    void on_button_edit_clicked();

    void on_button_sort_clicked();

    void on_button_load_clicked();

    void on_button_save_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<contact> contact_list;
    bool enabled;
    bool enabled_edit;
    int current;
    void updateUI();
};
#endif // MAINWINDOW_H

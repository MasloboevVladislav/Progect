#ifndef EXTRAFUNCTION_H
#define EXTRAFUNCTION_H

#include <QDialog>
#include <QString>
#include "mainwindow.h"

namespace Ui {
class ExtraFunction;
}

class ExtraFunction : public QDialog
{
    Q_OBJECT

public:
    explicit ExtraFunction(MainWindow *main, QWidget *parent = nullptr);
    ~ExtraFunction();
    bool isAuthorized;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();


private:
    Ui::ExtraFunction *ui;
    MainWindow *f_window;
};

#endif // EXTRAFUNCTION_H

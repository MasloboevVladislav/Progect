#ifndef TASK_H
#define TASK_H

#include <QDialog>
#include <QString>

namespace Ui {
class Task;
}

class Task : public QDialog
{
    Q_OBJECT

public:
    explicit Task(QString _log, QWidget *parent = nullptr);
    ~Task();

private slots:
    void on_pushButtonGetTask_clicked();

    void on_buttonBox_accepted();

private:
    Ui::Task *ui;
    QString log;
};

#endif // TASK_H

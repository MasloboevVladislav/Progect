#include "task.h"
#include "ui_task.h"
#include "socket.h"
#include <QErrorMessage>
#include <QMessageBox>

Task::Task(QString _log, QWidget *parent) : // Вызов окна с заданием
    QDialog(parent),
    ui(new Ui::Task)
{
    ui->setupUi(this);
    log = _log;
    Socket::GetInstance()->sk.write("ctrl:names"); // Возможность вывода задания через поля ввода текста
    Socket::GetInstance()->sk.waitForReadyRead(3000);
    QString buf = Socket::GetInstance()->sk.readAll();
    QStringList categories = buf.trimmed().split("\t");
    ui->comboBoxCategories->addItems(categories);
}

Task::~Task() // Диструктор, активирующийся при закрытии окна задания
{
    delete ui;
}

QString GetTaskTemplate(QString name) // Выбор шаблона задания из базы данных
{
    QString cmd = "ctrl:task_template&" + name;
    Socket::GetInstance()->sk.write(cmd.toUtf8());
    Socket::GetInstance()->sk.waitForReadyRead(3000);
    QString buf = Socket::GetInstance()->sk.readAll();

    return buf;
}

void Task::on_pushButtonGetTask_clicked() // Выводит выбранный вариант задания при нажатии кнопки "Получить задание"
{
    QString name = ui->comboBoxCategories->currentText();

    ui->labelTask->setText(GetTaskTemplate(name));

    QString cmd = "ctrl:task&" + name+"&"+log;
    Socket::GetInstance()->sk.write(cmd.toUtf8());
    Socket::GetInstance()->sk.waitForReadyRead(3000);
    QString buf = Socket::GetInstance()->sk.readAll();
    ui->plainTextEditVariant->document()->setPlainText(buf);
}

void Task::on_buttonBox_accepted() // Принимает данные из поля ввода ответа
{
    QString cmd = "ctrl:answer&" + ui->plainTextEditAnswer->toPlainText()+"&"+log;
    Socket::GetInstance()->sk.write(cmd.toUtf8());
    Socket::GetInstance()->sk.waitForReadyRead(3000);
    QString buf = Socket::GetInstance()->sk.readAll(); // Сравнение с правильным ответом

    QMessageBox msgBox;
    msgBox.setStandardButtons(QMessageBox::Ok);

    if (buf == "true")
    {
        msgBox.setInformativeText("Ответ правильный");
    }
    else
    {
        msgBox.setInformativeText("Ответ неправильный");
    }

    msgBox.exec();
}


#ifndef DATABASE_U_H
#define DATABASE_U_H


#include <QObject>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QString>


class Database_u
{
public:
    static Database_u* GetInstance();

    bool AddUser(QString login, QString password);
    bool CheckUser(QString login, QString password);
    QString GetTaskNames();
    QString GetTaskTemplate(QString name);
    void AddAnswer(QString login, QString answer, bool isCorrect);
    void AddVariant(QString login, QString name, QString answer, bool isCorrect); // Добавляем ответы в таблицу базы данных для ведения статистики и последующего использования
    QString get_answer(QString login);
    QString GetCurrentTask(QString login);

    QString GetStat(QString login);

private:
    static Database_u *instance;
    QSqlDatabase db;

    Database_u();
    bool CheckLogin(QString login);
    int GetUserId(QString login);
    int GetTaskId(QString name);
};

#endif // DATABASE_U_H

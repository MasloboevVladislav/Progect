#ifndef DATABASE_U_H
#define DATABASE_U_H


#include <QObject>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QString>

/*!
 * \brief класс базы данных The Database_u class
 */
class Database_u
{
public:
    static Database_u* GetInstance();

    /*!
     * \brief Функция добавления юзеров
     * \param login
     * \param password
     * \return
     */
    bool AddUser(QString login, QString password);

    /*!
     * \brief Функция проверки юзера в базе при регистрации/авторизации
     * \param login
     * \param password
     * \return
     */
    bool CheckUser(QString login, QString password);

    /*!
     * \brief Функция получения типа задания
     * \return
     */
    QString GetTaskNames();

    /*!
     * \brief Функция получения шаблона задания
     * \param name
     * \return
     */
    QString GetTaskTemplate(QString name);

    /*!
     * \brief Функция добавления ответов в базу для ведения статистики
     * \param login
     * \param answer
     * \param isCorrect
     */
    void AddAnswer(QString login, QString answer, bool isCorrect);

    /*!
     * \brief Функция как AddAnswer, только заносится задание
     * \param login
     * \param name
     * \param answer
     * \param isCorrect
     */
    void AddVariant(QString login, QString name, QString answer, bool isCorrect);

    /*!
     * \brief Получение ответов из базы
     * \param login
     * \return
     */
    QString get_answer(QString login);

    /*!
     * \brief Получение нынешнего задания
     * \param login
     * \return
     */
    QString GetCurrentTask(QString login);

    /*!
     * \brief Получение статистики из базы
     * \param login
     * \return
     */
    QString GetStat(QString login);

private:
    static Database_u *instance;
    QSqlDatabase db;

    Database_u();

    /*!
     * \brief Проверка авторизации
     * \param login
     * \return
     */
    bool CheckLogin(QString login);

    /*!
     * \brief Получение ID пользователя
     * \param login
     * \return
     */
    int GetUserId(QString login);

    /*!
     * \brief Получение ID задания
     * \param name
     * \return
     */
    int GetTaskId(QString name);
};

#endif // DATABASE_U_H

#ifndef TASK_H
#define TASK_H

#include <QDialog>
#include <QString>

namespace Ui {
class Task;
}

/*!
 * \brief Класс для заданий
 */
class Task : public QDialog
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор окна заданий
     * \param _log
     * \param parent
     */
    explicit Task(QString _log, QWidget *parent = nullptr);

    /*!
     * Деструктор окна заданий
     */
    ~Task();

private slots:
    /*!
     * \brief Кнопка получения задания
     */
    void on_pushButtonGetTask_clicked();

    /*!
     * \brief Кнопка "Ок" для приема ответа
     */
    void on_buttonBox_accepted();

private:
    Ui::Task *ui;
    QString log;
};

#endif // TASK_H

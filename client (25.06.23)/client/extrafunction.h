#ifndef EXTRAFUNCTION_H
#define EXTRAFUNCTION_H

#include <QDialog>
#include <QString>
#include "mainwindow.h"

namespace Ui {
class ExtraFunction;
}

/*!
 * Класс для окна авторизации
 */
class ExtraFunction : public QDialog
{
    Q_OBJECT

public:

    /*!
     * \brief коструктор окна авторизации ExtraFunction
     * \param qMain
     * \param parent
     */
    explicit ExtraFunction(MainWindow *main, QWidget *parent = nullptr);

    /*!
     * Деструктор окна ExtraFunction
    */
    ~ExtraFunction();

    bool isAuthorized;

private slots:
    /*!
     * \brief Подтверждение авторизации - on_pushButton_clicked
     */
    void on_pushButton_clicked();

    /*!
     * \brief Переход в окно регистрации - on_pushButton_2_clicked
     */
    void on_pushButton_2_clicked();


private:
    Ui::ExtraFunction *ui;
    MainWindow *f_window;
};

#endif // EXTRAFUNCTION_H

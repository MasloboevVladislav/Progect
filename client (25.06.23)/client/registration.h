#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QDialog>

namespace Ui {
class Registration;
}

/*!
 * \brief Класс окна регистрации
 */
class Registration : public QDialog
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор окна регистрации
     * \param parent
     */
    explicit Registration(QWidget *parent = nullptr);

    /*!
     * Деструктор окна
     */
    ~Registration();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Registration *ui;
};

#endif // REGISTRATION_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextStream>
#include <QCoreApplication>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*!
 * \brief Класс основного окна - MainWindow
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief Конструктор окна
     * \param parent
     */
    MainWindow(QWidget *parent = nullptr);

    /*!
     * Деструктор окна
     */
    ~MainWindow();
    bool isError;
    void setlog(QString _log){log = _log;}

public slots:
    /*!
     * \brief Кнопка "connect"
     */

    void on_pushButton_clicked();

    /*!
     * \brief Кнопка "-->"
     */
    void on_pushButton_2_clicked();

    /*!
     * \brief Окно для записи
     */
    void on_lineEdit_returnPressed();

    /*!
     * \brief Сообщение об отключении сервера
     */
    void ClientDisconnected();
private:
    Ui::MainWindow *ui;
    QByteArray Data;
    bool skip_read;
    QString log;

    void SendToServer(QString str);
    void Connect();

public slots:
    void slotReadyRead();
private slots:
    //void on_textinfo_anchorClicked(const QUrl &arg1);
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
};
#endif // MAINWINDOW_H

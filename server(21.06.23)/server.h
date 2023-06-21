#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QObject>
#include <QByteArray>
#include <QtNetwork>
#include <QTextStream>
#include <QSqlDatabase>
#include <QDebug>
#include "database_u.h"

/*!
 * \brief Класс сервера
 */
class Server: public QTcpServer
{
    Q_OBJECT
public:
    Server();
    ~Server();
    QTcpSocket* socket;

private:
    QVector <QTcpSocket*> Sockets;
    int server_status;
    QByteArray Data;
    void SendToClient(QString str);

public slots:
    /*!
     * \brief Функция для подключения к серверу
     * \param socketDescriptor
     */
    void incomingConnection(qintptr socketDescriptor);

    /*!
     * \brief ПодготоslotReadyRead
     */
    void slotReadyRead();

    /*!
     * \brief Очистка сокетов отключившегося пользователя
     */
    void clientDisconnected();
};

#endif // SERVER_H

#ifndef SERVER_H
#define SERVER_H

#include <QPixmap>
#include <QNetworkReply>

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(QObject *parent = 0);

public slots:
    void upload(const QString &filename);
};

#endif // SERVER_H

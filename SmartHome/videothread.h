#ifndef VIDEOTHREAD_H
#define VIDEOTHREAD_H

#include <QThread>
#include <QImage>
#include <QDateTime>
#include <QtNetwork/QTcpSocket>

class VideoThread : public QThread
{
    Q_OBJECT
public:
    VideoThread(QObject *parent = 0);

    void setHostAddress(QString,int);
    void stopCapture();

protected:
    void run();

signals:
    void statusMessage(QString);
    void errorState(QString);
    void socketConnected(bool);
    void curImgChanged(QImage);

private:
    QImage curImg;

    QString ip;
    int port;

    bool stopFlag;
};

#endif // VIDEOTHREAD_H

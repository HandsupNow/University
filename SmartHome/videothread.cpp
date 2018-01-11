#include "videothread.h"

#include <QDebug>


VideoThread::VideoThread(QObject *parent) :
    QThread(parent)
{
}

void VideoThread::run()
{
    stopFlag = false;
    QTcpSocket tcpSocket;
    QByteArray dataStream;
    QByteArray frame;
    tcpSocket.connectToHost(ip,port);
    if(!tcpSocket.waitForConnected())//等待连接请求成功
    {
        emit errorState("Server unreachable!");
        //qDebug() << "tcp connect error!";
        return;
    }
    //qDebug() << "tcp connect success!";
    //用在成功连接后以开启录像按键功能
    emit socketConnected(true);

    dataStream.clear();
    dataStream = "?action=stream\n";
    tcpSocket.write(dataStream);
    if(!tcpSocket.waitForBytesWritten())//等待数据发送完毕
    {
        emit errorState("Request sent fail!");
        //qDebug() << "Request sent fail!";
        return;
    }

    //删除报文头
    dataStream.clear();
    while(!dataStream.contains("\r\n\r\n"))
    {
        if(!tcpSocket.waitForReadyRead())
        {
            emit errorState("None DataHead.");
            //qDebug() << "None DataHead.";
            return;
        }
        dataStream.append(tcpSocket.readAll());
    }
    dataStream.remove(0,dataStream.indexOf("\r\n\r\n")+4);

    //提取数据
    while(!stopFlag)
    {
        while(!dataStream.contains("\r\n--"))
        {
            if(!tcpSocket.waitForReadyRead())
            {
                emit errorState("None data.");
                //qDebug() << "None data.";
                return;
            }
            dataStream.append(tcpSocket.readAll());
        }
        dataStream.remove(0,dataStream.indexOf("\n\n")+2);//删除数据头
        frame = dataStream.mid(0,dataStream.indexOf("\r\n--"));//取出图片数据
        dataStream.remove(0,frame.size()+4);
        curImg.loadFromData(frame,"JPEG");
        emit curImgChanged(curImg);
    }
}

void VideoThread::setHostAddress(QString ip, int port)
{
    this->ip = ip;
    this->port = port;
}

void VideoThread::stopCapture()
{
    stopFlag = true;
}

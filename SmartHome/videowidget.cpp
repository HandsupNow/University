#include "videowidget.h"
#include <QPainter>
VideoWidget::VideoWidget(QWidget *parent) : QWidget(parent)
{
    videoThread = new VideoThread(this);
    connect(videoThread,SIGNAL(curImgChanged(QImage))
            ,this,SLOT(setImage(QImage)));

    videoThread->setHostAddress("127.0.0.1",10002);
    videoThread->start();

    backImage.load(":/images/ipad.png");

//    curImg = QImage(640,480,QImage::Format_RGB32);

    rectBack.setRect(0,0,768,540);
    rectVideo.setRect(62,26,649,490);
}

void VideoWidget::setImage(QImage image)
{
    curImg = image;
    update();
}

void VideoWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.drawImage(rectBack,backImage);
    painter.drawImage(rectVideo,curImg);
}

void VideoWidget::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    this->setVisible(false);
}

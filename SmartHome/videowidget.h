#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QWidget>

#include "videothread.h" // 添加视频采集模块

class VideoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VideoWidget(QWidget *parent = 0);

signals:

public slots:
    void setImage(QImage image); //设置当前图片
private:
    VideoThread *videoThread; //视频采集对象

    QImage curImg; //保存当前图片
    QImage backImage; //背景图片

    QRect rectBack; //背景矩形区域
    QRect rectVideo; //绘制视频区域

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

};

#endif // VIDEOWIDGET_H

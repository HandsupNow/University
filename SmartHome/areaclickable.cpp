#include "areaclickable.h"
#include <QPainter>

AreaClickable::AreaClickable(QWidget *parent) : QWidget(parent)
{

}

AreaClickable::~AreaClickable()
{

}

void AreaClickable::setPixMap(const QPixmap &cPix)
{
    pix = cPix;
}

void AreaClickable::paintEvent(QPaintEvent *)
{
    if(pix.isNull())
        return;
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

void AreaClickable::mouseReleaseEvent(QMouseEvent *)
{
    emit clicked(); //发送信号
}


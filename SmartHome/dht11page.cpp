#include "dht11page.h"
#include <QPainter>

DHT11Page::DHT11Page(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(245,282);
    ia = 0;
    ib = 0;
    numPix[0].load(":/images/num_0.png");
    numPix[1].load(":/images/num_1.png");
    numPix[2].load(":/images/num_2.png");
    numPix[3].load(":/images/num_3.png");
    numPix[4].load(":/images/num_4.png");
    numPix[5].load(":/images/num_5.png");
    numPix[6].load(":/images/num_6.png");
    numPix[7].load(":/images/num_7.png");
    numPix[8].load(":/images/num_8.png");
    numPix[9].load(":/images/num_9.png");

}

DHT11Page::~DHT11Page()
{

}

void DHT11Page::setData(int a, int b)
{
    ia = a;
    ib = b;
}

void DHT11Page::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QPixmap pix(":/images/temperature.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    int iGeWei;
    int iShiWei;

    //温度
    iShiWei = ia / 10 % 10;
    iGeWei = ia %10;
    painter.drawPixmap(60,32,41,72,numPix[iShiWei]);
    painter.drawPixmap(100,32,41,72,numPix[iGeWei]);
    painter.drawPixmap(148,32,41,72,numPix[0]);

    //湿度
    iShiWei = ib / 10 % 10;
    iGeWei = ib %10;
    painter.drawPixmap(60,114,41,72,numPix[iShiWei]);
    painter.drawPixmap(100,114,41,72,numPix[iGeWei]);
    painter.drawPixmap(148,114,41,72,numPix[0]);
}

void DHT11Page::mouseReleaseEvent(QMouseEvent *)
{
    this->setVisible(false);
}


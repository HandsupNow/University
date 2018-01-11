#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include "showpage.h"
#include "myserialport.h"

ShowPage::ShowPage(QWidget *parent) : QWidget(parent)
{
      this->setFixedSize(1024,768);
    bLeftLightIsOpen = false;
    bRightLightIsOpen = false;
    bMidLightIsOpen = false;
    iChuanglianStat = 0;
    //详情点击区域
    areaMoreAboutWidget = new AreaClickable(this);
    areaMoreAboutWidget->setGeometry(QRect(544 ,508 ,130, 39));
    connect(areaMoreAboutWidget,SIGNAL(clicked()),
            this,SLOT(moreAboutWidgetClickedSlot()));
    //areaLeftLight
    areaLeftLight = new AreaClickable(this);
    areaLeftLight->setGeometry(QRect(520,387,60,30));
    connect(areaLeftLight,SIGNAL(clicked()),
            this,SLOT(areaLeftLightClickedSlot()));
    //areaRightLight
    areaRightLight = new AreaClickable(this);
    areaRightLight->setGeometry(QRect(946,390,100,60));
    connect(areaRightLight,SIGNAL(clicked()),
            this,SLOT(areaRightLightClickedSlot()));
    //areaPad
    areaPad = new AreaClickable(this);
    areaPad->setGeometry(QRect(292,583,81,43));
    connect(areaPad,SIGNAL(clicked()),
            this,SLOT(areaPadClickedSlot()));
    //areaOpen
    areaOpen = new AreaClickable(this);
    areaOpen->setGeometry(QRect(254,83,260,390));
    connect(areaOpen,SIGNAL(clicked()),
            this,SLOT(areaOpenClickedSlot()));
    //areaClose
    areaClose = new AreaClickable(this);
    areaClose->setGeometry(QRect(45,100,175,450));
    connect(areaClose,SIGNAL(clicked()),
            this,SLOT(areaCloseClickedSlot()));
    areaDHT11 = new AreaClickable(this);
    areaDHT11->setGeometry(QRect(922,298,36,32));
    connect(areaDHT11,SIGNAL(clicked()),
             this,SLOT(areaDHT11ClickedSlot()));

    areaBall = new AreaClickable(this);
    areaBall->setGeometry(QRect(86,608,30,30));
    connect(areaBall,SIGNAL(clicked()),
             this,SLOT(areaBallClickedSlot()));
    areaBall->setPixMap(QPixmap(":/images/ball.png"));

    pHomePage = new HomePageWidget(this);
    pHomePage->setGeometry(QRect(112,84,800,600));
    pHomePage->setVisible(false);

    pDHT11Page = new DHT11Page(this);
    pDHT11Page->setGeometry(QRect(390,243,245,282));
    pDHT11Page->setVisible(false);

    pVideoPage = new VideoWidget(this);
    pVideoPage->setGeometry(QRect(128,114,768,540));
    pVideoPage->setVisible(false);

    chuanglianPix[0].load(":/images/cl0.png");
    chuanglianPix[1].load(":/images/cl1.png");
    chuanglianPix[2].load(":/images/cl2.png");
    chuanglianPix[3].load(":/images/cl3.png");
    chuanglianPix[4].load(":/images/cl4.png");

    backGroundPix[1].load(":/images/black1.png");
    backGroundPix[2].load(":/images/black2.png");
    backGroundPix[3].load(":/images/black3.png");
    backGroundPix[4].load(":/images/black4.png");

    connect(MySerialPort::getobject(),SIGNAL(newDataRead(int,int,bool,bool,bool)),this,SLOT(newDataGet(int,int,bool,bool,bool)));
}

ShowPage::~ShowPage()
{

}

void ShowPage::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix(":/images/background.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    if(bLeftLightIsOpen)
    {
        QPixmap pixLeft(":/images/left_on.png");
        painter.drawPixmap(465,300,187,164,pixLeft);
    }
    if(bRightLightIsOpen)
    {
        QPixmap pixRight(":/images/right_on.png");
        painter.drawPixmap(883,279,141,221,pixRight);
    }
    if(bMidLightIsOpen)
    {
        QPixmap pixMId(":/images/mid_on.png");
        painter.drawPixmap(427,67,103,80,pixMId);
    }

    paintChuanglian(painter);
}

void ShowPage::mouseReleaseEvent(QMouseEvent *e)
{
    qDebug() << "当前位置坐标为：（" << e->x() <<"," << e->y() << ")。";
    pHomePage->setVisible(false);
    pDHT11Page->setVisible(false);
    pVideoPage->setVisible(false);

}

void ShowPage::paintChuanglian(QPainter &painter)
{
    QRect rect(0,0,1024,768);
    if(iChuanglianStat == 0)
    {
        painter.drawPixmap(rect,chuanglianPix[0]);
    }
    else
    {
        painter.drawPixmap(rect,chuanglianPix[iChuanglianStat]);
        painter.drawPixmap(rect,backGroundPix[iChuanglianStat]);
    }
}

void ShowPage::moreAboutWidgetClickedSlot()
{
    qDebug() << "moreAboutWidgetClickedSlot";
    pHomePage->refrashPageData();
    pHomePage->setVisible(true);
}

void ShowPage::areaLeftLightClickedSlot()
{
    //qDebug() << "areaLeftLightClickedSlot";
    if(bLeftLightIsOpen == false)
    {
        bLeftLightIsOpen = true;
        MySerialPort::getobject()->sendData(MySerialPort::LEDData,MySerialPort::LED1 | MySerialPort::LED2,MySerialPort::LEDOpen);
    }
    else
    {
        bLeftLightIsOpen = false;
        MySerialPort::getobject()->sendData(MySerialPort::LEDData,MySerialPort::LED1 | MySerialPort::LED2,MySerialPort::LEDClose);

    }
    this->update();
}

void ShowPage::areaRightLightClickedSlot()
{
    //qDebug() << "areaRightLightClickedSlot";
    if(bRightLightIsOpen == false)
    {
        bRightLightIsOpen = true;
        MySerialPort::getobject()->sendData(MySerialPort::LEDData,MySerialPort::LED7 | MySerialPort::LED8,MySerialPort::LEDOpen);

    }
    else
    {
        bRightLightIsOpen = false;
        MySerialPort::getobject()->sendData(MySerialPort::LEDData,MySerialPort::LED7 | MySerialPort::LED8,MySerialPort::LEDClose);

    }
    this->update();
}

void ShowPage::areaPadClickedSlot()
{
    //qDebug() << "areaPadClickedSlot";
    pVideoPage->setVisible(true);
}

void ShowPage::areaOpenClickedSlot()
{
    //qDebug() << "areaOpenClickedSlot";
    iChuanglianStat --;
    if(iChuanglianStat < 0)
    {
        iChuanglianStat = 0;
    }
    else
    {
        MySerialPort::getobject()->sendData(MySerialPort::MotorData,MySerialPort::MotorRight);
    }
    this->update();
}

void ShowPage::areaCloseClickedSlot()
{
    //qDebug() << "areaCloseClickedSlot";
    iChuanglianStat ++;
    if(iChuanglianStat > 4)
    {
        iChuanglianStat = 4;
    }
    else
    {
        MySerialPort::getobject()->sendData(MySerialPort::MotorData,MySerialPort::MotorLeft);
    }
    this->update();
}
void ShowPage::areaDHT11ClickedSlot()
{
    //qDebug() << "areaDHT11ClickedSlot";
    pDHT11Page->setVisible(true);
}

void ShowPage::areaBallClickedSlot()
{
    QPropertyAnimation *animl = new QPropertyAnimation(areaBall,"pos");
    QPropertyAnimation *anim2 = new QPropertyAnimation(areaBall,"pos");
    animl->setDuration(250);
    animl->setStartValue(QPoint(86,608));
    animl->setEndValue(QPoint(86,500));

    anim2->setDuration(1500);
    anim2->setStartValue(QPoint(86,500));
    anim2->setEndValue(QPoint(86,608));
    anim2->setEasingCurve(QEasingCurve::OutBounce);

    QSequentialAnimationGroup *group = new QSequentialAnimationGroup;
    group->addAnimation(animl);
    group->addAnimation(anim2);
    group->start();
}

void ShowPage::newDataGet(int a, int b, bool bGM, bool bHW, bool bZD)
{
    pDHT11Page->setData(a,b);
    if(bGM && bHW)
    {
        //开启大灯
        bMidLightIsOpen = true;
    }
    else
    {
        //关闭大灯
        bMidLightIsOpen = false;
    }

    if(bZD)
        areaBallClickedSlot();

    this->update();
}


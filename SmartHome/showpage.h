#ifndef SHOWPAGE_H
#define SHOWPAGE_H

#include <QWidget>
#include "areaclickable.h"
#include "homepagewidget.h"
#include "dht11page.h"
#include "videowidget.h"

class ShowPage : public QWidget
{
    Q_OBJECT
public:
    explicit ShowPage(QWidget *parent = 0);
    ~ShowPage();

private:
    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void paintChuanglian(QPainter &painter);
private slots:
    void moreAboutWidgetClickedSlot();
    void areaLeftLightClickedSlot();
    void areaRightLightClickedSlot();
    void areaPadClickedSlot();
    void areaOpenClickedSlot();
    void areaCloseClickedSlot();
    void areaDHT11ClickedSlot();
    void areaBallClickedSlot();
    void newDataGet(int, int, bool, bool, bool);



 private:
    AreaClickable *areaMoreAboutWidgetClickedSlot;


signals:
private:
     AreaClickable *areaMoreAboutWidget; //详情界面
     AreaClickable *areaLeftLight;//左灯点击区域
     AreaClickable *areaRightLight;//右灯点击区域
     AreaClickable *areaPad;//iPad点击区域
     AreaClickable *areaOpen;//窗帘开点击区域
     AreaClickable *areaClose;//窗帘关点击区域
     AreaClickable *areaDHT11;//温湿度点击区域
     AreaClickable *areaBall;//小球点击区域
     HomePageWidget *pHomePage; //设置页
     DHT11Page *pDHT11Page; //温度页面
     VideoWidget *pVideoPage;//监控页面
     bool bLeftLightIsOpen;//左灯
     bool bRightLightIsOpen;//右灯
     bool bMidLightIsOpen;//顶灯
     int iChuanglianStat;//窗帘状态
     QPixmap chuanglianPix[5];
     QPixmap backGroundPix[5];
public slots:
};

#endif // SHOWPAGE_H

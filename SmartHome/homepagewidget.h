/*
 *  Data: 2017.7.6
 *  Author:
 *  Edition: V0.1
 *  Explan: 主页
 *  Classl: HomePageWidget
 *  ClasslExplan: 显示设备的详细信息，完全控制
 */


#ifndef HOMEPAGEWIDGET_H
#define HOMEPAGEWIDGET_H


#include <QWidget>

namespace Ui {
class HomePageWidget;
}

class HomePageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HomePageWidget(QWidget *parent = 0);
    ~HomePageWidget();
    void refrashPageData();

private slots:
    void on_btnSerial_clicked();

    void on_btnBeer_clicked();

    void on_btnMotorLeft_clicked();

    void on_btnMotorStop_clicked();

    void on_btnMotorRight_clicked();

    void on_btnLED_1_clicked();

    void newDataGet(int,int,bool,bool,bool);

    void on_btnLED_2_clicked();

    void on_btnLED_3_clicked();

    void on_btnLED_4_clicked();

    void on_btnLED_5_clicked();

    void on_btnLED_6_clicked();

    void on_btnLED_7_clicked();

    void on_btnLED_8_clicked();

private:
    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    Ui::HomePageWidget *ui;
};


#endif // HOMEPAGEWIDGET_H

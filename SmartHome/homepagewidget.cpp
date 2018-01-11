#include "homepagewidget.h"
#include "ui_homepagewidget.h"
#include <QPainter>
#include "myserialport.h"

HomePageWidget::HomePageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomePageWidget)
{
    ui->setupUi(this);
    connect(MySerialPort::getobject(),SIGNAL(newDataRead(int,int,bool,bool,bool)),this,SLOT(newDataGet(int,int,bool,bool,bool)));
}

HomePageWidget::~HomePageWidget()
{
    delete ui;
}

void HomePageWidget::refrashPageData()
{
    //刷新串口状态

        //刷新串口列表
    ui->comboSerial->clear();
    ui->comboSerial->addItems(MySerialPort::getobject()->getSerialPortNameList());
        //匹配当前打开的串口
        //按钮形态
        //更新状态lab
    if(MySerialPort::getobject()->getSerialStat())
    {
        QStringList portList;
        portList = MySerialPort::getobject()->getSerialPortNameList();
        for(int i = 0; i < portList.size(); i++ )
        {
            if(portList.at(i) == MySerialPort::getobject()->getNowPortName())
            {
                ui->comboSerial->setCurrentIndex(i);
                break;
            }
        }
        ui->btnSerial->setText("关闭串口");
        ui->labelStat->setText(tr("串口已打开，串口号：%1，波特率：%2。").arg(MySerialPort::getobject()->getNowPortName()).arg(MySerialPort::getobject()->getNowBaudRate()));
     }
    else
    {
        ui->btnSerial->setText("打开串口");
        ui->labelStat->setText("串口未打开");
    }

    //刷新传感器数据
        int  iDHT11a,iDHT11b;
        bool bGM,bHW,bZD;
        MySerialPort::getobject()->getNewData(&iDHT11a,&iDHT11b,&bGM,&bHW,&bZD);
        ui->labelDH11_1->setText(tr("温度:%1℃").arg(iDHT11a));
        ui->labelDH11_2->setText(tr("湿度:%1 %").arg(iDHT11b));
        if(bGM)
        {
            ui->labelGroup_2->setText("是");
        }
        else
        {
            ui->labelGroup_2->setText("否");
        }
        if(bHW)
        {
            ui->labelGroup_3->setText("是");
        }
        else
        {
            ui->labelGroup_3->setText("否");
        }
        if(bZD)
        {
            ui->labelGroup_4->setText("是");
        }
        else
        {
            ui->labelGroup_4->setText("否");
        }
   }

void HomePageWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix(":/images/background.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

void HomePageWidget::mouseReleaseEvent(QMouseEvent *)
{
    this->setVisible(false);
}

void HomePageWidget::on_btnSerial_clicked()
{
  if(ui->btnSerial->text() == "打开串口")
  {
        bool ok = MySerialPort::getobject()->openSerial(ui->comboSerial->currentText(),57600);
    if(ok)
    {
        ui->btnSerial->setText("关闭串口");
        ui->labelStat->setText(tr("串口已打开，串口号：%1，波特率：%2。").arg(MySerialPort::getobject()->getNowPortName()).arg(MySerialPort::getobject()->getNowBaudRate()));
        MySerialPort::getobject()->saveNowConfig();
    }
    else
    {
        MySerialPort::getobject()->closeSerial();
        ui->btnSerial->setText("打开串口");
        ui->labelStat->setText("串口打开失败，可能被占用！");
    }
  }
  else
  {
      MySerialPort::getobject()->closeSerial();
      ui->btnSerial->setText("打开串口");
      ui->labelStat->setText("串口已关闭");
  }
}

void HomePageWidget::on_btnBeer_clicked()
{
    if(ui->btnBeer->text() == "打开蜂鸣器")
    {
        MySerialPort::getobject()->sendData(MySerialPort::BeerData,MySerialPort::BeerOpen);
        ui->btnBeer->setText("关闭蜂鸣器");
    }
    else
    {
        MySerialPort::getobject()->sendData(MySerialPort::BeerData,MySerialPort::BeerClose);
        ui->btnBeer->setText("打开蜂鸣器");
    }
}

void HomePageWidget::on_btnMotorLeft_clicked()
{
    MySerialPort::getobject()->sendData(MySerialPort::MotorData,MySerialPort::MotorLeft);
}

void HomePageWidget::on_btnMotorStop_clicked()
{
    MySerialPort::getobject()->sendData(MySerialPort::MotorData,MySerialPort::MotorStop);
}

void HomePageWidget::on_btnMotorRight_clicked()
{
    MySerialPort::getobject()->sendData(MySerialPort::MotorData,MySerialPort::MotorRight);
}

void HomePageWidget::on_btnLED_1_clicked()
{
    if(ui->btnLED_1->text() == "1开")
    {
        MySerialPort::getobject()->sendData(MySerialPort::LEDData,MySerialPort::LED1,MySerialPort::LEDOpen);
        ui->btnLED_1->setText("1关");
    }
    else
    {
        MySerialPort::getobject()->sendData(MySerialPort::LEDData,MySerialPort::LED1,MySerialPort::LEDClose);
        ui->btnLED_1->setText("1开");
    }

}

void HomePageWidget::newDataGet(int i, int j, bool a, bool b, bool c)
{
    ui->labelDH11_1->setText(tr("温度:%1℃").arg(i));
    ui->labelDH11_2->setText(tr("湿度:%1 %").arg(j));
    if(a)
    {
        ui->labelGroup_2->setText("是");
    }
    else
    {
        ui->labelGroup_2->setText("否");
    }
    if(b)
    {
        ui->labelGroup_3->setText("是");
    }
    else
    {
        ui->labelGroup_3->setText("否");
    }
    if(c)
    {
        ui->labelGroup_4->setText("是");
    }
    else
    {
        ui->labelGroup_4->setText("否");
    }
}

void HomePageWidget::on_btnLED_2_clicked()
{
    if(ui->btnLED_2->text() == "2开")
    {
        MySerialPort::getobject()->sendData(MySerialPort::LEDData,MySerialPort::LED2,MySerialPort::LEDOpen);
        ui->btnLED_2->setText("2关");
    }
    else
    {
        MySerialPort::getobject()->sendData(MySerialPort::LEDData,MySerialPort::LED2,MySerialPort::LEDClose);
        ui->btnLED_2->setText("2开");
    }
}

void HomePageWidget::on_btnLED_3_clicked()
{
    if(ui->btnLED_3->text() == "3开")
    {
        MySerialPort::getobject()->sendData(MySerialPort::LEDData,MySerialPort::LED3,MySerialPort::LEDOpen);
        ui->btnLED_3->setText("3关");
    }
    else
    {
        MySerialPort::getobject()->sendData(MySerialPort::LEDData,MySerialPort::LED3,MySerialPort::LEDClose);
        ui->btnLED_3->setText("3开");
    }
}

void HomePageWidget::on_btnLED_4_clicked()
{
    if(ui->btnLED_4->text() == "4开")
    {
        MySerialPort::getobject()->sendData(MySerialPort::LEDData,MySerialPort::LED4,MySerialPort::LEDOpen);
        ui->btnLED_4->setText("4关");
    }
    else
    {
        MySerialPort::getobject()->sendData(MySerialPort::LEDData,MySerialPort::LED4,MySerialPort::LEDClose);
        ui->btnLED_4->setText("4开");
    }
}

void HomePageWidget::on_btnLED_5_clicked()
{
    if(ui->btnLED_5->text() == "5开")
    {
        MySerialPort::getobject()->sendData(MySerialPort::LEDData,MySerialPort::LED5,MySerialPort::LEDOpen);
        ui->btnLED_5->setText("5关");
    }
    else
    {
        MySerialPort::getobject()->sendData(MySerialPort::LEDData,MySerialPort::LED5,MySerialPort::LEDClose);
        ui->btnLED_5->setText("5开");
    }
}

void HomePageWidget::on_btnLED_6_clicked()
{
    if(ui->btnLED_6->text() == "6开")
    {
        MySerialPort::getobject()->sendData(MySerialPort::LEDData,MySerialPort::LED6,MySerialPort::LEDOpen);
        ui->btnLED_6->setText("6关");
    }
    else
    {
        MySerialPort::getobject()->sendData(MySerialPort::LEDData,MySerialPort::LED6,MySerialPort::LEDClose);
        ui->btnLED_6->setText("6开");
    }
}

void HomePageWidget::on_btnLED_7_clicked()
{
    if(ui->btnLED_7->text() == "7开")
    {
        MySerialPort::getobject()->sendData(MySerialPort::LEDData,MySerialPort::LED7,MySerialPort::LEDOpen);
        ui->btnLED_7->setText("7关");
    }
    else
    {
        MySerialPort::getobject()->sendData(MySerialPort::LEDData,MySerialPort::LED7,MySerialPort::LEDClose);
        ui->btnLED_7->setText("7开");
    }
}

void HomePageWidget::on_btnLED_8_clicked()
{
    if(ui->btnLED_8->text() == "8开")
    {
        MySerialPort::getobject()->sendData(MySerialPort::LEDData,MySerialPort::LED8,MySerialPort::LEDOpen);
        ui->btnLED_8->setText("8关");
    }
    else
    {
        MySerialPort::getobject()->sendData(MySerialPort::LEDData,MySerialPort::LED8,MySerialPort::LEDClose);
        ui->btnLED_8->setText("8开");
    }
}

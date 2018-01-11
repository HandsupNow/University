#ifndef MYSERIALPORT_H
#define MYSERIALPORT_H

#include <QObject>
#include <QSerialPort>
#include <QStringList>
#include <QTimer>

class MySerialPort : public QObject
{
    Q_OBJECT
private:
    explicit MySerialPort(QObject *parent = 0);

public:
    enum SendDataType{
        BeerData = 3,
        MotorData = 4,
        LEDData = 5,
        RefrashData = 6
    };
    enum BeerType{
        BeerOpen = 0x01,
        BeerClose = 0x00
    };
    enum MotorType{
        MotorLeft = 0x01,
        MotorRight = 0xff,
        MotorStop = 0x00
    };
    enum LEDNum{

        LED1 = 0x01,
        LED2 = 0x02,
        LED3 = 0x04,
        LED4 = 0x08,
        LED5 = 0x10,
        LED6 = 0x20,
        LED7 = 0x40,
        LED8 = 0x80
    };
    enum LEDType{
        LEDOpen,
        LEDClose
    };
    enum RefrashType{
        Refrash = 0xee
    };


    static MySerialPort * getobject();
    ~MySerialPort();
    //打开串口
    bool openSerial(); //"COM1" 57600
    //打开串口
    bool openSerial(const QString &csPortName,const int &ciBaudRate);
    //关闭串口
    void closeSerial();
    //获取串口列表
    QStringList getSerialPortNameList();
    //获取串口状态
    bool getSerialStat();
    //获取当前串口号
    QString getNowPortName();
    //获取当前波特率
    int getNowBaudRate();
    //获取默认串口号
    QString getDefaultPortName();
    //获取默认波特率
    int getDefaultBaudRate();
    //保存当前配置
    bool saveNowConfig();
    //保存指定配置
    bool saveNewConfig(const QString &csPortName,const int &ciBaudRate);
    void getNewData(int *i,int *j,bool *pgm,bool *phw,bool *pzd);
    void sendData(SendDataType sendDataType,BeerType beerType);
    void sendData(SendDataType sendDataType,char ledNum,LEDType ledType);
    void sendData(SendDataType sendDataType,LEDNum ledNum,LEDType ledType);
    void sendData(SendDataType sendDataType,MotorType motorType);
    void sendData(SendDataType sendDataType,RefrashType refrashType);


protected slots:
    void serialReadyReadSlot();//接收
    void timerTimeoutSlot();//定时器槽函数

protected:
    void dataCheck(QByteArray data); //接收处理
    void oneDataReadyRead(QByteArray oneData); //一帧接收结束
    void initSerialConfigFile(); //初始化配置文件

signals:
    void newDataRead(int,int,bool,bool,bool);

public slots:

private:
    QSerialPort *pSerial;
    QByteArray readData;//接收到的数据
    int iReadDataLen;//接收到的数据长度
    int iDHT11a,iDHT11b;//温湿度
    bool bGM,bHW,bZD;  //光敏，红外，震动
    char cSendData[13];
    QTimer *pTimer;

private slots:


};

#endif // MYSERIALPORT_H

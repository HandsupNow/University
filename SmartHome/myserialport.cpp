#include "myserialport.h"
#include <QDebug>
#include <QSerialPortInfo>
#include <QSettings>
#include <QMutex>
#include <QFile>

#define SERIALCONFIGFILE "SerialSettings.ini"
#define SERIALGROUPNAME "SerialGroup"

#define PORTNAME "Serial_PortName"
#define BAUDRATE "Serial_BaudRate"

#define PORTNAME "Serial_PortName"
#define BAUDRATE "Serial_BaudRate"

#define DEFAULT_SERIAL_PORTNAME "COM1"
#define DEFAULT_SERIAL_BAUDRATE 57600


MySerialPort::MySerialPort(QObject *parent) : QObject(parent)
{
    iDHT11a = 0;
    iDHT11b = 0;
    bGM =false;
    bHW = false;
    bZD = false;
    iReadDataLen = 0;
    readData.clear();
    cSendData[0] = 0xef;
    cSendData[1] = 0xef;
    cSendData[2] = 0x0d;
    cSendData[12] = 0xff;
    for(int i = 3; i < 12; i++)
    {
        cSendData[i]= 0x00;
    }

    pSerial = new QSerialPort(this);
    connect(pSerial,SIGNAL(readyRead()),this,SLOT(serialReadyReadSlot()));
    initSerialConfigFile();
    pTimer = new QTimer(this);
    connect(pTimer,SIGNAL(timeout()),this,SLOT(timerTimeoutSlot()));
    pTimer->start(1000);
}

MySerialPort *MySerialPort::getobject()
{
    static MySerialPort *obj = NULL;
    if(obj == NULL)
    {
        obj = new MySerialPort;
    }
    return obj;
}

MySerialPort::~MySerialPort()
{

}

bool MySerialPort::openSerial()
{
    //如果串口已打开
    if(pSerial->isOpen())
       pSerial->close();
     //设置串口号
     pSerial->setPortName(getDefaultPortName());

     if(!pSerial->open(QIODevice::ReadWrite))
     {

         return false;
     }

     pSerial->setBaudRate(getDefaultBaudRate());

     pSerial->setDataBits(QSerialPort::Data8);

     pSerial->setStopBits(QSerialPort::OneStop);

     pSerial->setParity(QSerialPort::NoParity);

     pSerial->setFlowControl(QSerialPort::NoFlowControl);

     return true;
}

bool MySerialPort::openSerial(const QString &csPortName, const int &ciBaudRate)
{
    if(pSerial->isOpen())
       pSerial->close();
     //设置串口号
     pSerial->setPortName(csPortName);

     if(!pSerial->open(QIODevice::ReadWrite))
     {

         return false;
     }

     pSerial->setBaudRate(ciBaudRate);

     pSerial->setDataBits(QSerialPort::Data8);

     pSerial->setStopBits(QSerialPort::OneStop);

     pSerial->setParity(QSerialPort::NoParity);

     pSerial->setFlowControl(QSerialPort::NoFlowControl);

     return true;
}

void MySerialPort::closeSerial()
{
    pSerial->close();
}

QStringList MySerialPort::getSerialPortNameList()
{
    QStringList serialPortNameList;
    foreach (const QSerialPortInfo &info,
             QSerialPortInfo::availablePorts())
    {
        serialPortNameList.append(info.portName());
    }
    return serialPortNameList;
}

bool MySerialPort::getSerialStat()
{
    return pSerial->isOpen();
}

QString MySerialPort::getNowPortName()
{
    if(pSerial->isOpen())
        return pSerial->portName();
    else
        return "ERROR";
}

int MySerialPort::getNowBaudRate()
{
    if(pSerial->isOpen())
        return pSerial->baudRate();
    else
        return 0;
}

QString MySerialPort::getDefaultPortName()
{
    QString sPortName;
    QSettings set(SERIALCONFIGFILE,QSettings::IniFormat);
    set.beginGroup(SERIALGROUPNAME);
    sPortName = set.value(PORTNAME).toString();
    set.endGroup();
    return sPortName;
}

int MySerialPort::getDefaultBaudRate()
{
    int iBaudRate;
    QSettings set(SERIALCONFIGFILE,QSettings::IniFormat);
    set.beginGroup(SERIALGROUPNAME);
    iBaudRate = set.value(BAUDRATE).toInt();
    set.endGroup();
    return iBaudRate;
}

bool MySerialPort::saveNowConfig()
{
    if(!pSerial->isOpen())
        return false;
    static QMutex mutex;
    QMutexLocker locker(&mutex);

    QSettings sets(SERIALCONFIGFILE,QSettings::IniFormat);
    sets.beginGroup(SERIALGROUPNAME);
    sets.setValue(PORTNAME,pSerial->portName());
    sets.setValue(BAUDRATE,pSerial->baudRate());
    sets.endGroup();
    return true;
}

bool MySerialPort::saveNewConfig(const QString &csPortName, const int &ciBaudRate)
{
    if(!pSerial->isOpen())
        return false;
    static QMutex mutex;
    QMutexLocker locker(&mutex);

    QSettings sets(SERIALCONFIGFILE,QSettings::IniFormat);
    sets.beginGroup(SERIALGROUPNAME);
    sets.setValue(PORTNAME,csPortName);
    sets.setValue(BAUDRATE,ciBaudRate);
    sets.endGroup();
    return true;
}

void MySerialPort::getNewData(int *i, int *j, bool *pgm, bool *phw, bool *pzd)
{
    *i = iDHT11a;
    *j = iDHT11b;
    *pgm = bGM;
    *phw = bHW;
    *pzd = bZD;

}

void MySerialPort::sendData(MySerialPort::SendDataType sendDataType, MySerialPort::BeerType beerType)
{
    if(sendDataType != MySerialPort::BeerData)
        return;
    cSendData[sendDataType] = beerType;
    cSendData[11] = 0x00;
    for(int i = 3; i < 11; i++)
    {
        cSendData[11] ^= cSendData[i];
    }
    if(pSerial->isOpen())
        pSerial->write(cSendData,13);
}

void MySerialPort::sendData(MySerialPort::SendDataType sendDataType, char ledNum, MySerialPort::LEDType ledType)
{
    if(sendDataType != MySerialPort::LEDData)
        return;
    if(ledType == MySerialPort::LEDOpen)
        cSendData[sendDataType] |= ledNum;
    else
        cSendData[sendDataType] &= -ledNum;
    cSendData[11] = 0x00;
    for(int i = 3; i < 11; i++)
    {
        cSendData[11] ^= cSendData[i];
    }
    if(pSerial->isOpen())
        pSerial->write(cSendData,13);
}

void MySerialPort::sendData(MySerialPort::SendDataType sendDataType, LEDNum ledNum, MySerialPort::LEDType ledType)
{

    if(sendDataType != MySerialPort::LEDData)
        return;
    if(ledType == MySerialPort::LEDOpen)
        cSendData[sendDataType] |= ledNum;
    else
        cSendData[sendDataType] &= -ledNum;
    cSendData[11] = 0x00;
    for(int i = 3; i < 11; i++)
    {
        cSendData[11] ^= cSendData[i];
    }
    if(pSerial->isOpen())
        pSerial->write(cSendData,13);
}


void MySerialPort::sendData(MySerialPort::SendDataType sendDataType, MySerialPort::MotorType motorType)
{

    if(sendDataType != MySerialPort::MotorData)
        return;
    cSendData[sendDataType] = motorType;
    cSendData[11] = 0x00;
    for(int i = 3; i < 11; i++)
    {
        cSendData[11] ^= cSendData[i];
    }
    if(pSerial->isOpen())
        pSerial->write(cSendData,13);
    cSendData[sendDataType] = 0x00;
}

void MySerialPort::sendData(MySerialPort::SendDataType sendDataType, MySerialPort::RefrashType refrashType)
{

    if(sendDataType != MySerialPort::RefrashData)
        return;
    cSendData[sendDataType] = refrashType;
    cSendData[11] = 0x00;
    for(int i = 3; i < 11; i++)
    {
        cSendData[11] ^= cSendData[i];
    }
    if(pSerial->isOpen())
        pSerial->write(cSendData,13);
        cSendData[sendDataType] = 0x00;
}

void MySerialPort::serialReadyReadSlot()
{
    QSerialPort *s = (QSerialPort *) sender();
    QByteArray data;
    while(s->bytesAvailable())
    {
        data.append(s->readAll());
    }
    //接收完成，进行数据解析
    dataCheck(data);
}

void MySerialPort::timerTimeoutSlot()
{
    if(!pSerial->isOpen())
        return;
    sendData(MySerialPort::RefrashData,MySerialPort::Refrash);
}

void MySerialPort::dataCheck(QByteArray data)
{
    //待数据存储到一个类成员变量中
    //判断开始标志
    //判断结束标志与数据长度

    for(int i = 0; i< data.length();i++)
    {
        //判断是否为帧头
      if( data[i] == 0xfe && iReadDataLen > 0)
      {
        if(readData[iReadDataLen - 1] == 0xfe)
        {
            //接收到起始标志
            readData[0] = 0xfe;
            iReadDataLen = 1;
        }
      }

      if(data[i] == 0xff && iReadDataLen == 12)
      {
          readData[12] = data[i];
          //一帧接收结束
          oneDataReadyRead(readData);
      }
      else
      {
          readData[iReadDataLen++] = data[i];
      }
    }
}

void MySerialPort::oneDataReadyRead(QByteArray oneData)
{
    qDebug() << readData.toHex();
    int DHT11[2];
    bool GM;//光敏
    bool HW;//红外
    bool ZD;//震动
    bool ok;
    DHT11[0] = oneData.mid(3,1).toHex().toInt(&ok,16);
    DHT11[1] = oneData.mid(4,1).toHex().toInt(&ok,16);
    if( oneData[5] == 0x01 )
        GM = true;
    else
        GM = false;
    if( oneData[6] == 0x01)
        HW = true;
    else
        HW = false;
    if( oneData[7] == 0x01)
        ZD = true;
    else
        ZD = false;
    iDHT11a = DHT11[0];
    iDHT11b = DHT11[1];
    bGM = GM;
    bHW = HW;
    bZD = ZD;
    emit newDataRead(DHT11[0],DHT11[1],GM,HW,ZD);
    readData.clear();
    iReadDataLen = 0;
}

void MySerialPort::initSerialConfigFile()
{
    static QMutex mutex;
    QMutexLocker locker(&mutex);

    if(QFile::exists(SERIALCONFIGFILE))
        return;

    QSettings sets(SERIALCONFIGFILE,QSettings::IniFormat);
    sets.beginGroup(SERIALGROUPNAME);
    sets.setValue(PORTNAME,DEFAULT_SERIAL_PORTNAME);
    sets.setValue(BAUDRATE,DEFAULT_SERIAL_BAUDRATE);
    sets.endGroup();
}


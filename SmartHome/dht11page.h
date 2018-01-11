#ifndef DHT11PAGE_H
#define DHT11PAGE_H

#include <QWidget>

class DHT11Page : public QWidget
{
    Q_OBJECT
public:
    explicit DHT11Page(QWidget *parent = 0);
    ~DHT11Page();
    void setData(int a,int b);
    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *);


signals:

public slots:

private:
    QPixmap numPix[10];
    int ia,ib;
};

#endif // DHT11PAGE_H

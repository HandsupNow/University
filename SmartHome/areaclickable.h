#ifndef AREACLICKABLE_H
#define AREACLICKABLE_H

#include <QWidget>

class AreaClickable : public QWidget
{
    Q_OBJECT
public:
    explicit AreaClickable(QWidget *parent = 0);
    ~AreaClickable();
    void setPixMap(const QPixmap &cPix);
    void paintEvent(QPaintEvent *);

signals:
     void clicked();


private:
     void mouseReleaseEvent(QMouseEvent *);
     QPixmap pix;


public slots:
};

#endif // AREACLICKABLE_H

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QImage>

class Widget : public QWidget
{
    Q_OBJECT
    QImage image;

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void mousePressEvent(QMouseEvent*);

    void paintEvent(QPaintEvent*);
};
#endif // WIDGET_H

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QImage>

struct ivec2 {
    int x, y;
};

class Widget : public QWidget
{
    Q_OBJECT
    QImage image;
    std::vector<ivec2> control_points;

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void mousePressEvent(QMouseEvent*);

    void paintEvent(QPaintEvent*);

};
#endif // WIDGET_H

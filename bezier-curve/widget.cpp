#include "widget.h"

#include <QPainter>
#include <QMouseEvent>

void draw_bezier(std::vector<ivec2> &control_points, QImage &img) {
    float t = 0.0f;
    float step = 1.0f / 16.0f;

    int x0 = control_points[0].x;
    int y0 = control_points[0].y;

    int cx = 3 * (control_points[1].x - x0);
    int bx = 3 * (control_points[2].x - control_points[1].x) - cx;
    int ax = control_points[3].x - x0 - cx - bx;

    int cy = 3 * (control_points[1].y - y0);
    int by = 3 * (control_points[2].y - control_points[1].y) - cy;
    int ay = control_points[3].y - y0 - cy - by;

    for (; t <= 1.0f; t += step) {
        int x = ax * t * t * t + bx * t * t + cx * t + x0;
        int y = ay * t * t * t + by * t * t + cy * t + y0;

        QRgb *pixel_img = (QRgb*) img.scanLine(y);
        pixel_img[x] = qRgb(255, 255, 255);
    }
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    image = QImage(800, 800, QImage::Format_RGB32);
    image.fill(Qt::black);
}

Widget::~Widget()
{
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    ivec2 point = {event->pos().x(), event->pos().y()};
    control_points.push_back(point);

    if (control_points.size() == 4) {
        draw_bezier(control_points, image);
        update(); // image are changed -> update()
    }
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter paint(this); // this -> widget
    paint.drawImage(0, 0, image);
}


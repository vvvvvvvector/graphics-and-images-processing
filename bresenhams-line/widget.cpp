#include "widget.h"

#include <QPainter>
#include <QMouseEvent>

bool flag = false;

int x_1, y_1, x_2, y_2;

void draw_a_line(int start_x, int start_y, int end_x, int end_y, QImage &img) {
    int dx = abs(end_x - start_x);
    int dy = abs(end_y - start_y);

    int x = start_x;
    int y = start_y;

    if (dx > dy) {
        int ix, iy;

        int decision_variable = 2 * dy - dx;

        if (end_x > start_x) {
            ix = 1;
        } else {
            ix = -1;
        }

        if (end_y > start_y) {
            iy = 1;
        } else {
            iy = -1;
        }

        while (x != end_x) {
            if (decision_variable > 0) {
                decision_variable += 2 * (dy - dx);
                x += ix;
                y += iy;
            } else {
                decision_variable += 2 * dy;
                x += ix;
            }

            QRgb *pixel_image = (QRgb*) img.scanLine(y);
            pixel_image[x] = qRgb(255, 255, 255);
        }
    } else {
        int ix, iy;

        int decision_variable = 2 * dx - dy;

        if (end_y > start_y) {
            iy = 1;
        } else {
            iy = -1;
        }

        if (end_x > start_x) {
            ix = 1;
        } else {
            ix = -1;
        }

        while (y != end_y) {
            if (decision_variable > 0) {
                decision_variable += 2 * (dx - dy);
                x += ix;
                y += iy;
            } else {
                decision_variable += 2 * dx;
                y += iy;
            }

            QRgb *pixel_image = (QRgb*) img.scanLine(y);
            pixel_image[x] = qRgb(255, 255, 255);
        }
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
    if (event->button() == Qt::LeftButton) {
        int x = event->pos().x();
        int y = event->pos().y();

        if (flag) {
            x_2 = x;
            y_2 = y;

            draw_a_line(x_1, y_1, x_2, y_2, image);
            update();

            flag = false;
        } else {
            x_1 = x;
            y_1 = y;

            flag = true;
        }
    }
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter paint(this);
    paint.drawImage(0, 0, image);
}


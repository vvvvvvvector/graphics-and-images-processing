#include "widget.h"

#include <QPainter>
#include <QMouseEvent>

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

bool flag = false;

ivec2 prev_point;

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

        if (!flag) {
            prev_point = {x , y};

            flag = true;
        } else {
            draw_a_line(prev_point.x, prev_point.y, x, y, img);

            prev_point = {x, y};
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

bool first_four_points = false;
int points_counter = 0;

void Widget::mousePressEvent(QMouseEvent *event)
{
    if (!first_four_points) {
        control_points.push_back({event->pos().x(), event->pos().y()});
        points_counter++;

        if (points_counter == 4) {
            draw_bezier(control_points, image);

            update();

            first_four_points = true;

            control_points.clear();
            points_counter = 0;

            control_points.push_back(prev_point);
        }
    } else {
        control_points.push_back({event->pos().x(), event->pos().y()});
        points_counter++;

        if (points_counter == 3) {
            draw_bezier(control_points, image);

            update();

            control_points.clear();
            points_counter = 0;

            control_points.push_back(prev_point);
        }
    }
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter paint(this); // this -> widget
    paint.drawImage(0, 0, image);
}


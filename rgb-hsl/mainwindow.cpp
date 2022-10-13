#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

void hsl2rgb(float h, float s, float l, uchar &r, uchar &g, uchar &b) {
    float fr = 0.0f;
    float fg = 0.0f;
    float fb = 0.0f;

    if (s == 0.0f) {
        fr = fg = fb = l;
    } else {
        float q = 0.0f;

        if (l < 0.5f) {
            q = l * (1 + s);
        } else if (l >= 0.5f) {
            q = l + s - l * s;
        }

        float p = 2 * l - q;

        h /= 360.0f;

        float tr = h + 0.3333333333f;
        float tg = h;
        float tb = h - 0.3333333333f;

        if (tr < 0.0f) {
            tr += 1;
        } else if (tr > 1.0f) {
            tr -= 1;
        }

        if (tg < 0.0f) {
            tg += 1;
        } else if (tg > 1.0f) {
            tg -= 1;
        }

        if (tb < 0.0f) {
            tb += 1;
        } else if (tb > 1.0f) {
            tb -= 1;
        }

        if (tr < 0.166666666f) {
            fr = p + (q - p) * 6  * tr;
        } else if (tr >= 0.166666666f && tr < 0.5f) {
            fr = q;
        } else if (tr >= 0.5f && tr < 0.666666666f) {
            fr = p + (q - p) * 6 * (0.666666666f - tr);
        } else {
            fr = p;
        }

        if (tg < 0.166666666f) {
            fg = p + (q - p) * 6  * tg;
        } else if (tg >= 0.166666666f && tg < 0.5f) {
            fg = q;
        } else if (tg >= 0.5f && tg < 0.666666666f) {
            fg = p + (q - p) * 6 * (0.666666666f - tg);
        } else {
            fg = p;
        }

        if (tb < 0.166666666f) {
            fb = p + (q - p) * 6  * tb;
        } else if (tb >= 0.166666666f && tb < 0.5f) {
            fb = q;
        } else if (tb >= 0.5f && tb < 0.666666666f) {
            fb = p + (q - p) * 6 * (0.666666666f - tb);
        } else {
            fb = p;
        }
    }

    r = fr * 255;
    g = fg * 255;
    b = fb * 255;
}

void rgb2hsl(uchar r, uchar g, uchar b, float &h, float &s, float &l) {
    float fr = r / 255.0f;
    float fg = g / 255.0f;
    float fb = b / 255.0f;

    float max = std::max(fr, std::max(fg, fb));
    float min = std::min(fr, std::min(fg, fb));
    float dm = max - min;

    l = ((max + min) / 2.0f);

    s = 0.0f;

    if (l == 0.0f || max == min) {
        s = 0.0f;
    } else if (l > 0.0f && l <= 0.5f) {
        s = dm / (2 * l);
    } else if (l > 0.5f) {
        s = dm / (2.0f - 2 * l);
    }

    h = 0.0f;

    if (max == min) {
        h = 0.0f;
    } else {
        if (max == fr && fg >= fb) {
            h = 60 * (fg - fb) / dm;
        } else if (max == fr && fg < fb) {
            h = 360 + (60 * (fg - fb) / dm);
        } else if (max == fg) {
            h = 120 + (60 * (fb - fr) / dm);
        } else if (max == fb) {
            h = 240 + (60 * (fr - fg) / dm);
        }
    }
}

void hue(QImage &src, QImage &dst, float dl) {
    // hello world
}

void saturation(QImage &src, QImage &dst, float ds) {
    for (int y = 0; y < src.height(); y++) {
        QRgb *pixel_src = (QRgb*)src.scanLine(y);
        QRgb *pixel_dst = (QRgb*)dst.scanLine(y);

        for (int x = 0; x < src.width(); x++) {
            uchar r = qRed(pixel_src[x]);
            uchar g = qGreen(pixel_src[x]);
            uchar b = qBlue(pixel_src[x]);

            float h, s, l;

            rgb2hsl(r, g, b, h, s, l);

            s = clamp<float>(s + ds, 0.0f, 1.0f);

            hsl2rgb(h, s, l, r, g, b);

            pixel_dst[x] = qRgb(r, g, b);
        }
    }
}

void lightness(QImage &src, QImage &dst, float dl) {
    for (int y = 0; y < src.height(); y++) {
        QRgb *pixel_src = (QRgb*)src.scanLine(y);
        QRgb *pixel_dst = (QRgb*)dst.scanLine(y);

        for (int x = 0; x < src.width(); x++) {
            uchar r = qRed(pixel_src[x]);
            uchar g = qGreen(pixel_src[x]);
            uchar b = qBlue(pixel_src[x]);

            float h, s, l;

            rgb2hsl(r, g, b, h, s, l);

            l = clamp<float>(l + dl, 0.0f, 1.0f);

            hsl2rgb(h, s, l, r, g, b);

            pixel_dst[x] = qRgb(r, g, b);
        }
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openImage() {
    QString fileName = QFileDialog::getOpenFileName();

    if (!fileName.isNull()) {
        original_image.load(fileName);
        process_image = original_image;
        ui->image->setPixmap(QPixmap::fromImage(original_image));
    }
}

void MainWindow::on_actionOpen_triggered()
{
    openImage();
}

void MainWindow::on_h_slider_valueChanged(int value)
{
    float dh = 0.0f;

    // dh = value / 100.0f;

    hue(original_image, process_image, dh);
    ui->image->setPixmap(QPixmap::fromImage(process_image));
}

void MainWindow::on_s_slider_valueChanged(int value)
{
    float ds = 0.0f;

    ds = value / 100.0f;

    saturation(original_image, process_image, ds);
    ui->image->setPixmap(QPixmap::fromImage(process_image));
}

void MainWindow::on_l_slider_valueChanged(int value)
{
    float dl = 0.0f;

    dl = value / 100.0f;

    lightness(original_image, process_image, dl);
    ui->image->setPixmap(QPixmap::fromImage(process_image));
}


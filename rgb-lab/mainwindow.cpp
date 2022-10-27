#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

// it is working
void rgb2xyz(uchar r, uchar g, uchar b, float &x, float &y, float &z) {
    float fr = r / 255.0f;
    float fg = g / 255.0f;
    float fb = b / 255.0f;

    if (fr <= 0.04045f) {
        fr /= 12.92f;
    } else {
        fr = std::pow((fr + 0.055f) / 1.055f, 2.4f);
    }

    if (fg <= 0.04045f) {
        fg /= 12.92f;
    } else {
        fg = std::pow((fg + 0.055f) / 1.055f, 2.4f);
    }

    if (fb <= 0.04045f) {
        fb /= 12.92f;
    } else {
        fb = std::pow((fb + 0.055f) / 1.055f, 2.4f);
    }

    x = fr * 0.41242f + fg * 0.35759f + fb * 0.18046f;
    y = fr * 0.21266f + fg * 0.71517f + fb * 0.07218f;
    z = fr * 0.01933f + fg * 0.11919f + fb * 0.95044f;

    // qInfo() << x << " " << y << " " << z << '\n';
}

// it is working
void xyz2lab(float x, float y, float z, float &l, float &a, float &b) {
    x /= 0.9505f;
    y /= 1.0f;
    z /= 1.0891f;

    float eps = 0.008856f;
    float k = 903.3f;

    float fx, fy, fz;

    if (x > eps) {
        fx = std::pow(x, 1.0 / 3.0);
    } else {
        fx = (k * x + 16) / 116.0;
    }

    if (y > eps) {
        fy = std::pow(y, 1.0 / 3.0);
    } else {
        fy = (k * y + 16) / 116.0;
    }

    if (z > eps) {
        fz = std::pow(z, 1.0 / 3.0);
    } else {
        fz = (k * z + 16) / 116.0;
    }

    l = 116 * fy - 16;
    a = 500 * (fx - fy);
    b = 200 * (fy - fz);

    // qInfo() << l << " " << a << " " << b << "\n";
}

// it is working
void lab2xyz(float l, float a, float b, float &x, float &y, float &z) {
    float eps = 0.008856f;
    float k = 903.3;

    float xr, yr, zr;

    if (l > k * eps) {
        yr = std::pow((l + 16.0f) / 116.0f, 3);
    } else {
        yr = l / k;
    }

    float fx, fy, fz;

    if (yr > eps) {
        fy = (l + 16) / 116.0f;
    } else {
        fy = (k * yr + 16) / 116.0f;
    }

    fx = a / 500.0f + fy;
    fz = fy - b / 200.0f;

    if (std::pow(fx, 3) > eps) {
        xr = std::pow(fx, 3);
    } else {
        xr = (116 * fx - 16) / k;
    }

    if (std::pow(fz, 3) > eps) {
        zr = std::pow(fz, 3);
    } else {
        zr = (116 * fz - 16) / k;
    }

    x = xr * 0.9505f;
    y = yr * 1.0f;
    z = zr * 1.0891f;

    // qInfo() << x << " " << y << " " << z << "\n";
}

// it is working
void xyz2rgb(float x, float y, float z, uchar &r, uchar &g, uchar &b) {
    float fr = x * 3.24071f + y * (-1.53726f) + z * (-0.49857f);
    float fg = x * (-0.96925f) + y * 1.87599 + z * 0.04155f;
    float fb = x * 0.05563 + y * (-0.20399f) + z * 1.05707f;

    if (fr <= 0.0031308f) {
        fr *= 12.92;
    } else {
        fr = 1.055f * std::pow(fr, 1.0f / 2.4f) - 0.055f;
    }

    if (fg <= 0.0031308f) {
        fg *= 12.92;
    } else {
        fg = 1.055f * std::pow(fg, 1.0f / 2.4f) - 0.055f;
    }

    if (fb <= 0.0031308f) {
        fb *= 12.92;
    } else {
        fb = 1.055f * std::pow(fb, 1.0f / 2.4f) - 0.055f;
    }

    r = clamp<int>(fr * 255, 0, 255);
    g = clamp<int>(fg * 255, 0, 255);
    b = clamp<int>(fb * 255, 0, 255);

    // qInfo() << r << " " << g << " " << b << "\n";
}

void process(const QImage &src, QImage &dst, float dl, float da, float db) {
    for (int row = 0; row < src.height(); row++) {
        QRgb *pixel_src = (QRgb*)src.scanLine(row);
        QRgb *pixel_dst = (QRgb*)dst.scanLine(row);

        for (int column = 0; column < src.width(); column++) {
            uchar red = qRed(pixel_src[column]);
            uchar green = qGreen(pixel_src[column]);
            uchar blue = qBlue(pixel_src[column]);

            float x, y, z;
            rgb2xyz(red, green, blue, x, y, z);

            float l, a, b;
            xyz2lab(x, y, z, l, a, b);

            l = clamp<float>(l + dl, 0.0f, 100.0f); // 0...100
            a = clamp<float>(a + da, -128.0f, 127.0f); // -128...127
            b = clamp<float>(b + db, -128.0f, 127.0f); // -128...127

            lab2xyz(l, a, b, x, y, z);
            xyz2rgb(x, y, z, red, green, blue);

            pixel_dst[column] = qRgb(red, green, blue);
        }
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

     float x, y, z;
     float l, a, b;
     uchar red, green, blue;

     rgb2xyz(125, 34, 129, x, y, z);

     qInfo() << x << " " << y << " " << z << "\n";

     xyz2lab(x, y, z, l, a, b);

     qInfo() << l << " " << a << " " << b << "\n";

     lab2xyz(l, a, b, x, y, z);

     qInfo() << x << " " << y << " " << z << "\n";

     xyz2rgb(x, y, z, red, green, blue);

     qInfo() << red << " " << green << " " << blue << "\n";
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
        ui->image->setPixmap(QPixmap::fromImage(process_image));
    }
}

void MainWindow::on_open_triggered()
{
    openImage();
}

void MainWindow::on_l_slider_valueChanged(int value)
{
    process(original_image, process_image, value, ui->a_slider->value(), ui->b_slider->value());
    ui->image->setPixmap(QPixmap::fromImage(process_image));
}

void MainWindow::on_a_slider_valueChanged(int value)
{
    process(original_image, process_image, ui->l_slider->value(), value, ui->b_slider->value());
    ui->image->setPixmap(QPixmap::fromImage(process_image));
}

void MainWindow::on_b_slider_valueChanged(int value)
{
    process(original_image, process_image, ui->l_slider->value(), ui->a_slider->value(), value);
    ui->image->setPixmap(QPixmap::fromImage(process_image));
}


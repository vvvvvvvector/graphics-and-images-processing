#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

void brightness_gamma(const QImage &src, QImage &dst, float gamma) {
    for (int y = 0; y < src.height(); y++) {
        QRgb *pixel_src = (QRgb*)src.scanLine(y);
        QRgb *pixel_dst = (QRgb*)dst.scanLine(y);

        for (int x = 0; x < src.width(); x++) {
            float r = qRed(pixel_src[x]);
            float g = qGreen(pixel_src[x]);
            float b = qBlue(pixel_src[x]);

            r = 255 * pow(r / 255.0f, gamma);
            g = 255 * pow(g / 255.0f, gamma);
            b = 255 * pow(b / 255.0f, gamma);

            pixel_dst[x] = qRgb(r, g, b);
        }
    }
}

void brightness(const QImage &src, QImage &dst, int v) {
    for (int y = 0; y < src.height(); y++) {
        QRgb *pixel_src = (QRgb*)src.scanLine(y);
        QRgb *pixel_dst = (QRgb*)dst.scanLine(y);

        for (int x = 0; x < src.width(); x++) {
            unsigned char r = qRed(pixel_src[x]);
            unsigned char g = qGreen(pixel_src[x]);
            unsigned char b = qBlue(pixel_src[x]);

            r = clamp<int>(r + v, 0, 255);
            g = clamp<int>(g + v, 0, 255);
            b = clamp<int>(b + v, 0, 255);

            pixel_dst[x] = qRgb(r, g, b);
        }
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->image->setText("No image");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openImage() {
    QString fileName = QFileDialog::getOpenFileName();

    if (!fileName.isNull()) {
        originalImage.load(fileName);
        processImage = originalImage;
        ui->image->setPixmap(QPixmap::fromImage(processImage));
    }
}

void MainWindow::on_actionOpen_triggered()
{
    openImage();
}


void MainWindow::on_linear_valueChanged(int value)
{
    brightness(originalImage, processImage, value);
    ui->image->setPixmap(QPixmap::fromImage(processImage));
}


void MainWindow::on_nonlinear_valueChanged(int value)
{
    float gamma = 0.0f;

    value *= -1;

    if (value <= 0) {
        gamma = (100 + value) / 100.0;
    } else {
        gamma = value / 10.0 + 1;
    }

    brightness_gamma(originalImage, processImage, gamma);
    ui->image->setPixmap(QPixmap::fromImage(processImage));
    // ui->image->setText(QString::number(gamma));
}


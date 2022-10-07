#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

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

    ui->label->setText("No image");
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
        ui->label->setPixmap(QPixmap::fromImage(processImage));
    }
}

void MainWindow::on_actionOpen_triggered()
{
    openImage();
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    brightness(originalImage, processImage, value);
    ui->label->setPixmap(QPixmap::fromImage(processImage));
}


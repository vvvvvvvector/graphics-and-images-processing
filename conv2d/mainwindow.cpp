#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->image_1->setText("Image with borders");
    ui->image_2->setText("Destination image");
}

MainWindow::~MainWindow()
{
    delete ui;
}

QImage make_border_image(const QImage &src, int r) {
    QImage border(src.width() + 2 * r, src.height() + 2 * r, src.format());

    border.fill(Qt::black);

    for (int y = 0; y < src.height(); y++) {
        uchar *pixel_src = (uchar*) src.scanLine(y);
        uchar *pixel_dst = (uchar*) border.scanLine(y + r) + 4 * r; // linia przesunieta o 4 bajty; jesli int(4x > char) to -> + r

        memcpy(pixel_dst, pixel_src, src.width() * 4);
    }

    return border;
}

void conv2d(const QImage &src, QImage &dst, std::vector<int> mask, int r) {
    int w = src.width();

    for (int y = 0; y < dst.height(); ++y) {
        QRgb *pixel_src = (QRgb*) src.scanLine(y + r);
        QRgb *pixel_dst = (QRgb*) dst.scanLine(y);

        for (int x = 0; x < dst.width(); ++x) {
            int mask_index = 0;
            int red = 0, green = 0, blue = 0;

            for (int iy = -1; iy <= 1; ++iy) {
                for (int ix = -1; ix <= 1; ++ix) {
                    red += qRed(pixel_src[x + r + ix + iy * w]) * mask[mask_index];
                    green += qGreen(pixel_src[x + r + ix + iy * w]) * mask[mask_index];
                    blue += qBlue(pixel_src[x + r + ix + iy * w]) * mask[mask_index];
                }
            }

            pixel_dst[x] = qRgb(red, green, blue);
        }
    }
}

void MainWindow::openImage() {
    QString fileName = QFileDialog::getOpenFileName();

    if (!fileName.isNull()) {
        original_image.load(fileName);

        QImage dest = QImage(original_image.width(),  original_image.height(), original_image.format());
        dest.fill(Qt::white);

        QImage border_src = make_border_image(original_image, 10);

        ui->image_1->setPixmap(QPixmap::fromImage(border_src));

        std::vector<int> mask = {1, 1, 1, 1, 1, 1, 1, 1, 1};

        conv2d(border_src, dest, mask, 10);

        ui->image_2->setPixmap(QPixmap::fromImage(dest));
    }
}


void MainWindow::on_open_triggered()
{
    openImage();
}


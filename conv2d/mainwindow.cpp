#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <cmath>

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

template<class T>
void conv2d(const QImage &src, QImage &dst, std::vector<T> mask, int r) {
    int w = src.width();

    T mask_elements_sum = std::accumulate(mask.begin(), mask.end(), 0);

    for (int y = 0; y < dst.height(); y++) {
        QRgb *pixel_src = (QRgb*) src.scanLine(y + r);
        QRgb *pixel_dst = (QRgb*) dst.scanLine(y);

        for (int x = 0; x < dst.width(); x++) {
            int mask_index = 0;
            int red = 0, green = 0, blue = 0;

            for (int iy = -r; iy <= r; iy++) {
                for (int ix = -r; ix <= r; ix++, mask_index++) {
                    red += qRed(pixel_src[x + r + ix + iy * w]) * mask[mask_index];
                    green += qGreen(pixel_src[x + r + ix + iy * w]) * mask[mask_index];
                    blue += qBlue(pixel_src[x + r + ix + iy * w]) * mask[mask_index];
                }
            }

            if (mask_elements_sum != 0) {
                red = clamp<int>(red / mask_elements_sum, 0, 255);
                green = clamp<int>(green / mask_elements_sum, 0, 255);
                blue = clamp<int>(blue / mask_elements_sum, 0, 255);
            } else {
                red = clamp<int>(red, 0, 255);
                green = clamp<int>(green , 0, 255);
                blue = clamp<int>(blue , 0, 255);
            }

            pixel_dst[x] = qRgb(red, green, blue);
        }
    }
}

void MainWindow::openImage() {
    QString fileName = QFileDialog::getOpenFileName();

    if (!fileName.isNull()) {
        original_image.load(fileName);

        int r = 10; // filter radius && image border width -> filter_width_and_height = 2 * r + 1

        QImage dest = QImage(original_image.width(),  original_image.height(), original_image.format());
        dest.fill(Qt::white);

        QImage border_src = make_border_image(original_image, r);

        ui->image_1->setPixmap(QPixmap::fromImage(border_src));

        // 1. edge detection
        // std::vector<int> mask = {-1, -1, -1, -1, 8, -1, -1, -1, -1};

        // 2. sharpening
        // std::vector<int> mask = {-1, -1, -1, -1, 9, -1, -1, -1, -1};

        // 3. another sharpening
        // std::vector<int> mask = {
        //    -1, -1, -1, -1, -1,
        //    -1, -1, -1, -1, -1,
        //    -1, -1, 25, -1, -1,
        //    -1, -1, -1, -1, -1,
        //    -1, -1, -1, -1, -1,
        //};

        // 4. blur
        std::vector<int> mask(21 * 21, 1);

        // 5. identity
        // std::vector<int> mask = {0, 0, 0, 0, 1, 0, 0, 0 ,0};

        // 6. box blur
        // std::vector<float> mask = {0.1111f, 0.1111f, 0.1111f, 0.1111f, 0.1111f, 0.1111f, 0.1111f, 0.1111f, 0.1111f};

        conv2d<int>(border_src, dest, mask, r);

        ui->image_2->setPixmap(QPixmap::fromImage(dest));
    }
}


void MainWindow::on_open_triggered()
{
    openImage();
}


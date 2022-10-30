#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->original_image->setText("Original image here.");
    ui->destination_image->setText("Destination image here.");
}

MainWindow::~MainWindow()
{
    delete ui;
}

QImage make_image_with_borders(const QImage &src, int r) {
    QImage image_with_borders(src.width() + 2 * r, src.height() + 2 * r, src.format());

    image_with_borders.fill(Qt::black);

    for (int y = 0; y < src.height(); y++) {
        uchar *pixel_src = (uchar*) src.scanLine(y);
        uchar *pixel_dst = (uchar*) image_with_borders.scanLine(y + r) + 4 * r;

        memcpy(pixel_dst, pixel_src, src.width() * 4);
    }

    return image_with_borders;
}

void apply_median_filter(const QImage &image_with_borders, QImage &dst, int r) {
    int w = image_with_borders.width();

    for (int y = 0; y < dst.height(); y++) {
        for (int x = 0; x < dst.width(); x++) {
            QRgb *pixel_src = (QRgb*) image_with_borders.scanLine(y + r);
            QRgb *pixel_dst = (QRgb*) dst.scanLine(y);

            std::vector<int> mask_values_red;
            std::vector<int> mask_values_green;
            std::vector<int> mask_values_blue;

            for (int iy = -r; iy <= r; iy++) {
                for (int ix = -r; ix <= r; ix++) {
                    mask_values_red.push_back(qRed(pixel_src[x + r + ix + iy * w]));
                    mask_values_green.push_back(qGreen(pixel_src[x + r + ix + iy * w]));
                    mask_values_blue.push_back(qBlue(pixel_src[x + r + ix + iy * w]));
                }
            }

            std::sort(mask_values_red.begin(), mask_values_red.end());
            std::sort(mask_values_green.begin(), mask_values_green.end());
            std::sort(mask_values_blue.begin(), mask_values_blue.end());

            float floor = std::floor(mask_values_red.size() / 2.0);
            int middle_element = (int) floor;

            pixel_dst[x] = qRgb(mask_values_red[middle_element], mask_values_green[middle_element], mask_values_blue[middle_element]);

            mask_values_red.clear();
            mask_values_green.clear();
            mask_values_blue.clear();
        }
    }
}

void MainWindow::open_image() {
    QString file_name = QFileDialog::getOpenFileName();

    if (!file_name.isNull()) {
        original_image.load(file_name);

        int r = 10;

        QImage destination_image = QImage(original_image.width(), original_image.height(), original_image.format());
        destination_image.fill(Qt::white);

        QImage image_with_borders = make_image_with_borders(original_image, r);

        apply_median_filter(image_with_borders, destination_image, r);

        ui->original_image->setPixmap(QPixmap::fromImage(image_with_borders));
        ui->destination_image->setPixmap(QPixmap::fromImage(destination_image));
    }
}

void MainWindow::on_open_file_triggered()
{
    open_image();
}


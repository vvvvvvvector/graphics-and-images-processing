#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <cmath>

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

void apply_optimized_median_filter(const QImage &src, QImage &dst, int r) {
    int w = src.width();

    for (int y = 0; y < dst.height(); y++) {
        QRgb *pixel_src = (QRgb*) src.scanLine(y + r);
        QRgb *pixel_dst = (QRgb*) dst.scanLine(y);

        float red_hist[256] = {0.0f};
        float green_hist[256] = {0.0f};
        float blue_hist[256] = {0.0f};

        for (int x = 0; x < dst.width(); x++) {
            int red = 0, green = 0, blue = 0;

            if (x == 0) {
                for (int iy = -r; iy <= r; iy++) {
                    for (int ix = -r; ix <= r; ix++) {
                        red_hist[qRed(pixel_src[x + r + ix + iy * w])]++;
                        green_hist[qGreen(pixel_src[x + r + ix + iy * w])]++;
                        blue_hist[qBlue(pixel_src[x + r + ix + iy * w])]++;
                    }
                }
            } else {
                for (int i = -r; i <= r; i++) {
                    red_hist[qRed(pixel_src[x - 1 + i * w])]--;
                    red_hist[qRed(pixel_src[(2 * r + 1) + x + i * w])]++;

                    green_hist[qGreen(pixel_src[x - 1 + i * w])]--;
                    green_hist[qGreen(pixel_src[(2 * r + 1) + x + i * w])]++;

                    blue_hist[qBlue(pixel_src[x - 1 + i * w])]--;
                    blue_hist[qBlue(pixel_src[(2 * r + 1) + x + i * w])]++;
                }
            }

            float r_count = 0.0f;
            bool red_value_founded = false;

            for (int i = 0; i < 256 && !red_value_founded; i++) {
                r_count += red_hist[i];

                if (r_count > pow(2 * r + 1, 2) / 2.0) {
                    red = i;

                    red_value_founded = true;
                }
            }

            float g_count = 0.0f;
            bool green_value_founded = false;

            for (int i = 0; i < 256 && !green_value_founded; i++) {
                g_count += green_hist[i];

                if (g_count > pow(2 * r + 1, 2) / 2.0) {
                    green = i;

                    green_value_founded = true;
                }
            }

            float b_count = 0.0f;
            bool blue_value_founded = false;

            for (int i = 0; i < 256 && !blue_value_founded; i++) {
                b_count += blue_hist[i];

                if (b_count > pow(2 * r + 1, 2) / 2.0) {
                    blue = i;

                    blue_value_founded = true;
                }
            }

            pixel_dst[x] = qRgb(red, green, blue);
        }
    }
}

void apply_median_filter(const QImage &src, QImage &dst, int r) {
    int w = src.width();

    for (int y = 0; y < dst.height(); y++) {
        QRgb *pixel_src = (QRgb*) src.scanLine(y + r);
        QRgb *pixel_dst = (QRgb*) dst.scanLine(y);

        for (int x = 0; x < dst.width(); x++) {
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

        int r = 15;

        QImage destination_image = QImage(original_image.width(), original_image.height(), original_image.format());
        destination_image.fill(Qt::white);

        QImage image_with_borders = make_image_with_borders(original_image, r);

        // apply_median_filter(image_with_borders, destination_image, r);

        apply_optimized_median_filter(image_with_borders, destination_image, r);

        ui->original_image->setPixmap(QPixmap::fromImage(image_with_borders));
        ui->destination_image->setPixmap(QPixmap::fromImage(destination_image));
    }
}

void MainWindow::on_open_file_triggered()
{
    open_image();
}


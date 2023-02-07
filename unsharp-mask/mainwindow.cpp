#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->original_image->setText("Image with borders here.");
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

void apply_separable_gauss_filter(const QImage &src, QImage &dst, std::vector<int> mask, int r) {
    QImage intermediate_image = src;

    int mask_elements_sum = std::accumulate(mask.begin(), mask.end(), 0);

    for (int y = 0; y < dst.height(); y++) {
        QRgb *pixel_src = (QRgb*) src.scanLine(y + r);
        QRgb *pixel_intermediate = (QRgb*) intermediate_image.scanLine(y + r);

        for (int x = 0; x < dst.width(); x++) {
            int mask_index = 0;
            int red = 0, green = 0, blue = 0;

            // horizontal
            for (int i = -r; i <= r; i++, mask_index++) {
                red += qRed(pixel_src[x + r + i]) * mask[mask_index];
                green += qGreen(pixel_src[x + r + i]) * mask[mask_index];
                blue += qBlue(pixel_src[x + r + i]) * mask[mask_index];
            }

            red = clamp<int>(red / mask_elements_sum, 0, 255);
            green = clamp<int>(green / mask_elements_sum, 0, 255);
            blue = clamp<int>(blue / mask_elements_sum, 0, 255);

            pixel_intermediate[x + r] = qRgb(red, green, blue);
        }
    }

    int w = src.width();

    for (int y = 0; y < dst.height(); y++) {
        QRgb *pixel_intermediate = (QRgb*) intermediate_image.scanLine(y + r);
        QRgb *pixel_dst = (QRgb*) dst.scanLine(y);

        for (int x = 0; x < dst.width(); x++) {
            int mask_index = 0;
            int red = 0, green = 0, blue = 0;

            // vertical
            for (int i = -r; i <= r; i++, mask_index++) {
                red += qRed(pixel_intermediate[x + r + i * w]) * mask[mask_index];
                green += qGreen(pixel_intermediate[x + r + i * w]) * mask[mask_index];
                blue += qBlue(pixel_intermediate[x + r + i * w]) * mask[mask_index];
            }

            red = clamp<int>(red / mask_elements_sum, 0, 255);
            green = clamp<int>(green / mask_elements_sum, 0, 255);
            blue = clamp<int>(blue / mask_elements_sum, 0, 255);

            pixel_dst[x] = qRgb(red, green, blue);
        }
    }
}

std::vector<int> generate_gauss_mask(int radius) {
    std::vector<int> mask;

    float sigma = (2 * radius + 1) / (2 * 3.14159265359);

    for (int i = -radius; i <= radius; i++) {
        mask.push_back(100 * (exp(-(pow(i, 2)) / (2 * pow(sigma, 2)))));
    }

    return mask;
}

void images_difference(const QImage &src, const QImage &dst, short *r_channel, short *g_channel, short *b_channel,  float alpha) {
    int width = src.width();

    for (int y = 0; y < dst.height(); y++) {
        QRgb *pixel_src = (QRgb*) src.scanLine(y);
        QRgb *pixel_dst = (QRgb*) dst.scanLine(y);

        for (int x = 0; x < dst.width(); x++) {
            int red = qRed(pixel_src[x]) - qRed(pixel_dst[x]);
            int green = qGreen(pixel_src[x]) - qGreen(pixel_dst[x]);
            int blue = qBlue(pixel_src[x]) - qBlue(pixel_dst[x]);

            r_channel[x + y * width]  = alpha * red;
            g_channel[x + y * width]  = alpha * green;
            b_channel[x + y * width]  = alpha * blue;
        }
    }
}

QImage unsharp_mask(const QImage &src, short *r_channel, short *g_channel, short *b_channel) {
    int width = src.width();

    QImage result = QImage(src.width(), src.height(), src.format());
    result.fill(Qt::white);

    for (int y = 0; y < result.height(); y++) {
        QRgb *pixel_src = (QRgb*) src.scanLine(y);
        QRgb *pixel_result = (QRgb*) result.scanLine(y);

        for (int x = 0; x < result.width(); x++) {
            int red = qRed(pixel_src[x]) + r_channel[x + y * width];
            int green = qGreen(pixel_src[x]) + g_channel[x + y * width];
            int blue = qBlue(pixel_src[x]) + b_channel[x + y * width];

            red = clamp<int>(red, 0, 255);
            green = clamp<int>(green, 0, 255);
            blue = clamp<int>(blue, 0, 255);

            pixel_result[x] = qRgb(red, green, blue);
        }
    }

    return result;
}

void MainWindow::open_image() {
    QString file_name = QFileDialog::getOpenFileName();

    if (!file_name.isNull()) {
        original_image.load(file_name);

        int r = 10;

        std::vector<int> mask = generate_gauss_mask(r);

        QImage blurred_image = QImage(original_image.width(), original_image.height(), original_image.format());
        blurred_image.fill(Qt::white);

        QImage image_with_borders = make_image_with_borders(original_image, r);
        ui->original_image->setPixmap(QPixmap::fromImage(image_with_borders));

        apply_separable_gauss_filter(image_with_borders, blurred_image, mask, r);

        short *r_channel = new short[original_image.width() * original_image.height()];
        short *g_channel = new short[original_image.width() * original_image.height()];
        short *b_channel = new short[original_image.width() * original_image.height()];

        images_difference(original_image, blurred_image, r_channel, g_channel, b_channel, 1.0f);

        QImage result = unsharp_mask(original_image, r_channel, g_channel, b_channel);

        ui->destination_image->setPixmap(QPixmap::fromImage(result));

        delete[] r_channel;
        delete[] g_channel;
        delete[] b_channel;
    }
}

void MainWindow::on_open_file_triggered()
{
    open_image();
}


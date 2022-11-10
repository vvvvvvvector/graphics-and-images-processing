#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->image->setText("Your image here.");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void apply_identity(const QImage &src, QImage &dst, float *matrix3x3) {
    int width = src.width();
    int height = src.height();

    dst = QImage(width, height, src.format());
    dst.fill(Qt::white);

    QRgb *pixel_src = (QRgb*) src.scanLine(0);
    QRgb *pixel_dst = (QRgb*) dst.scanLine(0);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int out_x = x * matrix3x3[0] + y * matrix3x3[1] + matrix3x3[2];
            int out_y = x * matrix3x3[3] + y * matrix3x3[4] + matrix3x3[5];

            pixel_dst[x + y * width] = pixel_src[out_x + out_y * width];
        }
    }
}

void apply_reflection_x(const QImage &src, QImage &dst, float *matrix3x3) {
    int width = src.width();
    int height = src.height();

    dst = QImage(width, height, src.format());
    dst.fill(Qt::white);

    QRgb *pixel_src = (QRgb*) src.scanLine(0);
    QRgb *pixel_dst = (QRgb*) dst.scanLine(0);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int out_x = x * matrix3x3[0] + y * matrix3x3[1] + matrix3x3[2];
            int out_y = x * matrix3x3[3] + y * matrix3x3[4] + matrix3x3[5];

            out_x += width - 1;

            pixel_dst[x + y * width] = pixel_src[out_x + out_y * width];
        }
    }
}

void apply_reflection_y(const QImage &src, QImage &dst, float *matrix3x3) {
    int width = src.width();
    int height = src.height();

    dst = QImage(width, height, src.format());
    dst.fill(Qt::white);

    QRgb *pixel_src = (QRgb*) src.scanLine(0);
    QRgb *pixel_dst = (QRgb*) dst.scanLine(0);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int out_x = x * matrix3x3[0] + y * matrix3x3[1] + matrix3x3[2];
            int out_y = x * matrix3x3[3] + y * matrix3x3[4] + matrix3x3[5];

            out_y += height - 1;

            pixel_dst[x + y * width] = pixel_src[out_x + out_y * width];
        }
    }
}


void apply_translation(const QImage &src, QImage &dst, float *matrix3x3) {
    int width = src.width();
    int height = src.height();

    dst = QImage(width, height, src.format());
    dst.fill(Qt::white);

    QRgb *pixel_src = (QRgb*) src.scanLine(0);
    QRgb *pixel_dst = (QRgb*) dst.scanLine(0);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int out_x = x * matrix3x3[0] + y * matrix3x3[1] + matrix3x3[2];
            int out_y = x * matrix3x3[3] + y * matrix3x3[4] + matrix3x3[5];


            if (out_x >= 0 && out_y >= 0 && out_y < height && out_x < width) {
                pixel_dst[out_x + out_y * width] = pixel_src[x + y * width];
            }
        }
    }
}

void apply_scale(const QImage &src, QImage &dst, float *matrix3x3) {
    int width = src.width();
    int height = src.height();

    dst = QImage(width, height, src.format());
    dst.fill(Qt::black);

    QRgb *pixel_src = (QRgb*) src.scanLine(0);
    QRgb *pixel_dst = (QRgb*) dst.scanLine(0);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // round(x / matrix3x3[0]) - coordinates in old image
            // round(y / matrix3x3[4]) - coordinates in old image

            int out_x = round(x / matrix3x3[0]) + y * matrix3x3[1] + matrix3x3[2];
            int out_y = x * matrix3x3[3] + round(y / matrix3x3[4]) + matrix3x3[5];

            if (out_x < width && out_y < height) {
                pixel_dst[x + y * width] = pixel_src[out_x + out_y * width];
            }
        }
    }
}

void apply_rotate(const QImage &src, QImage &dst, float *matrix3x3) {
    int width = src.width();
    int height = src.height();

    dst = QImage(width, height, src.format());
    dst.fill(Qt::black);

    QRgb *pixel_src = (QRgb*) src.scanLine(0);
    QRgb *pixel_dst = (QRgb*) dst.scanLine(0);

    float sin_value = matrix3x3[3];
    float cos_value = matrix3x3[0];

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int out_x = x * cos_value - y * sin_value;
            int out_y = x * sin_value + y * cos_value;

            if (out_x < width && out_y < height && out_x > 0 && out_y > 0) {
                pixel_dst[x + y * width] = pixel_src[out_x + out_y * width];
            }
        }
    }
}

void apply_shear(const QImage &src, QImage &dst, float *matrix3x3) {
    int width = src.width();
    int height = src.height();

    dst = QImage(width, height, src.format());
    dst.fill(Qt::black);

    QRgb *pixel_src = (QRgb*) src.scanLine(0);
    QRgb *pixel_dst = (QRgb*) dst.scanLine(0);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int out_x = x * matrix3x3[0] + y * matrix3x3[1] + matrix3x3[2];
            int out_y = x * matrix3x3[3] + y * matrix3x3[4] + matrix3x3[5];

            if (out_x < width && out_y < height && out_x > 0 && out_y > 0) {
                pixel_dst[x + y * width] = pixel_src[out_x + out_y * width];
            }
        }
    }
}

void identity(float *matrix3x3) {
    matrix3x3[0] = 1.0f; matrix3x3[1] = 0.0f; matrix3x3[2] = 0.0f;
    matrix3x3[3] = 0.0f; matrix3x3[4] = 1.0f; matrix3x3[5] = 0.0f;
    matrix3x3[6] = 0.0f; matrix3x3[7] = 0.0f; matrix3x3[8] = 1.0f;
}

void reflection_x(float *matrix3x3) {
    matrix3x3[0] = -1.0f; matrix3x3[1] = 0.0f; matrix3x3[2] = 0.0f;
    matrix3x3[3] = 0.0f; matrix3x3[4] = 1.0f; matrix3x3[5] = 0.0f;
    matrix3x3[6] = 0.0f; matrix3x3[7] = 0.0f; matrix3x3[8] = 1.0f;
}

void reflection_y(float *matrix3x3) {
    matrix3x3[0] = 1.0f; matrix3x3[1] = 0.0f; matrix3x3[2] = 0.0f;
    matrix3x3[3] = 0.0f; matrix3x3[4] = -1.0f; matrix3x3[5] = 0.0f;
    matrix3x3[6] = 0.0f; matrix3x3[7] = 0.0f; matrix3x3[8] = 1.0f;
}

void translation(float *matrix3x3, float tx, float ty) {
    matrix3x3[0] = 1.0f; matrix3x3[1] = 0.0f; matrix3x3[2] = tx;
    matrix3x3[3] = 0.0f; matrix3x3[4] = 1.0f; matrix3x3[5] = ty;
    matrix3x3[6] = 0.0f; matrix3x3[7] = 0.0f; matrix3x3[8] = 1.0f;
}

void scale(float *matrix3x3, float sx, float sy) {
    matrix3x3[0] = sx; matrix3x3[1] = 0.0f; matrix3x3[2] = 0.0f;
    matrix3x3[3] = 0.0f; matrix3x3[4] = sy; matrix3x3[5] = 0.0f;
    matrix3x3[6] = 0.0f; matrix3x3[7] = 0.0f; matrix3x3[8] = 1.0f;
}

void rotate(float *matrix3x3, float theta) {
    matrix3x3[0] = cos(theta); matrix3x3[1] = -sin(theta); matrix3x3[2] = 0.0f;
    matrix3x3[3] = sin(theta); matrix3x3[4] = cos(theta); matrix3x3[5] = 0.0f;
    matrix3x3[6] = 0.0f; matrix3x3[7] = 0.0f; matrix3x3[8] = 1.0f;
}

void shear(float *matrix3x3, float sx, float sy) {
    matrix3x3[0] = 1.0f; matrix3x3[1] = sx; matrix3x3[2] = 0.0f;
    matrix3x3[3] = sy; matrix3x3[4] = 1.0f; matrix3x3[5] = 0.0f;
    matrix3x3[6] = 0.0f; matrix3x3[7] = 0.0f; matrix3x3[8] = 1.0f;
}

void MainWindow::open_image() {
    QString file_name = QFileDialog::getOpenFileName();

    if (!file_name.isNull()) {
        original_image.load(file_name);

        QImage process_image;

        float matrix3x3[9] = {0.0f};

        // 1. Identity
        // identity(matrix3x3);
        // apply_identity(original_image, process_image, matrix3x3);

        // 2. Reflection x
        // reflection_x(matrix3x3);
        // apply_reflection_x(original_image, process_image, matrix3x3);

        // 3. Reflection y
        // reflection_y(matrix3x3);
        // apply_reflection_y(original_image, process_image, matrix3x3);

        // 4. Translation
        // translation(matrix3x3, original_image.width() / 2.0, -original_image.height() / 2.0);
        // apply_translation(original_image, process_image, matrix3x3);

        // 5. Scale
        // scale(matrix3x3, 1.5f, 1.5f);
        // apply_scale(original_image, process_image, matrix3x3);

        // 6. Rotate
        rotate(matrix3x3, M_PI / 10);
        apply_rotate(original_image, process_image, matrix3x3);

        // 7. Shear
        // shear(matrix3x3, 0.5f, 0.0f);
        // apply_shear(original_image, process_image, matrix3x3);

        ui->image->setPixmap(QPixmap::fromImage(process_image));
    }
}

void MainWindow::on_action_open_triggered()
{
    open_image();
}


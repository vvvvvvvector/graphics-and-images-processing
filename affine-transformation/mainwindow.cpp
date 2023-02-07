#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

struct Matrix3x3 {
    float matrix3x3[9] = {0.0f};
};

Matrix3x3 multiply_transformations(float *, float *);

Matrix3x3 identity();
Matrix3x3 reflection_x();
Matrix3x3 reflection_y();
Matrix3x3 translation(float, float);
Matrix3x3 scale(float, float);
Matrix3x3 rotate(float);
Matrix3x3 shear(float, float);

QImage apply_affine_transformation(const QImage &, float *);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ui->image->setText("Your image here.");

    QString file_name = "/Users/vvvvvec1or/Downloads/Lenna.png";

    if (!file_name.isNull()) {
        original_image.load(file_name);

        // 1. Identity
        // Matrix3x3 matrix = identity();

        // 2. Reflection x
        // Matrix3x3 reflection_x_matrix = reflection_x();
        // Matrix3x3 translation_matrix = translation(original_image.width() - 1, 0);
        // Matrix3x3 matrix = multiply_transformations(reflection_x_matrix.matrix3x3, translation_matrix.matrix3x3);

        // 3. Reflection y
        // Matrix3x3 reflection_y_matrix = reflection_y();
        // Matrix3x3 translation_matrix = translation(0, original_image.height() - 1);
        // Matrix3x3 matrix = multiply_transformations(reflection_y_matrix.matrix3x3, translation_matrix.matrix3x3);

        // 4. Translation
        // Matrix3x3 matrix = translation(original_image.width() / 2, 0);

        // 5. Scale
        // Matrix3x3 matrix = scale(1.5f, 1.0f);

        // 6. Rotate
        Matrix3x3 matrix = rotate(M_PI / 6);

        // 7. Shear
        // Matrix3x3 matrix = shear(0.5f, 0.0f);

        QImage process_image = apply_affine_transformation(original_image, matrix.matrix3x3);

        ui->image->setPixmap(QPixmap::fromImage(process_image));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

Matrix3x3 multiply_transformations(float *first, float *second) {
    Matrix3x3 m;

    m.matrix3x3[0] = first[0] * second[0] + first[1] * second[3] + first[2] * second[6];
    m.matrix3x3[1] = first[0] * second[1] + first[1] * second[4] + first[2] * second[7];
    m.matrix3x3[2] = first[0] * second[2] + first[1] * second[5] + first[2] * second[8];
    m.matrix3x3[3] = first[3] * second[0] + first[4] * second[3] + first[5] * second[6];
    m.matrix3x3[4] = first[3] * second[1] + first[4] * second[4] + first[5] * second[7];
    m.matrix3x3[5] = first[3] * second[2] + first[4] * second[5] + first[5] * second[8];
    m.matrix3x3[6] = first[6] * second[0] + first[7] * second[3] + first[8] * second[6];
    m.matrix3x3[7] = first[6] * second[1] + first[7] * second[4] + first[8] * second[7];
    m.matrix3x3[8] = first[6] * second[2] + first[7] * second[5] + first[8] * second[8];

    return m;
}

Matrix3x3 identity() {
    Matrix3x3 m;

    m.matrix3x3[0] = 1.0f; m.matrix3x3[1] = 0.0f; m.matrix3x3[2] = 0.0f;
    m.matrix3x3[3] = 0.0f; m.matrix3x3[4] = 1.0f; m.matrix3x3[5] = 0.0f;
    m.matrix3x3[6] = 0.0f; m.matrix3x3[7] = 0.0f; m.matrix3x3[8] = 1.0f;

    return m;
}

Matrix3x3 reflection_x() {
    Matrix3x3 m;

    m.matrix3x3[0] = -1.0f; m.matrix3x3[1] = 0.0f; m.matrix3x3[2] = 0.0f;
    m.matrix3x3[3] = 0.0f; m.matrix3x3[4] = 1.0f; m.matrix3x3[5] = 0.0f;
    m.matrix3x3[6] = 0.0f; m.matrix3x3[7] = 0.0f; m.matrix3x3[8] = 1.0f;

    return m;
}

Matrix3x3 reflection_y() {
    Matrix3x3 m;

    m.matrix3x3[0] = 1.0f; m.matrix3x3[1] = 0.0f; m.matrix3x3[2] = 0.0f;
    m.matrix3x3[3] = 0.0f; m.matrix3x3[4] = -1.0f; m.matrix3x3[5] = 0.0f;
    m.matrix3x3[6] = 0.0f; m.matrix3x3[7] = 0.0f; m.matrix3x3[8] = 1.0f;

    return m;
}

Matrix3x3 translation(float tx, float ty) {
    Matrix3x3 m;

    m.matrix3x3[0] = 1.0f; m.matrix3x3[1] = 0.0f; m.matrix3x3[2] = -tx;
    m.matrix3x3[3] = 0.0f; m.matrix3x3[4] = 1.0f; m.matrix3x3[5] = -ty;
    m.matrix3x3[6] = 0.0f; m.matrix3x3[7] = 0.0f; m.matrix3x3[8] = 1.0f;

    return m;
}

Matrix3x3 scale(float sx, float sy) {
    Matrix3x3 m;

    m.matrix3x3[0] = 1 / sx; m.matrix3x3[1] = 0.0f; m.matrix3x3[2] = 0.0f;
    m.matrix3x3[3] = 0.0f; m.matrix3x3[4] = 1 / sy; m.matrix3x3[5] = 0.0f;
    m.matrix3x3[6] = 0.0f; m.matrix3x3[7] = 0.0f; m.matrix3x3[8] = 1.0f;

    return m;
}

Matrix3x3 rotate(float theta) {
    Matrix3x3 m;

    m.matrix3x3[0] = cos(theta); m.matrix3x3[1] = -sin(theta); m.matrix3x3[2] = 0.0f;
    m.matrix3x3[3] = sin(theta); m.matrix3x3[4] = cos(theta); m.matrix3x3[5] = 0.0f;
    m.matrix3x3[6] = 0.0f; m.matrix3x3[7] = 0.0f; m.matrix3x3[8] = 1.0f;

    return m;
}

Matrix3x3 shear(float sx, float sy) {
    Matrix3x3 m;

    m.matrix3x3[0] = 1.0f; m.matrix3x3[1] = sx; m.matrix3x3[2] = 0.0f;
    m.matrix3x3[3] = sy; m.matrix3x3[4] = 1.0f; m.matrix3x3[5] = 0.0f;
    m.matrix3x3[6] = 0.0f; m.matrix3x3[7] = 0.0f; m.matrix3x3[8] = 1.0f;

    return m;
}

QImage apply_affine_transformation(const QImage &src, float *matrix3x3) {
    int width = src.width();
    int height = src.height();

    float zero = matrix3x3[0];
    float one = matrix3x3[1];
    float two = matrix3x3[2];
    float three = matrix3x3[3];
    float four = matrix3x3[4];
    float five = matrix3x3[5];

    QImage dst = QImage(width, height, src.format());
    dst.fill(Qt::black);

    QRgb *pixel_src = (QRgb*) src.scanLine(0);
    QRgb *pixel_dst = (QRgb*) dst.scanLine(0);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int out_x = x * zero + y * one + two;
            int out_y = x * three + y * four + five;

            if ((out_x < width && out_x >= 0) && (out_y < height && out_y >= 0))
                pixel_dst[x + y * width] = pixel_src[out_x + out_y * width];
        }
    }

    return dst;
}

void MainWindow::open_image() {
    QString file_name = QFileDialog::getOpenFileName();

    if (!file_name.isNull()) {
        original_image.load(file_name);

        // 1. Identity
        // Matrix3x3 matrix = identity();

        // 2. Reflection x
        // Matrix3x3 reflection_x_matrix = reflection_x();
        // Matrix3x3 translation_matrix = translation(original_image.width() - 1, 0);
        // Matrix3x3 matrix = multiply_transformations(reflection_x_matrix.matrix3x3, translation_matrix.matrix3x3);

        // 3. Reflection y
        Matrix3x3 reflection_y_matrix = reflection_y();
        Matrix3x3 translation_matrix = translation(0, original_image.height() - 1);
        Matrix3x3 matrix = multiply_transformations(reflection_y_matrix.matrix3x3, translation_matrix.matrix3x3);

        // 4. Translation
        // Matrix3x3 matrix = translation(original_image.width() / 2, 0);

        // 5. Scale
        // Matrix3x3 matrix = scale(1.5f, 1.0f);

        // 6. Rotate
        // Matrix3x3 matrix = rotate(M_PI / 6);

        // 7. Shear
        // Matrix3x3 matrix = shear(0.5f, 0.0f);

        QImage process_image = apply_affine_transformation(original_image, matrix.matrix3x3);

        ui->image->setPixmap(QPixmap::fromImage(process_image));
    }
}

void MainWindow::on_action_open_triggered()
{
    open_image();
}


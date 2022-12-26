#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

float* multiply_transformations(float *, float *);

float* identity();
float* reflection_x();
float* reflection_y();
float* translation(float, float);
float* scale(float, float);
float* rotate(float);
float* shear(float, float);

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
        // float* matrix = identity();

        // 2. Reflection x
        // float* reflection_x_matrix = reflection_x();
        // float *translation_matrix = translation(original_image.width() - 1, 0);
        // float *matrix = multiply_transformations(reflection_x_matrix, translation_matrix);

        // 3. Reflection y
        // float* reflection_y_matrix = reflection_y();
        // float *translation_matrix = translation(0, original_image.height() - 1);
        // float *matrix = multiply_transformations(reflection_y_matrix, translation_matrix);

        // 4. Translation
        float *matrix = translation(original_image.width() / 2, 0);

        // 5. Scale
        // float *matrix = scale(1.5f, 1.5f);

        // 6. Rotate
        // float *matrix = rotate(M_PI / 6);

        // 7. Shear
        // float *matrix = shear(0.5f, 0.0f);

        QImage process_image = apply_affine_transformation(original_image, matrix);

        ui->image->setPixmap(QPixmap::fromImage(process_image));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

float* multiply_transformations(float *first, float *second) {
    static float matrix3x3[9] = {0.0f};

    matrix3x3[0] = first[0] * second[0] + first[1] * second[3] + first[2] * second[6];
    matrix3x3[1] = first[0] * second[1] + first[1] * second[4] + first[2] * second[7];
    matrix3x3[2] = first[0] * second[2] + first[1] * second[5] + first[2] * second[8];
    matrix3x3[3] = first[3] * second[0] + first[4] * second[3] + first[5] * second[6];
    matrix3x3[4] = first[3] * second[1] + first[4] * second[4] + first[5] * second[7];
    matrix3x3[5] = first[3] * second[2] + first[4] * second[5] + first[5] * second[8];
    matrix3x3[6] = first[6] * second[0] + first[7] * second[3] + first[8] * second[6];
    matrix3x3[7] = first[6] * second[1] + first[7] * second[4] + first[8] * second[7];
    matrix3x3[8] = first[6] * second[2] + first[7] * second[5] + first[8] * second[8];

    return matrix3x3;
}

float* identity() {
    static float matrix3x3[9] = {0.0f};

    matrix3x3[0] = 1.0f; matrix3x3[1] = 0.0f; matrix3x3[2] = 0.0f;
    matrix3x3[3] = 0.0f; matrix3x3[4] = 1.0f; matrix3x3[5] = 0.0f;
    matrix3x3[6] = 0.0f; matrix3x3[7] = 0.0f; matrix3x3[8] = 1.0f;

    return matrix3x3;
}

float* reflection_x() {
    static float matrix3x3[9] = {0.0f};

    matrix3x3[0] = -1.0f; matrix3x3[1] = 0.0f; matrix3x3[2] = 0.0f;
    matrix3x3[3] = 0.0f; matrix3x3[4] = 1.0f; matrix3x3[5] = 0.0f;
    matrix3x3[6] = 0.0f; matrix3x3[7] = 0.0f; matrix3x3[8] = 1.0f;

    return matrix3x3;
}

float* reflection_y() {
    static float matrix3x3[9] = {0.0f};

    matrix3x3[0] = 1.0f; matrix3x3[1] = 0.0f; matrix3x3[2] = 0.0f;
    matrix3x3[3] = 0.0f; matrix3x3[4] = -1.0f; matrix3x3[5] = 0.0f;
    matrix3x3[6] = 0.0f; matrix3x3[7] = 0.0f; matrix3x3[8] = 1.0f;

    return matrix3x3;
}

float* translation(float tx, float ty) {
    static float matrix3x3[9] = {0.0f};

    matrix3x3[0] = 1.0f; matrix3x3[1] = 0.0f; matrix3x3[2] = -tx;
    matrix3x3[3] = 0.0f; matrix3x3[4] = 1.0f; matrix3x3[5] = -ty;
    matrix3x3[6] = 0.0f; matrix3x3[7] = 0.0f; matrix3x3[8] = 1.0f;

    return matrix3x3;
}

float* scale(float sx, float sy) {
    static float matrix3x3[9] = {0.0f};

    matrix3x3[0] = 1 / sx; matrix3x3[1] = 0.0f; matrix3x3[2] = 0.0f;
    matrix3x3[3] = 0.0f; matrix3x3[4] = 1 / sy; matrix3x3[5] = 0.0f;
    matrix3x3[6] = 0.0f; matrix3x3[7] = 0.0f; matrix3x3[8] = 1.0f;

    return matrix3x3;
}

float* rotate(float theta) {
    static float matrix3x3[9] = {0.0f};

    matrix3x3[0] = cos(theta); matrix3x3[1] = -sin(theta); matrix3x3[2] = 0.0f;
    matrix3x3[3] = sin(theta); matrix3x3[4] = cos(theta); matrix3x3[5] = 0.0f;
    matrix3x3[6] = 0.0f; matrix3x3[7] = 0.0f; matrix3x3[8] = 1.0f;

    return matrix3x3;
}

float* shear(float sx, float sy) {
    static float matrix3x3[9] = {0.0f};

    matrix3x3[0] = 1.0f; matrix3x3[1] = sx; matrix3x3[2] = 0.0f;
    matrix3x3[3] = sy; matrix3x3[4] = 1.0f; matrix3x3[5] = 0.0f;
    matrix3x3[6] = 0.0f; matrix3x3[7] = 0.0f; matrix3x3[8] = 1.0f;

    return matrix3x3;
}

QImage apply_affine_transformation(const QImage &src, float *matrix3x3) {
    int width = src.width();
    int height = src.height();

    QImage dst = QImage(width, height, src.format());
    dst.fill(Qt::black);

    QRgb *pixel_src = (QRgb*) src.scanLine(0);
    QRgb *pixel_dst = (QRgb*) dst.scanLine(0);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int out_x = x * matrix3x3[0] + y * matrix3x3[1] + matrix3x3[2];
            int out_y = x * matrix3x3[3] + y * matrix3x3[4] + matrix3x3[5];

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
        // float* matrix = identity();

        // 2. Reflection x
        // float* reflection_x_matrix = reflection_x();
        // float *translation_matrix = translation(original_image.width() - 1, 0);
        // float *matrix = multiply_transformations(reflection_x_matrix, translation_matrix);

        // 3. Reflection y
        // float* reflection_y_matrix = reflection_y();
        // float *translation_matrix = translation(0, original_image.height() - 1);
        // float *matrix = multiply_transformations(reflection_y_matrix, translation_matrix);

        // 4. Translation
        // float *matrix = translation(original_image.width() / 2, 0);

        // 5. Scale
        float *matrix = scale(1.5f, 1.5f);

        // 6. Rotate
        // float *matrix = rotate(M_PI / 6);

        // 7. Shear
        // float *matrix = shear(0.5f, 0.0f);

        QImage process_image = apply_affine_transformation(original_image, matrix);

        ui->image->setPixmap(QPixmap::fromImage(process_image));
    }
}

void MainWindow::on_action_open_triggered()
{
    open_image();
}


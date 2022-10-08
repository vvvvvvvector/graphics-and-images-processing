#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    hist_image_r = QImage(255, 256, QImage::Format_RGB32);
    hist_image_r.fill(Qt::white);

    hist_image_g = QImage(256, 256, QImage::Format_RGB32);
    hist_image_g.fill(Qt::white);

    hist_image_b = QImage(256, 256, QImage::Format_RGB32);
    hist_image_b.fill(Qt::white);

    ui->histogram_red->setPixmap(QPixmap::fromImage(hist_image_r));
    ui->histogram_green->setPixmap(QPixmap::fromImage(hist_image_g));
    ui->histogram_blue->setPixmap(QPixmap::fromImage(hist_image_b));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openImage() {
    QString fileName = QFileDialog::getOpenFileName();

    float r_count[256] = {0.0f};
    float g_count[256] = {0.0f};
    float b_count[256] = {0.0f};

    if (!fileName.isNull()) {
        original_image.load(fileName);

        //----------------red----------------
        for (short y = 0; y < original_image.height(); ++y) {
            QRgb *row = (QRgb*) original_image.scanLine(y);

            for (short x = 0; x < original_image.width(); ++x) {
                unsigned char r = qRed(row[x]);

                r_count[r]++;
            }
        }

        float max_red = r_count[0];
        for (int i = 0; i < 256; ++i) {
            if (r_count[i] > max_red) {
                max_red = r_count[i];
            }
        }

        for (int i = 0; i < 256; ++i) {
            r_count[i] = ((r_count[i] - 0) / (max_red - 0)) * 255;
        }

        int counter_red = 0;

        for (short y = hist_image_r.height() - 1; y >= 0; --y) {
            QRgb *row = (QRgb*) hist_image_r.scanLine(y);

            counter_red++;

            for (short x = 0; x < hist_image_r.width(); ++x) {
                if (r_count[x] >= counter_red) {
                    row[x] = QColor(255, 0, 0).rgba();
                }
            }
        }

        ui->histogram_red->setPixmap(QPixmap::fromImage(hist_image_r));
        //----------------red----------------

        //----------------green----------------
        for (short y = 0; y < original_image.height(); ++y) {
            QRgb *row = (QRgb*) original_image.scanLine(y);

            for (short x = 0; x < original_image.width(); ++x) {
                unsigned char g = qGreen(row[x]);

                g_count[g]++;
            }
        }

        float max_green = g_count[0];
        for (int i = 0; i < 256; ++i) {
            if (g_count[i] > max_green) {
                max_green = g_count[i];
            }
        }

        for (int i = 0; i < 256; ++i) {
            g_count[i] = ((g_count[i] - 0) / (max_green - 0)) * 255;
        }

        int counter_green = 0;

        for (short y = hist_image_g.height() - 1; y >= 0; --y) {
            QRgb *row = (QRgb*) hist_image_g.scanLine(y);

            counter_green++;

            for (short x = 0; x < hist_image_g.width(); ++x) {
                if (g_count[x] >= counter_green) {
                    row[x] = QColor(0, 255, 0).rgba();
                }
            }
        }

        ui->histogram_green->setPixmap(QPixmap::fromImage(hist_image_g));
        //----------------green----------------

        //----------------blue----------------
        for (short y = 0; y < original_image.height(); ++y) {
            QRgb *row = (QRgb*) original_image.scanLine(y);

            for (short x = 0; x < original_image.width(); ++x) {
                unsigned char b = qBlue(row[x]);

                b_count[b]++;
            }
        }

        float max_blue = b_count[0];
        for (int i = 0; i < 256; ++i) {
            if (b_count[i] > max_blue) {
                max_blue = b_count[i];
            }
        }

        for (int i = 0; i < 256; ++i) {
            b_count[i] = ((b_count[i] - 0) / (max_blue - 0)) * 255;
        }

        int counter_blue = 0;

        for (short y = hist_image_b.height() - 1; y >= 0; --y) {
            QRgb *row = (QRgb*) hist_image_b.scanLine(y);

            counter_blue++;

            for (short x = 0; x < hist_image_b.width(); ++x) {
                if (b_count[x] >= counter_blue) {
                    row[x] = QColor(0, 0, 255).rgba();
                }
            }
        }

        ui->histogram_blue->setPixmap(QPixmap::fromImage(hist_image_b));
        //----------------blue----------------
    }
}

void MainWindow::on_actionOpen_triggered()
{
    openImage();
}


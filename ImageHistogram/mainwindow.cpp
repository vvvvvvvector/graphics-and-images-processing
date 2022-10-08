#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    hist_image = QImage(256, 256, QImage::Format_RGB32);
    hist_image.fill(Qt::white);

    ui->histogram->setPixmap(QPixmap::fromImage(hist_image));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openImage() {
    QString fileName = QFileDialog::getOpenFileName();

    float r_count[256] = {0.0f};

    if (!fileName.isNull()) {
        original_image.load(fileName);

        for (short y = 0; y < original_image.height(); ++y) {
            QRgb *row = (QRgb*) original_image.scanLine(y);

            for (short x = 0; x < original_image.width(); ++x) {
                unsigned char r = qRed(row[x]);

                r_count[r]++;
            }
        }

        float max = r_count[0];
        for (int i = 0; i < 256; ++i) {
            if (r_count[i] > max) {
                max = r_count[i];
            }
        }

        for (int i = 0; i < 256; ++i) {
            r_count[i] = ((r_count[i] - 0) / (max - 0)) * 255;
        }

        int counter = 0;

        for (short y = hist_image.height() - 1; y >= 0; --y) {
            QRgb *row = (QRgb*) hist_image.scanLine(y);

            counter++;

            for (short x = 0; x < hist_image.width(); ++x) {
                if (r_count[x] >= counter) {
                    row[x] = QColor(204, 0, 12).rgba();
                }
            }
        }

        ui->histogram->setPixmap(QPixmap::fromImage(hist_image));

        for (int i = 0; i < 256; ++i) {
            qInfo() << qRound(r_count[i]) << " ";
        }
    }
}

void MainWindow::on_actionOpen_triggered()
{
    openImage();
}


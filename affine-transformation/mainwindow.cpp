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

void MainWindow::open_image() {
    QString file_name = QFileDialog::getOpenFileName();

    if (!file_name.isNull()) {
        original_image.load(file_name);
        ui->image->setPixmap(QPixmap::fromImage(original_image));
    }
}

void MainWindow::on_action_open_triggered()
{
    open_image();
}


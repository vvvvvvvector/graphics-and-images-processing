#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

template<class T>
T clamp(T v, T minv, T maxv) {
    if (v >= maxv) return maxv;
    if (v <= minv) return minv;
    return v;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QImage original_image;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void open_image();

private slots:
    void on_open_file_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

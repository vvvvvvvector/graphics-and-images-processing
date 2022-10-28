#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>

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
    void openImage();


private slots:
    void on_open_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

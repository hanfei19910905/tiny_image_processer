#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <opencv2/opencv.hpp>
#include <QFileDialog>
#include <QMainWindow>
#include <algo.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    void clickImageX(int);
    void clickImageY(int);
    void clickImage(cv::Mat&,int,int);

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Algo* algo;
    cv::Mat image,result;
    void mousePressEvent(QMouseEvent *);
    void frush(cv::Mat&);
};

#endif // MAINWINDOW_H

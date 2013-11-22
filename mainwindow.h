#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void LoadImage(const QString&);
    void signal_awb();
private slots:
    void on_LoadFileBtn_clicked();
    void on_AWBbtn_clicked();
private:
    Ui::MainWindow *ui;
    QImage image;
};

#endif // MAINWINDOW_H

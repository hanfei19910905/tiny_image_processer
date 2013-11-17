#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cassert>
#include <QMouseEvent>

using namespace std;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->AWBbtn->setEnabled(false);
    connect(this,SIGNAL(LoadImage(QString)),ui->ImgEditor,SLOT(SetImage(QString)));
    connect(this,SIGNAL(signal_awb()),ui->ImgEditor,SLOT(img_awb()));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_LoadFileBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("OpenImage"),
                                                    ".",
                                                    tr("Image Files(*.png *.jpg *.jpeg *.bmp)"));
    ui->AWBbtn->setEnabled(true);
    emit LoadImage(fileName);
}


void MainWindow::on_AWBbtn_clicked()
{
    emit signal_awb();
}

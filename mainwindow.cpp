#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DisplayImage.hpp"
#include "algo.hpp"
#include <cassert>
#include <QMouseEvent>

using namespace std;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->setEnabled(false);
    algo = new Algo();

    connect(this,SIGNAL(clickImage(cv::Mat&,int,int)),algo, SLOT(DrawCircle(cv::Mat&,int,int)));
    connect(algo,SIGNAL(refrush(cv::Mat&)), this, SLOT(frush(cv::Mat&)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
QImage ConvertImage(cv:: Mat img){
   // cv::Mat img;
   // image.copyTo(img);
    assert(img.channels() == 3);
    if(img.channels() == 3){
        cv::cvtColor(img,img,CV_BGR2RGB);
        QImage image = QImage((const unsigned char*)(img.data),
                      img.cols,
                      img.rows,
                      img.cols*img.channels(),
                      QImage::Format_RGB888);
        return image;
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton ){
        int x = event -> x();
        int y = event -> y();
        int sx = ui->label->x();
        int sy = ui->label->y();
        int w = ui->label->width();
        int h = ui->label->height();
        y -= 15;
        //printf("%d %d %d %d %d %d\n",x,y,sx,sy,w,h);
        if(x > sx && x < sx + w && y > sy && y < sy + h){
            emit clickImage(image,x-sx,y-sy);
        }
    }
}

void MainWindow::frush(cv::Mat& image){

    QImage img = ConvertImage(image);
    ui->label->setPixmap(QPixmap::fromImage(img));
    ui->label->resize(ui->label->pixmap()->size());
    cv::cvtColor(image,image,CV_BGR2RGB);
}

void MainWindow::on_pushButton_2_clicked()
{
    // this is "open file" button
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("OpenImage"),
                                                    ".",
                                                    tr("Image Files(*.png *.jpg *.jpeg *.bmp)"));
    if(fileName == "") return ;
    image = cv::imread(fileName.toLatin1().data());
    if(image.data) {
        ui->pushButton->setEnabled(true);
    }
    //ui->label->show();
    frush(image);
}

void MainWindow::on_pushButton_clicked()
{
    aws(image);
    frush(image);
}

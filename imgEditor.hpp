#ifndef IMGEDITOR_HPP
#define IMGEDITOR_HPP

#include<QtGui>
#include<QWidget>
#include<QRegion>
#include "awb.hpp"
#include<iostream>

class imgEditor : public QWidget {
    Q_OBJECT
public :
    imgEditor(QWidget *par = 0){
        setAttribute(Qt::WA_StaticContents);
        setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
        img = QImage(16,16,QImage::Format_ARGB32);
        img.fill(qRgba(0,0,0,0));
        std::cout <<"hello!\n";

    }

protected:
    void paintEvent(QPaintEvent *event){
        QPainter painter(this);
        std::cout <<"paint!\n";
        for(int i =0; i <img.width(); i++)
            for(int j =0; j< img.height(); j++){
                QRect rect = pixelRect(i,j);
                if(!event->region().intersects(rect)){
                    QColor c = QColor::fromRgba(img.pixel(i,j));
                    painter.fillRect(rect,c);
                }
            }
    }

    void mousePressEvent(QMouseEvent *event){


    }

private slots:
    void SetImage(QString path){
        img.load(path);
        update();
        updateGeometry();
    }
    void img_awb(){
        AWB::awb(img);
        update();
        updateGeometry();
    }

private:
    QRect pixelRect(int i,int j) const{
        return QRect(i,j,1,1);
    }

private:
    QImage img;

};

#endif

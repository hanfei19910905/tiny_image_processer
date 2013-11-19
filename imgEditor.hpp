#ifndef IMGEDITOR_HPP
#define IMGEDITOR_HPP

#include<QtGui>
#include<QWidget>
#include<QLabel>
#include<QRegion>
#include<iostream>
#include "IWarp.hpp"
#include "awb.hpp"

class imgEditor : public QWidget {
    Q_OBJECT
public :
    imgEditor(QWidget *par = 0):
    QWidget(par){
        setAttribute(Qt::WA_StaticContents);
        setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
        img = QImage(16,16,QImage::Format_ARGB32);
        img.fill(qRgba(0,0,0,0));
        iwarpHelper = new iWarpSolver();
    }
    ~imgEditor(){
    }

   
protected:
    void paintEvent(QPaintEvent *event){
        QPainter painter(this);
        for(int i =0; i <img.width(); i++)
            for(int j =0; j< img.height(); j++){
                QRect rect = pixelRect(i,j);
                if(event->region().intersects(rect)){
                    QColor c = QColor::fromRgba(img.pixel(i,j));
                    painter.fillRect(rect,c);
                }
            }
    }
    void DrawCircle(int x,int y,int r){
        QPainter painter(&img);
        painter.setPen(QPen(QColor(0,0,255)));
        painter.drawEllipse(QRect(x-r,y-r,2*r+1,2*r+1));
    }
    void mousePressEvent(QMouseEvent *event){
        std::cout <<"press!\n";
        // debug
        
        int x= event -> pos().x();
        int y= event -> pos().y();
        //DrawCircle(x,y,r);
        //
        iwarpHelper -> IwarpDeform(img,x,y);
        
        update();
        updateGeometry();
        //
    }

private slots:
    void SetImage(QString path){
        if(img.load(path)){
            resize(img.width(),img.height());
            iwarpHelper -> InitVec(img.width(),img.height());
            update();
            updateGeometry();
        }
    }
    void img_awb(){
        AWB::awb(img);
        update();
        updateGeometry();
    }
    void setIWarp(int _r,double _d){
        iwarpHelper -> Set(_r,_d);
    }

private:
    QRect pixelRect(int i,int j) const{
        return QRect(i,j,1,1);
    }
    QRect circleRect(int i,int j,int r) const {
        return QRect(i-r,j-r,2*r+1,2*r+1);
    }

private:
    QImage img;
    iWarpSolver *iwarpHelper;
};

#endif

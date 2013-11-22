#include "imgEditor.h"
#include "awb.h"
#include "IWarp.h"

#include <QPainter>
#include <QPaintEvent>

imgEditor::imgEditor(QWidget *par):
  QWidget(par){
    setAttribute(Qt::WA_StaticContents);
    setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    img = QImage(16,16,QImage::Format_ARGB32);
    img.fill(qRgba(0,0,0,0));
    iwarpHelper = new iWarpSolver();
}

void imgEditor::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    for(int i =0; i <img.width(); i++){
        for(int j =0; j< img.height(); j++){
            QRect rect = pixelRect(i,j);
            if(event->region().intersects(rect)){
                QColor c = QColor::fromRgba(img.pixel(i,j));
                painter.fillRect(rect,c);
            }
        }
    }
}

void imgEditor::DrawCircle(int x,int y,int r){
    QPainter painter(&img);
    painter.setPen(QPen(QColor(0,0,255)));
    painter.drawEllipse(QRect(x-r,y-r,2*r+1,2*r+1));
}
void imgEditor::mousePressEvent(QMouseEvent *event){
    int x= event -> pos().x();
    int y= event -> pos().y();

    iwarpHelper -> IwarpDeform(img,x,y);

    update();
    updateGeometry();
}

void imgEditor::SetImage(const QString& path){
    if(img.load(path)){
        resize(img.width(),img.height());
        iwarpHelper -> InitVec(img.width(),img.height());
        update();
        updateGeometry();
    }
}

void imgEditor::img_awb(){
    AWB::awb(img);
    update();
    updateGeometry();
}

void imgEditor::setIWarp(int _r,double _d){
    iwarpHelper -> Set(_r,_d);
}

QRect imgEditor::pixelRect(int i,int j) const{
    return QRect(i,j,1,1);
}

QRect imgEditor::circleRect(int i,int j,int r) const {
    return QRect(i-r,j-r,2*r+1,2*r+1);
}

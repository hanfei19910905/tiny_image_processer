#ifndef IMGEDITOR_H
#define IMGEDITOR_H

#include<QWidget>

class iWarpSolver;

class imgEditor : public QWidget {
    Q_OBJECT
public :
    imgEditor(QWidget *par = 0);
protected:
    void paintEvent(QPaintEvent*);
    void DrawCircle(int x, int y, int r);
    void mousePressEvent(QMouseEvent*);
private slots:
    void SetImage(const QString& path);
    void img_awb();
    void setIWarp(int r, double d);
private:
    QRect pixelRect(int i, int j)const;
    QRect circleRect(int i, int j, int r)const;
private:
    QImage img;
    iWarpSolver *iwarpHelper;
};

#endif // IMGEDITOR_H

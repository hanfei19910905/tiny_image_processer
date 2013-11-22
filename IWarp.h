#ifndef IWARP_H
#define IWARP_H

#include <vector>
#include <QPoint>

class QImage;

class iWarpSolver{
public:
    iWarpSolver(int _r = 20, double _d = 0.3);
    bool IwarpDeform(QImage& img,int x,int y);
    void InitVec(int w,int h);
    void Set(int _r,double _d);

private:
    int radius,w,h;
    double deformAmount;
    std::vector<QPoint> deform_vectors;
    void GetDeformVector(double x,double y,double &xv,double &yv);
};

#endif // IWARP_H

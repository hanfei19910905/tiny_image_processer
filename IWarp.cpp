#include "IWarp.h"

#include <QImage>

#include <cmath>

const double pi = std::acos(-1.0);
const int MAXR = 250;

iWarpSolver::iWarpSolver(int _r, double _d):
    radius(_r),deformAmount(_d){
}

bool iWarpSolver::IwarpDeform(QImage& img,int x,int y){
    int r = radius;
    w = img.width();
    h = img.height();
    int x0 = -r, x1 = r, y0 = -r, y1 = r;
    if(x0 + x < 0 || x1 + x >= img.height()) return 0;
    if(y + y0 < 0 || y1 + y >= img.width()) return 0;

    // x0, y0 stand for the left buttom point
    // and x1, y1 is the oppisite
    int r2 = radius * radius;
    int L = 2*r2 + 1;
    std::vector<QPoint> deform_area_vector(L*L, QPoint(0,0));
    std::vector<QRgb> dst;
    dst.resize(w*h);
    for(int yi = y0; yi <= y1 ; yi ++){
        for(int xi = x0; xi <= x1; xi ++){
            double len2 = (xi*xi + yi*yi) / r2; // dis^2 / r^2
            int fptr = (yi + r) * L + (xi + r);
            if(len2 < 1.0){
                // cal the nvx , nvy
                double deformValue = 0.1 * deformAmount * std::pow(std::cos(std::sqrt(len2) * pi) * 0.5,0.7);
                double nvx = -deformValue * xi;
                double nvy = -deformValue * yi; // (x,y) is replaced by (nvx,nvy)
                double xv,yv;
                GetDeformVector(nvx,nvy,xv,yv);
                xv += nvx, yv += nvy;
                deform_area_vector[fptr] = QPoint(yv,xv);
                double nx = xv + xi + x;
                double ny = yv + yi + y;
                dst[fptr] = img.pixel((int)nx,(int)ny);
            } else {
                dst[fptr] = img.pixel(x + xi, y + yi);
            }
        }
    }
    for(int xi = x0; xi <= x1; xi ++){
        for(int yi = y0; yi <= y1; yi ++){
            double len2 = (xi*xi + yi*yi) / r2;
            if(len2 < 1.0){
                int fptr = (yi + r) * L + (xi + r);
                img.setPixel(xi,yi,dst[fptr]);
                int ptr =  (y + yi) * w + x + xi;
                deform_vectors[ptr] = deform_area_vector[fptr];
            }
        }
    }
    return 1;
}

void iWarpSolver::InitVec(int w,int h){
    deform_vectors = std::vector<QPoint>(w*h,QPoint(0,0));
}

void iWarpSolver::Set(int _r,double _d){
    radius = _r;
    deformAmount = _d;
}

void iWarpSolver::GetDeformVector(double x,double y,double &xv,double &yv){
    int    i, xi, yi;
    double dx, dy, my0, my1, mx0, mx1;
    if(x < 0 || x >= h - 1 || y < 0 || y >= w -1) {xv = yv = 0;return ;}
    xi = (int) x;
    yi = (int) y;
    dx = x-xi;
    dy = y-yi;
    i = (yi * w + xi);
    mx0 =
      deform_vectors[i].x() +
      (deform_vectors[i+1].x() -
       deform_vectors[i].x()) * dx;
    mx1 =
      deform_vectors[i+w].x() +
      (deform_vectors[i+w+1].x() -
       deform_vectors[i+w].x()) * dx;
    my0 =
      deform_vectors[i].y() +
      dx * (deform_vectors[i+1].y() -
            deform_vectors[i].y());
    my1 =
      deform_vectors[i+w].y() +
      dx * (deform_vectors[i+w+1].y() -
            deform_vectors[i+w].y());
    xv = mx0 + dy * (mx1 - mx0);
    yv = my0 + dy * (my1 - my0);
}

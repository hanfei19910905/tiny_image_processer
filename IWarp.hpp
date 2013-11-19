#ifndef IWARP_HPP 
#define IWARP_HPP

#include<QObject>
#include<QtCore>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<iostream>


const double pi = std::acos(-1.0);
const int MAXR = 250;

struct Point{
    double x,y;
    Point(){}
    Point(double _x,double _y):x(_x),y(_y){}
};
class iWarpSolver   {
    private:
        std::FILE* fileptr;
        int radius,w,h;
        double deformAmount;
        std::vector<Point> deform_vectors;
        
        void GetDeformVector(double x,double y,double &xv,double &yv){
            int    i, xi, yi;
            double dx, dy, my0, my1, mx0, mx1;
            if(x < 0 || x >= w - 1 || y < 0 || y >= h -1) {xv = yv = 0;return ;}
            xi = (int) x;
            yi = (int) y;
            dx = x-xi;
            dy = y-yi;
            i = (yi * w + xi);
            std::fprintf(fileptr,"pos: %d %d i: %d\n",xi,yi,i);
            std::cout<<"vec: "<<deform_vectors[i].x<<" "<<deform_vectors[i].y<<std::endl;
            mx0 =
                deform_vectors[i].x +
                (deform_vectors[i+1].x -
                deform_vectors[i].x) * dx;
            mx1 =
                deform_vectors[i+w].x +
                (deform_vectors[i+w+1].x -
                deform_vectors[i+w].x) * dx;
            my0 =
                deform_vectors[i].y +
                dx * (deform_vectors[i+1].y -
                deform_vectors[i].y);
            my1 =
                deform_vectors[i+w].y +
                dx * (deform_vectors[i+w+1].y -
                deform_vectors[i+w].y);
            xv = mx0 + dy * (mx1 - mx0);
            yv = my0 + dy * (my1 - my0);
        }
    public :
    iWarpSolver(int _r = 20, double _d = 0.3):
        radius(_r),deformAmount(_d){
             fileptr = fopen("debug.log","w");
        }
    bool IwarpDeform(const QImage& img,QImage& result,int x,int y){
        int r = radius;
        w = img.width();
        h = img.height();
        std::cout<<"size: "<<w<<" "<<h<<std::endl;
        int x0 = -r, x1 = r, y0 = -r, y1 = r;
        if(x0 + x < 0 || x1 + x >= img.width()) return 0;
        if(y + y0 < 0 || y1 + y >= img.height()) return 0;
        // x0, y0 stand for the left buttom point, and x1, y1 is the oppisite
        int r2 = radius * radius;
        int L = 2*r2 + 1;
        std::vector<Point> deform_area_vector(L*L,Point(0,0));
        std::vector<QRgb> dst;
        dst.resize(w*h);
        for(int yi = y0; yi <= y1 ; yi ++)
            for(int xi = x0; xi <= x1; xi ++){
                double len2 = 1.0 * (xi*xi + yi*yi) / r2; // dis^2 / r^2
                int fptr = (yi + r) * L + (xi + r);
               // std::cout<<"pos: "<<xi<<" "<<yi<<" "<<len2<<"\n";
                if(len2 < 1.0){
                    // cal the nvx , nvy
                    double deformValue = 0.1 * deformAmount * std::pow((std::cos(std::sqrt(len2) * pi) + 1)* 0.5,0.7);
//                    std::cout<<deformValue<<std::endl;
                    double nvx = -deformValue * xi;
                    double nvy = -deformValue * yi; // (x,y) is replaced by (nvx,nvy)
                    double xv,yv;
                    GetDeformVector(nvx + x + xi,nvy + y + yi,xv,yv);
                    xv += nvx, yv += nvy;
                    deform_area_vector[fptr] = Point(xv,yv);
                    std::fprintf(fileptr,"fptr %d %lf\n",fptr,deform_area_vector[fptr].x);
                    std::cout<<xv<<" "<<yv<<"\n";
                    double nx = xv + xi + x;
                    double ny = yv + yi + y;
                    dst[fptr] = img.pixel((int)nx,(int)ny);
                    std::printf("pos(%d,%d) turn to -> pos(%lf,%lf)\n",xi,yi,xi+xv,yi+yv);
                } else {
                    //dst[fptr] = img.pixel(x + xi, y + yi);
                    ;
                }
            }
        for(int xi = x0; xi <= x1; xi ++)
            for(int yi = y0; yi <= y1; yi ++){
                double len2 = 1.0 * (xi*xi + yi*yi) / r2;
                if(len2 < 1.0){
                    int fptr = (yi + r) * L + (xi + r);
                    result.setPixel(xi + x,yi + y,dst[fptr]);
                    int ptr =  (y + yi) * w + x + xi;
                    deform_vectors[ptr] = deform_area_vector[fptr];
                    std::fprintf(fileptr,"pos: %d %d v: %d %d %lf\n",xi + x,yi + y,ptr,fptr,deform_area_vector[fptr].x);
                }
            }

        return 1;
    }
    void InitVec(int w,int h){
        deform_vectors = std::vector<Point>(w*h,Point(0,0));
    }
    void Set(int _r,double _d){
        radius = _r;
        deformAmount = _d;
    }
};
#endif // ALGO_HPP

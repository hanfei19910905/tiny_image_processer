#ifndef IWARP_HPP 
#define IWARP_HPP

#include<QObject>
#include<QtCore>
#include<cmath>
#include<iostream>


const double pi = std::acos(-1.0);
const int MAXR = 250;

namespace IWarp{
//#ifdef IWarp
class iWarpSolver : public QObject{
    Q_OBJECT
    private:
        int radius,w,h;
        double deformAmount;
        std::vector<int> deform_vector;
        
        void GetDeformVector(double x,double y,double &xv,double &yv){
            int    i, xi, yi;
            double dx, dy, my0, my1, mx0, mx1;

            xi = (int) x;
            yi = (gint) y;
            dx = x-xi;
            dy = y-yi;
            i = (yi * w + xi);
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
        randius(_r),deformAmount(_d){}
    bool IwarpDeform(QImage& img,int x,int y){

        int r = radius;
        w = img.width();
        h = img.height();
        int x0 = -r, x1 = r, y0 = -r, y1 = r;
        if(x0 < 0 || x1 > img.width()) return 0;
        if(y0 < 0 || y1 > img.height()) return 0;
        // x0, y0 stand for the left buttom point, and x1, y1 is the oppisite
        int r2 = radius * radius;
        std::vector<std::vector<int> > deform_area_vector(2*r + 1,vector<int>(2*r + 1,0) );
        for(int yi = y0; yi <= y1 ; yi ++)
            for(int xi = x0; xi <= x1; xi ++){
                double len2 = (xi*xi + yi*yi) / r2; // dis^2 / r^2
                if(len2 < 1.0){
                    // cal the nvx , nvy
                    double deformValue = 0.1 * deformAmount * std::pow(std::cos(std::sqrt(len2) * pi) * 0.5,0.7);
                    double nvx = -deformValue * xi;
                    double nvy = -deformValue * yi; // (x,y) is replaced by (nvx,nvy)
                    double vx,yv;
                    GetDeformVector(nvx,nvy,xv,yv);
                    
                   }
            }


        return 1;
    }
    void InitVec(int w,int h){
        deform_vector = std::vector<std::vector<int> >(h,std::vector<int>(w,0));
    }
}
}
#endif // ALGO_HPP

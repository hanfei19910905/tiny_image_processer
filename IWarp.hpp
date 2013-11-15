#ifndef ALGO_HPP
#define ALGO_HPP

#include<QObject>
#include<opencv2/opencv.hpp>

class Algo: public QObject {
    Q_OBJECT
public:
    explicit Algo(int _r = 10):radius(_r){
        enable = false;
    }
private:
    int radius;
    int deformValue;
    bool enable;
private slots :
    void DrawCircle(cv::Mat& img,int x,int y){
        cv::circle(img,cv::Point(x,y),radius,cv::Scalar(255,255,255));
        emit refrush(img);
    }
    void SetRadius(int _r){
        if(_r > 0 && _r * _r < MAXR){
            radius = _r;
        }
    }
#ifdef IWarp
    void IwarpDeform(cv::Mat& img,int x,int y,int w,int h){
        if(!enable) return ;
        if(x < r || x + r > w || y < r || y + r > h){
            emit iwarp_err(QString("exceed the bound !"));
        }
        int x0 = -r, x1 = r, y0 = -r, y1 = r;
        // x0, y0 stand for the left buttom point, and x1, y1 is the oppisite
        int r2 = radius * radius;
        for(int yi = y0; yi <= y1 ; yi ++)
            for(int xi = x0; xi <= x1; xi ++){
                int len2 = (xi*xi + yi*yi) / r2; // dis^2 / r^2
                if(len2 < MAXR){
                    ptr = (y + yi)
                }
            }
    }
#endif
signals :
    void refrush(cv::Mat&);
};

#endif // ALGO_HPP

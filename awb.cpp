#include "awb.h"

#include <QImage>

#include <cmath>

template<typename T>
void chkmin(T &a, T b){
    if(a == -1 || a > b) a = b;
}

template<typename T>
void chkmax(T &a, T b){
    if(a == -1 || a < b) a = b;
}

typedef unsigned char color_t;

const int MAXC = 256;

static color_t lut[3][MAXC];
static color_t low_input[4], high_input[4];
static int num[4][MAXC] ;

int AWB::awb(QImage& image)
{
    memset(low_input,-1,sizeof(low_input));
    memset(high_input,-1,sizeof(high_input));
    memset(num,0,sizeof(num));
    memset(lut,0,sizeof(lut));
    for(int i = 0; i < image.width(); i++){
        for(int j = 0; j < image.height(); j++){
            QRgb c = image.pixel(i,j);
            num[0][qRed(c)] ++;
            num[1][qGreen(c)] ++;
            num[2][qBlue(c)] ++;
        }
    }

    for(int i = 0; i < 3; i++){
        double sum = 0;
        for(int j = 0; j < MAXC; j ++){
            sum += num[i][j];
        }
        double now = 0;
        for(int j = 0; j < MAXC - 1; j++){
            double s = now + num[i][j]/sum;
            double t = now + s + num[i][j+1]/sum;
            if(std::fabs(s - 0.006) < std::fabs(t - 0.006)){
                low_input[i] = j;
                break;
            }
            now += s;
        }
        now = 0;
        for(int j = MAXC - 1; j >= 0; j--){
            double s = now + num[i][j]/sum;
            double t = now + s + num[i][j-1]/sum;
            if(std::fabs(s - 0.006) < std::fabs(t - 0.006)){
                high_input[i] = j;
                break;
            }
            now += s;
        }
    }

    for(int channel = 0; channel < 3; channel ++){
        double low = (double)low_input[channel] / 255.0;
        double high = (double)high_input[channel] / 255.0;
        for(int value = 0; value < MAXC; value ++){
            double v = value / 255.0;
            double result = (1.0 * (v - low) / (high - low) * 255);
            if(result < 0) result = 0;
            if(result > 255.0) result = 255.0;

            lut[channel][value] = (color_t)result;
        }
    }

    for(int i = 0; i < image.width(); i++){
        for(int j = 0; j < image.height(); j++){
            QRgb c = image.pixel(i,j);
            int red = qRed(c);
            int green = qGreen(c);
            int blue = qBlue(c);
            QRgb value = qRgb(lut[0][red],lut[1][green],lut[2][blue]);
            image.setPixel(i,j,value);
        }
    }
    return 1;
}

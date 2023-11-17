#include "Encode.hpp"
#include <cstdlib>
#include <iostream>
#include <limits>


Encode::Encode(cv::Mat image,std::string msg,std::string fileName) : _img(image) ,_messageToEncode(msg),_fileName(fileName)
{

}

void Encode::initMarkingChannel(Channel chan)
{
    if(_img.channels() != 3){
        throw "Image number of channels is different than 3.";
        return;
    }

    for(int i = 0; i < _img.cols;i++){
        for(int j = 0;j < _img.rows;j++){
            cv::Vec3b pix = _img.at<cv::Vec3b>(j,i);
            auto channelVal = pix.val[chan];

            if(channelVal % 10 == 0)
                continue;
  
            pix.val[chan] = abs(channelVal - channelVal % 10);
            _img.at<cv::Vec3b>(j,i) = pix;
                  
        }
    }
}

void Encode::setPixelToAscii(const Point cord, const char c, Channel chan)
{
}

void Encode::markPixel(const Point cord, Channel chan)
{
}

void Encode::rankPixel(const Point cord, const int posInStringBatch, Channel chan)
{
}

Point Encode::findClosestColorPixel(const int col, const char c,  Channel encodeChan,  Channel markingChan) const
{
    Point newPoint;
    newPoint.x = col;
    int deltaX = std::numeric_limits<int>::max();

    for(int i = 0; i < _img.rows;i++){
        cv::Vec3b pix = _img.at<cv::Vec3b>(i,col);

        //(red channel - ascii < dlx) and pixel isn't marked.
        if(abs(pix.val[encodeChan] - (int)c) < deltaX && pix[markingChan] % 10 != 1){
            deltaX = abs(pix.val[encodeChan] - (int)c);
            newPoint.y = i;
            
        }
        
    }
    
    return newPoint;
      
}

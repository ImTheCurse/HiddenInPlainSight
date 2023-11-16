#include "Encode.hpp"
#include <cstdlib>
#include <iostream>
#include <opencv2/imgcodecs.hpp>

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
            auto channelVal = pix.val[1];

            if(channelVal % 10 == 0)
                continue;
  
            pix.val[1] = abs(channelVal - channelVal % 10);
            _img.at<cv::Vec3b>(j,i) = pix;
                  
        }
    }
}

void Encode::setPixelToAscii(Point cord, char c, Channel chan)
{
}

void Encode::markPixel(Point cord, Channel chan)
{
}

void Encode::rankPixel(Point cord, int posInStringBatch, Channel chan)
{
}

Point Encode::findClosestColorPixel(char c, Channel chan)
{
    
}

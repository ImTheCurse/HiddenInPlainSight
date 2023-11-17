#include "Encode.hpp"
#include <cstdlib>
#include <iostream>
#include <limits>
#include <opencv2/imgcodecs.hpp>

#define RGB_CHANNEL_LIMIT 255

Encode::Encode(cv::Mat image,std::string msg,std::string fileName,int numOfThreads, Channel encChan,Channel markChan,Channel rankChan) 

: _img(image) ,_messageToEncode(msg),_fileName(fileName),_numOfThreads(numOfThreads) , encodeChan(encChan),markingChan(markChan),rankingChan(rankChan)
{

    


}

void Encode::encodeSinglePixel(const int rowStartPixel,const int rowEndPixel,const int colStartPixel,const int colEndPixel)
{
}

void Encode::writeToImage()
{
    cv::imwrite("enc_"+_fileName,_img);

}

void Encode::initMarkingChannel()
{
    if(_img.channels() != 3){
        throw "Image number of channels is different than 3.";
        return;
    }

    for(int i = 0; i < _img.cols;i++){
        for(int j = 0;j < _img.rows;j++){
            cv::Vec3b pix = _img.at<cv::Vec3b>(j,i);
            auto channelVal = pix.val[markingChan];

            if(channelVal % 10 == 0)
                continue;
  
            pix.val[markingChan] = abs(channelVal - channelVal % 10);
            _img.at<cv::Vec3b>(j,i) = pix;
                  
        }
    }
}

void Encode::setPixelToAscii(const Point cord,char c)
{
    _img.at<cv::Vec3b>(cord.x,cord.y).val[encodeChan] = (int)c;
    markPixel(cord);
}

void Encode::markPixel(const Point cord)
{
    cv::Vec3b pix = _img.at<cv::Vec3b>(cord.y,cord.x);
    auto channelVal = pix.val[markingChan];

    //not necassery to check, but being on the safe side and assuming channel wasen't initialized.
    if(channelVal < RGB_CHANNEL_LIMIT){
        channelVal++;
    }
    _img.at<cv::Vec3b>(cord.y,cord.x).val[markingChan] = channelVal;


}

void Encode::rankPixel(const Point cord, const int posInStringBatch)
{
    cv::Vec3b pix = _img.at<cv::Vec3b>(cord.y,cord.x);
    auto channelVal = pix.val[rankingChan];

    if(channelVal % 10 != 0){
        pix.val[rankingChan] = abs(channelVal - channelVal % 10) + posInStringBatch;
        _img.at<cv::Vec3b>(cord.y,cord.x) = pix;
        return;
    }
    pix.val[rankingChan] += posInStringBatch;
    _img.at<cv::Vec3b>(cord.y,cord.x) = pix;

}

Point Encode::findClosestColorPixel(const int col, const char c) const
{
    Point newPoint;
    newPoint.x = col;
    int delta = std::numeric_limits<int>::max();

    for(int i = 0; i < _img.rows;i++){
        cv::Vec3b pix = _img.at<cv::Vec3b>(i,col);

        //(red channel - ascii < dlx) and pixel isn't marked.
        if(abs(pix.val[encodeChan] - (int)c) < delta && pix[markingChan] % 10 != 1){
            delta = abs(pix.val[encodeChan] - (int)c);
            newPoint.y = i;
            
        }
        
    }
    
    return newPoint;
      
}

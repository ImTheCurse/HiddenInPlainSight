#pragma once
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <opencv2/core/mat.hpp>

enum  Channel{
    BLUE = 0, 
    GREEN, 
    RED
};

struct Point{
    Point(int x_cord, int y_cord):x(x_cord),y(y_cord) {}
    Point(){}
    int x;
    int y;
};


class Encode{
public:

Encode(cv::Mat image,std::string msg,std::string fileName,int numOfThreads = std::thread::hardware_concurrency(),
Channel encChan = Channel::RED,Channel markChan = Channel::GREEN,Channel rankChan = Channel::BLUE);

cv::Mat getImage();


private:
    cv::Mat _img;
    std::string _fileName;
    std::string _messageToEncode;
    int _numOfThreads;
    std::mutex _mtx;
    
    Channel encodeChan;
    Channel markingChan;
    Channel rankingChan;

    //sets the chosen pixel and channel to the value of ascii character.
    void setPixelToAscii(Point cord,char c);

    void encodeTenPixels(const int col, std::string tenCharString);
    void encodeSinglePixel(const int col, char c,int charIndex);

    void writeToImage();
    //initialize marking channel LSD(least significat digit) to zero.
    void initMarkingChannel();
    
    //mark the LSD so we could decode the pixels that are marked.
    void markPixel(const Point cord);

    //mark the LSD with the position of the char relative to a batch of 10 characters.
    void rankPixel(const Point cord,const int posInStringBatch);


    Point findClosestColorPixel(const int col, const char c) const;
};
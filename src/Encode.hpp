#pragma once
#include <vector>
#include <string>
#include <thread>
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

struct ColorRGB{
    int red;
    int green;
    int blue;
};

class Encode{
public:

Encode(cv::Mat image,std::string msg,std::string fileName,int numOfThreads = std::thread::hardware_concurrency(),
Channel encChan = Channel::RED,Channel markChan = Channel::GREEN,Channel rankChan = Channel::BLUE);

void encodeTenPixels(const int col, std::string tenCharString);

void encodeSinglePixel(const int col, char c,int charIndex);
//setters

void writeToImage();
//initialize marking channel LSD(least significat digit) to zero.
void initMarkingChannel();
//sets the chosen pixel and channel to the value of ascii character.


//mark the LSD so we could decode the pixels that are marked.
void markPixel(const Point cord);

//mark the LSD with the position of the char relative to a batch of 10 characters.
void rankPixel(const Point cord,const int posInStringBatch);




private:
    cv::Mat _img;
    std::string _fileName;
    std::string _messageToEncode;
    std::vector<std::pair<Point,ColorRGB>> _pixelsToEncode;
    int _numOfThreads;
    
    Channel encodeChan;
    Channel markingChan;
    Channel rankingChan;

    void setPixelToAscii(Point cord,char c);
    Point findClosestColorPixel(const int col, const char c) const;
};
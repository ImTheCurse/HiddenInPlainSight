#pragma once
#include <vector>
#include <string>
#include <opencv2/core/mat.hpp>

enum  Channel{
    BLUE = 0, 
    GREEN, 
    RED
};

struct Point{
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

Encode(cv::Mat image,std::string msg,std::string fileName);

//setters

//initialize marking channel LSD(least significat digit) to zero.
void initMarkingChannel(Channel chan = Channel::GREEN);
//sets the chosen pixel and channel to the value of ascii character.
void setPixelToAscii(Point cord, const char c, Channel chan = Channel::RED);

//mark the LSD so we could decode the pixels that are marked.
void markPixel(const Point cord,Channel chan = Channel::GREEN);

//mark the LSD with the position of the char relative to a batch of 10 characters.
void rankPixel(const Point cord,const int posInStringBatch ,Channel chan = Channel::BLUE);

Point findClosestColorPixel(const int col, const char c, Channel encodeChan = Channel::RED, Channel markingChan = Channel::GREEN) const;


private:
    cv::Mat _img;
    std::string _fileName;
    std::string _messageToEncode;
    std::vector<std::pair<Point,ColorRGB>> _pixelsToEncode;

    

};
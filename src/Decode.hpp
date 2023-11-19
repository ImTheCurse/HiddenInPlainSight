#pragma once
#include <opencv2/core/mat.hpp>
#include <iostream>
#include <fstream>
#include <tuple>
#include "Encode.hpp"



class Decode {
public:
Decode(cv::Mat image,Channel encodingChannel = Channel::RED,Channel markingChannel = Channel::GREEN,Channel rankingChannel = Channel::BLUE);


private:
    cv::Mat _img;
    std::string _decodedString;
    std::vector<std::tuple<Point,char,int>> _unsortedCharValues;
    
    Channel _encodeChannel;
    Channel _markChannel;
    Channel _rankChannel;


    void setDataToUnsortedCharVal();
    void setDataToDecodedString();

};
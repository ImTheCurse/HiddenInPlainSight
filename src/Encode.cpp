#include "Encode.hpp"

Encode::Encode(cv::Mat image,std::string msg) : _img(image) ,_messageToEncode(msg)
{

}

void Encode::initMarkingChannel(Channel chan)
{
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

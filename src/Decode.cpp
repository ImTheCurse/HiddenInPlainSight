#include "Decode.hpp"
#include <fstream>
#define MAX_RANK_AMOUNT 10

Decode::Decode(cv::Mat image, Channel encodingChannel, Channel markingChannel, Channel rankingChannel) : _img(image),_encodeChannel(encodingChannel)
,_markChannel(markingChannel),_rankChannel(rankingChannel)
{
    setDataToUnsortedCharVal();
    setDataToDecodedString();
    std::cout<<_decodedString<<std::endl;

    std::ofstream outfile ("results/decodedMessage.txt");
    outfile <<_decodedString<< std::endl;
    outfile.close();


}

void Decode::setDataToUnsortedCharVal()
{
    for(int i = 0;i < _img.cols;i++){
        for(int j = 0;j <_img.rows;j++){
            if(_img.at<cv::Vec3b>(j,i).val[_markChannel] % 10 != 0){
                char charVal = _img.at<cv::Vec3b>(j,i).val[_encodeChannel];
                int charIndex = _img.at<cv::Vec3b>(j,i).val[_rankChannel] % 10;
                _unsortedCharValues.push_back(std::make_tuple(Point(i,j),charVal,charIndex));
            }
        }
    }
}

void Decode::setDataToDecodedString()
{

    _decodedString.reserve(_unsortedCharValues.size());
    _decodedString.resize(_unsortedCharValues.size());
    for(auto itr: _unsortedCharValues){
        int charIndex = std::get<int>(itr);
        char charVal = std::get<char>(itr);
        Point currentPoint = std::get<Point>(itr);

        _decodedString[currentPoint.x * MAX_RANK_AMOUNT + charIndex] = charVal;
        
        

    }
}

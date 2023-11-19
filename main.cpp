#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "src/Encode.hpp"
#include "src/Decode.hpp"


int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }
    cv::Mat image;
    image = cv::imread( argv[1], cv::IMREAD_COLOR );
    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }

    
        Encode enc(image,"what the fucking hell is this","lena.png");
        //Decode dec(image);
    
    


    
    //namedWindow("Display Image", WINDOW_AUTOSIZE );
    //imshow("Display Image", image);
    cv::waitKey(0);
    return 0;
}
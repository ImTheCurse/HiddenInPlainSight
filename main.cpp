#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "src/Encode.hpp"
#include "src/Decode.hpp"


int main(int argc, char** argv )
{
    if ( argc < 3 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }
    cv::Mat image;
    image = cv::imread( argv[1], cv::IMREAD_COLOR);
    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }

        /*
        Flags:
        -i : image path
        -e : encode image
        -d : decode image
        -t : file path to read

        */
        
        //Encode enc(image,"Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum","lena.png");
        Decode dec(image);
        //Decode dec(enc.getImage());

        

    
    //namedWindow("Display Image", WINDOW_AUTOSIZE );
    //imshow("Display Image", image);
    cv::waitKey(0);
    return 0;
}
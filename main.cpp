#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "src/Encode.hpp"
#include "src/Decode.hpp"


class InputParser{
    public:
        InputParser (int &argc, char **argv){
            for (int i=1; i < argc; ++i)
                this->tokens.push_back(std::string(argv[i]));
        }
        /// @author iain
        const std::string& getCmdOption(const std::string &option) const{
            std::vector<std::string>::const_iterator itr;
            itr =  std::find(this->tokens.begin(), this->tokens.end(), option);
            if (itr != this->tokens.end() && ++itr != this->tokens.end()){
                return *itr;
            }
            static const std::string empty_string("");
            return empty_string;
        }
        /// @author iain
        bool cmdOptionExists(const std::string &option) const{
            return std::find(this->tokens.begin(), this->tokens.end(), option)
                   != this->tokens.end();
        }
    private:
        std::vector <std::string> tokens;
};


int main(int argc, char** argv )
{
    
    bool gotEncDecFlag = false;
    bool gotInputFlag = false;
    bool gotFileFlag = false;
    std::stringstream buffer;
    std::string newBuff;
    cv::Mat image;

    InputParser input(argc,argv);
    if(input.cmdOptionExists("-i")){
        const std::string &filePath = input.getCmdOption("-i");
        image = cv::imread(filePath,cv::IMREAD_COLOR);
        if ( !image.data ){
        printf("No image data \n");
        return -1;
        }
        gotInputFlag = true;

    }

    if(input.cmdOptionExists("-f")){
        std::ifstream t(input.getCmdOption("-f"));
        buffer << t.rdbuf();
        newBuff = buffer.str();
        gotFileFlag = true;
        
    }

    if(input.cmdOptionExists("-m")){
        newBuff = input.getCmdOption("-m");
        gotFileFlag = true;
    }

    if(input.cmdOptionExists("-e") && gotInputFlag){
        Encode enc(image,newBuff,"file.png");
        gotEncDecFlag = true;
    }

    if(input.cmdOptionExists("-d") && !gotEncDecFlag){
        Decode dec(image);
    }

    if(input.cmdOptionExists("-h")){
        std::cout<<"usage:\n-i <image_path> : relative PNG image path(with name and extension)\n-e              : encode image(write after all the flags)\n-d              : decode image(write after all the flags)\n-m <message>    : CLI message\n-f <file_path>  : relative file path to encode(with name and extension)\n\n";
        return 0;
    }

    std::cout<<"Finished."<<std::endl;    
    cv::waitKey(0);
    return 0;
}
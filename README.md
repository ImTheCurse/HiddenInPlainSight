# HiddenInPlainSight

A multi-threaded command line interface based program for Image Steganography.<br>
it uses an algorithm that I've developed in which there are 3 steps to encoding an image.

:mag_right:  find closest ascii character in choosen encoding channel, and insert value to encode inside the encoding channel.<br>
:pushpin: Mark inside marking channel.<br>
:bookmark_tabs: create a "10 char buffer", and rank each character in pixel column.

### Limitations
As we store ascii values inside the encoding channel, there is a need for a variety of color in the image.<br>
Could encode upto:<br>
10 characters per column = cc<br>
Num of Characters = 10 * lines = n <br>
Avg. of words: <br> $` cc * n / 4.7 `$



### Installation
1. <b>Install Open-CV : </b><br>
follow instruction at:
https://docs.opencv.org/4.x/d7/d9f/tutorial_linux_install.html
and run the following command in the CLI:
```
sudo apt-install libopencv-dev
```
2. clone to chossen folder and compile the program:
```
git clone https://github.com/ImTheCurse/HiddenInPlainSight.git
cd HiddenInPlainSight
cmake .
make
```
### Running the Program
1. Place .png file to encode inside ```images``` folder.
2. Place text file(or any other file that you can read from) inside ```textFile``` folder.

```
   usage:
   -h              : shows this screen.
   -i <image_path> : relative PNG image path(with name and extension).
   -f <file_path>  : relative file path to encode(with name and extension).
   -m <message>    : command line message to encode.
   -e              : encode image(write after all the flags).
   -d              : decode image(write after all the flags).
```

encoding image example:
```
./HIPS -i images/lena.png -f test.txt -e
```
```
./HIPS -i images/newroad.png -m "this is amazing!" -e
```
decoding image example:
```
./HIPS -i enc_file.png -d
```
Encoded image and Decoded file will be saved to results directory.

## Disclaimer

This program is a proof-of-concept, and should not be intended for transfring important information, and I won't be liable for any damagaes caused by this program.

## Copyright

This software is licensed under MIT. Copyright © 2022 Rani Giro
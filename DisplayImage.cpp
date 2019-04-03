/** @file
 *  
 *  Author: Amey Chavan (apchavan)
 *
 *  File description:-
 *  This is short program to display an image and has capability to zoom up to that level where we can see each pixel of opened image separately.
 *  We have to execute this program separately for each image by passing path of the image file as argument.
 */


#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }

    Mat image;
    image = imread( argv[1], 1 );

    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", image);

    waitKey(0);

    return 0;
}

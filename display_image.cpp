#include "opencv2/core/core.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include "opencv2/contrib/contrib.hpp"
#include <boost/thread/thread.hpp>
#include <iostream>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/io/pcd_io.h>
#include <fstream>
#include <cstdio>
#include "pcl/common/common_headers.h"

using namespace cv;
using namespace std;
using namespace pcl;



int main( int argc, char** argv )
{
    if( argc != 3)
    {
     cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
     return -1;
    }

    const double fx = 7.215377e+02;
    const double fy = 7.215377e+02;
    long double mean = (fx + fy)/2;
    cout<<"Mean:"<< mean  << endl;

    Mat image;
    Mat dimage;
    Mat nimage;

    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);   // Read the file
    dimage = imread(argv[2], CV_LOAD_IMAGE_GRAYSCALE);

    int width,height;
    double row,column;
    double centerx,centery;

    height = image.size().height;
    width = image.size().width;
    
    row = image.rows;
    column = image.cols;
    if(! image.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window", image );
                    // Show our image inside it.
    
    cout << "row : " << row << endl;
    cout << " column: " << column << endl;
    centerx =  row/2;
    centery = column/2;

    cout << " center row : " << centerx << endl;
    cout << " center column: " << centery << endl;

    Vec3b bgrPixel = image.at<Vec3b>(centerx,centery);
    cout << bgrPixel<<endl;

    pcl::PointCloud<pcl::PointXYZRGB> cloud;
    pcl::PointXYZRGB pcl_point;
    //cloud.width = column;
    //cloud.height = row;
    //cloud.resize(cloud.width*cloud.height);

for(int i = 0; i < image.rows; i++)
{
  for(int j = 0; j < image.cols; j++)
    {
         Vec3f bgrPixel = image.at<Vec3f>(i, j);

         double v = i-centerx;
         double u = j-centery;

//cout << static_cast<int>(dimage.at<uchar>(i,j)) << endl;
double disp = static_cast<int>(dimage.at<uchar>(i,j));
double z;
/*if ( disp == 0)
   { z = (mean*0.54);}
else
   {*/ z = ((mean*0.54)/disp);//}

double x = ((u*z)/ fx);
double y = ((v*z)/fy);


pcl_point.x = x;
pcl_point.y = y;
pcl_point.z = z;
 cv::Vec3b intensity = image.at<cv::Vec3b>(i,j);
uint32_t rgb = (static_cast<uint32_t>(intensity[2]) << 16 | static_cast<uint32_t>(intensity[1]) << 8 | static_cast<uint32_t>(intensity[0]));
pcl_point.rgb = *reinterpret_cast<float*>(&rgb);


 cloud.push_back(pcl_point);

  }
}
pcl::io::savePCDFileASCII ("test_pcd.pcd", cloud);
    waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
}
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "iostream"
#include <time.h>
#include <fstream>
#include <Windows.h>


using namespace cv;
using namespace std;


void convertImage(Mat, Mat);

int main()
{
	double time[600];
	char name[600];
	int i = 100;
	int k=0;
	cv::Size s[600];
	double avg=0.0;
	while (1)
	{
		sprintf(name,"c%d.png",i);
		Mat image=imread(name);
		if(!image.data)
			break;
		Mat gray(image.size(), CV_8UC1);

		
		double t1 = (double)getTickCount();
		convertImage(image, gray);
		double t2 = (double)getTickCount();
		time[k] = (t2 - t1) / getTickFrequency();
		s[k] = image.size();
		avg+=time[k];
		//display rgb image
		namedWindow("Display Window", CV_WINDOW_AUTOSIZE);
		imshow("Display Window", image);
		//waitKey(20);

		//display gray image
		namedWindow("Result Window", CV_WINDOW_AUTOSIZE);
		imshow("Result Window", gray);
		

		
		waitKey(30);
		destroyAllWindows();
		
		i--;
		k++;

	}

	ofstream output("abc.csv");
	int j = 1;
	for (int x = 0; x < 100; x++)
	{	
		if (j == 1)
		{
			output << ' ';
			output <<",";
			output << ' ';
			output << endl;
			j++;

		}
		else
		{
			output << s[x];
			output << ",";
			output << time[x];
			output << endl;
		}
	}
	output << "avg";
	output << ",";
	output << avg/100;
	output << endl;
	output.close();

	system("abc.csv");

	waitKey(0);

	return 0;
}

void convertImage(Mat image, Mat gray)
{
	int rows = image.rows;
	int cols = image.cols;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			Vec3b intensity = image.at<Vec3b>(i, j);

			int blue = intensity.val[0];
			int green = intensity.val[1];
			int red = intensity.val[2];

			gray.at<uchar>(i, j) = blue*0.0722 + green*0.7152 + red*0.2126;

		}
	}
}
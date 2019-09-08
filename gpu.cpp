#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <cuda.h>
#include <cuda_runtime.h>
#include <time.h>
#include <fstream>
#include <Windows.h>
using namespace std;
using namespace cv;
extern "C" void gray_parallel(unsigned char* h_in, unsigned char* h_out, int elems, int rows, int cols);
int main(int argc, char** argv)
{
	Mat image;
	double time[600];
	cv::Size s[600];
	char name[600];
	int i = 0, k = 100;
	double avg = 0;
	while (1)
	{
		sprintf(name, "c%d.png", k);
		Mat image = imread(name, 1);
		if (!image.data)
			break;
		imshow("c1.png", image);
		int64 t3 = cv::getTickCount();
		const int rows = image.rows;
		const int cols = image.cols;
		int elems = rows*cols * 3;
		unsigned char *h_in = image.data;
		unsigned char *h_out = new unsigned char[rows*cols];

		gray_parallel(h_in, h_out, elems, rows, cols);

		Mat gray2 = Mat(rows, cols, CV_8UC1, h_out);
		int64 t4 = cv::getTickCount();
		time[i] = (t4 - t3) / getTickFrequency();
		s[i] = image.size();
		cout << s[i];
		cout << time[i]<<endl;
		avg += time[i];
		imshow("image.png", gray2);
		waitKey(350);
		destroyAllWindows();
		k--;
		i++;
	}
	ofstream output("abc.csv", ios::out);
	int j = 1;
	for (int x = 0; x < 100; ++x)
	{
		if (j == 1)
		{
			output << ' ';
			output << ",";
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


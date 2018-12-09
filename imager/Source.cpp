#include<opencv2/opencv.hpp>

#include<iostream>
#include<conio.h>           
#include <fstream>
#include <time.h>

#include <omp.h>

void doTask() {

		cv::Mat imgOriginal;        // input image
		cv::Mat imgProcessed;           // Canny edge image

		imgOriginal = cv::imread("image.png");          // open image

		if (imgOriginal.empty()) {                                  // if unable to open image
			std::cout << "error: image not read from file\n\n";     // show error message on command line
			_getch();                                               // may have to modify this line if not using Windows
			//return(0);                                              // and exit program
		}
		imgOriginal.copyTo(imgProcessed);
		
		int counter = 0;
#pragma omp parallel for 
		for (int y = 0; y<imgProcessed.rows; y++)
		{
			for (int x = 0; x<imgProcessed.cols; x++)
			{
				if (((x / 10) % 2 ==(y / 10) % 2 )) {
					cv::Vec3b color = imgProcessed.at<cv::Vec3b>(cv::Point(x, y));
					int c = 0.3*color[2] + 0.59*color[1] + 0.11*color[0];
					color[0] = c;//blue
					color[1] = c;//green
					color[2] = c;//red
					imgProcessed.at<cv::Vec3b>(cv::Point(x, y)) = color;
				}
			}
		}

		//cv::imshow("imgOriginal", imgOriginal);     // show windows
		//cv::imshow("imgProcessed", imgProcessed);

		cv::imwrite("out.png", imgProcessed);

		//cv::waitKey(0);
}

int main() {

	int start = clock();

	doTask();

	int fin = clock();
	std::ofstream fout("out.txt");
	fout << (fin - start);
	fout.close();
	system("PAUSE");
}

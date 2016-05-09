#if 1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pigpio.h>

/*
OH3144E or equivalent Hall effect sensor

Pin 1 - 5V
Pin 2 - Ground
Pin 3 - gpio (here P1-8, gpio 14, TXD is used)

The internal gpio pull-up is enabled so that the sensor
normally reads high.  It reads low when a magnet is close.

gcc -o hall hall.c -lpigpio -lrt -lpthread
sudo ./hall
*/

#define HALL 14

void alert(int gpio, int level, uint32_t tick)
{
   static uint32_t lastTick=0;

   if (lastTick) printf("%d %.6f\n", level, (float)(tick-lastTick)/1000000.0);
   else          printf("%d-0.000000\n", level);

   lastTick = tick;
}

int main(int argc, char *argv[])
{
   int secs=60;

   if (argc>1) secs = atoi(argv[1]); /* program run seconds */

   if ((secs<1) || (secs>3600)) secs = 3600;

   if (gpioInitialise()<0) return 1;

   gpioSetMode(HALL, PI_INPUT);

   gpioSetPullUpDown(HALL, PI_PUD_UP);
//   gpioSetPullUpDown(HALL, PI_PUD_DOWN);

   gpioSetAlertFunc(HALL, alert);

   sleep(secs);

   gpioTerminate();
}

#else

#include <ctime>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	int		frame_count = 0;

	time_t	timer_begin, timer_end;

	system("sudo modprobe bcm2835-v4l2");

	VideoCapture cap(0); // open the video camera no. 0

	if(!cap.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the video cam" << endl;

		return -1;
	}

	cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);

	/* This does not work on the Raspberry Pi ... */

	cap.set(CV_CAP_PROP_FORMAT, CV_8UC1);

	namedWindow("Source", CV_WINDOW_AUTOSIZE);

	time(&timer_begin);

	while (1)
	{
		Mat frame;
		Mat scaled;

		bool bSuccess = cap.read(scaled);

		if(!bSuccess)
		{
			cout << "Frame skipped." << endl;

			continue;
		}

		Mat image;

		/* Running this will halve the frame rate. */

//		pyrMeanShiftFiltering(scaled, image, 3, 128);

//		bilateralFilter(scaled, image, 15, 1000, 1000);

//		std::vector<cv::Mat> channels;

//		cv::Mat hsv;

//		cv::cvtColor(scaled, hsv, CV_RGB2HSV);
//		cv::split(hsv, channels);

//		image = channels[2];

		cvtColor(scaled, image, CV_BGR2GRAY);

//		erode(image, image, Mat(), Point(-1, -1), 5);
//		dilate(image, image, Mat(), Point(-1, -1), 5);

//		threshold(image, image, 127, 255, CV_THRESH_TOZERO);
//		threshold(image, image, 127, 255, CV_THRESH_BINARY);
//		medianBlur(image, image, 9);
//		equalizeHist(image, image);

	#if 0

		float x = 80;
		float y = x * 2;

		Canny(image, image, x, y, 3);

	#endif

//		GaussianBlur(image, image, Size(11, 11), 2, 2);
		GaussianBlur(image, image, Size(7, 7), 2, 2);
//		GaussianBlur(image, image, Size(5, 5), 2, 2);

		vector<Vec3f> circles;

		HoughCircles(image, circles,
		             CV_HOUGH_GRADIENT,
		             2,
		             image.rows / 4,
		             80, 100,
					 8, image.rows);

		for(size_t i = 0; i < circles.size(); i++)
		{
			Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));

			int radius = cvRound(circles[i][2]);

			circle(scaled, center, 3, Scalar(0,255,0), -1, 8, 0 );

			circle(scaled, center, radius, Scalar(0,0,255), 3, 8, 0 );
		}

//		imshow("WIP", image);
		imshow("Source", scaled);

		if(waitKey(1) == 27)
		{
			cout << "esc key is pressed by user" << endl;

			break;
		}

		++frame_count;

		time(&timer_end);

		double elapsed = difftime(timer_end, timer_begin);

		printf("\rFPS=%3.2f", (float) frame_count / elapsed);
		fflush(stdout);
	}

	return 0;
}

#endif

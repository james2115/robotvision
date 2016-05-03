#if 1

#if 1

#if 1

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>

using namespace cv;
using namespace std;

inline uchar reducepixel(const uchar value)
{
	if(value < 128)
	{
		return 0;
	}

	return 255;
}

int main(int argc, char* argv[])
{
	VideoCapture cap(0); // open the video camera no. 0

	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the video cam" << endl;

		return -1;
	}

	cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);

	double dWidth  = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
	double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

	cout << "Frame size : " << dWidth << " x " << dHeight << endl;

	namedWindow("MyVideo", CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"

	while (1)
	{
		Mat frame;
		Mat scaled;

		bool bSuccess = cap.read(scaled);

		if(!bSuccess)
		{
			cout << "Cannot read a frame from video stream" << endl;

			break;
		}

//		resize(frame, scaled, Size(0, 0), 0.5, 0.5, INTER_LINEAR);
//		resize(frame, scaled, Size(0, 0), 1, 1, INTER_LINEAR);

		Mat image;

	#if 0

		Mat channels[3];

		cv::split(scaled, &channels[0]);

		for(int i = 0; i <= 2; i++)
		{
			image = channels[i];

			uchar *pixel = image.data;

			for(int j = 0; j < image.rows; ++j)
			{
				for(int k = 0; k < image.cols; ++k)
				{
					*pixel++ = reducepixel(*pixel);

				}
			}
		}

		merge(&channels[0], 3, image);

	#else

//		pyrMeanShiftFiltering(scaled, image, 3, 128);
//		bilateralFilter(scaled, image, 15, 1000, 1000);

	#endif

//		scaled.convertTo(image, -1, 0.5, 0); //decrease the contrast (halve)

//		std::vector<cv::Mat> channels;

//		cv::Mat hsv;

//		cv::cvtColor(scaled, hsv, CV_RGB2HSV);
//		cv::split(hsv, channels);

//		image = channels[2];

		cvtColor(scaled, image, CV_BGR2GRAY);

//		erode(image, image, Mat(), Point(-1, -1), 5);
//		dilate(image, image, Mat(), Point(-1, -1), 5);
//		Canny(image, image, 10, 250, 3);

//		threshold(image, image, 127, 255, CV_THRESH_TOZERO);
//		threshold(image, image, 127, 255, CV_THRESH_BINARY);
//		medianBlur(image, image, 9);
//		equalizeHist(image, image);

		float x = 80;
		float y = x * 2;

	#if 1

//		Canny(image, image, x, y, 3);

	#endif

	#if 0

//		GaussianBlur(image, image, Size(11, 11), 2, 2);
		GaussianBlur(image, image, Size(7, 7), 2, 2);
//		GaussianBlur(image, image, Size(5, 5), 2, 2);

		vector<Vec3f> circles;

		HoughCircles(image, circles,
		             CV_HOUGH_GRADIENT,
		             1,
		             image.rows / 4,
		             x, 100,
					 8, image.rows);

		for(size_t i = 0; i < circles.size(); i++)
		{
			Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));

			int radius = cvRound(circles[i][2]);

			circle(scaled, center, 3, Scalar(0,255,0), -1, 8, 0 );

			circle(scaled, center, radius, Scalar(0,0,255), 3, 8, 0 );
		}

	#endif

//		Mat canvas = Mat::zeros(scaled.rows, scaled.cols*2, scaled.type());

//		scaled.copyTo(canvas(Range::all(), Range(0, image.cols)));

//		cvtColor(image, image, CV_GRAY2BGR);

//		image.copyTo(canvas(Range::all(), Range(image.cols, image.cols*2)));

//		imshow("MyVideo", canvas);
		imshow("MyVideo", scaled);

		if (waitKey(1) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;

			break;
		}
	}

	return 0;
}

#else

#include <iostream>
#include <highgui.h>
#include <opencv2/imgproc.hpp>

using namespace std;

#define CAMERA_OUTPUT_WINDOW_NAME "camera-output"

int main(int argc, char **argv)
{
	cv::Capture *camCapture;

	int ret = 0;

	if (!(camCapture = cvCaptureFromCAM(CV_CAP_ANY)))
	{
		cout << "Failed to capture from camera" << endl;

		ret = 1;

		goto exitCameraOpenFailed;
	}

	cout << "Camera opened successfully" << endl;

	cvNamedWindow(CAMERA_OUTPUT_WINDOW_NAME, CV_WINDOW_AUTOSIZE);

	IplImage *cameraFrame;

	int grabFrameRet;

	while(true)
	{
		if((cameraFrame = cvQueryFrame(camCapture)))
		{
			cvResize(cameraFrame, cameraFrame, CV_INTER_LINEAR);

			cvShowImage(CAMERA_OUTPUT_WINDOW_NAME, cameraFrame);
		}

		if (cvWaitKey(60) != -1)
		{
			cout << "Input" << endl;

			break;
		}
	}

	cout << "Done" << endl;

	cvReleaseCapture(&camCapture);
	cvDestroyWindow(CAMERA_OUTPUT_WINDOW_NAME);

exitCameraOpenFailed:

	return ret;
}

#endif

#else

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/video/video.hpp"
#include "opencv2/imgcodecs/imgcodecs.hpp"

using namespace std;
using namespace cv;

Mat src;
Mat dst;

String window_name1 = "Unprocessed Image";
String window_name2 = "Processed Image";

int main( int argc, char** argv )
{
	/// Load the source image
	src = imread( argv[1], 1 );

	namedWindow( window_name1, WINDOW_AUTOSIZE );
	imshow("Unprocessed Image",src);

	dst = src.clone();
	GaussianBlur( src, dst, Size( 15, 15 ), 0, 0 );

	namedWindow( window_name2, WINDOW_AUTOSIZE );
	imshow("Processed Image",dst);

	waitKey();
	return 0;
}

#endif

#endif

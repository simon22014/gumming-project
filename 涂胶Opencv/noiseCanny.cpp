#include "stdafx.h"
#include "noiseCanny.h"


noiseCanny::noiseCanny()
{
}
noiseCanny::noiseCanny(Mat sourceImage)
:sourceImage(sourceImage)
{

	//Mat changeImage = Mat::zeros(sourceImage.size(), CV_8UC3);
	Mat changeImage = sourceImage.clone();
//	blur(sourceImage, sourceImage, Size(3, 3));
//	cvtColor(sourceImage, sourceImage, CV_BGR2HLS); //CV_BGR2HLS
	Mat element = getStructuringElement(0, Size(4 * 1 + 1, 4 * 1 + 1), Point(1, 1));
	int cPointR, cPointG, cPointB, cPoint;//currentPoint;
	for (int i = 1; i < sourceImage.rows; i++)
	{
		for (int j = 1; j < sourceImage.cols; j++)
		{
			cPointB = sourceImage.at<Vec3b>(i, j)[0];
			cPointG = sourceImage.at<Vec3b>(i, j)[1];
			cPointR = sourceImage.at<Vec3b>(i, j)[2];
			if ((cPointB == 0) && (cPointG == 0) && (cPointR = 255))
			{
				changeImage.at<Vec3b>(i, j)[0] = 0;
				changeImage.at<Vec3b>(i, j)[1] = 255;
				changeImage.at<Vec3b>(i, j)[2] = 0;
				changeImage.at<Vec3b>(i, j)[0] = 0;
				changeImage.at<Vec3b>(i, j)[1] = 255;
				changeImage.at<Vec3b>(i, j)[2] = 0;

			}
			else
			{
			//	changeImage.at<Vec3b>(i, j)[0] = 255;
			//	changeImage.at<Vec3b>(i, j)[1] = 255;
			//	changeImage.at<Vec3b>(i, j)[2] = 255;
			}
		}
	}
	//imshow("sImhage", changeImage);


	//【1、高斯去噪】
//	GaussianBlur(changeImage, changeImage, Size(3, 3), 0, 0, BORDER_DEFAULT);


//	erode(changeImage, changeImage, element);
	erode(changeImage, changeImage, element);
	dilate(changeImage, changeImage, element);
	dilate(changeImage, changeImage, element);
	dilate(changeImage, changeImage, element);  //dilate
	/// 腐蚀操作 
  //  erode(changeImage, changeImage, element);
	cvtColor(changeImage, changeImage, CV_BGR2GRAY);
//	cvtColor(changeImage, changeImage, CV_GRAY2BGR);
	//	imshow("cnny", changeImage);

	Canny(changeImage, changeImage, 85, 85*3, 3);
//	imshow("cannyERode", changeImage);
	Mat changeage = Mat::zeros(sourceImage.size(), CV_8UC3);

	vector<Vec4i> lines;
	HoughLinesP(changeImage, lines, 1, CV_PI / 180, 40, 10, 20);
	for (size_t i = 0; i < lines.size(); i++)
	{
		Scalar color(rand() & 255, rand() & 255, rand() & 255);
		Vec4i l = lines[i];
		line(sourceImage, Point(l[0], l[1]), Point(l[2], l[3]), color, 2, 4);
		line(changeage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(255,255,255), 2, 4);
		circle(changeage, Point(l[0], l[1]), 4, Scalar(255, 0, 0));
		circle(changeage, Point(l[2], l[3]), 4, Scalar(255, 0, 0));
	}
	


	imshow("zero", changeage);


	cout << "总共找到线数" << lines.size() << endl;
	imshow("can", sourceImage);
	waitKey(0);

}
noiseCanny::~noiseCanny()
{
}

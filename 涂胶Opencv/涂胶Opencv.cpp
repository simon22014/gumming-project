// 涂胶Opencv.cpp: 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include "IncludeGlobal.h"
#include"GetRectTwoPoint.h"
#include"CImageToRect.h"
#include"dealWithFourPoint.h"
#include"Cbtw_GluingInpectionAllInto.h"
#include <iostream>    
#include <string.h>    
#include <cxcore.h>    
#include <cv.h>    
#include <highgui.h>    
#include <fstream>    
#include"Snake.h"
#include"log.h"


using namespace std;
using namespace cv;

IplImage *image = 0; //原始图像    
IplImage *image2 = 0; //原始图像copy    

using namespace std;
int Thresholdness = 20;
int ialpha = 20;
int ibeta = 20;
int igamma = 20;

void onChange(int pos)
{

	if (image2) cvReleaseImage(&image2);
	if (image) cvReleaseImage(&image);

	image2 = cvLoadImage("C:\\Users\\user\\Desktop\\simon涂胶项目\\涂胶Opencv\\x64\\Debug\\image\\Testimage\\12.jpg", 1); //显示图片    
	image = cvLoadImage("C:\\Users\\user\\Desktop\\simon涂胶项目\\涂胶Opencv\\x64\\Debug\\image\\Testimage\\8.jpg", 0);

	cvThreshold(image, image, 72, 255, CV_THRESH_BINARY); //分割域值   

	cvShowImage("image", image);
	cvWaitKey(0);
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* contours = 0;

	cvFindContours(image, storage, &contours, sizeof(CvContour), //寻找初始化轮廓    
		CV_RETR_LIST, CV_CHAIN_CODE);

//	if (!contours) return;
	int length = contours->total;
	cout << "leagth:" << length << endl;
	//cout << length;  
	//system("pause");  
//	if (length < 10) return;
	CvPoint* point = new CvPoint[length]; //分配轮廓点    

	CvSeqReader reader;
	CvPoint pt = cvPoint(0, 0);;
	CvSeq *contour2 = contours;

	cvStartReadSeq(contour2, &reader);
	for (int i = 0; i < length; i++)
	{
		CV_READ_SEQ_ELEM(pt, reader);
		point[i] = pt;
	}
	cvReleaseMemStorage(&storage);

	//显示轮廓曲线    
	for (int i = 0; i < length; i++)
	{
		int j = (i + 1) % length;
		cvLine(image2, point[i], point[j], CV_RGB(255, 0, 0), 2, 8, 0);
	}

	cvShowImage("image2", image2);
	cvWaitKey(0);
	float alpha = ialpha / 100.0f;
	float beta = ibeta / 100.0f;
	float gamma = igamma / 100.0f;

	CvSize size;
	size.width = 3;
	size.height = 3;
	CvTermCriteria criteria;
	criteria.type = CV_TERMCRIT_ITER;
	criteria.max_iter = 1000;
	criteria.epsilon = 0.1;
	cvSnakeImage(image, point, length, &alpha, &beta, &gamma, CV_VALUE, size, criteria, 0);
	cout << "leagth:" << length << endl;
	//显示曲线    
	for (int i = 0; i < length; i++)
	{
		int j = (i + 1) % length;
		cvLine(image2, point[i], point[j], CV_RGB(0, 255, 0), 2, 8, 0);
	}
	delete[]point;
}

int main()
{
	Log("run the main",true);
	int NumPicture = 4;
	vector<float>all_Leagth;
	string resultTest;
	Mat resultMat;
	Mat image = imread("C:\\Users\\user\\Desktop\\simon涂胶项目\\涂胶Opencv\\x64\\Debug\\image\\Testimage\\1.jpg");  //存放自己图像的路径 
	Mat NochangeImage = image.clone();
#if 0
		/*dilate(image, image, element);
		dilate(image, image, element);
		erode(image, image, element);
		erode(image, image, element);*/
//	Sobel(image, image, image.depth(), 1, 1);
//	imshow("imageTestimage", image);
	//Laplacian(imageTest, imageTest, imageTest.depth());
	//	imshow("imageTestimage", imageTest);
	//cvtColor(imageTest, imageTest, CV_BGR2GRAY);
	//imshow("imageTest", imageTest);
	//equalizeHist(imageTest, imageTest);
	/*cvtColor(imageTest, imageTest, CV_RGB2HSV);
	imshow("mergeImg", imageTest);*/
	
//
//	Mat mergeImg;//合并后的图像  
//	vector<Mat> splitBGR(imageTest.channels());
//	//分割通道，存储到splitBGR中  
//	split(imageTest, splitBGR);
//	//对各个通道分别进行直方图均衡化  
////	for (int i = 0; i<imageTest.channels(); i++)
//		equalizeHist(splitBGR[1], splitBGR[1]);
//	//合并通道  
//	merge(splitBGR, mergeImg);
//	imshow("mergeImg", mergeImg);
//	waitKey(0);

	
//	Mat element = getStructuringElement(0, Size(4 * 1 + 1, 4 * 1 + 1), Point(1, 1));
//	dilate(imageTest, imageTest, element);
//	dilate(imageTest, imageTest, element);
//	erode(imageTest, imageTest, element);
//	erode(imageTest, imageTest, element);
//	erode(imageTest, imageTest, element);
	cvtColor(image, imageTest, CV_BGR2GRAY);
	Mat BGRtheSImage;
	Mat CannytheSImage;
	threshold(imageTest, BGRtheSImage, 42, 250, THRESH_BINARY);
	Canny(BGRtheSImage, CannytheSImage, 20, 20 * 3, 3);
#endif 

#if 1
	Cbtw_GluingInpectionAllInto* resultInto = new Cbtw_GluingInpectionAllInto(NumPicture,image, NochangeImage); //机器人传过来第几张图片，以及图片

	all_Leagth = resultInto->returnDealWithLeagth();
	cout << "the test leagth:" << endl;
	Log("the test leagth:", true);
	for (vector <float>::iterator iterLeagth = all_Leagth.begin(); iterLeagth != all_Leagth.end(); iterLeagth++)
	{
		cout << "  " << *iterLeagth;
		Log(std::to_string(*iterLeagth), false);
	}
	Log("", true);
	cout << endl;
	resultTest = resultInto->returnResult();
	cout << "the test result: " << resultTest << endl;
	Log("运行检测的结果:" + resultTest,true);
	resultMat = resultInto->returnResultDealWithMat(); //程序优化后，不在需要
	if (resultTest == "NG")
	{
		cv::putText(NochangeImage, resultTest, Point(resultMat.cols * 5 / 8, (resultMat.rows) * 5 / 6), FONT_HERSHEY_COMPLEX, 2, cv::Scalar(0, 0, 255), 2, 4, 0);
	}
	else
	{
		cv::putText(NochangeImage, resultTest, Point(resultMat.cols * 5 / 8, (resultMat.rows) * 5 / 6), FONT_HERSHEY_COMPLEX, 2, cv::Scalar(0, 255, 0), 2, 4, 0);
	}
	imshow("resultMat", NochangeImage);
	//imshow("NochangeImageNochangeImage", NochangeImage);
	waitKey(0);


#else 
//		cvNamedWindow("win1", 0);
	//	cvCreateTrackbar("Thd", "win1", &Thresholdness, 255, onChange);
	//	cvCreateTrackbar("alpha", "win1", &ialpha, 100, onChange);
	//	cvCreateTrackbar("beta", "win1", &ibeta, 100, onChange);
	//	cvCreateTrackbar("gamma", "win1", &igamma, 100, onChange);
		cvResizeWindow("win1", 300, 500);
		onChange(0);
		cvShowImage("win1", image2);
		cvWaitKey(0);
	//	for (;;)
	//	{
	//		if (cvWaitKey(0) == 27) break;
	//		cvShowImage("win1", image2);
	//	}
#endif

		return 0;
}


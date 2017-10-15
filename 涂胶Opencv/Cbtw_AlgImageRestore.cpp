#include "stdafx.h"
#include "Cbtw_AlgImageRestore.h"
#include <algorithm>
Cbtw_AlgImageRestore::Cbtw_AlgImageRestore()
{
}
int my_camp(float p1, float p2)
{
	return p1 <  p2;
}
Cbtw_AlgImageRestore::Cbtw_AlgImageRestore(Mat firstImage,Mat sourceImage, Cbtw_Singleton* Singleton,string TheLastResult, Cbtw_GetInAllResult*getInAllResult,Mat NochangeImage)
	:firstImage(firstImage),sourceImage(sourceImage), Singleton(Singleton), TheLastResult(TheLastResult), getInAllResult(getInAllResult), NochangeImage(NochangeImage)
{
	Mat sectionalDrawing = sourceImage.clone();//先抠图再合在一起
	Point PointCenter = Singleton->PointCenterRotate;
	float PointCenterAngel = Singleton->CenterRotateAngel;
	Mat RotateImage = (Singleton->RatationedChangeImg).clone();
	vector<Point> theLastPoint = Singleton->theLastPoint;
//	cout << "center:X:" << PointCenter.x << "Y:" << PointCenter.y << "Angel" << PointCenterAngel << endl;
	//circle(sourceImage, PointCenter, 2, Scalar(0, 0, 255));
//	line(RotateImage,Point(PointCenter.x-5, PointCenter.y) , Point(PointCenter.x + 5, PointCenter.y), Scalar(0, 0, 255), 3, 4, 0);
//	line(RotateImage, Point(PointCenter.x, PointCenter.y-5), Point(PointCenter.x, PointCenter.y+5), Scalar(0, 0, 255), 3, 4, 0);
	int Rextx;
	int Recty;
	if (PointCenter.x - firstImage.cols < 0)
	{
		Rextx = 0;
	}

	else
	{
		Rextx = PointCenter.x - firstImage.cols;
	}
	if (PointCenter.y - firstImage.rows < 0)
	{
		Recty = 0;
	}
	else
	{
		Recty = PointCenter.y - firstImage.rows;
	}
	Mat imageROI = RotateImage(cv::Rect(Rextx, Recty, firstImage.cols, firstImage.rows));
	firstImage.copyTo(imageROI);

	//Mat  RatationedImg(RotateImage.rows, RotateImage.cols , CV_8UC1);
	//RatationedImg.setTo(0);
//	imshow("sourceImage",sourceImage);
//	Mat RatationedImg = sourceImage.clone();
	//对RoiSrcImg进行旋转  
	Mat M2 = getRotationMatrix2D(PointCenter, -PointCenterAngel, 1);//计算旋转加缩放的变换矩阵 
	warpAffine(RotateImage, sectionalDrawing, M2, RotateImage.size(), 4, 5, Scalar(0));//仿射变换 


	line(sectionalDrawing, theLastPoint.at(0), theLastPoint.at(1), Scalar(55, 100, 255), 2, 4, 0);
	line(sectionalDrawing, theLastPoint.at(1), theLastPoint.at(2), Scalar(55, 100, 255), 2, 4, 0);
	line(sectionalDrawing, theLastPoint.at(2), theLastPoint.at(3), Scalar(55, 100, 255), 2, 4, 0);
	line(sectionalDrawing, theLastPoint.at(3), theLastPoint.at(0), Scalar(55, 100, 255), 2, 4, 0);
	
	vector<float> theX;
	theX.push_back(theLastPoint.at(0).x);
	theX.push_back(theLastPoint.at(1).x);
	theX.push_back(theLastPoint.at(2).x);
	theX.push_back(theLastPoint.at(3).x);
	for (vector <float>::iterator iterX = theX.begin(); iterX != theX.end(); iterX++)
	{
		if ((*iterX) < 0)
		{
			(*iterX) = 0.0;
		}
	}

	sort(theX.begin(),theX.end(),my_camp);
	vector<float> theY;
	theY.push_back(theLastPoint.at(0).y);
	theY.push_back(theLastPoint.at(1).y);
	theY.push_back(theLastPoint.at(2).y);
	theY.push_back(theLastPoint.at(3).y);
	for (vector <float>::iterator iterY = theY.begin(); iterY != theY.end(); iterY++)
	{
		if ((*iterY) < 0)
		{
			(*iterY) = 0.0;
		}
	}
	sort(theY.begin(), theY.end(), my_camp);
	rectangle(sectionalDrawing, Point(theX.at(0), theY.at(0)), cvPoint(theX.at(3), theY.at(3)), Scalar(0, 255, 0), 4);

#if 0
	if (TheLastResult == "OK")
	{
		cv::putText(sectionalDrawing, TheLastResult, Point(sourceImage.cols *5  / 8, (sourceImage.rows)* 5 /6), FONT_HERSHEY_COMPLEX, 2, cv::Scalar(0, 255, 0), 2, 4, 0);
	}
	else
	{
		cv::putText(sectionalDrawing, TheLastResult, Point(sourceImage.cols * 5/ 8, (sourceImage.rows)* 4 / 5), FONT_HERSHEY_COMPLEX, 2, cv::Scalar(0, 0, 255), 2, 4, 0);
	}
#endif 
	Rect rect2(theX.at(0), theY.at(0), (theX.at(3)- theX.at(0)), (theY.at(3) - theY.at(0))); //抠图出来的矩形
	Mat sectionalDrawingMat; //抠图出来的image
	sectionalDrawing(rect2).copyTo(sectionalDrawingMat); // copy the region rect1 from the image to roi1
	imageROI = NochangeImage(Rect(theX.at(0), theY.at(0), (theX.at(3) - theX.at(0)), (theY.at(3) - theY.at(0))));
	sectionalDrawingMat.copyTo(imageROI); //抠图出来再次合入进去
	//imshow("imageROI", imageROI);
	//waitKey(0);
//	Mat dstImage;
//	addWeighted(NochangeImage, 0.4, sectionalDrawingMat, 0.6, 0.0, NochangeImage);
	//imshow("RatationedImg", dstImage);
	//waitKey(0);

	//imshow("NochangeImage", NochangeImage);
//	waitKey(0);
	
}

Cbtw_AlgImageRestore::~Cbtw_AlgImageRestore()
{
}

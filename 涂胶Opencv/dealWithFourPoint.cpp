#include "stdafx.h"
#include <math.h>
#include "dealWithFourPoint.h"
#include "log.h"


dealWithFourPoint::dealWithFourPoint()
{

}
dealWithFourPoint::dealWithFourPoint(int NumPicture, int theTwoNum,vector<Point> TheFourPoint,Mat sourceImage,Mat NochangeImage)
	:TheFourPoint(TheFourPoint),sourceImage(sourceImage), NumPicture(NumPicture), theTwoNum(theTwoNum),NochangeImage(NochangeImage)
{
	firstImage = sourceImage.clone();
	/*********************定义一个收集结果的类******************/
	getInAllResult = new Cbtw_GetInAllResult();
	/************************************************************/
}
vector<float> dealWithFourPoint::getOneLeagth()
{
	return getInAllResult->getOneLeagth();
}

string dealWithFourPoint::getOneResult()
{
	return getInAllResult->getOneResult();
}

void dealWithFourPoint:: SetRightFourPoint()
{

	int num = 0;
	for (vector <Point>::iterator iter = TheFourPoint.begin(); iter != TheFourPoint.end(); iter++)
	{
	//circle(sourceImage, *iter, 4, Scalar(255, 0, 0));
		num++;
		if (num != 5)
		{
			fourPoint.push_back(*iter);
		}
	}
	double LengthB = (TheFourPoint.at(1).y - TheFourPoint.at(0).y)*(TheFourPoint.at(1).y - TheFourPoint.at(0).y) + (TheFourPoint.at(1).x - TheFourPoint.at(0).x)*(TheFourPoint.at(1).x - TheFourPoint.at(0).x);
	double A1A2theLength = sqrt(LengthB);
	double LengthA = (TheFourPoint.at(2).y - TheFourPoint.at(1).y)*(TheFourPoint.at(2).y - TheFourPoint.at(1).y) + (TheFourPoint.at(2).x - TheFourPoint.at(1).x)*(TheFourPoint.at(2).x - TheFourPoint.at(1).x);
	double A2A3theLength = sqrt(LengthA);

	double SinQ = (TheFourPoint.at(1).y - TheFourPoint.at(0).y) / A1A2theLength;
	double CosQ = (TheFourPoint.at(1).x - TheFourPoint.at(0).x) / A1A2theLength;
	theLastPoint.push_back(TheFourPoint.at(0));
	theLastPoint.push_back(TheFourPoint.at(1));
	theLastPoint.push_back(Point(A2A3theLength*SinQ+TheFourPoint.at(1).x , TheFourPoint.at(1).y - A2A3theLength*CosQ));
	Point a = Point(A2A3theLength*SinQ + TheFourPoint.at(1).x, TheFourPoint.at(1).y - A2A3theLength*CosQ);

	theLastPoint.push_back(Point(a.x - A1A2theLength*CosQ, a.y - A1A2theLength*SinQ));
	vector <Point>::iterator Lastiter = theLastPoint.begin();
	//for (; Lastiter != theLastPoint.end(); Lastiter++)
	{
	//	circle(sourceImage, *Lastiter, 4, Scalar(0, 0, 255));
	}
//	line(sourceImage, theLastPoint.at(0), theLastPoint.at(1), Scalar(0, 255, 255), 2, 4, 0);
//	line(sourceImage, theLastPoint.at(1), theLastPoint.at(2), Scalar(0, 255, 255), 2, 4, 0);
//	line(sourceImage, theLastPoint.at(2), theLastPoint.at(3), Scalar(0, 255, 255), 2, 4, 0);
//	line(sourceImage, theLastPoint.at(3), theLastPoint.at(0), Scalar(0, 255, 255), 2, 4, 0);
	
	cout << "point size:" << A1A2theLength<<"  " << SinQ  << "  "<< CosQ << endl;
	Log("point size:" + to_string(A1A2theLength)+" "+ to_string(SinQ)+" "+to_string(CosQ), true);


}
void dealWithFourPoint::SetRightRect()
{
	
	double LengthB = (TheFourPoint.at(1).y - TheFourPoint.at(0).y)*(TheFourPoint.at(1).y - TheFourPoint.at(0).y) + (TheFourPoint.at(1).x - TheFourPoint.at(0).x)*(TheFourPoint.at(1).x - TheFourPoint.at(0).x);
	double A1A2theLength = sqrt(LengthB);

	double LengthA = (TheFourPoint.at(2).y - TheFourPoint.at(1).y)*(TheFourPoint.at(2).y - TheFourPoint.at(1).y) + (TheFourPoint.at(2).x - TheFourPoint.at(1).x)*(TheFourPoint.at(2).x - TheFourPoint.at(1).x);
	double A2A3theLength = sqrt(LengthA);
	CvBox2D theRect;
    //theRect.center = Point2f((theLastPoint.at(2).x + theLastPoint.at(0).x) / 2, (theLastPoint.at(2).y + theLastPoint.at(0).y) / 2);
    //double tanQ = atan((theLastPoint.at(1).y - theLastPoint.at(0).y) / (theLastPoint.at(1).x - theLastPoint.at(0).x));
	double SinQ = (TheFourPoint.at(1).y - TheFourPoint.at(0).y)/ A1A2theLength;
	double CosQ = (TheFourPoint.at(1).x - TheFourPoint.at(0).x) / A1A2theLength;
	theRect.center = theLastPoint.at(1);
	theRect.angle = SinQ * 180 / PI;
	cout << "angle" << theRect.angle << endl;
	Log("angle:" + to_string(theRect.angle) , true);
	theRect.size.width = A1A2theLength;
	theRect.size.height = A2A3theLength;
	Mat binImg = sourceImage.clone();
	Mat RoiSrcImg(sourceImage.rows, sourceImage.cols, CV_8UC3); //注意这里必须选CV_8UC3

	RoiSrcImg.setTo(0); //颜色都设置为黑色  
						//imshow("新建的ROI", RoiSrcImg);
						//对得到的轮廓填充一下  

	//抠图到RoiSrcImg
	
	sourceImage.copyTo(RoiSrcImg, binImg);
	
//	NochangeImage.copyTo(RoiSrcImg, binImg);

	//再显示一下看看，除了感兴趣的区域，其他部分都是黑色的了  

	//创建一个旋转后的图像  
   Mat  RatationedImg(RoiSrcImg.rows, RoiSrcImg.cols, CV_8UC1);
  //RatationedImg.setTo(0);
   RatationedImg = sourceImage.clone();

 //  RatationedImg = NochangeImage.clone();

	//对RoiSrcImg进行旋转  
	Mat M2 = getRotationMatrix2D(theRect.center, theRect.angle, 1);//计算旋转加缩放的变换矩阵 
	warpAffine(RoiSrcImg, RatationedImg, M2, RoiSrcImg.size(), 4, 5, Scalar(0));//仿射变换 
   //imshow("旋转之后",RatationedImg);
	RatationedChangeImg = RatationedImg.clone();
	//waitKey(0);
	Singleton = new Cbtw_Singleton(theRect.center, theRect.angle, RatationedChangeImg, theLastPoint);

	getRightRect(A1A2theLength, A2A3theLength, theRect.center); //抠图出感兴趣的区域
	
}
void dealWithFourPoint::getRightRect(double A1A2theLength,double A2A3theLength,Point theCenterPoint)
{
	
	Point firstPoint = Point(theCenterPoint.x - A1A2theLength, theCenterPoint.y - A2A3theLength);
//	circle(RatationedChangeImg, theCenterPoint, 8, Scalar(0, 0, 255));
//	circle(RatationedChangeImg, firstPoint, 8, Scalar(255, 0, 255));
	//imshow("firstMat", RatationedChangeImg);

	if (firstPoint.x < 0)
	{
		firstPoint.x = 0;
	}
	if (firstPoint.y< 0)
	{
		firstPoint.y = 0;
	}

	Mat ROIImage = RatationedChangeImg(Rect(firstPoint.x ,firstPoint.y,A1A2theLength, A2A3theLength));

//	namedWindow("ROI", WINDOW_NORMAL);
	//imshow("ROI", sourceImage);
	//waitKey(0);//
	dealWithFindArea = new CutApartArea(NumPicture, theTwoNum,ROIImage,sourceImage, Singleton, getInAllResult, NochangeImage);
	
}
dealWithFourPoint::~dealWithFourPoint()
{
}

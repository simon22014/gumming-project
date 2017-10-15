#include "stdafx.h"
#include "DealWithGetLine.h"
#include"log.h"
#include"Cbtw_AlgImageRestore.h"
#include "log.h"

DealWithGetLine::DealWithGetLine()
{

}

/*******************处理图片构造函数*******************/
DealWithGetLine::DealWithGetLine(int NumPicture,int theTwoNum,vector<Mat> GetImageLine,Mat theFirstImage,Mat sourceImage, Cbtw_Singleton* Singleton,Cbtw_GetInAllResult*getInAllResult,int CutLeath,Mat NochangeImage)
	:GetImageLine(GetImageLine),theFirstImage(theFirstImage),sourceImage(sourceImage), Singleton(Singleton), getInAllResult(getInAllResult), CutLeath(CutLeath),NumPicture(NumPicture),theTwoNum(theTwoNum), NochangeImage(NochangeImage)
{
	Linelegath = 0;
	theGlueWidth  = 30 ;  //人为设定的胶的宽度
    continueLeagth = 3; //人为设定的连续的胶宽的个数


	vector<float> everyTimeTestLeagth;
	TheLastResult = "NG";
#if 0
	bool ifthePointFIrst = false;
	int theAllNumLine = 0;
#endif 
	int numOne = 0;
    theLatOne = Point2d(0.0, 0.0);
	int theThreeNum = 0;//这是每个矩形的小框
	for (vector <Mat>::iterator iter = GetImageLine.begin(); iter != GetImageLine.end(); iter++)
	{
		theThreeNum++;
		GetLineImage(theThreeNum,*iter);
		Point CanFindOnePoint;
		Point CanFindTwoPoint;
		for (vector <Point>::iterator iterTheTwoLine = TheTwoLine.begin(); iterTheTwoLine != TheTwoLine.end(); iterTheTwoLine++)
		{
		//    cv::circle(NochangeImage, Point((*iterTheTwoLine).x + numOne, (*iterTheTwoLine).y), 0.5, Scalar(0, 0, 255));
			cv::circle(theFirstImage, Point((*iterTheTwoLine).x + numOne, (*iterTheTwoLine).y), 0.5, Scalar(0, 0, 255));
			CanFindTwoPoint = Point((*iterTheTwoLine).x + numOne, (*iterTheTwoLine).y);	
			CenterTwoLine.push_back(CanFindTwoPoint);
		}

		for (vector <Point>::iterator iterTheOneLine = TheOneLine.begin(); iterTheOneLine != TheOneLine.end(); iterTheOneLine++)
		{
	//		cv::circle(NochangeImage, Point((*iterTheOneLine).x + numOne, (*iterTheOneLine).y), 0.5, Scalar(255, 0, 255));
			cv::circle(theFirstImage, Point((*iterTheOneLine).x + numOne, (*iterTheOneLine).y), 0.5, Scalar(255, 0, 255));
			CanFindOnePoint = Point((*iterTheOneLine).x + numOne, (*iterTheOneLine).y);
			CenterOneLine.push_back(CanFindOnePoint);
		}
		 //getTheVerticalLeagth(); //求出点到拟合直线的垂直距离
		 //if (lineTheCenter[2] <= 0 || lineTheCenter[3] <= 0|| _isnan(lineTheCenter[2])|| _isnan(lineTheCenter[3]))
		 //{
			// getTheMinLeagth();//最小距离
		 //}

		JudgeThePointIfOnline(); //判断点是否在曲线上否则，采用曲线上的点

#if 0
		double LengthB = ((lineTheCenter[3] - lineTheCenter[1])*(lineTheCenter[3] - lineTheCenter[1])) + ((lineTheCenter[2] - lineTheCenter[0])*(lineTheCenter[2] - lineTheCenter[0]));
		double Linelegath = sqrt(LengthB);//亮点之间的距离

		if (Linelegath < 12)
		{	
			if (ifthePointFIrst)
			{
				NotFindOnePoint.push_back(TheOneLine);
				NotFindTwoPoint.push_back(TheTwoLine);
				theAllNumLine++;
			}
		}
		else
		{
			ifthePointFIrst = true;
			if (theAllNumLine >= 3)
			{
				theTwoCenterPointLine[0] = One.x;
				theTwoCenterPointLine[1] = One.y;
				theTwoCenterPointLine[2] = (lineTheCenter[0] + numOne + lineTheCenter[2] + numOne) / 2;
				theTwoCenterPointLine[3] = (lineTheCenter[1] + lineTheCenter[3]) / 2;
			//	line(NochangeImage, Point(theTwoCenterPointLine[0], theTwoCenterPointLine[1]), Point(theTwoCenterPointLine[2], theTwoCenterPointLine[3]), Scalar(0, 255, 255), 2, 4, 0);
				line(theFirstImage, Point(theTwoCenterPointLine[0], theTwoCenterPointLine[1]), Point(theTwoCenterPointLine[2], theTwoCenterPointLine[3]), Scalar(0, 255, 255), 2, 4, 0);
				cout << "NUM:" << theAllNumLine << endl;
				JudgeLineSize(numOne- theAllNumLine *numOne/2);
				theAllNumLine = 0;
			}
			else
			{
				NotFindOnePoint.clear();
				NotFindTwoPoint.clear();
				theAllNumLine = 0;
			}
		
			std::stringstream ss;
			std::string str;
			ss << Linelegath;
			ss >> str;

	//	line(theFirstImage, Point(lineTheCenter[0] + numOne, lineTheCenter[1]), Point(lineTheCenter[2] + numOne, lineTheCenter[3]), Scalar(0, 255, 255), 2, 4, 0);
		//	cv::circle(theFirstImage, Point(lineTheCenter[0] + numOne, lineTheCenter[1]), 3, Scalar(100, 0, 255));
	//		line(theFirstImage, Point(lineTheCenter[0] + numOne - 5, lineTheCenter[1]), Point(lineTheCenter[0] + numOne + 5, lineTheCenter[1]), Scalar(255, 0, 255), 2, 4, 0);	
		//	cv::circle(theFirstImage, Point(lineTheCenter[2] + numOne, lineTheCenter[3]), 3, Scalar(0, 0, 255));
		//	line(theFirstImage, Point(lineTheCenter[2] + numOne - 5, lineTheCenter[3]), Point(lineTheCenter[2] + numOne + 5, lineTheCenter[3]), Scalar(255, 0, 255), 2, 4, 0);
#endif 
	    bool isOk = false;
	
		isOk = getBestTwoPoint(Point(lineTheCenter[0], lineTheCenter[1]), Point(lineTheCenter[2], lineTheCenter[3]), numOne);// 两点之间的距离
		if (!isOk)
		{
			Log("没有找到垂直的两点，则使用拟合之后亮点", true);
			Log("拟合亮点(" + to_string(lineTheCenter[0] + numOne) + "," + to_string(lineTheCenter[1]) + ")" + " (" + to_string(lineTheCenter[2] + numOne) + "," + to_string(lineTheCenter[3]) + ")", true);
			cv::circle(theFirstImage, Point(lineTheCenter[0] + numOne, lineTheCenter[1]), 3, Scalar(100, 0, 255));
			cv::circle(theFirstImage, Point(lineTheCenter[2] + numOne, lineTheCenter[3]), 3, Scalar(0, 0, 255));
			//亮点之间的距离
	  	cv::line(theFirstImage, Point(lineTheCenter[0] + numOne, lineTheCenter[1]), Point(lineTheCenter[2] + numOne, lineTheCenter[3]), Scalar(0, 0, 200), 2, 4, 0);
		double LengthB = ((lineTheCenter[3] - lineTheCenter[1])*(lineTheCenter[3] - lineTheCenter[1])) + ((lineTheCenter[2] - lineTheCenter[0])*(lineTheCenter[2] - lineTheCenter[0]));
		Linelegath = sqrt(LengthB);//亮点之间的距离
		}	
	//	One = Point((lineTheCenter[0] + numOne + lineTheCenter[2] + numOne) / 2, (lineTheCenter[1] + lineTheCenter[3]) / 2);
		//	cv::putText(theFirstImage, str, Point(lineTheCenter[0] + numOne, lineTheCenter[1]), FONT_HERSHEY_COMPLEX, 0.5, cv::Scalar(0, 0, 255), 1, 4, 0);
		
//		}
		BestCenterLine.push_back(Point((lineTheCenter[0] + numOne + lineTheCenter[2] + numOne)*1.0 / 2, (lineTheCenter[1] + lineTheCenter[3])*1.0 / 2));
		Point2d FitOne = Point((lineTheCenter[0] + numOne + lineTheCenter[2] + numOne) / 2, (lineTheCenter[1] + lineTheCenter[3]) / 2);
		theLatOne = FitOne;//两个框的中心点垂直
		cv::line(theFirstImage, Point(FitOne.x -5, FitOne.y), Point(FitOne.x + 5, FitOne.y), Scalar(0, 0, 255), 2, 4, 0);
		cv::line(theFirstImage, Point(FitOne.x, FitOne.y -5), Point(FitOne.x, FitOne.y + 5), Scalar(0, 0, 255), 2, 4, 0);
	//	cout << "  " << Linelegath;
		removeMaxMinPoint(1, 1);//表示去掉最小几个点，最大几个点
		FittingOneTwoLine(numOne);//分别拟合每个矩形框中小区域
		CenterTwoLine.clear();
		CenterOneLine.clear();
		everyTimeTestLeagth.push_back(Linelegath);
		theAllPoint.clear();
		TheOneLine.clear();
		TheTwoLine.clear();
		numOne = numOne + CutLeath;//GutLeath代表每一个的宽度
	}
   
	getInAllResult->writeOneLeagth(everyTimeTestLeagth);
	TheLastResult = JudgeIsOKOrNg(everyTimeTestLeagth); //返回结果

	everyTimeTestLeagth.clear();
#if 0 //将找到的中心点拟合为一条线
	/***********************************拟合最佳寻找到的线*********************************/
	Vec4f lineBest;
	//	Vec4f lineTheCenter;
	// 直线拟合函数  
	cv::fitLine(BestCenterLine, lineBest, CV_DIST_L2, 0, 0.01, 0.01);
	double cos_thetaBest = lineBest[0];
	double sin_thetaBest = lineBest[1];
	double x0Best = lineBest[2], y0Best = lineBest[3];
	double kBest = (sin_thetaBest / cos_thetaBest);
	double bBest = y0Best - kBest*x0Best;
	Point TwoPointBest = Point(x0Best, y0Best);
	Point OnePointBest = Point(0, bBest);
	Point RowsPointBest = Point(theFirstImage.cols, kBest* theFirstImage.cols + bBest);
	line(theFirstImage, OnePointBest, TwoPointBest, Scalar(255, 255, 255), 1, 4, 0);
	line(theFirstImage, TwoPointBest, RowsPointBest, Scalar(255,255,255), 1, 4, 0);
#else //将中心点相互之间连线
	Point2d OnePoint;
	Point2d TwoPoint;
	for (vector <Point2d>::iterator iter = BestCenterLine.begin(); iter != BestCenterLine.end(); iter++)
	{
		vector <Point2d>::iterator Oneiter = iter;
		Oneiter++;
		if (Oneiter == BestCenterLine.end())
		{
			break;
		}
		cv::line(theFirstImage, *iter, *Oneiter, Scalar(255, 255, 255), 1, 4, 0);	
    }

#endif 
#if 0
	/*********************************第二条线拟合*****************************************/
	Vec4f lineTwo;
	//	Vec4f lineTheCenter;
	// 直线拟合函数  

	fitLine(CenterLine, lineTwo, CV_DIST_L2, 0, 0.01, 0.01);
	double cos_theta = lineTwo[0];
	double sin_theta = lineTwo[1];
	double x0 = lineTwo[2], y0 = lineTwo[3];
	double k = (sin_theta / cos_theta);
	double b = y0 - k*x0;
	Point TwoPoint = Point(x0, y0);
	Point OnePoint = Point(0,b);
	Point RowsPoint = Point(theFirstImage.cols, k* theFirstImage.cols + b);

 
//	line(theFirstImage, OnePoint, TwoPoint, Scalar(255, 255, 255), 1, 4, 0);
//	line(theFirstImage, TwoPoint, RowsPoint, Scalar(255, 255, 255), 1, 4, 0);
	/********************************第一条线拟合*****************************************************/
	Vec4f lineOne;
	//	Vec4f lineTheCenter;
	// 直线拟合函数  
	cv::fitLine(CenterOneLine, lineOne, CV_DIST_L2, 0, 0.01, 0.01);
	double cos_thetaOne = lineOne[0];
	double sin_thetaOne = lineOne[1];
	double Onex0 = lineOne[2], Oney0 = lineOne[3];
	double Onek = (sin_thetaOne / cos_thetaOne);
	double Oneb = Oney0 - Onek*Onex0;
	Point TwoPointOne = Point(Onex0, Oney0);
	Point OnePointOne = Point(0, Oneb);
	Point RowsPointOne = Point(theFirstImage.cols, Onek* theFirstImage.cols + Oneb);
//	line(theFirstImage, OnePointOne, TwoPointOne, Scalar(255, 255, 255), 1, 4, 0);
//	line(theFirstImage, TwoPointOne, RowsPointOne, Scalar(255, 255, 255), 1, 4, 0);
  /********************************拟合直线结束***************************************************/
//	imshow("TheFirstImage", theFirstImage);
//	waitKey(0);
#endif
//	imshow("NochangeImage", NochangeImage);
//	waitKey(0);
	getInAllResult->writeOneResult(TheLastResult);
	Cbtw_AlgImageRestore* ImageRestore = new Cbtw_AlgImageRestore(theFirstImage, sourceImage, Singleton, TheLastResult, getInAllResult, NochangeImage);
}

/*******************求出最佳垂直的距离*******************/
bool DealWithGetLine::getBestTwoPoint(Point Fpoint, Point Tpoint,int numOne)
{
	Point2d thePointOne;
	Point2d thePointTwo;
#if 0

#if 0
//	TheOneLine
	vector<Point> TheOneLineRemoveOnePoint;
	TheOneLineRemoveOnePoint.clear();
	for (vector<Point>::iterator iter = TheOneLine.begin(); iter != TheOneLine.end(); iter++)
	{
		if (((*iter).x != Fpoint.x) && ((*iter).y != Fpoint.y))
		{
			TheOneLineRemoveOnePoint.push_back(*iter);
		}
	}
	Vec4f lineLeagth;

	if (TheOneLineRemoveOnePoint.size() == 0)
	{
		return false;
	}
	cv::fitLine(TheOneLineRemoveOnePoint, lineLeagth, CV_DIST_L2, 0, 0.01, 0.01);
	double x0 = lineLeagth[2], y0 = lineLeagth[3];
	double Length = ((y0 - Fpoint.y)*(y0 - Fpoint.y)) + ((x0 - Fpoint.x)*(x0 - Fpoint.x));
	double Linelegath = sqrt(Length);//亮点之间的距离
	double sinQ = (y0 - Fpoint.y) / Linelegath;
	double conQ = (x0 - Fpoint.x) / Linelegath;


	double sinQ = 0.0;
	double conQ = 0.0;
	if ((theLatOne.x == 0.0) && (theLatOne.y == 0.0))
	{
		return false;
	}
	Point theNumtwo =  Point((Fpoint.x + numOne + Tpoint.x + numOne) / 2, (Fpoint.y + Tpoint.y) / 2);
	/*double LengthLast = ((theNumtwo.y - theLatOne.y)*(theNumtwo.y - theLatOne.y)) + ((theNumtwo.x - theLatOne.x)*(theNumtwo.x - theLatOne.x));*/
	//double LinelegathLast = sqrt(LengthLast);//亮点之间的距离
	//sinQQ = (theNumtwo.y - theLatOne.y) / LinelegathLast;
	//conQQ = (theNumtwo.x - theLatOne.x) / LinelegathLast;
	//double angle_sinValue = sin(angle_atanValue);

//	double angle_tanValue = sqrt(pow(theNumtwo.y - theLatOne.y, 2)) / sqrt(pow(theNumtwo.x - theLatOne.x, 2));
	if ((theNumtwo.x - theLatOne.x) == 0.0)
	{
		return false;
	}
	double angle_tanValue = (theNumtwo.y - theLatOne.y) / (theNumtwo.x - theLatOne.x);
	double angle_atanValue = atan(angle_tanValue);
	double P = angle_atanValue * 180 / PI;

	line(theFirstImage, theNumtwo, theLatOne, Scalar(255, 0, 0), 2, 4, 0);
	if (theNumtwo.x - (Fpoint.x + numOne) == 0.0)
	{
		imshow("theFirstImage", theFirstImage);
		waitKey(0);
		return false;
	}
	double angle_tanValueQ = (theNumtwo.y - Fpoint.y) / (theNumtwo.x - (Fpoint.x +numOne));
	double angle_atanValueQ = atan(angle_tanValueQ);
	cout << "角度：" << angle_tanValueQ << " " <<angle_atanValueQ << endl;
	line(theFirstImage, theNumtwo, Point(Fpoint.x + numOne, Fpoint.y), Scalar(0, 0, 255), 2, 4, 0);

	double Q = angle_atanValueQ * 180 / PI;

	double theQP = 90 + P - Q; //两个角度之差
	Log("角度：" + to_string(P) + " " + " " + to_string(Q), false);
	
	sinQ = sin(theQP*PI / 180.0);
	conQ = cos(theQP*PI / 180.0);
	//conQ = cos(theQP);
#else
	double sinQ = 0.0;
	double conQ = 0.0;
	if ((theLatOne.x == 0.0) && (theLatOne.y == 0.0))
	{
		return false;
	}
	Point theNumtwo = Point((Fpoint.x + numOne + Tpoint.x + numOne) / 2, (Fpoint.y + Tpoint.y) / 2);

	double angle_Value = ((theNumtwo.y - theLatOne.y)*(theNumtwo.y - theLatOne.y)) + ((theNumtwo.x - theLatOne.x)*(theNumtwo.x - theLatOne.x));
	double LinelegathLast = sqrt(angle_Value);//亮点之间的距离
	sinQ = (theNumtwo.y - theLatOne.y) / LinelegathLast;
	conQ = (theNumtwo.x - theLatOne.x) / LinelegathLast;
	cv::line(theFirstImage, theNumtwo, theLatOne, Scalar(0, 255, 255), 2, 4, 0);

#endif 
	double b = sqrt(((Tpoint.y - Fpoint.y)*(Tpoint.y - Fpoint.y)) + ((Tpoint.x - Fpoint.x)*(Tpoint.x - Fpoint.x)));	
	double L = b*sinQ / 2;

	Point a = Point(Fpoint.x   - L*conQ, Fpoint.y + L*sinQ);

	Point FitOne = Point((lineTheCenter[0] + numOne + lineTheCenter[2] + numOne) / 2, (lineTheCenter[1] + lineTheCenter[3]) / 2);
	if (a.x <= 0 || a.y <= 0 || _isnan(a.x) || _isnan(a.y))
	{
		return false;
	}
	else
	{
//	circle(theFirstImage, Point(a.x + numOne, a.y), 3, Scalar(255, 255, 255));
	//	circle(theFirstImage, Point(x0 + numOne, y0), 2, Scalar(255, 255, 255));
		cv::line(theFirstImage, Point(FitOne.x, FitOne.y), Point(a.x + numOne, a.y), Scalar(0, 0, 255), 2, 4, 0);
		imshow("theFirstImage", theFirstImage);
		waitKey(0);
	}

	return true;

	//Point theNumtwo = Point((Fpoint.x + numOne + Tpoint.x + numOne) / 2, (Fpoint.y + Tpoint.y) / 2);
	//Point2f p = Point2f((theNumtwo.x - theLatOne.x), theNumtwo.y - theLatOne.y);
#endif 
	if ((theLatOne.x == 0.0) && (theLatOne.y == 0.0))
	{
		Log("计算垂直距离theLatOne.x和theLatOne.y 为0",true);
		return false;
	}
	Point2d theNumCenter = Point((Fpoint.x + numOne + Tpoint.x + numOne)*1.0 / 2, (Fpoint.y + Tpoint.y)*1.0 / 2);
//	circle(theFirstImage, theNumCenter, 2, Scalar(0, 255, 255));
//	circle(theFirstImage, theLatOne, 2, Scalar(0, 255, 255));
	double k = (theNumCenter.y - theLatOne.y)*1.0 / (theNumCenter.x - theLatOne.x)*1.0 ;
	double b = theNumCenter.y - k*(theNumCenter.x);
	if (k != 0.0)
	{
		double b0 = theNumCenter.y + (theNumCenter.x) / k;
	//	cv::line(theFirstImage, theNumCenter, Point(0, b0), Scalar(0, 0, 255), 2, 4, 0);
		for (vector <Point>::iterator iterTheOne = CenterOneLine.begin(); iterTheOne != CenterOneLine.end(); iterTheOne++)
		{
		//	if ((*iterTheOne).y*1.0 == (b0 - 1/k*(*iterTheOne).x))

		//	if(((b0 - 1 / k*(*iterTheOne).x) >= (*iterTheOne).y*1.0- 10 ) && (((b0 - 1 / k*(*iterTheOne).x) <= (*iterTheOne).y*1.0 + 10)) && (( b - (*iterTheOne).y)*k>=(*iterTheOne).x*1.0 -10) && ((b - (*iterTheOne).y)*k <= (*iterTheOne).x*1.0 + 10))
			if (((b0 - 1 / k*(*iterTheOne).x) >= (*iterTheOne).y*1.0 - 10) && (((b0 - 1 / k*(*iterTheOne).x) <= (*iterTheOne).y*1.0 + 10)))
			{
				Log("找到了thePointOne( " + to_string(thePointOne.x) + "," + to_string(thePointOne.y)+" )",true);
				thePointOne = (*iterTheOne);
				break;
			}
		}
	//	cv::line(theFirstImage, theNumCenter, thePointOne, Scalar(255, 255, 255), 2, 4, 0);
		for (vector <Point>::iterator iterTheTwo = CenterTwoLine.begin(); iterTheTwo != CenterTwoLine.end(); iterTheTwo++)
		{
		//	if (((b0 - 1 / k*(*iterTheTwo).x) >= (*iterTheTwo).y*1.0 - 10) && (((b0 - 1 / k*(*iterTheTwo).x) <= (*iterTheTwo).y*1.0 + 10)) && ((b - (*iterTheTwo).y)*k >= (*iterTheTwo).x*1.0 - 10) && ((b - (*iterTheTwo).y)*k <= (*iterTheTwo).x*1.0 + 10))
			if (((b0 - 1 / k*(*iterTheTwo).x) >= (*iterTheTwo).y*1.0 - 10) && (((b0 - 1 / k*(*iterTheTwo).x) <= (*iterTheTwo).y*1.0 + 10)))
			{
				thePointTwo = (*iterTheTwo);
				if ((thePointTwo.x == thePointOne.x) && (thePointTwo.y == thePointOne.y))
				{
					Log("找到相同的点( " + to_string(thePointOne.x) + "," + to_string(thePointOne.y) + " ) (" + to_string(thePointTwo.x) + "," + to_string(thePointTwo.y) + " )", true);
					continue;
				}
				Log("找到了PointTwo( " + to_string(thePointTwo.x) + ","+ to_string(thePointTwo.y) + " )",true);
				break;
			}
		}

		if ((thePointOne.x == 0 && thePointOne.y == 0) || (thePointTwo.x == 0 && thePointTwo.y == 0))
		{
			Log("OnePoint 或者TwoPoint 没有找到",true);
			return false;
		}
		else
		{
			double LengthLastOneTwo = ((thePointOne.y - thePointTwo.y)*(thePointOne.y - thePointTwo.y)) + ((thePointOne.x - thePointTwo.x)*(thePointOne.x - thePointTwo.x));
			double theLastLine = sqrt(LengthLastOneTwo);//亮点之间的距离
			if (theLastLine < 5)
			{
				Log("计算垂直距离的时候两点之间的距离小于10，判断是误判",true);
				return false;
			}
			cv::circle(theFirstImage, thePointOne, 3, Scalar(0, 0, 255));
			cv::circle(theFirstImage, thePointTwo, 3, Scalar(0, 0, 255));
		//	cv::line(theFirstImage, theNumCenter, thePointOne, Scalar(0, 0, 255), 2, 4, 0);
		//	cv::line(theFirstImage, theNumCenter, thePointTwo, Scalar(0, 0, 255), 2, 4, 0);
			cv::line(theFirstImage, thePointOne, thePointTwo, Scalar(0, 0, 255), 2, 4, 0);
			double LengthB = ((thePointTwo.y - thePointOne.y)*(thePointTwo.y - thePointOne.y)) + ((thePointTwo.x - thePointOne.x)*(thePointTwo.x - thePointOne.x));
			Linelegath = sqrt(LengthB);//亮点之间的距离
			Log("垂直对应两点：(" + to_string(thePointOne.x) + "," + to_string(thePointOne.y) + ")" + " (" + to_string(thePointTwo.x) + "," + to_string(thePointTwo.y) + ")", true);
		}
	}
	else
	{
		Log("计算垂直距离的时候,斜率K为0.0",true);
		return false;
	}

//	imshow("theFirstImage", theFirstImage);
//	waitKey(0);
	return true;
}

/********************移除偏差的几个点********************/
void DealWithGetLine::removeMaxMinPoint(int MinPoint, int MaxPoint)
{
	Log("移除不准确的几个点", true);
}

/******************** 分别拟合矩形每个小框两边********************/
void DealWithGetLine::FittingOneTwoLine(int num) 
{
	Log("分别拟合矩形每个小框两边", true);
	/*********************************第一条线拟合*****************************************/
	Vec4f lineOne;
	//	Vec4f lineTheCenter;
	// 直线拟合函数  
	if (CenterOneLine.size() == 0)
	{
		return;
	}
	cv::fitLine(CenterOneLine, lineOne, CV_DIST_L2, 0, 0.01, 0.01);

	double cos_theta = lineOne[0];
	double sin_theta = lineOne[1];
	double x0 = lineOne[2], y0 = lineOne[3];
	double k = (sin_theta / cos_theta);
	double b = y0 - k*x0;
	//double phi = atan2(sin_theta, cos_theta) + PI / 2.0;
	//double rho = y0 * cos_theta - x0 * sin_theta;
	Point TwoPoint = Point(x0, y0);;
	Point OnePoint = Point(x0-5,(x0-5)*k+b);
	Point RowsPoint = Point(x0 + 5, (x0 + 5)*k + b);
	//Point RowsPoint = Point(theFirstImage.cols, k* theFirstImage.cols + b);
	//cv::line(theFirstImage, OnePoint, TwoPoint, Scalar(0, 255, 0), 1, 4, 0);
	//cv::line(theFirstImage, TwoPoint, RowsPoint, Scalar(0, 255, 0), 1, 4, 0);
	/********************************第一条线拟合*****************************************************/
	/*********************************第二条线拟合*****************************************/
	Vec4f lineTwo;
	//	Vec4f lineTheCenter;
	// 直线拟合函数  
	if (CenterTwoLine.size() == 0)
	{
		return;
	}
	cv::fitLine(CenterTwoLine, lineTwo, CV_DIST_L2, 0, 0.01, 0.01);

	double cos_thetaTwo = lineTwo[0];
	double sin_thetaTwo = lineTwo[1];
	double x0Two = lineTwo[2], y0Two = lineTwo[3];
	double kTwo = (sin_thetaTwo / cos_thetaTwo);
	double bTwo = y0Two - kTwo*x0Two;
	//double phi = atan2(sin_theta, cos_theta) + PI / 2.0;
	//double rho = y0 * cos_theta - x0 * sin_theta;
	Point TwoPointTwo = Point(x0Two, y0Two);
	Point OnePointTwo = Point(x0Two - 8, (x0Two - 8)*kTwo + bTwo);
	Point RowsPointTwo = Point(x0Two + 8, (x0Two + 8)*kTwo + bTwo);
	//Point RowsPoint = Point(theFirstImage.cols, k* theFirstImage.cols + b);
	double Line = ((RowsPointTwo.y - OnePointTwo.y)*(RowsPointTwo.y - OnePointTwo.y)) + ((RowsPointTwo.x - OnePointTwo.x)*(RowsPointTwo.x - OnePointTwo.x));
	double Linelegath = sqrt(Line);//亮点之间的距离
	if (Linelegath < 20)
	{
		cv::line(theFirstImage, OnePointTwo, TwoPointTwo, Scalar(0, 255, 0), 1, 4, 0);
		cv::line(theFirstImage, TwoPointTwo, RowsPointTwo, Scalar(0, 255, 0), 1, 4, 0);
	}
//	imshow("theFirstImage", theFirstImage);
//	waitKey(0);

	/********************************第二条线拟合*****************************************************/
//	drawLine(theFirstImage, phi, rho, cv::Scalar(255,0,255));
//	imshow("theFirstImage", theFirstImage);
	//waitKey(0);
}

/******************** 画出拟合的直线********************/
void DealWithGetLine::drawLine(cv::Mat &image, double theta, double rho, cv::Scalar color)
{
	if (theta < PI / 4. || theta > 3.*PI / 4.)// ~vertical line
	{
		cv::Point pt1(rho / cos(theta), 0);
		cv::Point pt2((rho - image.rows * sin(theta)) / cos(theta), image.rows);
		cv::line(image, pt1, pt2, cv::Scalar(255), 1);
	}
	else
	{
		cv::Point pt1(0, rho / sin(theta));
		cv::Point pt2(image.cols, (rho - image.cols * cos(theta)) / sin(theta));
		cv::line(image, pt1, pt2, color, 1);
	}
}

/******************** 判断是否是OK或者NG********************/
string DealWithGetLine::JudgeIsOKOrNg(vector<float> everyTimeTestLeagth)
{

	int theNum = 0;
	string theResult = "OK";
	for (vector<float>::iterator iter= everyTimeTestLeagth.begin(); iter != everyTimeTestLeagth.end(); iter++)
	{
		if ((*iter) < theGlueWidth)
		{
			if (theNum > continueLeagth)
			{
				theResult = "NG";
				return theResult;
			}
			theNum++;
		}
		else
		{
			theNum = 0;
		}
	}
	
	return theResult;	
}

/******************** 判断line的size********************/
void DealWithGetLine::JudgeLineSize(int numOne)
{
	vector<Point> FindTwoPoint;
	vector<Point> FindOnePoint;
	for (vector<vector<Point> >::iterator iterTwoLine = NotFindTwoPoint.begin(); iterTwoLine != NotFindTwoPoint.end(); iterTwoLine++)
	{
		for (vector<Point>::iterator iterFindTwoLine = (*iterTwoLine).begin(); iterFindTwoLine != (*iterTwoLine).end(); iterFindTwoLine++)
		{
		//	circle(theFirstImage, Point((*iterFindTwoLine).x + numOne, (*iterFindTwoLine).y), 0.5, Scalar(255, 0, 255));
			FindTwoPoint.push_back(*iterFindTwoLine);
		}
	}
	for (vector<vector<Point> >::iterator iterOneLine = NotFindOnePoint.begin(); iterOneLine != NotFindOnePoint.end(); iterOneLine++)
	{
		for (vector<Point>::iterator iterFindOneLine = (*iterOneLine).begin(); iterFindOneLine != (*iterOneLine).end(); iterFindOneLine++)
		{
		//	circle(theFirstImage, Point((*iterFindOneLine).x + numOne, (*iterFindOneLine).y), 0.5, Scalar(255, 0, 255));
			FindOnePoint.push_back(*iterFindOneLine);
		}
	}

	Point TwoFindPoint = Point((theTwoCenterPointLine[0] + theTwoCenterPointLine[2]) / 2, (theTwoCenterPointLine[1] + theTwoCenterPointLine[3]) / 2);
	circle(theFirstImage, TwoFindPoint, 2, Scalar(0, 20, 255));
	std::cout << "Find Point come in" << FindTwoPoint.size()<<"Agein"<< FindOnePoint.size()<< endl;
	Log("Find Point come in" + to_string(FindTwoPoint.size()) + "Agein" + to_string(FindOnePoint.size()), true);
	for (vector <Point>::iterator iterTheTwoLine = FindTwoPoint.begin(); iterTheTwoLine != FindTwoPoint.end(); iterTheTwoLine++)
	{
		if ((TwoFindPoint.x - 2 <= ((*iterTheTwoLine).x)) && (((*iterTheTwoLine).x) <= TwoFindPoint.x + 2))
		{
			if ((TwoFindPoint.y - 10 <= ((*iterTheTwoLine).y)) && (((*iterTheTwoLine).y) <= TwoFindPoint.y - 5))
			{
				std::cout << "Find Point" << endl;
				Log("Find Point", true);
				break;
			}
		}
	}
	for (vector <Point>::iterator iterTheOneLine = FindOnePoint.begin(); iterTheOneLine != FindOnePoint.end(); iterTheOneLine++)
	{
		if ((TwoFindPoint.x -2<= (*iterTheOneLine).x) && ((*iterTheOneLine).x <= TwoFindPoint.x + 2) && (TwoFindPoint.y - 6 <= (*iterTheOneLine).y) && (((*iterTheOneLine).y) <= TwoFindPoint.y - 20))
		{
		circle(theFirstImage, Point((*iterTheOneLine).x + numOne, (*iterTheOneLine).y), 2, Scalar(255, 0, 0));
	   //  	line(theFirstImage, TwoFindPoint, Point((*iterTheOneLine).x + numOne, (*iterTheOneLine).y), Scalar(0, 255, 255), 2, 4, 0);
		//	line(theFirstImage, TwoFindPoint, Point(lineTheCenter[0], lineTheCenter[1]), Scalar(0, 255, 255), 2, 4, 0);
		std::cout << "Find Point" << endl;
		Log("Find Point", true);
		break;
		}
	}
}

/***********************处理图片***********************/
void DealWithGetLine::GetLineImage(int theThreeNum,Mat SImage)
{

	Mat firstImage = SImage.clone();
	Mat BGRtheSImage;
	/************处理图片单独一个处理的类*************************************/
	Cbtw_imageDealWith* dealWithImage = new Cbtw_imageDealWith(NumPicture, theTwoNum, theThreeNum,firstImage, sourceImage);
	BGRtheSImage = dealWithImage->returnDealWithMat();
	/************************************************************************/
#if 0
	imwrite("C:\\Users\\user\\Desktop\\新建文件夹\\1.jpg", SourceImage);
	Mat imageROI;
	Mat firstImage = SourceImage.clone();
	Mat theSImage;
	Mat CannytheSImage;
	Mat element = getStructuringElement(0, Size(4 * 1 + 1, 4 * 1 + 1), Point(1, 1));
//	erode(firstImage, firstImage, element);
//	erode(firstImage, firstImage, element);
	erode(firstImage, firstImage, element);
	dilate(firstImage, firstImage, element);
	dilate(firstImage, firstImage, element);
	dilate(firstImage, firstImage, element);	
	cvtColor(firstImage, theSImage, CV_BGR2GRAY);
//	threshold(theSImage, theSImage, 40, 250, THRESH_BINARY);

#if 0
	Mat contours;
	Canny(theSImage, contours, 125, 350);
	threshold(contours, contours, 128, 255, THRESH_BINARY);
#endif  
	Mat BGRtheSImage;
	
	Canny(theSImage, CannytheSImage, 20, 20 * 3, 3);
	cvtColor(CannytheSImage, BGRtheSImage, CV_GRAY2BGR);//转化边缘检测后的图为灰度图

//	cout << "channels" << BGRtheSImage.channels() << endl;
//	imshow("CannytheSImage", theSImage);
//	waitKey(0);
//	theSImage.copyTo(imageROI, CannytheSImage);
	//cout << "channels: " << imageROI.channels() << " " << endl;
//	cout << "theSImage:cols:" << theSImage.cols << "rows:" << theSImage.rows <<"通道："<<theSImage.channels()<< endl;
//	imwrite("E:\\涂胶\\涂胶检测\\涂胶检测\\Testimage\\ImageROI.jpg", imageROI);
//	Mat readAgainCanny = imread("E:\\涂胶\\涂胶检测\\涂胶检测\\Testimage\\ImageROI.jpg",0);
//	imshow("readAgainCanny", readAgainCanny);
//	waitKey(0);
#endif 
	int cPointR, cPointG, cPointB;
	for (int i = 0; i < BGRtheSImage.rows; i++)
	{
		for (int j = 0; j < BGRtheSImage.cols; j++)
		{
	
			cPointR = BGRtheSImage.at<Vec3b>(i, j)[0];
			cPointG = BGRtheSImage.at<Vec3b>(i, j)[1];
			cPointB = BGRtheSImage.at<Vec3b>(i, j)[2];
			if (cPointR != 0 || cPointG != 0 || cPointB != 0)
			{
				 BGRtheSImage.at<Vec3b>(i, j)[0] = 255;
				 BGRtheSImage.at<Vec3b>(i, j)[1] = 0;
				 BGRtheSImage.at<Vec3b>(i, j)[2] = 255;
				 theAllPoint.push_back(Point(j, i));
		//		WriteLog(cPointR, cPointG, cPointB);
			}
		}
	}

	vector <Point> TheOneLineZero;
	
	for (vector <Point>::iterator iter = theAllPoint.begin(); iter != theAllPoint.end(); iter++)
	{ 
		vector <Point>::iterator Oneiter = iter;
		Oneiter++;
		for (vector <Point>::iterator iterTwo = Oneiter; iterTwo != theAllPoint.end(); iterTwo++)
		{
			if ((*iter).x == (*iterTwo).x)
			{
				if ((*iter).y <  (*iterTwo).y)
				{
					TheTwoLine.push_back(*iterTwo);
				}
				TheOneLineZero.push_back(*iter);
			//	break;
			}
		}
	}

	for (vector <Point>::iterator iter = TheOneLineZero.begin(); iter != TheOneLineZero.end(); iter++)
	{
		bool ifisOnLowest = false;
		Point theCenterPoint;
		vector <Point>::iterator Oneiter = iter;
		Oneiter++;
		for (vector <Point>::iterator iterTwo = Oneiter; iterTwo != TheOneLineZero.end(); iterTwo++)
		{
			vector <Point>::iterator OneiterTwo = iterTwo;
			OneiterTwo++;
			if (OneiterTwo == TheOneLineZero.end())
			{
				if (!ifisOnLowest)
				{
					TheOneLine.push_back(*iter);
				}
				else
				{
					TheOneLine.push_back(theCenterPoint);
				}
			}
			if ((*iter).x == (*iterTwo).x)
			{
				if ((*iter).y <  (*iterTwo).y)
				{
					theCenterPoint = *iterTwo;
					ifisOnLowest = true;
				}
			}
		}
	}

	//储存拟合直线的容器  
	Vec4f lineOne;
	Vec4f lineTwo;
//	Vec4f lineTheCenter;
// 直线拟合函数  
	if ((TheOneLine.size() == 0) || (TheTwoLine.size() == 0))
	{
		std::cout << "read have not't find line" << endl;
		Log("read have not't find line", true);
		//并且将四点否初始化为0.0
		lineTheCenter[0] = 0.0;
		lineTheCenter[1] = 0.0;
		lineTheCenter[2] = 0.0;
		lineTheCenter[3] = 0.0;
		return;
	}
 cv::fitLine(TheOneLine, lineOne, CV_DIST_L2, 0, 0.01, 0.01);
 cv::fitLine(TheTwoLine, lineTwo, CV_DIST_L2, 0, 0.01, 0.01);

 /*********************************第二条线拟合*****************************************/
 double cos_theta = lineTwo[0];
 double sin_theta = lineTwo[1];
 double x0 = lineTwo[2], y0 = lineTwo[3];
 double k = (sin_theta / cos_theta);
 double b = y0 - k*x0;
 Point TwoPoint = Point(x0, y0);
 Point OnePoint = Point(0, b);
 Point RowsPoint = Point(theFirstImage.cols, k* theFirstImage.cols + b);

 for (float i = x0 - 5; i <= x0 + 5; )
 {
	 TheTwoLineFitting.push_back(Point(i, i*k + b));
	 i = i + 1;
 }

 /************************************************************************************/
 Vec2f theVerPoint;
// theVerPoint[0] = ((lineOne[3] * k + lineOne[2] - b*k)) / (k*k + 1);
// theVerPoint[1] = k *  theVerPoint[0] + b;
 lineTheCenter[0] = lineOne[2];
 lineTheCenter[1] = lineOne[3];
 lineTheCenter[2] = lineTwo[2];
lineTheCenter[3] = lineTwo[3];
// lineTheCenter[2] = theVerPoint[0];
// lineTheCenter[3] = theVerPoint[1];
//// getTheVerticalLeagth(); //通过两点求出其垂直的距离
 //getTheMinLeagth(); //计算出最短的距离

 ////JudgeThePointIfOnline(); //判断点是否在曲线上否则，采用曲线上的点
// imshow("theFirstImage", theFirstImage);
// waitKey(0);

#if 0
	cout << "TheOneLine:" << TheTwoLine.size() << endl;
	for (vector <Point>::iterator iterTheTwoLine = TheTwoLine.begin(); iterTheTwoLine != TheTwoLine.end(); iterTheTwoLine++)
	{
		circle(theFirstImage, *iterTheTwoLine, 2, Scalar(255, 0, 255));
	}

	for (vector <Point>::iterator iterTheOneLine = TheOneLine.begin(); iterTheOneLine != TheOneLine.end(); iterTheOneLine++)
	{
		circle(theFirstImage, *iterTheOneLine, 2, Scalar(255, 255, 255));
	}


//#endif 
//#if 0
 // cv::line(theFirstImage, Point(line[0],line[1]), Point(line[2], line[3]), Scalar(0, 255, 255), 2, 4, 0);
 // circle(theFirstImage, Point(line[0], line[1]), 2, Scalar(0, 0, 255));
 // circle(theFirstImage, Point(line[2], line[3]), 2, Scalar(0, 0, 255));

//  cout << "Point" << line[0] << " " << line[1] << " " << line[2] << " " << line[3] << endl;
 // imshow("BGR", theFirstImage);
	//waitKey(0);
//#endif 
//#if 0
	cvtColor(BGRtheSImage, BGRtheSImage, CV_BGR2RGBA);//转化边缘检测后的图为灰度图
	Canny(BGRtheSImage, BGRtheSImage, 20, 20 * 3, 3);

	vector<Vec4i> lines;
	HoughLinesP(BGRtheSImage, lines, 1, CV_PI / 180, 10,0, 10);
	for (size_t i = 0; i < lines.size(); i++)
	{
		Scalar color(rand() & 255, rand() & 255, rand() & 255);
		Vec4i l = lines[i];
		line(BGRtheSImage, Point(l[0], l[1]), Point(l[2], l[3]), color, 2, 4);
		line(BGRtheSImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 255, 255), 2, 4);
		circle(BGRtheSImage, Point(l[0], l[1]), 4, Scalar(255, 0, 0));
		circle(BGRtheSImage, Point(l[2], l[3]), 4, Scalar(255, 0, 0));
		cout << "ni zai nali" << endl;
	}

//imshow("firstImage", BGRtheSImage);
//waitKey(0);
#endif 
}

/*******************计算出垂直的距离*******************/
void DealWithGetLine::getTheVerticalLeagth()//计算出垂直的距离
{
	Vec4f lineTwo;
	//	Vec4f lineTheCenter;
	// 直线拟合函数  
	if (CenterTwoLine.size() == 0)
	{
		return;
	}
	cv::fitLine(TheTwoLine, lineTwo, CV_DIST_L2, 0, 0.01, 0.01);

	double cos_thetaTwo = lineTwo[0];
	double sin_thetaTwo = lineTwo[1];
	double x0Two = lineTwo[2], y0Two = lineTwo[3];
	double kTwo = (sin_thetaTwo / cos_thetaTwo);
	double bTwo = y0Two - kTwo*x0Two;
	double b0 = lineTheCenter[1] + lineTheCenter[0] / kTwo;
	// lineTheCenter[2] = 13;
//	 lineTheCenter[3] =11;
	lineTheCenter[2] = (b0 - bTwo)*kTwo / (kTwo*kTwo - 1);
	lineTheCenter[3] = lineTheCenter[2] * kTwo + bTwo;
//	lineTheCenter[3] = b0 - 1/(lineTheCenter[2] * kTwo);

}

/*******************计算出亮点最短的距离*******************/
void DealWithGetLine::getTheMinLeagth()
{
	double LengthB;
	double Linelegath;
	double theMinimum = 0;
	bool theNum = true;//TheTwoLine TheTwoLineFitting
	for (vector <Point>::iterator iterTheTwoLine = TheTwoLineFitting.begin(); iterTheTwoLine != TheTwoLineFitting.end(); iterTheTwoLine++)
	{
		if (theNum)
		{
			LengthB = (((*iterTheTwoLine).y - lineTheCenter[1])*((*iterTheTwoLine).y - lineTheCenter[1])) + (((*iterTheTwoLine).x - lineTheCenter[0])*((*iterTheTwoLine).x - lineTheCenter[0]));
			Linelegath = sqrt(LengthB);//亮点之间的距离
			lineTheCenter[2] = (*iterTheTwoLine).x;
			lineTheCenter[3] = (*iterTheTwoLine).y;
			theMinimum = Linelegath;
			theNum = false;
		}
		else
		{
			LengthB = (((*iterTheTwoLine).y - lineTheCenter[1])*((*iterTheTwoLine).y - lineTheCenter[1])) + (((*iterTheTwoLine).x - lineTheCenter[0])*((*iterTheTwoLine).x - lineTheCenter[0]));
			Linelegath = sqrt(LengthB);//亮点之间的距离
			if (Linelegath <= theMinimum)
			{
				lineTheCenter[2] = (*iterTheTwoLine).x;
				lineTheCenter[3] = (*iterTheTwoLine).y;
				theMinimum = Linelegath;
			}
		}
		Log("theMinmun" + to_string(theMinimum), false);
	}
	TheTwoLineFitting.clear();
	Log("", true);

}

/************判断点是否在曲线上否则，采用曲线上的点*********/
void DealWithGetLine::JudgeThePointIfOnline() 
{
	bool theOnePoint = false;
	bool theTwoPoint = false;
	Point OnePoint;
	Point TwoPoint;
	for (vector <Point>::iterator iterTheOneLine = TheOneLine.begin(); iterTheOneLine != TheOneLine.end(); iterTheOneLine++)
	{
		vector <Point>::iterator Oneiter = iterTheOneLine;
		Oneiter++;
		if (((*iterTheOneLine).x - 5) <= lineTheCenter[0] && lineTheCenter[0] < ((*iterTheOneLine).x + 5) && ((*iterTheOneLine).y - 5) <= lineTheCenter[1] && lineTheCenter[1] < ((*iterTheOneLine).y + 5))
		{
			break;
		}
		if ((*iterTheOneLine).x == (int)lineTheCenter[0] )
		{
			OnePoint = (*iterTheOneLine);
			theOnePoint = true;
		}
		if ((Oneiter == TheOneLine.end()) && theOnePoint)
		{
			lineTheCenter[0] = OnePoint.x;
			lineTheCenter[1] = OnePoint.y;
		}

	}
	for (vector <Point>::iterator iterTheTwoLine = TheTwoLine.begin(); iterTheTwoLine != TheTwoLine.end(); iterTheTwoLine++)
	{
		vector <Point>::iterator Twoiter = iterTheTwoLine;
		Twoiter++;
		if (((*iterTheTwoLine).x - 5) <= lineTheCenter[2] && lineTheCenter[2] < ((*iterTheTwoLine).x + 5) && ((*iterTheTwoLine).y - 5) <= lineTheCenter[3] && lineTheCenter[3] < ((*iterTheTwoLine).y + 5))
		{
			break;
		}
		if ((*iterTheTwoLine).x == (int)lineTheCenter[2] && (int)lineTheCenter[1]   <  (*iterTheTwoLine).y)
		{
			TwoPoint = (*iterTheTwoLine);
			theTwoPoint = true;
		}
		if ((Twoiter == TheTwoLine.end()) && theTwoPoint)
		{
			lineTheCenter[2] = TwoPoint.x;
			lineTheCenter[3] = TwoPoint.y;
		}
	}
}

/************************析构函数****************************/
DealWithGetLine::~DealWithGetLine()
{

}


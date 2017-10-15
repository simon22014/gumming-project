/*******************************************************************
*  Copyright(c) 2017-2020 上海贝特威自动化科技有限公司
*  All rights reserved.
*
*  文件名称:  DealWithGetLine.h
*  简要描述: 处理寻找的线集合
*
*  创建日期:  2017/10/11
*  说明:
*
*  修改日期:
*  作者:     simon.li
*  说明:
******************************************************************/
#pragma once
#include"IncludeGlobal.h"
#include"Cbtw_Singleton.h"
#include "Cbtw_imageDealWith.h"
#include"Cbtw_GetInAllResult.h"

class DealWithGetLine
{
public:
	DealWithGetLine();//构造函数
//******************************************************
// 函数名称:  DealWithGetLine
// 函数说明:  拷贝构造函数
// 输入说明：传入image num，矩形框num，矩形框分割的小矩形num,矩形，image、类与类之间联系变量
// 权限:      public
// 返回值:    无
//*****************************************************
	DealWithGetLine(int,int,vector<Mat>,Mat,Mat,Cbtw_Singleton*,Cbtw_GetInAllResult*,int,Mat);
//******************************************************
// 函数名称:  GetLineImage
// 函数说明:  图像处理的接口
// 输入说明： 矩形框中小矩形的num,Mat
// 权限:      public
// 返回值:    无
//*****************************************************
	void GetLineImage(int,Mat );
//******************************************************
// 函数名称:  JudgeLineSize
// 函数说明:  将检测的线画出来
// 输入说明： 矩形框中小矩形的num
// 权限:      public
// 返回值:    无
//*****************************************************
	void JudgeLineSize(int numOne);
//******************************************************
// 函数名称:  JudgeThePointIfOnline
// 函数说明:  判断点是否在曲线上否则，采用曲线上的点
// 输入说明： 无
// 权限:      public
// 返回值:    无
//*****************************************************
	void JudgeThePointIfOnline();
//******************************************************
// 函数名称:  JudgeIsOKOrNg
// 函数说明:  用来对所有的结果进行判断
// 输入说明： 无
// 权限:      public
// 返回值:    无
//*****************************************************
	string JudgeIsOKOrNg(vector<float>); //用来对所有的结果进行判断；

//******************************************************
// 函数名称:  getTheMinLeagth
// 函数说明:  计算出最短的距离
// 输入说明： 无
// 权限:      public
// 返回值:    无
//*****************************************************
	void getTheMinLeagth(); //计算出最短的距离
 //******************************************************
 // 函数名称:  getTheVerticalLeagth
 // 函数说明:  计算出垂直的距离
 // 输入说明： 无
 // 权限:      public
 // 返回值:    无
 //*****************************************************
	void getTheVerticalLeagth(); //计算出垂直的距离

 //******************************************************
 // 函数名称:  FittingOneTwoLine
 // 函数说明:  分别拟合矩形每个小框两边
 // 输入说明： 无
 // 权限:      public
 // 返回值:    无
 //*****************************************************
	void FittingOneTwoLine(int); //分别拟合矩形每个小框两边
//******************************************************
 // 函数名称:  drawLine
 // 函数说明:  画出拟合后的直线
 // 输入说明： 无
 // 权限:      public
 // 返回值:    无
 //*****************************************************
	void drawLine(cv::Mat &, double, double, cv::Scalar color);
	//******************************************************
	// 函数名称:  removeMaxMinPoint
	// 函数说明:  对于拟合小框的时候，去掉最大点和最小点
	// 输入说明： MaxPoint 表示最大去掉几个点，MinPoint表示最小去掉几个点
	// 权限:      public
	// 返回值:    无
	//*****************************************************
	void removeMaxMinPoint(int MinPoint,int MaxPoint);
	//******************************************************
	// 函数名称:  getBestTwoPoint
	// 函数说明:  求出垂直的距离
	// 输入说明：Fpoint为最上面一点，Tpoint为下面一点
	// 权限:      public
	// 返回值:    无
	//*****************************************************
	bool getBestTwoPoint(Point Fpoint,Point Tpoint,int numOne);


	~DealWithGetLine();//析构函数
private:
	Mat NochangeImage; //永远不变的量 用来显示最终的结果
	double Linelegath;//每次检测到的胶宽
	Point2d theLatOne;
	int NumPicture; //机器人传过来的图片
	int theTwoNum; //第几个矩形
	int theGlueWidth;  //人为设定的胶的宽度
	int continueLeagth; //人为设定的连续的胶宽的个数
	int CutLeath;
	Mat sourceImage;
	vector<vector<Point> > NotFindOnePoint;
	vector<vector<Point> > NotFindTwoPoint;
	vector<Point> FindPointLine;
	vector <Mat> GetImageLine;
	Mat theFirstImage;
	vector<Point> theAllPoint;
	vector<Point> TheTwoLine;
	vector<Point> TheOneLine;
	vector<Point> CenterTwoLine; //检测出来的矩形框中2线的小矩形，点的集合
	vector<Point> CenterOneLine; //检测出来的矩形框中1线的小矩形，点的集合
	vector<Point>TheTwoLineFitting;//2线拟合之后点的集合
	vector<Point2d> BestCenterLine;
	Vec4f lineTheCenter;
	Vec4f theTwoCenterPointLine;
	Cbtw_Singleton* Singleton;
	String TheLastResult;
	Cbtw_GetInAllResult*getInAllResult;
};


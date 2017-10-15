/*******************************************************************
*  Copyright(c) 2017-2020 上海贝特威自动化科技有限公司
*  All rights reserved.
*
*  文件名称:  dealWithFourPoint.h
*  简要描述: 与处理四个点并且旋转变换为需要的矩形框
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
#include"CutApartArea.h"
#include "Cbtw_Singleton.h"
#include "Cbtw_GetInAllResult.h"
class dealWithFourPoint
{
public:
	dealWithFourPoint();//构造函数
//******************************************************
// 函数名称:  dealWithFourPoint
// 函数说明:  拷贝构造函数
// 输入说明：传入image num，矩形框num，四点的集合，需要处理的图片
// 权限:      public 
// 返回值:    无
//*****************************************************
	dealWithFourPoint(int,int,vector<Point>,Mat,Mat);

//******************************************************
// 函数名称:  SetRightFourPoint
// 函数说明:  进行初步的预处理图片，初步预处理矩形框四个点，让其为标准的矩形框四个点
// 输入说明： 无
// 权限:      public 
// 返回值:    进行预处理矩形框，得到标准的矩形框的四个点
//*****************************************************
	void SetRightFourPoint();
//******************************************************
// 函数名称:  SetRightRect
// 函数说明:  将得到预处理之后的整个图片进行旋转变换到水平方向，以第2点为旋转中心，旋转角度为矩形框长边变水平方向所夹角
// 输入说明： 无
// 权限:      public 
// 返回值:    
//*****************************************************
	void SetRightRect();
//******************************************************
// 函数名称:  getRightRect
// 函数说明:  将旋转之后的矩形框抠图出来，单独进行处理
// 输入说明： 矩形框两边的长度，已经旋转中心点
// 权限:      public 
// 返回值:    无
//*****************************************************
	void getRightRect(double,double,Point);

	vector<float> getOneLeagth();//返回一个矩形的长度集合
	string getOneResult();//返回一个矩形检测的结果
	~dealWithFourPoint(); //析构函数
private:
	Mat NochangeImage;//永远不变得量
	int NumPicture; //机器人传过来的图片
	int theTwoNum; //第几个矩形

	vector<Point> TheFourPoint;
	vector <Point> fourPoint;
	vector<Point> theLastPoint;
	Mat sourceImage;
	Mat firstImage;
	Mat RatationedChangeImg; //旋转之后的图片
	CutApartArea* dealWithFindArea;
	Cbtw_Singleton* Singleton; //用来作为类与类之间的数据传输
	Cbtw_GetInAllResult* getInAllResult;//用来作为类与类之间的数据传输
};


#pragma once
/*******************************************************************
*  Copyright(c) 2017-2020 上海贝特威自动化科技有限公司
*  All rights reserved.
*
*  文件名称:  GetRectTwoPoint.h
*  简要描述:  涂胶项目类的接口
*
*  创建日期:  2017/10/11
*  说明:从txt中加载所有的矩形框或者手动鼠标获取矩形框
*
*  修改日期:
*  作者:      simon.li
*  说明:
******************************************************************/
#include"IncludeGlobal.h"

class GetRectTwoPoint
{
public:
	//构造函数
	GetRectTwoPoint();
	//***************************************
	// 函数名称:  GetRectTwoPoint
	// 函数说明:  拷贝构造函数
	// 输入说明：传入image和num
	// 权限:      public 
	// 返回值:    无
	//**************************************
    GetRectTwoPoint(Mat ,int );
	//***************************************
	// 函数名称:  CornerGetPoint
	// 函数说明:  鼠标获取矩形框
	// 输入说明：无
	// 权限:      public 
	// 返回值:    无
	//**************************************
	void CornerGetPoint();
	void ItChangeImage();
	Mat getSourceImageMat();
	//***************************************
	// 函数名称:  findFourPoint
	// 函数说明: 返回获取到的矩形框，点的集合
	// 输入说明：无
	// 权限:      public 
	// 返回值:    无
	//**************************************
	vector<Point> findFourPoint();
	//***************************************
	// 函数名称:  ReadFourPoint
	// 函数说明: 从txt文件中读取所有的矩形框，并且通过image和image num返回满足要求的矩形框点
	// 输入说明：无
	// 权限:      public 
	// 返回值:    无
	//**************************************
	void ReadFourPoint();
	~GetRectTwoPoint();
private:
	int NumPicture;//image num
	Mat sourceImage; //传入image
	Mat firstImage;
	map<int, vector<Point>> my_Map; //从文件读取出来所有的集合（int为image编号。vector为当前编号点的集合）
};


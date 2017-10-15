#pragma once
/*******************************************************************
*  Copyright(c) 2017-2020 上海贝特威自动化科技有限公司
*  All rights reserved.
*
*  文件名称:  Cbtw_GluingInpectionAllInto.h
*  简要描述:  涂胶项目类的接口
*
*  创建日期:  2017/10/11
*  说明:一个算法类的接口，需要输入的是image，以及image编号。
*
*  修改日期:
*  作者:      simon.li
*  说明:
******************************************************************/
#include "IncludeGlobal.h"
#include"GetRectTwoPoint.h"
#include"CImageToRect.h"
#include"dealWithFourPoint.h"

class Cbtw_GluingInpectionAllInto
{
public:
	//构造函数
	Cbtw_GluingInpectionAllInto();
	//************************************
	// 函数名称:  Cbtw_GluingInpectionAllInto
	// 函数说明:  拷贝构造函数
	// 权限:      public 
	// 返回值:    无
	//************************************
	Cbtw_GluingInpectionAllInto(int NumPicture, Mat dealWithMat,Mat NochangeImage);
	//************************************
	// 函数名称:  returnResultDealWithMat
	// 函数说明:  返回处理之后的图片
	// 权限:      public 
	// 返回值:    Mat
	//************************************
	Mat returnResultDealWithMat();
	//************************************
	// 函数名称:  returnDealWithLeagth
	// 函数说明:  返回所有的计算出来的胶宽度集合
	// 权限:      public 
	// 返回值:   vector<float>
	//************************************
	vector<float> returnDealWithLeagth();
	//************************************
	// 函数名称:  returnResult
	// 函数说明:  返回处理之后的是OK或者NG
	// 权限:      public 
	// 返回值:   string（“NG”或者“OK”）
	//************************************
	string  returnResult();
	//析构函数
	~Cbtw_GluingInpectionAllInto();
private:
	Mat NochangeImage;//永远不变的的Image
	int NumPicture; //image编号
	Mat dealWithMat; //传入进来的image
	vector<float> dealWithLeagth; //处理之后的长度集合
	string result;//处理之后（OK或者NG）
	Mat resuultDealWithMat; //处理之后的Image

};


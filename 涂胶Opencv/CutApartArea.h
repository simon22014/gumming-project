/*******************************************************************
*  Copyright(c) 2017-2020 上海贝特威自动化科技有限公司
*  All rights reserved.
*
*  文件名称:  CutApartArea.h
*  简要描述: 矩形框分割为多个小矩形
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
#include"Cbtw_GetInAllResult.h"
class CutApartArea
{
public:
	CutApartArea();//构造函数
//******************************************************
// 函数名称:  CutApartArea
// 函数说明:  拷贝构造函数
// 输入说明： image num，矩形框num，抠图出来的Mat，原来的Mat，以及类与类之间的数据传输
// 权限:      public 
// 返回值:    
//*****************************************************
	CutApartArea(int,int,Mat,Mat, Cbtw_Singleton*, Cbtw_GetInAllResult*,Mat);
//******************************************************
// 函数名称:  CutALitterArea
// 函数说明:  将传入进来的矩形框进行分割为多个小框
// 输入说明： image num，矩形框num，抠图出来的Mat，原来的Mat，以及类与类之间的数据传输
// 权限:      public 
// 返回值:    
//*****************************************************
	void CutALitterArea();
//******************************************************
// 函数名称:  GetTheLine
// 函数说明:  矩形框分割的小矩形进行处理
// 输入说明： 无
// 权限:      public 
// 返回值:    
//*****************************************************
	void GetTheLine();
	~CutApartArea();
private:
	Mat NochangeImage;
	int NumPicture;//传入机器所选择的图片
	int theTwoNum;//所选择的区域
	int CutLeath; //代表检测的每一个的宽度
	Mat theFirstImage;
	Mat sourceImage;
	vector<Mat> theLitterArea; //所有分割出来的小矩形框中小矩形
	Cbtw_Singleton* Singleton;
	Cbtw_GetInAllResult* getInAllResult;
};


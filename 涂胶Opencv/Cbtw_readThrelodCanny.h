/*******************************************************************
*  Copyright(c) 2017-2020 上海贝特威自动化科技有限公司
*  All rights reserved.
*
*  文件名称:  Cbtw_readThrelodCanny.h
*  简要描述:  调用C#的dll读取阈值
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
#using "C:\Users\user\Desktop\simon涂胶项目\C#建立DLL\ReadThrethold\ReadThrethold\bin\Debug\ReadThrethold.dll"  
using namespace ReadThrethold;

class Cbtw_readThrelodCanny
{
public:
	Cbtw_readThrelodCanny();
	int readTCannyText(int,int,int);
	int readThreatoldText(int,int,int);
	void WriteTCannyText();
	void WriteThrelodText(int,int,int,int);
	~Cbtw_readThrelodCanny();
private:
	map<int, vector<Vec2i>> my_Threold; //threlod 与canny目前暂时使用这个vec2i表示
	int writeNum; //写人的数据
	int writeTwoNum;//写人的数据
	int writeNumNum;// 写人的数据
	int writeThrethold; //写人的数据
	int writeCanny;//写人的数据
};


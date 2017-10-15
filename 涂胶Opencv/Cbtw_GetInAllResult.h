
/*******************************************************************
*  Copyright(c) 2017-2020 上海贝特威自动化科技有限公司
*  All rights reserved.
*
*  文件名称:  Cbtw_GetInAllResult.h
*  简要描述:  作为一个专门收集结果的类所有的结果都写入这个类中，由主类回收数据
*
*  创建日期:  2017/08/08
*  说明:
*
*  修改日期:
*  作者:     simon.li
*  说明:
******************************************************************/
#pragma once
#include"IncludeGlobal.h"
class Cbtw_GetInAllResult
{
public:
	Cbtw_GetInAllResult();
	~Cbtw_GetInAllResult();
	void writeOneLeagth(vector<float> OneLeagth);
	void writeOneResult(string OneResult);
	vector<float> getOneLeagth();
	string getOneResult();
private:
	vector<float> OneLeagth;
	string OneResult;

};


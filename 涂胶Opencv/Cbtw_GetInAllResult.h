
/*******************************************************************
*  Copyright(c) 2017-2020 �Ϻ��������Զ����Ƽ����޹�˾
*  All rights reserved.
*
*  �ļ�����:  Cbtw_GetInAllResult.h
*  ��Ҫ����:  ��Ϊһ��ר���ռ�����������еĽ����д��������У��������������
*
*  ��������:  2017/08/08
*  ˵��:
*
*  �޸�����:
*  ����:     simon.li
*  ˵��:
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


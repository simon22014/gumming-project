/*******************************************************************
*  Copyright(c) 2017-2020 �Ϻ��������Զ����Ƽ����޹�˾
*  All rights reserved.
*
*  �ļ�����:  Cbtw_readThrelodCanny.h
*  ��Ҫ����:  ����C#��dll��ȡ��ֵ
*
*  ��������:  2017/10/11
*  ˵��:
*
*  �޸�����:
*  ����:     simon.li
*  ˵��:
******************************************************************/
#pragma once
#include"IncludeGlobal.h"
#using "C:\Users\user\Desktop\simonͿ����Ŀ\C#����DLL\ReadThrethold\ReadThrethold\bin\Debug\ReadThrethold.dll"  
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
	map<int, vector<Vec2i>> my_Threold; //threlod ��cannyĿǰ��ʱʹ�����vec2i��ʾ
	int writeNum; //д�˵�����
	int writeTwoNum;//д�˵�����
	int writeNumNum;// д�˵�����
	int writeThrethold; //д�˵�����
	int writeCanny;//д�˵�����
};


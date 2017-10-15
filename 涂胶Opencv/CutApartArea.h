/*******************************************************************
*  Copyright(c) 2017-2020 �Ϻ��������Զ����Ƽ����޹�˾
*  All rights reserved.
*
*  �ļ�����:  CutApartArea.h
*  ��Ҫ����: ���ο�ָ�Ϊ���С����
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
#include"Cbtw_Singleton.h"
#include"Cbtw_GetInAllResult.h"
class CutApartArea
{
public:
	CutApartArea();//���캯��
//******************************************************
// ��������:  CutApartArea
// ����˵��:  �������캯��
// ����˵���� image num�����ο�num����ͼ������Mat��ԭ����Mat���Լ�������֮������ݴ���
// Ȩ��:      public 
// ����ֵ:    
//*****************************************************
	CutApartArea(int,int,Mat,Mat, Cbtw_Singleton*, Cbtw_GetInAllResult*,Mat);
//******************************************************
// ��������:  CutALitterArea
// ����˵��:  ����������ľ��ο���зָ�Ϊ���С��
// ����˵���� image num�����ο�num����ͼ������Mat��ԭ����Mat���Լ�������֮������ݴ���
// Ȩ��:      public 
// ����ֵ:    
//*****************************************************
	void CutALitterArea();
//******************************************************
// ��������:  GetTheLine
// ����˵��:  ���ο�ָ��С���ν��д���
// ����˵���� ��
// Ȩ��:      public 
// ����ֵ:    
//*****************************************************
	void GetTheLine();
	~CutApartArea();
private:
	Mat NochangeImage;
	int NumPicture;//���������ѡ���ͼƬ
	int theTwoNum;//��ѡ�������
	int CutLeath; //�������ÿһ���Ŀ��
	Mat theFirstImage;
	Mat sourceImage;
	vector<Mat> theLitterArea; //���зָ������С���ο���С����
	Cbtw_Singleton* Singleton;
	Cbtw_GetInAllResult* getInAllResult;
};


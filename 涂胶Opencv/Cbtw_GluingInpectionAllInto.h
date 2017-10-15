#pragma once
/*******************************************************************
*  Copyright(c) 2017-2020 �Ϻ��������Զ����Ƽ����޹�˾
*  All rights reserved.
*
*  �ļ�����:  Cbtw_GluingInpectionAllInto.h
*  ��Ҫ����:  Ϳ����Ŀ��Ľӿ�
*
*  ��������:  2017/10/11
*  ˵��:һ���㷨��Ľӿڣ���Ҫ�������image���Լ�image��š�
*
*  �޸�����:
*  ����:      simon.li
*  ˵��:
******************************************************************/
#include "IncludeGlobal.h"
#include"GetRectTwoPoint.h"
#include"CImageToRect.h"
#include"dealWithFourPoint.h"

class Cbtw_GluingInpectionAllInto
{
public:
	//���캯��
	Cbtw_GluingInpectionAllInto();
	//************************************
	// ��������:  Cbtw_GluingInpectionAllInto
	// ����˵��:  �������캯��
	// Ȩ��:      public 
	// ����ֵ:    ��
	//************************************
	Cbtw_GluingInpectionAllInto(int NumPicture, Mat dealWithMat,Mat NochangeImage);
	//************************************
	// ��������:  returnResultDealWithMat
	// ����˵��:  ���ش���֮���ͼƬ
	// Ȩ��:      public 
	// ����ֵ:    Mat
	//************************************
	Mat returnResultDealWithMat();
	//************************************
	// ��������:  returnDealWithLeagth
	// ����˵��:  �������еļ�������Ľ���ȼ���
	// Ȩ��:      public 
	// ����ֵ:   vector<float>
	//************************************
	vector<float> returnDealWithLeagth();
	//************************************
	// ��������:  returnResult
	// ����˵��:  ���ش���֮�����OK����NG
	// Ȩ��:      public 
	// ����ֵ:   string����NG�����ߡ�OK����
	//************************************
	string  returnResult();
	//��������
	~Cbtw_GluingInpectionAllInto();
private:
	Mat NochangeImage;//��Զ����ĵ�Image
	int NumPicture; //image���
	Mat dealWithMat; //���������image
	vector<float> dealWithLeagth; //����֮��ĳ��ȼ���
	string result;//����֮��OK����NG��
	Mat resuultDealWithMat; //����֮���Image

};


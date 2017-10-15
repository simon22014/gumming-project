#pragma once
/*******************************************************************
*  Copyright(c) 2017-2020 �Ϻ��������Զ����Ƽ����޹�˾
*  All rights reserved.
*
*  �ļ�����:  GetRectTwoPoint.h
*  ��Ҫ����:  Ϳ����Ŀ��Ľӿ�
*
*  ��������:  2017/10/11
*  ˵��:��txt�м������еľ��ο�����ֶ�����ȡ���ο�
*
*  �޸�����:
*  ����:      simon.li
*  ˵��:
******************************************************************/
#include"IncludeGlobal.h"

class GetRectTwoPoint
{
public:
	//���캯��
	GetRectTwoPoint();
	//***************************************
	// ��������:  GetRectTwoPoint
	// ����˵��:  �������캯��
	// ����˵��������image��num
	// Ȩ��:      public 
	// ����ֵ:    ��
	//**************************************
    GetRectTwoPoint(Mat ,int );
	//***************************************
	// ��������:  CornerGetPoint
	// ����˵��:  ����ȡ���ο�
	// ����˵������
	// Ȩ��:      public 
	// ����ֵ:    ��
	//**************************************
	void CornerGetPoint();
	void ItChangeImage();
	Mat getSourceImageMat();
	//***************************************
	// ��������:  findFourPoint
	// ����˵��: ���ػ�ȡ���ľ��ο򣬵�ļ���
	// ����˵������
	// Ȩ��:      public 
	// ����ֵ:    ��
	//**************************************
	vector<Point> findFourPoint();
	//***************************************
	// ��������:  ReadFourPoint
	// ����˵��: ��txt�ļ��ж�ȡ���еľ��ο򣬲���ͨ��image��image num��������Ҫ��ľ��ο��
	// ����˵������
	// Ȩ��:      public 
	// ����ֵ:    ��
	//**************************************
	void ReadFourPoint();
	~GetRectTwoPoint();
private:
	int NumPicture;//image num
	Mat sourceImage; //����image
	Mat firstImage;
	map<int, vector<Point>> my_Map; //���ļ���ȡ�������еļ��ϣ�intΪimage��š�vectorΪ��ǰ��ŵ�ļ��ϣ�
};


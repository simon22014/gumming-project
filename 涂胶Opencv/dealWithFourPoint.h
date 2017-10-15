/*******************************************************************
*  Copyright(c) 2017-2020 �Ϻ��������Զ����Ƽ����޹�˾
*  All rights reserved.
*
*  �ļ�����:  dealWithFourPoint.h
*  ��Ҫ����: �봦���ĸ��㲢����ת�任Ϊ��Ҫ�ľ��ο�
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
#include"CutApartArea.h"
#include "Cbtw_Singleton.h"
#include "Cbtw_GetInAllResult.h"
class dealWithFourPoint
{
public:
	dealWithFourPoint();//���캯��
//******************************************************
// ��������:  dealWithFourPoint
// ����˵��:  �������캯��
// ����˵��������image num�����ο�num���ĵ�ļ��ϣ���Ҫ�����ͼƬ
// Ȩ��:      public 
// ����ֵ:    ��
//*****************************************************
	dealWithFourPoint(int,int,vector<Point>,Mat,Mat);

//******************************************************
// ��������:  SetRightFourPoint
// ����˵��:  ���г�����Ԥ����ͼƬ������Ԥ������ο��ĸ��㣬����Ϊ��׼�ľ��ο��ĸ���
// ����˵���� ��
// Ȩ��:      public 
// ����ֵ:    ����Ԥ������ο򣬵õ���׼�ľ��ο���ĸ���
//*****************************************************
	void SetRightFourPoint();
//******************************************************
// ��������:  SetRightRect
// ����˵��:  ���õ�Ԥ����֮�������ͼƬ������ת�任��ˮƽ�����Ե�2��Ϊ��ת���ģ���ת�Ƕ�Ϊ���ο򳤱߱�ˮƽ�������н�
// ����˵���� ��
// Ȩ��:      public 
// ����ֵ:    
//*****************************************************
	void SetRightRect();
//******************************************************
// ��������:  getRightRect
// ����˵��:  ����ת֮��ľ��ο��ͼ�������������д���
// ����˵���� ���ο����ߵĳ��ȣ��Ѿ���ת���ĵ�
// Ȩ��:      public 
// ����ֵ:    ��
//*****************************************************
	void getRightRect(double,double,Point);

	vector<float> getOneLeagth();//����һ�����εĳ��ȼ���
	string getOneResult();//����һ�����μ��Ľ��
	~dealWithFourPoint(); //��������
private:
	Mat NochangeImage;//��Զ�������
	int NumPicture; //�����˴�������ͼƬ
	int theTwoNum; //�ڼ�������

	vector<Point> TheFourPoint;
	vector <Point> fourPoint;
	vector<Point> theLastPoint;
	Mat sourceImage;
	Mat firstImage;
	Mat RatationedChangeImg; //��ת֮���ͼƬ
	CutApartArea* dealWithFindArea;
	Cbtw_Singleton* Singleton; //������Ϊ������֮������ݴ���
	Cbtw_GetInAllResult* getInAllResult;//������Ϊ������֮������ݴ���
};


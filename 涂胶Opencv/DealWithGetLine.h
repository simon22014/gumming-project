/*******************************************************************
*  Copyright(c) 2017-2020 �Ϻ��������Զ����Ƽ����޹�˾
*  All rights reserved.
*
*  �ļ�����:  DealWithGetLine.h
*  ��Ҫ����: ����Ѱ�ҵ��߼���
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
#include "Cbtw_imageDealWith.h"
#include"Cbtw_GetInAllResult.h"

class DealWithGetLine
{
public:
	DealWithGetLine();//���캯��
//******************************************************
// ��������:  DealWithGetLine
// ����˵��:  �������캯��
// ����˵��������image num�����ο�num�����ο�ָ��С����num,���Σ�image��������֮����ϵ����
// Ȩ��:      public
// ����ֵ:    ��
//*****************************************************
	DealWithGetLine(int,int,vector<Mat>,Mat,Mat,Cbtw_Singleton*,Cbtw_GetInAllResult*,int,Mat);
//******************************************************
// ��������:  GetLineImage
// ����˵��:  ͼ����Ľӿ�
// ����˵���� ���ο���С���ε�num,Mat
// Ȩ��:      public
// ����ֵ:    ��
//*****************************************************
	void GetLineImage(int,Mat );
//******************************************************
// ��������:  JudgeLineSize
// ����˵��:  �������߻�����
// ����˵���� ���ο���С���ε�num
// Ȩ��:      public
// ����ֵ:    ��
//*****************************************************
	void JudgeLineSize(int numOne);
//******************************************************
// ��������:  JudgeThePointIfOnline
// ����˵��:  �жϵ��Ƿ��������Ϸ��򣬲��������ϵĵ�
// ����˵���� ��
// Ȩ��:      public
// ����ֵ:    ��
//*****************************************************
	void JudgeThePointIfOnline();
//******************************************************
// ��������:  JudgeIsOKOrNg
// ����˵��:  ���������еĽ�������ж�
// ����˵���� ��
// Ȩ��:      public
// ����ֵ:    ��
//*****************************************************
	string JudgeIsOKOrNg(vector<float>); //���������еĽ�������жϣ�

//******************************************************
// ��������:  getTheMinLeagth
// ����˵��:  �������̵ľ���
// ����˵���� ��
// Ȩ��:      public
// ����ֵ:    ��
//*****************************************************
	void getTheMinLeagth(); //�������̵ľ���
 //******************************************************
 // ��������:  getTheVerticalLeagth
 // ����˵��:  �������ֱ�ľ���
 // ����˵���� ��
 // Ȩ��:      public
 // ����ֵ:    ��
 //*****************************************************
	void getTheVerticalLeagth(); //�������ֱ�ľ���

 //******************************************************
 // ��������:  FittingOneTwoLine
 // ����˵��:  �ֱ���Ͼ���ÿ��С������
 // ����˵���� ��
 // Ȩ��:      public
 // ����ֵ:    ��
 //*****************************************************
	void FittingOneTwoLine(int); //�ֱ���Ͼ���ÿ��С������
//******************************************************
 // ��������:  drawLine
 // ����˵��:  ������Ϻ��ֱ��
 // ����˵���� ��
 // Ȩ��:      public
 // ����ֵ:    ��
 //*****************************************************
	void drawLine(cv::Mat &, double, double, cv::Scalar color);
	//******************************************************
	// ��������:  removeMaxMinPoint
	// ����˵��:  �������С���ʱ��ȥ���������С��
	// ����˵���� MaxPoint ��ʾ���ȥ�������㣬MinPoint��ʾ��Сȥ��������
	// Ȩ��:      public
	// ����ֵ:    ��
	//*****************************************************
	void removeMaxMinPoint(int MinPoint,int MaxPoint);
	//******************************************************
	// ��������:  getBestTwoPoint
	// ����˵��:  �����ֱ�ľ���
	// ����˵����FpointΪ������һ�㣬TpointΪ����һ��
	// Ȩ��:      public
	// ����ֵ:    ��
	//*****************************************************
	bool getBestTwoPoint(Point Fpoint,Point Tpoint,int numOne);


	~DealWithGetLine();//��������
private:
	Mat NochangeImage; //��Զ������� ������ʾ���յĽ��
	double Linelegath;//ÿ�μ�⵽�Ľ���
	Point2d theLatOne;
	int NumPicture; //�����˴�������ͼƬ
	int theTwoNum; //�ڼ�������
	int theGlueWidth;  //��Ϊ�趨�Ľ��Ŀ��
	int continueLeagth; //��Ϊ�趨�������Ľ���ĸ���
	int CutLeath;
	Mat sourceImage;
	vector<vector<Point> > NotFindOnePoint;
	vector<vector<Point> > NotFindTwoPoint;
	vector<Point> FindPointLine;
	vector <Mat> GetImageLine;
	Mat theFirstImage;
	vector<Point> theAllPoint;
	vector<Point> TheTwoLine;
	vector<Point> TheOneLine;
	vector<Point> CenterTwoLine; //�������ľ��ο���2�ߵ�С���Σ���ļ���
	vector<Point> CenterOneLine; //�������ľ��ο���1�ߵ�С���Σ���ļ���
	vector<Point>TheTwoLineFitting;//2�����֮���ļ���
	vector<Point2d> BestCenterLine;
	Vec4f lineTheCenter;
	Vec4f theTwoCenterPointLine;
	Cbtw_Singleton* Singleton;
	String TheLastResult;
	Cbtw_GetInAllResult*getInAllResult;
};


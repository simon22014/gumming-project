#pragma once
#include"IncludeGlobal.h"
class Cbtw_Singleton
{
public:
	Cbtw_Singleton();
	Cbtw_Singleton(Point, float,Mat,vector<Point>);
	Cbtw_Singleton* GetInstance(Point,float,Mat,vector<Point>);
	~Cbtw_Singleton();
	Point PointCenterRotate;
	float CenterRotateAngel;
	Mat RatationedChangeImg;
	vector<Point> theLastPoint; //¼ì²âµÄ¾ØÐÎ
private:
	Cbtw_Singleton* m_pInstance;


};


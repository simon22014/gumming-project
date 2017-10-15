#include "stdafx.h"
#include "Cbtw_Singleton.h"


Cbtw_Singleton::Cbtw_Singleton()
{
}
Cbtw_Singleton::Cbtw_Singleton(Point PointCenterRotate,float CenterRotateAngel,Mat RatationedChangeImg,vector<Point> theLastPoint)
	:PointCenterRotate(PointCenterRotate), CenterRotateAngel(CenterRotateAngel), RatationedChangeImg(RatationedChangeImg),theLastPoint(theLastPoint)
{

}
Cbtw_Singleton* Cbtw_Singleton::GetInstance(Point PointCenterRotate, float CenterRotateAngel,Mat RatationedChangeImg, vector<Point> theLastPoint)
{
	if (m_pInstance == NULL)
		m_pInstance = new Cbtw_Singleton(PointCenterRotate,CenterRotateAngel,RatationedChangeImg,theLastPoint);
	return m_pInstance;
}
Cbtw_Singleton::~Cbtw_Singleton()
{
	if (Cbtw_Singleton::m_pInstance)
	{
		delete Cbtw_Singleton::m_pInstance;
	}
}

#pragma once
#include "stdafx.h"
#include "cv.h"    
#define _CV_SNAKE_BIG 2.e+38f    
#define _CV_SNAKE_IMAGE 1    
#define _CV_SNAKE_GRAD  2    
#define CV_VALUE 30
int icvSnake8uC1R(unsigned char *src,   //ԭʼͼ������    
	int srcStep,         //ÿ�е��ֽ���    
	CvSize roi,         //ͼ��ߴ�    
	CvPoint * pt,       //������(���ζ���)    
	int n,            //������ĸ���    
	float *alpha,       //ָ�����ָ�룬�������ǵ���ֵ��Ҳ�����������������һ�µ�����    
	float *beta,        //�µ�ֵ��ͬ��    
	float *gamma,       //�õ�ֵ��ͬ��    
	int coeffUsage,   //ȷ�����¦�����������ֵ���Ǹ�����    
	CvSize win,       //ÿ����������������С�������С,���Ϊ����    
	CvTermCriteria criteria,   //�ݹ������ֹ������׼��    
	int scheme);

void cvSnakeImage(const IplImage* src, CvPoint* points,
	int length, float *alpha,
	float *beta, float *gamma,
	int coeffUsage, CvSize win,
	CvTermCriteria criteria, int calcGradient);
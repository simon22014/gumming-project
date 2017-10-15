#pragma once
#include "stdafx.h"
#include "cv.h"    
#define _CV_SNAKE_BIG 2.e+38f    
#define _CV_SNAKE_IMAGE 1    
#define _CV_SNAKE_GRAD  2    
#define CV_VALUE 30
int icvSnake8uC1R(unsigned char *src,   //原始图像数据    
	int srcStep,         //每行的字节数    
	CvSize roi,         //图像尺寸    
	CvPoint * pt,       //轮廓点(变形对象)    
	int n,            //轮廓点的个数    
	float *alpha,       //指向α的指针，α可以是单个值，也可以是与轮廓点个数一致的数组    
	float *beta,        //β的值，同α    
	float *gamma,       //γ的值，同α    
	int coeffUsage,   //确定αβγ是用作单个值还是个数组    
	CvSize win,       //每个点用于搜索的最小的领域大小,宽度为奇数    
	CvTermCriteria criteria,   //递归迭代终止的条件准则    
	int scheme);

void cvSnakeImage(const IplImage* src, CvPoint* points,
	int length, float *alpha,
	float *beta, float *gamma,
	int coeffUsage, CvSize win,
	CvTermCriteria criteria, int calcGradient);
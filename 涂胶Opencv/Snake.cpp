#include "stdafx.h"
#include "Snake.h"
/*F///////////////////////////////////////////////////////////////////////////////////////
//    Name:      icvSnake8uC1R
//    Purpose:
//    Context:
//    Parameters:
//               src - source image,
//               srcStep - its step in bytes,
//               roi - size of ROI,
//               pt - pointer to snake points array
//               n - size of points array,
//               alpha - pointer to coefficient of continuity energy,
//               beta - pointer to coefficient of curvature energy,
//               gamma - pointer to coefficient of image energy,
//               coeffUsage - if CV_VALUE - alpha, beta, gamma point to single value
//                            if CV_MATAY - point to arrays
//               criteria - termination criteria.
//               scheme - image energy scheme
//                         if _CV_SNAKE_IMAGE - image intensity is energy
//                         if _CV_SNAKE_GRAD  - magnitude of gradient is energy
//    Returns:
//F*/

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
	int scheme)         //ȷ��ͼ��������������ѡ��1Ϊ�Ҷȣ�2Ϊ�Ҷ��ݶ�    
{
	int i, j, k;
	int neighbors = win.height * win.width;    //��ǰ�������е�ĸ���    

											   //��ǰ���λ��    
	int centerx = win.width >> 1;
	int centery = win.height >> 1;

	float invn;        //n �ĵ�����    
	int iteration = 0;     //��������    
	int converged = 0;      //������־��0Ϊ������    

							//����    
	float *Econt;    //    
	float *Ecurv;   //������������    
	float *Eimg;    //ͼ������    
	float *E;      //    

				   //���¦õĸ���    
	float _alpha, _beta, _gamma;

	/*#ifdef GRAD_SNAKE */
	float *gradient = NULL;
	uchar *map = NULL;
	int map_width = ((roi.width - 1) >> 3) + 1;
	int map_height = ((roi.height - 1) >> 3) + 1;
	//CvSepFilter pX, pY;  
#define WTILE_SIZE 8    
#define TILE_SIZE (WTILE_SIZE + 2)           
	short dx[TILE_SIZE*TILE_SIZE], dy[TILE_SIZE*TILE_SIZE];
	CvMat _dx = cvMat(TILE_SIZE, TILE_SIZE, CV_16SC1, dx);
	CvMat _dy = cvMat(TILE_SIZE, TILE_SIZE, CV_16SC1, dy);
	CvMat _src = cvMat(roi.height, roi.width, CV_8UC1, src);

	/* inner buffer of convolution process */
	//char ConvBuffer[400];    

	/*#endif */

	//�������ĺ�����    
	/* check bad arguments */
	//if (src == NULL)  
	//  return CV_NULLPTR_ERR;  
	//if ((roi.height <= 0) || (roi.width <= 0))  
	//  return CV_BADSIZE_ERR;  
	//if (srcStep < roi.width)  
	//  return CV_BADSIZE_ERR;  
	//if (pt == NULL)  
	//  return CV_NULLPTR_ERR;  
	//if (n < 3)                         //����������Ҫ����    
	//  return CV_BADSIZE_ERR;  
	//if (alpha == NULL)  
	//  return CV_NULLPTR_ERR;  
	//if (beta == NULL)  
	//  return CV_NULLPTR_ERR;  
	//if (gamma == NULL)  
	//  return CV_NULLPTR_ERR;  
	//if (coeffUsage != CV_VALUE && coeffUsage != CV_ARRAY)  
	//  return CV_BADFLAG_ERR;  
	//if ((win.height <= 0) || (!(win.height & 1)))   //�����������ڵ�������    
	//  return CV_BADSIZE_ERR;  
	//if ((win.width <= 0) || (!(win.width & 1)))  
	//  return CV_BADSIZE_ERR;  

	invn = 1 / ((float)n);        //��������n�ĵ�����������ƽ����    

	if (scheme == _CV_SNAKE_GRAD)
	{
		//X�����Ϻ�Y�����ϵ�Scoble�ݶ����ӣ�������ͼ����ݶ�,    
		//�����ͼ�����ߴ�ΪTILE_SIZE+2������Ϊ12�����Ӱ볤Ϊ3��{-3��-2��-1��0��1��2��3}    
		//��������������Ϊ16λ������,�ֱ�����_dx,_dy������,����Ϊ10    
		//pX.init_deriv(TILE_SIZE + 2, CV_8UC1, CV_16SC1, 1, 0, 3);  
		//pY.init_deriv(TILE_SIZE + 2, CV_8UC1, CV_16SC1, 0, 1, 3);  
		//ͼ���ݶȴ�Ż�����    
		gradient = (float *)cvAlloc(roi.height * roi.width * sizeof(float));

		//if (!gradient)  
		//return CV_OUTOFMEM_ERR;  
		//map���ڱ�־��Ӧλ�õķֿ��ͼ�������Ƿ��Ѿ����    
		map = (uchar *)cvAlloc(map_width * map_height);
		//if (!map)  
		//{  
		//cvFree(&gradient);  
		//return CV_OUTOFMEM_ERR;  
		//}  
		/* clear map - no gradient computed */
		//���map��־    
		memset((void *)map, 0, map_width * map_height);
	}
	//���������Ĵ�Ŵ���ȡÿ������������    
	Econt = (float *)cvAlloc(neighbors * sizeof(float));
	Ecurv = (float *)cvAlloc(neighbors * sizeof(float));
	Eimg = (float *)cvAlloc(neighbors * sizeof(float));
	E = (float *)cvAlloc(neighbors * sizeof(float));
	//��ʼ����    
	while (!converged)    //������־��Чʱ����    
	{
		float ave_d = 0;  //���������ƽ������    
		int moved = 0;      //��������ʱ�������ƶ�������    

		converged = 0;       //��־δ����    
		iteration++;        //���µ�������+1    

							//���������и����ƽ������    
							/* compute average distance */
							//�ӵ�0����n-1�ľ����    
		for (i = 1; i < n; i++)
		{
			int diffx = pt[i - 1].x - pt[i].x;
			int diffy = pt[i - 1].y - pt[i].y;

			ave_d += cvSqrt((float)(diffx * diffx + diffy * diffy));
		}
		//�ټ��ϴӵ�n-1����0�ľ���,�γɻ�·����    
		ave_d += cvSqrt((float)((pt[0].x - pt[n - 1].x) *
			(pt[0].x - pt[n - 1].x) +
			(pt[0].y - pt[n - 1].y) * (pt[0].y - pt[n - 1].y)));
		//��ƽ�����ó�ƽ������    
		ave_d *= invn;
		/* average distance computed */


		//����ÿ������������ض�ѭ���������    
		for (i = 0; i < n; i++)
		{
			/* Calculate Econt */
			//��ʼ����������    
			float maxEcont = 0;
			float maxEcurv = 0;
			float maxEimg = 0;
			float minEcont = _CV_SNAKE_BIG;
			float minEcurv = _CV_SNAKE_BIG;
			float minEimg = _CV_SNAKE_BIG;
			float Emin = _CV_SNAKE_BIG;
			//��ʼ�����κ��������ƫ����    
			int offsetx = 0;
			int offsety = 0;
			float tmp;

			//����߽�    
			/* compute bounds */
			//�������������߽磬�Է�������������ROIͼ��ķ�Χ    
			int left = MIN(pt[i].x, win.width >> 1);
			int right = MIN(roi.width - 1 - pt[i].x, win.width >> 1);
			int upper = MIN(pt[i].y, win.height >> 1);
			int bottom = MIN(roi.height - 1 - pt[i].y, win.height >> 1);
			//��ʼ��Econt    
			maxEcont = 0;
			minEcont = _CV_SNAKE_BIG;
			//�ں����������Χ�ڽ���Econt�ļ���    
			for (j = -upper; j <= bottom; j++)
			{
				for (k = -left; k <= right; k++)
				{
					int diffx, diffy;
					float energy;
					//�������㼯����β��Ӵ�����Ӧ����,����������    
					if (i == 0)
					{
						diffx = pt[n - 1].x - (pt[i].x + k);
						diffy = pt[n - 1].y - (pt[i].y + j);
					}
					else
						//�������ط���һ�㴦��    

					{
						diffx = pt[i - 1].x - (pt[i].x + k);
						diffy = pt[i - 1].y - (pt[i].y + j);
					}
					//�������������ת��Econt������±���ţ�����������ÿ���Econt    
					//Econt��ֵ����ƽ������ʹ˵����һ��ľ���Ĳ�ľ���ֵ��������ô���ģ���    
					Econt[(j + centery) * win.width + k + centerx] = energy =
						(float)fabs(ave_d -
							cvSqrt((float)(diffx * diffx + diffy * diffy)));
					//�������������е�Econt�����ֵ����Сֵ    
					maxEcont = MAX(maxEcont, energy);
					minEcont = MIN(minEcont, energy);
				}
			}
			//�������������ֵ����Сֵ֮��,�������е�������Econt���б�׼��һ��,�����ֵ��С    
			//��ȣ��������еĵ�Econtȫ��ȣ�Econt��һ������Ϊ0    
			tmp = maxEcont - minEcont;
			tmp = (tmp == 0) ? 0 : (1 / tmp);
			for (k = 0; k < neighbors; k++)
			{
				Econt[k] = (Econt[k] - minEcont) * tmp;
			}


			//����ÿ���Ecurv    
			/*  Calculate Ecurv */
			maxEcurv = 0;
			minEcurv = _CV_SNAKE_BIG;
			for (j = -upper; j <= bottom; j++)
			{
				for (k = -left; k <= right; k++)
				{
					int tx, ty;
					float energy;
					//��һ����Ķ��ײ��    
					if (i == 0)
					{
						tx = pt[n - 1].x - 2 * (pt[i].x + k) + pt[i + 1].x;
						ty = pt[n - 1].y - 2 * (pt[i].y + j) + pt[i + 1].y;
					}
					//���һ����Ķ��ײ��    
					else if (i == n - 1)
					{
						tx = pt[i - 1].x - 2 * (pt[i].x + k) + pt[0].x;
						ty = pt[i - 1].y - 2 * (pt[i].y + j) + pt[0].y;
					}
					//�����Ķ��ײ��    
					else
					{
						tx = pt[i - 1].x - 2 * (pt[i].x + k) + pt[i + 1].x;
						ty = pt[i - 1].y - 2 * (pt[i].y + j) + pt[i + 1].y;
					}
					//ת������Ϊ������ţ���������Ecurv��ֵ,���ײ�ֺ�ȡƽ��    
					Ecurv[(j + centery) * win.width + k + centerx] = energy =
						(float)(tx * tx + ty * ty);
					//ȡ��С��Ecurv������Ecurv    
					maxEcurv = MAX(maxEcurv, energy);
					minEcurv = MIN(minEcurv, energy);
				}
			}
			//��Ecurv���б�׼��һ��    
			tmp = maxEcurv - minEcurv;
			tmp = (tmp == 0) ? 0 : (1 / tmp);
			for (k = 0; k < neighbors; k++)
			{
				Ecurv[k] = (Ecurv[k] - minEcurv) * tmp;
			}

			//��Eimg    
			/* Calculate Eimg */
			for (j = -upper; j <= bottom; j++)
			{
				for (k = -left; k <= right; k++)
				{
					float energy;
					//�����ûҶ��ݶ�����    
					if (scheme == _CV_SNAKE_GRAD)
					{
						/* look at map and check status */
						int x = (pt[i].x + k) / WTILE_SIZE;
						int y = (pt[i].y + j) / WTILE_SIZE;
						//���˴���ͼ��������û�л�ȡ����Դ˴���Ӧ��ͼ��ֿ����ͼ�����������    
						if (map[y * map_width + x] == 0)
						{
							int l, m;

							/* evaluate block location */
							//����Ҫ�����ݶ����Ӵ����ͼ����λ��    
							int upshift = y ? 1 : 0;
							int leftshift = x ? 1 : 0;
							int bottomshift = MIN(1, roi.height - (y + 1)*WTILE_SIZE);
							int rightshift = MIN(1, roi.width - (x + 1)*WTILE_SIZE);
							//ͼ����λ�ô�С������ԭROI��һ����8�ı���������ͼ�����С��һ��    
							CvRect g_roi = { x*WTILE_SIZE - leftshift, y*WTILE_SIZE - upshift,
								leftshift + WTILE_SIZE + rightshift, upshift + WTILE_SIZE + bottomshift };
							CvMat _src1;
							cvGetSubArr(&_src, &_src1, g_roi);  //�õ�ͼ��������    
																//�ֱ��ͼ���X�����Y��������ݶ�����    
							cvSobel(&_src1, &_dx, 1, 0, 1);
							cvSobel(&_src1, &_dy, 1, 0, 1);
							//pX.process(&_src1, &_dx);  
							//pY.process(&_src1, &_dy);  
							//��ֿ������е�ÿ������ݶ�    
							for (l = 0; l < WTILE_SIZE + bottomshift; l++)
							{
								for (m = 0; m < WTILE_SIZE + rightshift; m++)
								{
									gradient[(y*WTILE_SIZE + l) * roi.width + x*WTILE_SIZE + m] =
										(float)(dx[(l + upshift) * TILE_SIZE + m + leftshift] *
											dx[(l + upshift) * TILE_SIZE + m + leftshift] +
											dy[(l + upshift) * TILE_SIZE + m + leftshift] *
											dy[(l + upshift) * TILE_SIZE + m + leftshift]);
								}
							}
							//map��Ӧλ����1��ʾ�˴�ͼ�������Ѿ���ȡ    
							map[y * map_width + x] = 1;
						}
						//���ݶ�������Ϊͼ������    
						Eimg[(j + centery) * win.width + k + centerx] = energy =
							gradient[(pt[i].y + j) * roi.width + pt[i].x + k];
					}
					else
					{
						//�ԻҶ���Ϊͼ������    
						Eimg[(j + centery) * win.width + k + centerx] = energy =
							src[(pt[i].y + j) * srcStep + pt[i].x + k];
					}
					//���������������С��ͼ������    
					maxEimg = MAX(maxEimg, energy);
					minEimg = MIN(minEimg, energy);
				}
			}
			//Eimg�ı�׼��һ��    
			tmp = (maxEimg - minEimg);
			tmp = (tmp == 0) ? 0 : (1 / tmp);

			for (k = 0; k < neighbors; k++)
			{
				Eimg[k] = (minEimg - Eimg[k]) * tmp;
			}
			//����ϵ��    
			/* locate coefficients */
			if (1)//if (coeffUsage == CV_VALUE)  
			{
				_alpha = *alpha;
				_beta = *beta;
				_gamma = *gamma;
			}
			else
			{
				_alpha = alpha[i];
				_beta = beta[i];
				_gamma = gamma[i];
			}

			/* Find Minimize point in the neighbors */
			//���ÿ��������Snake����    
			for (k = 0; k < neighbors; k++)
			{
				E[k] = _alpha * Econt[k] + _beta * Ecurv[k] + _gamma * Eimg[k];
			}
			Emin = _CV_SNAKE_BIG;
			//��ȡ��С���������Լ���Ӧ�������е����λ��    
			for (j = -upper; j <= bottom; j++)
			{
				for (k = -left; k <= right; k++)
				{

					if (E[(j + centery) * win.width + k + centerx] < Emin)
					{
						Emin = E[(j + centery) * win.width + k + centerx];
						offsetx = k;
						offsety = j;
					}
				}
			}
			//��������㷢���ı䣬��ǵ��ƶ�����    
			if (offsetx || offsety)
			{
				pt[i].x += offsetx;
				pt[i].y += offsety;
				moved++;
			}
		}

		//�������������������ɺ����û���ƶ��ĵ��ˣ���������־λ��Ч��ֹͣ����    
		converged = (moved == 0);
		//�ﵽ����������ʱ��������־λ��Ч��ֹͣ����    
		if ((criteria.type & CV_TERMCRIT_ITER) && (iteration >= criteria.max_iter))
			converged = 1;
		//������Ӧ����ʱ��ֹͣ���������һ����������ͬЧ����    
		if ((criteria.type & CV_TERMCRIT_EPS) && (moved <= criteria.epsilon))
			converged = 1;
	}

	//�ͷŸ���������    
	cvFree(&Econt);
	cvFree(&Ecurv);
	cvFree(&Eimg);
	cvFree(&E);

	if (scheme == _CV_SNAKE_GRAD)
	{
		cvFree(&gradient);
		cvFree(&map);
	}
	return 1;
}


void cvSnakeImage(const IplImage* src, CvPoint* points,
	int length, float *alpha,
	float *beta, float *gamma,
	int coeffUsage, CvSize win,
	CvTermCriteria criteria, int calcGradient)
{

	CV_FUNCNAME("cvSnakeImage");

	//__BEGIN__;  

	uchar *data;
	CvSize size;
	int step;

	//if (src->nChannels != 1)  
	//CV_ERROR(CV_BadNumChannels, "input image has more than one channel");  

	//if (src->depth != IPL_DEPTH_8U)  
	//CV_ERROR(CV_BadDepth, cvUnsupportedFormat);  

	cvGetRawData(src, &data, &step, &size);

	icvSnake8uC1R(data, step, size, points, length,
		alpha, beta, gamma, coeffUsage, win, criteria,
		calcGradient ? _CV_SNAKE_GRAD : _CV_SNAKE_IMAGE);
	//__END__;  
}
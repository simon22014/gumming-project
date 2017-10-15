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
	int scheme)         //确定图像能量场的数据选择，1为灰度，2为灰度梯度    
{
	int i, j, k;
	int neighbors = win.height * win.width;    //当前点领域中点的个数    

											   //当前点的位置    
	int centerx = win.width >> 1;
	int centery = win.height >> 1;

	float invn;        //n 的倒数？    
	int iteration = 0;     //迭代次数    
	int converged = 0;      //收敛标志，0为非收敛    

							//能量    
	float *Econt;    //    
	float *Ecurv;   //轮廓曲线能量    
	float *Eimg;    //图像能量    
	float *E;      //    

				   //αβγ的副本    
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

	//检点参数的合理性    
	/* check bad arguments */
	//if (src == NULL)  
	//  return CV_NULLPTR_ERR;  
	//if ((roi.height <= 0) || (roi.width <= 0))  
	//  return CV_BADSIZE_ERR;  
	//if (srcStep < roi.width)  
	//  return CV_BADSIZE_ERR;  
	//if (pt == NULL)  
	//  return CV_NULLPTR_ERR;  
	//if (n < 3)                         //轮廓点至少要三个    
	//  return CV_BADSIZE_ERR;  
	//if (alpha == NULL)  
	//  return CV_NULLPTR_ERR;  
	//if (beta == NULL)  
	//  return CV_NULLPTR_ERR;  
	//if (gamma == NULL)  
	//  return CV_NULLPTR_ERR;  
	//if (coeffUsage != CV_VALUE && coeffUsage != CV_ARRAY)  
	//  return CV_BADFLAG_ERR;  
	//if ((win.height <= 0) || (!(win.height & 1)))   //邻域搜索窗口得是奇数    
	//  return CV_BADSIZE_ERR;  
	//if ((win.width <= 0) || (!(win.width & 1)))  
	//  return CV_BADSIZE_ERR;  

	invn = 1 / ((float)n);        //轮廓点数n的倒数，用于求平均？    

	if (scheme == _CV_SNAKE_GRAD)
	{
		//X方向上和Y方向上的Scoble梯度算子，用于求图像的梯度,    
		//处理的图像最大尺寸为TILE_SIZE+2，此例为12，算子半长为3即{-3，-2，-1，0，1，2，3}    
		//处理后的数据类型为16位符号数,分别存放在_dx,_dy矩阵中,长度为10    
		//pX.init_deriv(TILE_SIZE + 2, CV_8UC1, CV_16SC1, 1, 0, 3);  
		//pY.init_deriv(TILE_SIZE + 2, CV_8UC1, CV_16SC1, 0, 1, 3);  
		//图像梯度存放缓冲区    
		gradient = (float *)cvAlloc(roi.height * roi.width * sizeof(float));

		//if (!gradient)  
		//return CV_OUTOFMEM_ERR;  
		//map用于标志相应位置的分块的图像能量是否已经求得    
		map = (uchar *)cvAlloc(map_width * map_height);
		//if (!map)  
		//{  
		//cvFree(&gradient);  
		//return CV_OUTOFMEM_ERR;  
		//}  
		/* clear map - no gradient computed */
		//清除map标志    
		memset((void *)map, 0, map_width * map_height);
	}
	//各种能量的存放处，取每点的邻域的能量    
	Econt = (float *)cvAlloc(neighbors * sizeof(float));
	Ecurv = (float *)cvAlloc(neighbors * sizeof(float));
	Eimg = (float *)cvAlloc(neighbors * sizeof(float));
	E = (float *)cvAlloc(neighbors * sizeof(float));
	//开始迭代    
	while (!converged)    //收敛标志无效时进行    
	{
		float ave_d = 0;  //轮廓各点的平均距离    
		int moved = 0;      //轮廓变形时，发生移动的数量    

		converged = 0;       //标志未收敛    
		iteration++;        //更新迭代次数+1    

							//计算轮廓中各点的平均距离    
							/* compute average distance */
							//从点0到点n-1的距离和    
		for (i = 1; i < n; i++)
		{
			int diffx = pt[i - 1].x - pt[i].x;
			int diffy = pt[i - 1].y - pt[i].y;

			ave_d += cvSqrt((float)(diffx * diffx + diffy * diffy));
		}
		//再加上从点n-1到点0的距离,形成回路轮廓    
		ave_d += cvSqrt((float)((pt[0].x - pt[n - 1].x) *
			(pt[0].x - pt[n - 1].x) +
			(pt[0].y - pt[n - 1].y) * (pt[0].y - pt[n - 1].y)));
		//求平均，得出平均距离    
		ave_d *= invn;
		/* average distance computed */


		//对于每个轮廓点进行特定循环迭代求解    
		for (i = 0; i < n; i++)
		{
			/* Calculate Econt */
			//初始化各个能量    
			float maxEcont = 0;
			float maxEcurv = 0;
			float maxEimg = 0;
			float minEcont = _CV_SNAKE_BIG;
			float minEcurv = _CV_SNAKE_BIG;
			float minEimg = _CV_SNAKE_BIG;
			float Emin = _CV_SNAKE_BIG;
			//初始化变形后轮廓点的偏移量    
			int offsetx = 0;
			int offsety = 0;
			float tmp;

			//计算边界    
			/* compute bounds */
			//计算合理的搜索边界，以防领域搜索超过ROI图像的范围    
			int left = MIN(pt[i].x, win.width >> 1);
			int right = MIN(roi.width - 1 - pt[i].x, win.width >> 1);
			int upper = MIN(pt[i].y, win.height >> 1);
			int bottom = MIN(roi.height - 1 - pt[i].y, win.height >> 1);
			//初始化Econt    
			maxEcont = 0;
			minEcont = _CV_SNAKE_BIG;
			//在合理的搜索范围内进行Econt的计算    
			for (j = -upper; j <= bottom; j++)
			{
				for (k = -left; k <= right; k++)
				{
					int diffx, diffy;
					float energy;
					//在轮廓点集的首尾相接处作相应处理,求轮廓点差分    
					if (i == 0)
					{
						diffx = pt[n - 1].x - (pt[i].x + k);
						diffy = pt[n - 1].y - (pt[i].y + j);
					}
					else
						//在其他地方作一般处理    

					{
						diffx = pt[i - 1].x - (pt[i].x + k);
						diffy = pt[i - 1].y - (pt[i].y + j);
					}
					//将邻域陈列坐标转成Econt数组的下标序号，计算邻域中每点的Econt    
					//Econt的值等于平均距离和此点和上一点的距离的差的绝对值（这是怎么来的？）    
					Econt[(j + centery) * win.width + k + centerx] = energy =
						(float)fabs(ave_d -
							cvSqrt((float)(diffx * diffx + diffy * diffy)));
					//求出所有邻域点中的Econt的最大值和最小值    
					maxEcont = MAX(maxEcont, energy);
					minEcont = MIN(minEcont, energy);
				}
			}
			//求出邻域点中最大值和最小值之差,并对所有的邻域点的Econt进行标准归一化,若最大值最小    
			//相等，则邻域中的点Econt全相等，Econt归一化束缚为0    
			tmp = maxEcont - minEcont;
			tmp = (tmp == 0) ? 0 : (1 / tmp);
			for (k = 0; k < neighbors; k++)
			{
				Econt[k] = (Econt[k] - minEcont) * tmp;
			}


			//计算每点的Ecurv    
			/*  Calculate Ecurv */
			maxEcurv = 0;
			minEcurv = _CV_SNAKE_BIG;
			for (j = -upper; j <= bottom; j++)
			{
				for (k = -left; k <= right; k++)
				{
					int tx, ty;
					float energy;
					//第一个点的二阶差分    
					if (i == 0)
					{
						tx = pt[n - 1].x - 2 * (pt[i].x + k) + pt[i + 1].x;
						ty = pt[n - 1].y - 2 * (pt[i].y + j) + pt[i + 1].y;
					}
					//最后一个点的二阶差分    
					else if (i == n - 1)
					{
						tx = pt[i - 1].x - 2 * (pt[i].x + k) + pt[0].x;
						ty = pt[i - 1].y - 2 * (pt[i].y + j) + pt[0].y;
					}
					//其余点的二阶差分    
					else
					{
						tx = pt[i - 1].x - 2 * (pt[i].x + k) + pt[i + 1].x;
						ty = pt[i - 1].y - 2 * (pt[i].y + j) + pt[i + 1].y;
					}
					//转换坐标为数组序号，并求各点的Ecurv的值,二阶差分后取平方    
					Ecurv[(j + centery) * win.width + k + centerx] = energy =
						(float)(tx * tx + ty * ty);
					//取最小的Ecurv和最大的Ecurv    
					maxEcurv = MAX(maxEcurv, energy);
					minEcurv = MIN(minEcurv, energy);
				}
			}
			//对Ecurv进行标准归一化    
			tmp = maxEcurv - minEcurv;
			tmp = (tmp == 0) ? 0 : (1 / tmp);
			for (k = 0; k < neighbors; k++)
			{
				Ecurv[k] = (Ecurv[k] - minEcurv) * tmp;
			}

			//求Eimg    
			/* Calculate Eimg */
			for (j = -upper; j <= bottom; j++)
			{
				for (k = -left; k <= right; k++)
				{
					float energy;
					//若采用灰度梯度数据    
					if (scheme == _CV_SNAKE_GRAD)
					{
						/* look at map and check status */
						int x = (pt[i].x + k) / WTILE_SIZE;
						int y = (pt[i].y + j) / WTILE_SIZE;
						//若此处的图像能量还没有获取，则对此处对应的图像分块进行图像能量的求解    
						if (map[y * map_width + x] == 0)
						{
							int l, m;

							/* evaluate block location */
							//计算要进行梯度算子处理的图像块的位置    
							int upshift = y ? 1 : 0;
							int leftshift = x ? 1 : 0;
							int bottomshift = MIN(1, roi.height - (y + 1)*WTILE_SIZE);
							int rightshift = MIN(1, roi.width - (x + 1)*WTILE_SIZE);
							//图像块的位置大小（由于原ROI不一定是8的倍数，所以图像块会大小不一）    
							CvRect g_roi = { x*WTILE_SIZE - leftshift, y*WTILE_SIZE - upshift,
								leftshift + WTILE_SIZE + rightshift, upshift + WTILE_SIZE + bottomshift };
							CvMat _src1;
							cvGetSubArr(&_src, &_src1, g_roi);  //得到图像块的数据    
																//分别对图像的X方向和Y方向进行梯度算子    
							cvSobel(&_src1, &_dx, 1, 0, 1);
							cvSobel(&_src1, &_dy, 1, 0, 1);
							//pX.process(&_src1, &_dx);  
							//pY.process(&_src1, &_dy);  
							//求分块区域中的每个点的梯度    
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
							//map相应位置置1表示此处图像能量已经获取    
							map[y * map_width + x] = 1;
						}
						//以梯度数据作为图像能量    
						Eimg[(j + centery) * win.width + k + centerx] = energy =
							gradient[(pt[i].y + j) * roi.width + pt[i].x + k];
					}
					else
					{
						//以灰度作为图像能量    
						Eimg[(j + centery) * win.width + k + centerx] = energy =
							src[(pt[i].y + j) * srcStep + pt[i].x + k];
					}
					//获得邻域中最大和最小的图像能量    
					maxEimg = MAX(maxEimg, energy);
					minEimg = MIN(minEimg, energy);
				}
			}
			//Eimg的标准归一化    
			tmp = (maxEimg - minEimg);
			tmp = (tmp == 0) ? 0 : (1 / tmp);

			for (k = 0; k < neighbors; k++)
			{
				Eimg[k] = (minEimg - Eimg[k]) * tmp;
			}
			//加入系数    
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
			//求得每个邻域点的Snake能量    
			for (k = 0; k < neighbors; k++)
			{
				E[k] = _alpha * Econt[k] + _beta * Ecurv[k] + _gamma * Eimg[k];
			}
			Emin = _CV_SNAKE_BIG;
			//获取最小的能量，以及对应的邻域中的相对位置    
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
			//如果轮廓点发生改变，则记得移动次数    
			if (offsetx || offsety)
			{
				pt[i].x += offsetx;
				pt[i].y += offsety;
				moved++;
			}
		}

		//各个轮廓点迭代计算完成后，如果没有移动的点了，则收敛标志位有效，停止迭代    
		converged = (moved == 0);
		//达到最大迭代次数时，收敛标志位有效，停止迭代    
		if ((criteria.type & CV_TERMCRIT_ITER) && (iteration >= criteria.max_iter))
			converged = 1;
		//到大相应精度时，停止迭代（与第一个条件有相同效果）    
		if ((criteria.type & CV_TERMCRIT_EPS) && (moved <= criteria.epsilon))
			converged = 1;
	}

	//释放各个缓冲区    
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
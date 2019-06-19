#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h> 
#pragma pack(1)

char fileName[100]	= "0.bmp";
int  grayDetail = 1;

typedef struct BmpPicHeader 
{
	unsigned char	bmpType[2];  //文件格式
	unsigned int	bmpSize;	 //文件大小
	unsigned short	bmpRes0;	 
	unsigned short	bmpRes1;
	unsigned int	bmpOffset;	 //偏移
}bmpHeader;

typedef struct BmpPicINFO
{
	unsigned int	bmpINFOSize;	
	int				width;					//宽度
	int				height;					//高度
	unsigned short	bmpPlanes;
	unsigned short  bmpBit;					//颜色位数
	unsigned int	bmpCompresion;
	unsigned int	bmpIMGSize;				//图像大小
	unsigned int	XPixPerMeter;			//X分辨率
	unsigned int	YPixPerMeter;			//Y分辨率
	unsigned int	bmpColorUsed;			//使用颜色
	unsigned int	bmpColorImportant;		//重要颜色
}bmpInfo;

typedef struct RGBColor 
{
	char rgbR;
	char rgbG;
	char rgbB;

}RGB;

void ReadBmpHeader(FILE *fl, bmpHeader * bmpH) 
{
	fseek(fl, 0L, SEEK_SET);
	fread(&bmpH->bmpType, 2L, 1, fl);
	fread(&bmpH->bmpSize, 4L, 1, fl);
	fread(&bmpH->bmpRes0, 2L, 1, fl);
	fread(&bmpH->bmpRes1, 2L, 1, fl);
	fread(&bmpH->bmpOffset, 4L, 1, fl);
	fseek(fl, 0L, SEEK_SET);
}

void ReadBmpInfo(FILE *fl, bmpInfo * bmpI)
{
	fseek(fl, 14, SEEK_SET);
	fread(&bmpI->bmpINFOSize, 4L, 1, fl);
	fread(&bmpI->width, 4L, 1, fl);
	fread(&bmpI->height, 4L, 1, fl);
	fread(&bmpI->bmpPlanes, 4L, 1, fl);
	fread(&bmpI->bmpBit, 4L, 1, fl);
	fread(&bmpI->bmpCompresion, 4L, 1, fl);
	fread(&bmpI->bmpIMGSize, 4L, 1, fl);
	fread(&bmpI->XPixPerMeter, 4L, 1, fl);
	fread(&bmpI->YPixPerMeter, 4L, 1, fl);
	fread(&bmpI->bmpColorUsed, 4L, 1, fl);
	fread(&bmpI->bmpColorImportant, 4L, 1, fl);
	fseek(fl, 0L, SEEK_SET);
}


void DrawGray(char rgbR,char rgbG,char rgbB) {
	/*if (rgb <= 0  && rgb >=-10) {
		printf(" ");
		return;
	}*/
	int R = rgbR;
	int G = rgbG;
	int B = rgbB;
	int temp = (R * 30 + G * 59 + B * 11) / 100;
	//char drawCol[13] = { ' ','-','*','=','c','o','e','N','M','R','K','G','@'};
	char drawCol[70] = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\|()1{}[]?-_+~<>i!lI;:,\"^'.  ";

	if (temp < 0) {
		temp *= -1;
	}
	//printf("%d ", temp);							
	temp /= grayDetail;
	if (temp > (CHAR_MAX /grayDetail/2)) {//增加颜色差异
		temp *= (grayDetail/1.85);
	}
	else if (temp < CHAR_MAX / grayDetail/2) {
		temp *= 0.2;
	}

	printf("%c", drawCol[69-temp]);
	//printf("%d ", temp);
}
void DrawPic(FILE *fl,bmpHeader *bmpH,bmpInfo *bmpI) 
{
	RGB			*rgbCT;

	rgbCT = (RGB*)malloc(sizeof(RGB));

	for (int i = 1; i <= bmpI->height; i++) 
	{
		fseek(fl, -((((bmpI->bmpBit * bmpI->width) + 31) >> 5) << 2)*i,SEEK_END);    //逐像素
		for (int j = 1; j <= bmpI->width; j++) 
		{
			fread(rgbCT, sizeof(RGB), 1, fl);
			if (rgbCT->rgbR == 0 && rgbCT->rgbG == 0 && rgbCT->rgbB == 0) 
			{
				printf(" ");
			}else
			{
				DrawGray(rgbCT->rgbR,rgbCT->rgbG,rgbCT->rgbB);
				//printf(" ");
			}
			
		}
		printf("\n");
		int temp = (	((((bmpI->bmpBit * bmpI->width) + 31) >> 5) << 2) -((bmpI->bmpBit  *  bmpI->width	)>>3));
		fseek(fl, temp, SEEK_CUR);//把读取点拉出来
	}

}
void main(void)
{
	FILE		*bmpFl;
	bmpHeader	*bmpHead;
	bmpInfo		*bmpInf;

	printf("输入抽象程度：");
	scanf("%d", &grayDetail);

	//读取图像
	if ((bmpFl = fopen(fileName, "rb")) == NULL) 
	{
		printf("打开失败！");
		exit(EXIT_FAILURE);
	}
	
	//ReadBmpHeader(bmpFl, &bmpHead);
	//ReadBmpInfo(bmpFl, &bmpInf);

	bmpHead = (bmpHeader*)malloc(sizeof(bmpHeader));
	if (!fread(bmpHead, sizeof(bmpHeader), 1, bmpFl)) {
		printf("这不是BMP文件！");
		exit(EXIT_FAILURE);
	}

	bmpInf = (bmpInfo*)malloc(sizeof(bmpInfo));
	if (!fread(bmpInf, sizeof(bmpInfo), 1, bmpFl)) {
		printf("这不是BMP文件！");
		exit(EXIT_FAILURE);
	}
		
	//printf("读取后位置：%d\n", ftell(bmpFl));
	//printf("文件格式：%c%cP\n", bmpHead->bmpType[0],bmpHead->bmpType[1]);
	//printf("文件大小：%d\n", bmpHead->bmpSize);
	printf("图像高度：%d\n",bmpInf->height);
	printf("图像宽度：%d\n", bmpInf->width);
	printf("使用颜色：%d\n", bmpInf->bmpColorUsed);
	printf("主要颜色：%d\n", bmpInf->bmpColorImportant);
	printf("MAXgray=%d\n正在生成...\n",CHAR_MAX);

	DrawPic(bmpFl, bmpHead, bmpInf);

	fclose(bmpFl);
}
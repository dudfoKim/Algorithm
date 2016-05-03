// ������ �ʿ��� ������� ����
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>
#include <memory.h>
#include <math.h>

// ��(x, y��)�� �ʿ��� ����ü ����
typedef struct Point
{
    float x,y;
}Point;

// ������ �ʿ��� �޼ҵ� ����
float y_minDistance(Point strip[], int n, float d);
float closest_Pair(Point *P,int n);
float calc_Distance(Point P1,Point P2);
float small(float a,float b);
int compareX(const void *a,const void *b);
int compareY(const void *a,const void *b);

void main()
{
	// ������ �ʿ��� ���� ���� �� �ʱ�ȭ
	int count = 0;
	int i =0;
	float result = 0;

	FILE* fop;
	FILE* fp;

	Point *p;
	p = (Point*)malloc(sizeof(Point));

	fp = fopen("data06.txt", "rt");
	fop = fopen("data06_out.txt", "wt");

	if(fp==NULL)
	{
		printf("***** Input file open error *****\n");

		return;
	}

	while(!feof(fp))
	{
		p = (Point*)realloc(p, sizeof(Point)*(count+1));

		// �ؽ�Ʈ ������ ��ǥ�� �Ҽ��� ���� �� �ڸ��̹Ƿ� �����߻�
		fscanf(fp, "%f %f,", &p[count].x, &p[count].y);
		count++;
	}

	printf("Reading the text file... \n");
	printf("Finish!\n");

	printf("\n=====Let's Calc closest pair of points!=====\n");

	qsort(p, count, sizeof(Point), compareX);

	// ������ x������ ������ ����� �ؽ�Ʈ ���Ϸ� ���(����°� ������ �׽�Ʈ �뵵)
	for(i=0; i<count; i++)
	{
		fprintf(fop, "%.3f %.3f\n,", p[i].x, p[i].y);
	}

	// ����� ���
    printf("Closest Pair Distance : %.3f\n\n", closest_Pair(p,count-1));
}

// 
float y_minDistance(Point newArray[], int n, float sigma)
{
    float y_min = sigma;
	int i = 0;
	int j = 0;

	// ���� y���� �������� ����
    qsort(newArray, n, sizeof(Point), compareY);
 
	// sigma�� y���� �Ÿ��� ���� ��, �ݺ��ؼ� ���ϸ鼭 ���� ���� ��ȯ
    for(i=0;i<n;i++)
	{
        j=i+1;

        while(j<n && (calc_Distance(newArray[i],newArray[j])<y_min))
		{
            y_min = small(y_min, calc_Distance(newArray[i],newArray[j]));
            j++;
        }
    }

    return y_min;
}

// �� ������ �ּ� �Ÿ��� ���ϴ� �޼ҵ�
float closest_Pair(Point *P,int n)
{
	int i = 0;
	int j = 0;
    float left =0;
	float right = 0;
	float sigma = 0;
	float y_min = 0;
	int mid = 0;
    Point *newArray;
	Point midPoint;

	// ���� ������ 3���� ���� ���� brute_force ������� ���� �Ÿ��� ���
    if(n<=3)
	{
        float error_distance = FLT_MAX;

        for(i=0;i<n;i++) 
		{
            for(j=i+1;j<n;j++) 
			{
                error_distance = small(error_distance, calc_Distance(P[i], P[j]));
            }
        }

        return error_distance;
    }

	// ���� ������ 3���� Ŭ ���� closest_Pair ������� �Ÿ��� ���
    mid = n/2;
    midPoint = P[n/2];

	/*
	x���� ������ ���� ���, �迭 �ε����� ���� �������� ���� ��,
	���� ��� �ɰ����鼭 �Ÿ��� �ּҰ�(sigma)�� ȹ��
	*/
    left = closest_Pair(P, mid);
    right = closest_Pair(P+mid, n-mid);
    sigma = small(left, right);
 
	newArray = (Point*)malloc(sizeof(Point));

    j=0;

	// ���� ������ �迭�� sigma���� ª�� �Ÿ�(���밪)�� ������ ����
    for(i=0;i<n;i++)
	{
        if(abs(midPoint.x-P[i].x)<sigma) 
		{
			newArray = (Point*)realloc(newArray, sizeof(Point)*(++i));
            newArray[j++]=P[i];
        }
    }
 
	// y������ ������ ���� ���� ��, sigma�� ���ؼ� ���� ���� ���
    y_min = y_minDistance(newArray,j,sigma);

    return small(y_min, sigma);
}

// �� �� ������ �Ÿ��� ����ϴ� �޼ҵ�
float calc_Distance(Point P1,Point P2)
{
    float result = (float)sqrt((P1.x-P2.x)*(P1.x-P2.x)+(P1.y-P2.y)*(P1.y-P2.y));

    return result;
}

// �� ���� ���� �޾� ���ؼ� �� ���� ���� ��ȯ�ϴ� �޼ҵ�
float small(float a,float b)
{
	return (a>=b)?b:a;
}

// �迭�� x���� �������� ������ �� ����ϴ� �޼ҵ�
int compareX(const void *a,const void *b)
{
	Point *p1 = (Point *)a, *p2 = (Point *)b;

	return (p1->x - p2->x);
}

// �迭�� y���� �������� ������ �� ����ϴ� �޼ҵ�
int compareY(const void *a,const void *b) 
{
	Point *p1 = (Point *)a, *p2 = (Point *)b;

	return (p1->y - p2->y);
}
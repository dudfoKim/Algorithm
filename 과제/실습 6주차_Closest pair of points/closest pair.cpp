// 구현에 필요한 헤더파일 선언
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <limits.h>
#include <memory.h>
#include <math.h>

// 점(x, y값)에 필요한 구조체 선언
typedef struct Point
{
    float x,y;
}Point;

// 구현에 필요한 메소드 선언
float y_minDistance(Point strip[], int n, float d);
float closest_Pair(Point *P,int n);
float calc_Distance(Point P1,Point P2);
float small(float a,float b);
int compareX(const void *a,const void *b);
int compareY(const void *a,const void *b);

void main()
{
	// 구현에 필요한 변수 선언 및 초기화
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

		// 텍스트 파일의 좌표는 소수점 이하 세 자리이므로 오차발생
		fscanf(fp, "%f %f,", &p[count].x, &p[count].y);
		count++;
	}

	printf("Reading the text file... \n");
	printf("Finish!\n");

	printf("\n=====Let's Calc closest pair of points!=====\n");

	qsort(p, count, sizeof(Point), compareX);

	// 점들을 x축으로 정렬한 결과를 텍스트 파일로 출력(입출력과 정렬의 테스트 용도)
	for(i=0; i<count; i++)
	{
		fprintf(fop, "%.3f %.3f\n,", p[i].x, p[i].y);
	}

	// 결과를 출력
    printf("Closest Pair Distance : %.3f\n\n", closest_Pair(p,count-1));
}

// 
float y_minDistance(Point newArray[], int n, float sigma)
{
    float y_min = sigma;
	int i = 0;
	int j = 0;

	// 점을 y축을 기준으로 정렬
    qsort(newArray, n, sizeof(Point), compareY);
 
	// sigma와 y값의 거리를 구한 후, 반복해서 비교하면서 작은 값을 반환
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

// 점 사이의 최소 거리를 구하는 메소드
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

	// 점의 갯수가 3보다 작을 때는 brute_force 방식으로 직접 거리를 계산
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

	// 점의 갯수가 3보다 클 때는 closest_Pair 방식으로 거리를 계산
    mid = n/2;
    midPoint = P[n/2];

	/*
	x축을 정렬한 값을 얻고, 배열 인덱스의 반을 기준으로 나눈 후,
	각각 계속 쪼개가면서 거리의 최소값(sigma)을 획득
	*/
    left = closest_Pair(P, mid);
    right = closest_Pair(P+mid, n-mid);
    sigma = small(left, right);
 
	newArray = (Point*)malloc(sizeof(Point));

    j=0;

	// 새로 선언한 배열에 sigma보다 짧은 거리(절대값)는 값들을 저장
    for(i=0;i<n;i++)
	{
        if(abs(midPoint.x-P[i].x)<sigma) 
		{
			newArray = (Point*)realloc(newArray, sizeof(Point)*(++i));
            newArray[j++]=P[i];
        }
    }
 
	// y축으로 정렬한 값을 얻어온 후, sigma와 비교해서 작은 값을 출력
    y_min = y_minDistance(newArray,j,sigma);

    return small(y_min, sigma);
}

// 두 점 사이의 거리를 계산하는 메소드
float calc_Distance(Point P1,Point P2)
{
    float result = (float)sqrt((P1.x-P2.x)*(P1.x-P2.x)+(P1.y-P2.y)*(P1.y-P2.y));

    return result;
}

// 두 수의 값을 받아 비교해서 더 작은 값을 반환하는 메소드
float small(float a,float b)
{
	return (a>=b)?b:a;
}

// 배열을 x값을 기준으로 정렬할 때 사용하는 메소드
int compareX(const void *a,const void *b)
{
	Point *p1 = (Point *)a, *p2 = (Point *)b;

	return (p1->x - p2->x);
}

// 배열을 y값을 기준으로 정렬할 때 사용하는 메소드
int compareY(const void *a,const void *b) 
{
	Point *p1 = (Point *)a, *p2 = (Point *)b;

	return (p1->y - p2->y);
}
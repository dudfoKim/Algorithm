#include "App.h"

int App_inputNumOfPoints (App * _this);
Bool App_inputPoints (App * _this) ;
Point * App_inputPoint (App * _this) ;
PointSet * App_points (App * _this) ;
void App_showPoints (App * _this) ;
void App_showClosestPair (App * _this) ;

int sel;

App * App_new()
{
	App * _this = NewObject (App) ;
	_this->points = NULL ;
	_this->fcp = NULL ;
	_this->closestPair = NULL ;
	
	return _this ;
}

void App_free (App * _this)
{
	PointSet_free (_this->points) ;
	FindClosestPair_free (_this->fcp) ;
	Pair_free (_this->closestPair) ;
	free (_this) ;
}

void App_run (App * _this)
{
	
	if (! App_inputPoints(_this) ) 
	{ // 입력 받기
		printf("오류: 점들이 적절히 입력되지 않았습니다.\n") ;
	}
	
	else 
	{
		App_showPoints (_this) ;
		printf("\nClosest Pair 찾기를 시작합니다.\n") ;
		_this->fcp = FindClosestPair_new (App_points(_this)) ; // fcp 객체의 생성
		
		_this->closestPair = FindClosestPair_run (_this->fcp) ; // closestPair를 찾는다
	
		App_showClosestPair (_this) ;
	
		printf("\nClosest Pair 찾기를 성공적으로 완료하였습니다.\n") ;
	}
	
	printf("프로그램을 종료합니다.\n") ;
}

int App_inputNumOfPoints (App * _this)
{
	int max;
	printf("점의 개수를 입력해 주세요 : ");
	scanf("%d", &max);
	printf("자동생성 = 1, 수동생성 = othernumber : ");
	scanf("%d", &sel);
	_this->points=PointSet_new (max);

	return max;
	//입력 받을 점의 개수를 입력 받는다.
}

Bool App_inputPoints (App * _this) 
{
	App_inputNumOfPoints (_this);
	
	if(sel==1)
	{
		printf("\n점을 생성합니다.(x, y)\n");
		srand((unsigned int)time(NULL));
	}
	while(!PointSet_isFull(_this->points))
	{
		
		App_inputPoint(_this);
	}
	return T;
	//키보드로부터 점들을 입력 받는다.
	//하나 이상의 점을 정상적으로 입력 받았으면 TRUE, 아니면 FALSE를 얻는다.
}
Point * App_inputPoint (App * _this) 
{
	Point * p;
	int x, y;
	
	if(sel==1)
	{	
		x=rand()%(100);
		y=rand()%(100);
	}
	else
	{
		printf("점을 입력하세요 (x, y) : ");
		scanf("%d %d", &x, &y);
	}

	
	p=Point_newWithXYCoordinates (x, y);

	PointSet_addPoint (_this->points, p) ;
	//한 개의 점을 입력 받는다.
	return ;
}

PointSet * App_points (App * _this) 
{
	return _this->points;
	//현재 가지고 있는 점들의 집합 객체의 포인터를 얻는다.
}

void App_showPoints (App * _this) 
{
	int i=0;
	printf("\n현재 가지고 있는 점들\n");
	
	while(i<_this->points->maxSize)
	{
		printf("(%0.f %0.f)\t", _this->points->body[i]->x, _this->points->body[i]->y);
		i++;
	}
	//현재 가지고 있는 점들을 (화면에) 출력하여 보여준다.
}

void App_showClosestPair (App * _this) 
{
	
	printf("\n최단거리쌍\n");
	
	
	
	printf("\n(%lf %lf), ", _this->closestPair->point1->x, _this->closestPair->point1->y);
	printf("(%lf %lf)\n", _this->closestPair->point2->x, _this->closestPair->point2->y);
	printf("\nDistance=%f\n", Point_distanceTo(_this->closestPair->point1, _this->closestPair->point2)) ;
		
	
	//현재 가지고 있는 최단거리쌍 closestPair를 (화면에) 출력하여 보여준다.
}
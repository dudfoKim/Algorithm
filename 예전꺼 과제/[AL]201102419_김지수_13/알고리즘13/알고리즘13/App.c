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
	{ // �Է� �ޱ�
		printf("����: ������ ������ �Էµ��� �ʾҽ��ϴ�.\n") ;
	}
	
	else 
	{
		App_showPoints (_this) ;
		printf("\nClosest Pair ã�⸦ �����մϴ�.\n") ;
		_this->fcp = FindClosestPair_new (App_points(_this)) ; // fcp ��ü�� ����
		
		_this->closestPair = FindClosestPair_run (_this->fcp) ; // closestPair�� ã�´�
	
		App_showClosestPair (_this) ;
	
		printf("\nClosest Pair ã�⸦ ���������� �Ϸ��Ͽ����ϴ�.\n") ;
	}
	
	printf("���α׷��� �����մϴ�.\n") ;
}

int App_inputNumOfPoints (App * _this)
{
	int max;
	printf("���� ������ �Է��� �ּ��� : ");
	scanf("%d", &max);
	printf("�ڵ����� = 1, �������� = othernumber : ");
	scanf("%d", &sel);
	_this->points=PointSet_new (max);

	return max;
	//�Է� ���� ���� ������ �Է� �޴´�.
}

Bool App_inputPoints (App * _this) 
{
	App_inputNumOfPoints (_this);
	
	if(sel==1)
	{
		printf("\n���� �����մϴ�.(x, y)\n");
		srand((unsigned int)time(NULL));
	}
	while(!PointSet_isFull(_this->points))
	{
		
		App_inputPoint(_this);
	}
	return T;
	//Ű����κ��� ������ �Է� �޴´�.
	//�ϳ� �̻��� ���� ���������� �Է� �޾����� TRUE, �ƴϸ� FALSE�� ��´�.
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
		printf("���� �Է��ϼ��� (x, y) : ");
		scanf("%d %d", &x, &y);
	}

	
	p=Point_newWithXYCoordinates (x, y);

	PointSet_addPoint (_this->points, p) ;
	//�� ���� ���� �Է� �޴´�.
	return ;
}

PointSet * App_points (App * _this) 
{
	return _this->points;
	//���� ������ �ִ� ������ ���� ��ü�� �����͸� ��´�.
}

void App_showPoints (App * _this) 
{
	int i=0;
	printf("\n���� ������ �ִ� ����\n");
	
	while(i<_this->points->maxSize)
	{
		printf("(%0.f %0.f)\t", _this->points->body[i]->x, _this->points->body[i]->y);
		i++;
	}
	//���� ������ �ִ� ������ (ȭ�鿡) ����Ͽ� �����ش�.
}

void App_showClosestPair (App * _this) 
{
	
	printf("\n�ִܰŸ���\n");
	
	
	
	printf("\n(%lf %lf), ", _this->closestPair->point1->x, _this->closestPair->point1->y);
	printf("(%lf %lf)\n", _this->closestPair->point2->x, _this->closestPair->point2->y);
	printf("\nDistance=%f\n", Point_distanceTo(_this->closestPair->point1, _this->closestPair->point2)) ;
		
	
	//���� ������ �ִ� �ִܰŸ��� closestPair�� (ȭ�鿡) ����Ͽ� �����ش�.
}
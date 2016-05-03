#include "WIScheduling.h"

WIScheduling* WIScheduling_new()
{
	WIScheduling* temp = NewObject(WIScheduling);

	return temp;

}
void WIScheduling_free(WIScheduling * _this)
{
	//free(_this->m);
	//free(_this->p);
	//free(_this->select);
	//free(_this->weightedInterval);
	free(_this);

}
Bool WIScheduling_input(WIScheduling * _this)
{
	int i=0;
	printf("Interval의 갯수를 입력하세요 : ");
	
	scanf("%d", &_this->intnumOfIntervals);

	while(i < _this->intnumOfIntervals)
	{
		while(1)
		{
			printf("%d번째 Interval을 입력하세요 : [start] [finish] [weight]", i);
			scanf("%d %d %d", &_this->weightedInterval[i].start, &_this->weightedInterval[i].finish, &_this->weightedInterval[i].weight);
			if(_this->weightedInterval[i].start < _this->weightedInterval[i].finish)
			{
				break;
			}
		}
		i++;
	}

}

void WIScheduling_computeOpt(WIScheduling* _this)
{
	int i, j;
	int sum;

	for (i=1;i<= _this->intnumOfIntervals+1;i++)
		_this->m[i]=_this->select[i]=0;

	sum=_this->sumKeep=0;
	while (1)
	{
		for (i=0;_this->m[i];i++)
		{
			sum-=_this->weightedInterval[i].weight;
			_this->m[i]=0;
		}
		if (i==_this->intnumOfIntervals+1)  
			break;

		sum+=_this->weightedInterval[i].weight;
		_this->m[i]=1;

		for (j=i+1;j<=_this->intnumOfIntervals;j++)
			if (_this->m[j])  
				if (i<=_this->p[j])  
					i=j;      
				else
					break;   

		if (j>_this->intnumOfIntervals && sum>_this->sumKeep) 
		{
			_this->sumKeep=sum;
			for (i=1;i<=_this->intnumOfIntervals;i++)
				_this->select[i]=_this->m[i];
		}
	}

}
void WIScheduling_showResults(WIScheduling* _this)
{
	int i;
	printf("start finish weight\n");
	for (i=0;i< _this->intnumOfIntervals;i++)
	{
		if (_this->select[i])
		{
			printf("%d %d %d",_this->weightedInterval[i].start,_this->weightedInterval[i].finish,_this->weightedInterval[i].weight);
			printf("\n");
		}
	}

	
}

void WIScheduling_computeP(WIScheduling* _this)
{
	int i;
	for (i=0;i<_this->intnumOfIntervals;i++)
		_this->p[i] = WIScheduling_qsort(_this,_this->intnumOfIntervals,_this->weightedInterval[i].start);

}
int WIScheduling_qsort(WIScheduling* _this,int n,int key)
{
	int low,high,mid;
	low=0;
	high=n-1;

	while (low<=high)
	{
		mid=(low+high)/2;
		if (_this->weightedInterval[mid].finish <=key)
			low=mid+1;
		else
			high=mid-1;
	}
	return high;


}
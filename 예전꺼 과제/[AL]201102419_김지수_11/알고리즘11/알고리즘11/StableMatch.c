#include "StableMatch.h"
#include <Windows.h>
#include <time.h>

StableMatch* StableMatch_new()
{
	StableMatch *temp=NewObject(StableMatch);
	
	temp->current=NULL;
	temp->freeMan=NULL;
	temp->manPref=NULL;
	temp->nex=NULL;
	temp->numOfPairs=0;
	temp->ranking=NULL;
	temp->womanPref=NULL;

	return temp;
}

void StableMatch_free(StableMatch* _this)
{
	free(_this->nex);
	free(_this->current);
	free(_this->manPref);
	free(_this->womanPref);
	free(_this->ranking);
	free(_this);
}

void StableMatch_runGS(StableMatch* _this)
{
	int i=0;
	Person m, w, currentMan;
	StableMatch_initGS(_this);
	
	while (!LinkedList_isEmpty(_this->freeMan)) 
	{
		
		m = LinkedList_delete(_this->freeMan);
		w = _this->manPref[m][_this->nex[m]++];
		currentMan= _this->current[w];
	
		if (currentMan== NONE) // w is free
			_this->current[w] = m;
	
		else if (_this->ranking[w][m] < _this->ranking[w][currentMan])
		{
			// w preferesm to currentMan
			_this->current[w] = m;
			LinkedList_add(_this->freeMan,currentMan);
		}
	
		else 
		{ // w rejects m
			LinkedList_add(_this->freeMan,m);
		}
	}
} //end of StableMatch_runGS()

void StableMatch_initGS(StableMatch* _this)
{
	int w, m, rank,i=0;
	
	_this->ranking=NewVector(int*, _this->numOfPairs);
	_this->current=NewVector(int, _this->numOfPairs);
	_this->nex=NewVector(int, _this->numOfPairs);
	_this->freeMan=LinkedList_new () ;
	
	i=0;
	
	while(i<_this->numOfPairs)
	{
		_this->ranking[i]=NewVector(int, _this->numOfPairs);
		i++;
	}
	
	i=0;
	for ( w=0 ; w< _this->numOfPairs; w++ )
	{
		for ( rank=0 ; rank<_this->numOfPairs; rank++ ) 
		{
			m = _this->womanPref[w][rank] ;
			_this->ranking[w][m]= rank ;
		}
	}
	
	i=0;
	while(i<_this->numOfPairs)
	{
		LinkedList_add(_this->freeMan, i);
		i++;
	}

	
	i=0;
	while(i<_this->numOfPairs)
	{
		_this->current[i]=-1;
		i++;
	}

	i=0;
	while(i<_this->numOfPairs)
	{
		_this->nex[i]=0;
		i++;
	}
	//ranking[][]�������ϰ��ʱ�ȭ����.
	//linked list��freeMan�������ϰ��ʱ�ȭ����.
	//��糲�ڸ�freeMan�������س��´�.
	//current[]�������ϰ��ʱ�ȭ����.
	//��翩�ڸ�NONE�����س��´�.
}

void StableMatch_generateTestData(StableMatch* _this , int testSize)
{
	int currentWoman, randomWoman, randomWomanPref, currentMan, randomMan, randomManPref, i=0, j=0, m=0;
	
	_this->numOfPairs=testSize;
	_this->manPref=NewVector(int*, _this->numOfPairs);
	_this->womanPref=NewVector(int*, _this->numOfPairs);
	
	while(i<_this->numOfPairs)
	{
		_this->manPref[i]=NewVector(int,_this->numOfPairs);
		_this->womanPref[i]=NewVector(int,_this->numOfPairs);
		i++;
	}
	i=0;
	while(i<testSize)
	{
		j=0;
		while(j<testSize)
		{
			_this->womanPref[i][j]=j;
			_this->manPref[i][j]=j;
			j++;
		}
		i++;
	}
	srand((unsigned int)time(NULL));
	while(m<testSize)
	{
		

		for (currentWoman= 0 ; currentWoman< testSize; currentWoman++) 
		{
			_this->manPref[m][currentWoman] = currentWoman;

			for (currentWoman= 0 ; currentWoman< testSize; currentWoman++) 
			{
				randomWoman= rand()%(testSize-1);//0����(testSize-1)�����Ǽ��ڸ�random�ϰԻ�������;
				randomWomanPref= _this->manPref[m][randomWoman] ;
				_this->manPref[m][randomWoman] = _this->manPref[m][currentWoman] ;
				_this->manPref[m][currentWoman] = randomWomanPref;
			}
		}

		for (currentMan= 0 ; currentMan< testSize; currentMan++) 
		{
			_this->womanPref[m][currentMan] = currentMan;

			for (currentMan= 0 ; currentMan< testSize; currentMan++) 
			{
				randomMan=rand()%(testSize-1);//0����(testSize-1)�����Ǽ��ڸ�random�ϰԻ�������;
				randomManPref= _this->womanPref[m][randomMan] ;
				_this->womanPref[m][randomMan] = _this->womanPref[m][currentMan] ;
				_this->womanPref[m][currentMan] = randomManPref;
			}
		}
		m++;
	}
}

void StableMatch_showPerformanceMeasure(StableMatch* _this , double duration)
{
	printf("����¦�ǰ���: %d, �����ð�: %lf nanoseconds\n", _this->numOfPairs, duration);
}
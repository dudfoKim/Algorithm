#include "StableMatch.h"

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
	//free(_this->next);
	//free(_this->current);
	//free(_this->manPref);
	//free(_this->womanPref);
	//free(_this->ranking);
	free(_this);
}

Bool StableMatch_input(StableMatch* _this)
{
	int i=0,j;
	
	printf("Pair ���� �Է��ϼ��� : ");
	scanf("%d", &_this->numOfPairs);

	_this->manPref=NewVector(int*, _this->numOfPairs);
	_this->womanPref=NewVector(int*, _this->numOfPairs);
	
	while(i<_this->numOfPairs)
	{
		_this->manPref[i]=NewVector(int,_this->numOfPairs);
		_this->womanPref[i]=NewVector(int,_this->numOfPairs);
		i++;
	}


	i=0;
	
	while(i<_this->numOfPairs)
	{
		j=0;
		while(j<_this->numOfPairs)
		{
			printf("input %d manPref to woman %d : ", i, j);
			printf("%d\n", j);
			_this->manPref[i][j]=j;
			//scanf("%d", &_this->manPref[i][j]);
			
			j++;
		}
		i++;
	}
	i=0;
	while(i<_this->numOfPairs)
	{
		j=0;
		while(j<_this->numOfPairs)
		{
			
			printf("input %d womanPref to man %d : ", i, j);
			printf("%d\n", j);
			_this->womanPref[i][j]=j;
			//scanf("%d", &_this->womanPref[i][j]);
			j++;
		}
		i++;
	}
	
	return T;


	
	
}

void StableMatch_showResults(StableMatch* _this)
{
	int j,i=0;
	
	printf("manPref\n");
	while(i<_this->numOfPairs)
	{
		j=0;
		
		while(j<_this->numOfPairs)
		{
			printf("%d ", _this->manPref[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}

	i=0;
	printf("womanPref\n");
	while(i<_this->numOfPairs)
	{
		j=0;
		
		while(j<_this->numOfPairs)
		{
			printf("%d ", _this->womanPref[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	
	i=0;
	printf("ranking\n");
	while(i<_this->numOfPairs)
	{
		j=0;
		
		while(j<_this->numOfPairs)
		{
			
			printf("%d ", _this->ranking[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}

	printf("couple\n");
	i=0;
	while(i<_this->numOfPairs)
	{
		printf("woman %d and man %d\n", i, _this->current[i]);
		i++;
	}

			
	
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
	//printf("%d", _this->freeMan->head->e);
	//printf("%d", _this->freeMan->head->next->e);
	//printf("<%d>", _this->freeMan->length);
	//printf("%d", _this->freeMan->head->next->next->e);
	

	
	
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
#include "RandomGen.h"

struct _RandomGen
{
	long maxSize ; // (������ �ִ밪 - 1)
} ;

RandomGen * RandomGen_new ()
{
	RandomGen * _this = NewObject(RandomGen) ; // ��ü ����
	_this ->maxSize = MaxSize-1 ; // (������ �ִ밪 - 1)
	srand ( (unsigned) time(NULL) ) ; // ���� ���� �ʱ�ȭ
	return _this ;
}

void RandomGen_free (RandomGen * _this)
{
	free (_this) ;
}

unsigned long RandomGen_number (RandomGen * _this)
{
	long systemRandomNumber = (long) rand() ;
	if (_this->maxSize > SYS_MAX_RAND)
	{
		systemRandomNumber = systemRandomNumber * (SYS_MAX_RAND +1) + (long) rand() ;
	}
	
	return systemRandomNumber % _this->maxSize ;
}

double RandomGen_probability (RandomGen * _this)
{
	return ( (double) RandomGen_number(_this) / (double) _this->maxSize ) ;
}
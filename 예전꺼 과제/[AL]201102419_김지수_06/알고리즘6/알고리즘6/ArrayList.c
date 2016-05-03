#include "ArrayList.h"

#define List_INIT_LENGTH 10 ;





ArrayList * ArrayList_new ()
{
	ArrayList * _this = NewObject(ArrayList) ;
	_this ->maxLength = List_INIT_LENGTH ;
	_this->body = NewVector(Element, _this->maxLength) ;
	// 리스트의 원소를 저장할 배열 list->body[]를 생성
	_this->length = 0 ; // 방금 만들었으므로, 현재 빈 리스트임.
	
	return _this ;
}

void ArrayList_free (ArrayList * _this)
{
	free(_this->body) ; // 배열부터 소멸
	free(_this) ; // 그 다음, 객체 소멸
}

Bool ArrayList_expandLengthInDouble (ArrayList * _this)
{
	int i=0;
	Element * newBody = NewVector(Element, _this->maxLength*2) ;
	// 두 배 길이의 새로운 배열을 생성
	if (newBody == NULL) 
	{
		return F ; // Error in malloc(). 메모리 부족
	}
	else 
	{
		while(i<_this->length)
		{
			// 여기를 채우시오
			newBody[i]=_this->body[i];
			i++;
		}
		// 원래 배열의 내용을 새로운 배열로 복사하여 옮긴다.
		free(_this->body) ; // 원래 배열을 소멸시킨다
		_this->body = newBody ;
		_this->maxLength=(_this->maxLength)*2;
		// 새로운 배열을 list의 배열로 설정한다.
		return T ;
	}
}

Bool ArrayList_isFull (ArrayList * _this)
{
	if(_this->length==_this->maxLength)
	{
		return T;
	}
	return F;// 리스트가 Full 이면 TRUE, 아니면 FALSE를 return 한다.
	// 여기를 채우시오.
}

int ArrayList_length(ArrayList * _this)
{
	return _this->length;// 리스트의 length를 return 한다.
	// 여기를 채우시오.
}

Bool ArrayList_add(ArrayList * _this, Element e)
{
	if ( ArrayList_isFull(_this) ) 
	{
// 리스트가 full 이면 FALSE를 return 한다.
		return F;
	}
	
	else 
	{
		_this->body[_this->length]=e;
		_this->length++;
		// Full이 아니므로, 원소 e를 리스트에 삽입한다.
		// 여기를 채우시오.
		return T;
	}
}

Element ArrayList_elementAtIndex(ArrayList * _this, int givenIndex)
{
	// givenIndex는 리스트의 길이보다 작다고 가정한다.
	// 그러므로 이 call을 하기 전에 반드시 givenIndex의 범위를 검사해야 한다.
	return _this->body[givenIndex] ;
}
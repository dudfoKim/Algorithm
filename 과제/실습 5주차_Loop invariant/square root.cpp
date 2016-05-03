#include <stdio.h>

// c언어 내부에서의 최대값 범위를 정해주기 위한 상수 정의
#define MAX 2147483647
#define ROOT_MAX 46340

// 메소드 선언
int fast_way(int n, int left, int right);
int slow_way(int n);

void main()
{
	int value;

	// 제곱근을 구하기 위한 숫자를 입력받는다
	printf("Input the number : ");
	scanf("%d", &value);

	// 두 개의 다른 방법으로 제곱근을 구한다.
	printf("\nThis is Fast way for search square root\n");
	printf("fast way : %d\n\n", fast_way(value, 0, ROOT_MAX));

	printf("\nAnother, slow way..!\n");
	printf("slow way : %d\n\n", slow_way(value));
}

// 제곱근을 찾는 효율적인 방법(제곱수가 아닐 경우 근사값 출력)
int fast_way(int n, int left, int right)
{
	int result = -1;

	while(n<=MAX)
	{
		int mid = (left+right)/2;

		if(left==right)
		{
			result = mid-1;
			break;
		}
		if(n<mid*mid)
		{
			right = mid;
		}
		else if(n>=mid*mid)
		{
			left = mid+1;
		}
	}

	return result;
}

// 제곱근을 찾는 단순한 방법(제곱수가 아닐 경우 -1 출력)
int slow_way(int n)
{
	int mult = 1;
	int root = 0;

	while(mult<=n)
	{
		root++;
		mult = mult + 2*root + 1;
	}

	return root;
}
#include <stdio.h>

// c��� ���ο����� �ִ밪 ������ �����ֱ� ���� ��� ����
#define MAX 2147483647
#define ROOT_MAX 46340

// �޼ҵ� ����
int fast_way(int n, int left, int right);
int slow_way(int n);

void main()
{
	int value;

	// �������� ���ϱ� ���� ���ڸ� �Է¹޴´�
	printf("Input the number : ");
	scanf("%d", &value);

	// �� ���� �ٸ� ������� �������� ���Ѵ�.
	printf("\nThis is Fast way for search square root\n");
	printf("fast way : %d\n\n", fast_way(value, 0, ROOT_MAX));

	printf("\nAnother, slow way..!\n");
	printf("slow way : %d\n\n", slow_way(value));
}

// �������� ã�� ȿ������ ���(�������� �ƴ� ��� �ٻ簪 ���)
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

// �������� ã�� �ܼ��� ���(�������� �ƴ� ��� -1 ���)
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
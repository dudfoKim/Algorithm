#include "sort_time.h"

int main(){

	/* �Լ� ���� �ش��ϴ� ���� ������ �߻��Ͽ�, �� ���Ŀ� ���� �ð��ֱ� ��� */
	sortTest(bubbleData, insertionData, quickData, 1000);
	sortTest(bubbleData, insertionData, quickData, 5000);
	sortTest(bubbleData, insertionData, quickData, 10000);
	sortTest(bubbleData, insertionData, quickData, 15000);
	sortTest(bubbleData, insertionData, quickData, 20000);
	sortTest(bubbleData, insertionData, quickData, 25000);
	sortTest(bubbleData, insertionData, quickData, 30000);
	return 0;
}
	










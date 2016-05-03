#include "sort_time.h"

int main(){

	/* 함수 끝에 해당하는 수의 난수를 발생하여, 각 정렬에 대한 시간주기 계산 */
	sortTest(bubbleData, insertionData, quickData, 1000);
	sortTest(bubbleData, insertionData, quickData, 5000);
	sortTest(bubbleData, insertionData, quickData, 10000);
	sortTest(bubbleData, insertionData, quickData, 15000);
	sortTest(bubbleData, insertionData, quickData, 20000);
	sortTest(bubbleData, insertionData, quickData, 25000);
	sortTest(bubbleData, insertionData, quickData, 30000);
	return 0;
}
	










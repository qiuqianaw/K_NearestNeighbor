#include "kNN.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define K 5

int main() {
	
	//����ѵ������ 
	int N, D;
	double **sampleData = NULL;  //��������
	double **distanceAndResult = NULL; // K�ڽ���� ���� �� ��ǩ
	loadData(&N, &D, &sampleData, &distanceAndResult);
	
while(1) {

	//����������� 
    double *testData=(double *)malloc((D-1)*sizeof(double));
    printf("����һ�����ݣ���������Ӧ�ð���% d��ά��:\n", D-1);
    for ( int i = 0; i < D-1; i++ ) {
	    scanf("%lf", &testData[i]);//��ȡ��������
	}
    
    //д�����ͽ�� 
	writeDistanceAndResult(K, distanceAndResult, N, D, testData, sampleData);
    //����Ȼ��ȡֵ���� 
    qsort(*distanceAndResult, K, sizeof(double), cmp);
    //���� 
    findMeet(distanceAndResult, sampleData, &testData, K, N, D);
	//test�����ڲ鿴����������ΧK��ֵ�ľ���ͽ�� 
    test(distanceAndResult);//��Kֵ����ʱ�벻Ҫ����test�������������̨��ӡʱ���ܳ� 
	//���ش� 
    getResult(Search(K,distanceAndResult[1]));
    
}
	return 0;
	
}

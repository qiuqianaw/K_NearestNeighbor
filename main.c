#include "kNN.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define K 5

int main() {
	
	//读入训练数据 
	int N, D;
	double **sampleData = NULL;  //数据数组
	double **distanceAndResult = NULL; // K邻近点的 距离 及 标签
	loadData(&N, &D, &sampleData, &distanceAndResult);
	
while(1) {

	//读入测试数据 
    double *testData=(double *)malloc((D-1)*sizeof(double));
    printf("输入一组数据，该组数据应该包含% d个维度:\n", D-1);
    for ( int i = 0; i < D-1; i++ ) {
	    scanf("%lf", &testData[i]);//读取测试数据
	}
    
    //写入距离和结果 
	writeDistanceAndResult(K, distanceAndResult, N, D, testData, sampleData);
    //排序，然后取值分析 
    qsort(*distanceAndResult, K, sizeof(double), cmp);
    //分析 
    findMeet(distanceAndResult, sampleData, &testData, K, N, D);
	//test，便于查看样本数据周围K个值的距离和结果 
    test(distanceAndResult);//当K值过大时请不要启用test函数，否则控制台打印时间会很长 
	//返回答案 
    getResult(Search(K,distanceAndResult[1]));
    
}
	return 0;
	
}

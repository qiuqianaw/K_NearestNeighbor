#include "kNN.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define K 5

//读取样本数据 
void loadData(int *n, int *d, double ***sampleData, double ***distanceAndResult) {
	FILE *fp;
	fp=fopen("./data/data_cancer.txt", "r");
	
	if ( fp == NULL ) {
    	fprintf(stderr, "无法读取样本数据\n");
    	return; 
	}    
    if ( fscanf(fp, "N=%d,D=%d", n, d) != 2 ) {
    	fprintf(stderr, "数据出错\n");
    	return;
	}
	
    *sampleData=createArray(*n, *d);
    *distanceAndResult=createArray(2, K);

    for ( int i = 0; i < *n; i++ ) {
    	for ( int j = 0; j < *d; j++ ) {
    		fscanf(fp, "%lf", &(*sampleData)[i][j]);//读取数据
		}
	}

	//对distanceAndResult进行操作，默认最大值 
    for ( int i = 0; i < 2; i++ ) {
    	for ( int j = 0; j < K; j++ ) {
    		(*distanceAndResult)[i][j] = INT_MAX;
		}
	}
	
	//样本数据读取失败 
	if ( fclose(fp) ) {
    	fprintf(stderr, "无法读取样本数据");
    	return;
	}
	printf("数据读入完成\n");

}

//动态申请数组 
double **createArray(int n, int m) {
    double **sampleData;
    sampleData = (double **)malloc(n*sizeof(double *));
    sampleData[0] = (double *)malloc(n*m*sizeof(double));
    for ( int i = 1; i < n; i++ ) {
    	sampleData[i] = sampleData[i-1] + m;
	}
    return sampleData;
}

//初始化distanceAndResult数组
//distanceAndResult[0][i]存储距离
//distanceAndResult[1][i]存储标签 
void writeDistanceAndResult(int n, double **distanceAndResult, int N, int D, double *testData, double **sampleData) {
	for ( int i = 0; i < n; i++ ){
        if ( n > N ) {
        	printf("K取值错误！(0<k<N)");
        	exit(-1);
		}
        distanceAndResult[0][i] = computeDistance(D-1, testData, sampleData[i]);
        distanceAndResult[1][i] = sampleData[i][D-1];
    }
} 

int cmp(const void *a, const void *b) {
	return *(int*)b - *(int*)a;//升序 
}

//K值后面，比K值所对应的顺序的距离小的值，放到K的前面 
void findMeet(double **distanceAndResult, double **sampleData, double **testData, int n,  int N, int D) {
    //初始化k近邻数组的距离最大值
	double maxDistance = distanceAndResult[0][n-1];
    double distance;
    for ( int i = n; i < N; i++ ){
        distance = computeDistance(D-1, *testData, sampleData[i]);
        if ( distance < maxDistance ) {
        	for ( int j = 0; j < n; j++ ) {
                if ( distance < distanceAndResult[0][j] ) {
                	//j后元素复制到后一位，为插入做准备
                    for ( int k = n-1; k > j; k-- ) { 
                        distanceAndResult[0][k] = distanceAndResult[0][k-1];
                        distanceAndResult[1][k] = distanceAndResult[1][k-1];
                    }
                    //插入到j位置
                    distanceAndResult[0][j] = distance;  
                    distanceAndResult[1][j] = sampleData[i][D-1];
                    break;
                }
            }
		}
        maxDistance = distanceAndResult[0][n-1];
    }
}

void test(double **distanceAndResult) {
//    distanceAndResult[0][i]存储距离
//	distanceAndResult[1][i]存储标签 
	for ( int i = 0; i < K; i++ ) {
    	printf("distanceAndResult:%6.2f  %6.0f\n", 
			distanceAndResult[0][i],
			distanceAndResult[1][i]
		);
	}
}

//统计出现次数最多的结果 
//temp[数值]=次数 
double Search(int len, double *a) {
	int tmp[100] = {0};
	int key = 0;
	double max = 0;
	double index=0;
	for ( int i = 0; i < len; i++ ) {
		key = a[i];
		tmp[key]++;
	}
	for ( int i = 0; i < 100; i++ ) {
		if (max < tmp[i]) {
			max = tmp[i];
			index=i;
		}
	}
	printf("\n出现频率最大的标签为%.0f\n", index);
	return index;
}

void getResult(double ans) {
	printf("\n------------------------------------------------------------预测该未知样本类别为: %.0f\n\n", ans );
}

double computeDistance(int n, double *a, double *b) {
    double distance=0;
    for ( int i = 0; i < n; i++ ) {
    	distance += pow( a[i] - b[i], 2 );
	}
	double ans = sqrt(distance);
    return ans;
}



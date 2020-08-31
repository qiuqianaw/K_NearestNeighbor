#include "kNN.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define K 5

//��ȡ�������� 
void loadData(int *n, int *d, double ***sampleData, double ***distanceAndResult) {
	FILE *fp;
	fp=fopen("./data/data_cancer.txt", "r");
	
	if ( fp == NULL ) {
    	fprintf(stderr, "�޷���ȡ��������\n");
    	return; 
	}    
    if ( fscanf(fp, "N=%d,D=%d", n, d) != 2 ) {
    	fprintf(stderr, "���ݳ���\n");
    	return;
	}
	
    *sampleData=createArray(*n, *d);
    *distanceAndResult=createArray(2, K);

    for ( int i = 0; i < *n; i++ ) {
    	for ( int j = 0; j < *d; j++ ) {
    		fscanf(fp, "%lf", &(*sampleData)[i][j]);//��ȡ����
		}
	}

	//��distanceAndResult���в�����Ĭ�����ֵ 
    for ( int i = 0; i < 2; i++ ) {
    	for ( int j = 0; j < K; j++ ) {
    		(*distanceAndResult)[i][j] = INT_MAX;
		}
	}
	
	//�������ݶ�ȡʧ�� 
	if ( fclose(fp) ) {
    	fprintf(stderr, "�޷���ȡ��������");
    	return;
	}
	printf("���ݶ������\n");

}

//��̬�������� 
double **createArray(int n, int m) {
    double **sampleData;
    sampleData = (double **)malloc(n*sizeof(double *));
    sampleData[0] = (double *)malloc(n*m*sizeof(double));
    for ( int i = 1; i < n; i++ ) {
    	sampleData[i] = sampleData[i-1] + m;
	}
    return sampleData;
}

//��ʼ��distanceAndResult����
//distanceAndResult[0][i]�洢����
//distanceAndResult[1][i]�洢��ǩ 
void writeDistanceAndResult(int n, double **distanceAndResult, int N, int D, double *testData, double **sampleData) {
	for ( int i = 0; i < n; i++ ){
        if ( n > N ) {
        	printf("Kȡֵ����(0<k<N)");
        	exit(-1);
		}
        distanceAndResult[0][i] = computeDistance(D-1, testData, sampleData[i]);
        distanceAndResult[1][i] = sampleData[i][D-1];
    }
} 

int cmp(const void *a, const void *b) {
	return *(int*)b - *(int*)a;//���� 
}

//Kֵ���棬��Kֵ����Ӧ��˳��ľ���С��ֵ���ŵ�K��ǰ�� 
void findMeet(double **distanceAndResult, double **sampleData, double **testData, int n,  int N, int D) {
    //��ʼ��k��������ľ������ֵ
	double maxDistance = distanceAndResult[0][n-1];
    double distance;
    for ( int i = n; i < N; i++ ){
        distance = computeDistance(D-1, *testData, sampleData[i]);
        if ( distance < maxDistance ) {
        	for ( int j = 0; j < n; j++ ) {
                if ( distance < distanceAndResult[0][j] ) {
                	//j��Ԫ�ظ��Ƶ���һλ��Ϊ������׼��
                    for ( int k = n-1; k > j; k-- ) { 
                        distanceAndResult[0][k] = distanceAndResult[0][k-1];
                        distanceAndResult[1][k] = distanceAndResult[1][k-1];
                    }
                    //���뵽jλ��
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
//    distanceAndResult[0][i]�洢����
//	distanceAndResult[1][i]�洢��ǩ 
	for ( int i = 0; i < K; i++ ) {
    	printf("distanceAndResult:%6.2f  %6.0f\n", 
			distanceAndResult[0][i],
			distanceAndResult[1][i]
		);
	}
}

//ͳ�Ƴ��ִ������Ľ�� 
//temp[��ֵ]=���� 
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
	printf("\n����Ƶ�����ı�ǩΪ%.0f\n", index);
	return index;
}

void getResult(double ans) {
	printf("\n------------------------------------------------------------Ԥ���δ֪�������Ϊ: %.0f\n\n", ans );
}

double computeDistance(int n, double *a, double *b) {
    double distance=0;
    for ( int i = 0; i < n; i++ ) {
    	distance += pow( a[i] - b[i], 2 );
	}
	double ans = sqrt(distance);
    return ans;
}



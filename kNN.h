#ifndef KNN_H
#define KNN_H

void loadData(int *n, int *d, double ***sampleData, double ***distanceAndResult);
double **createArray(int n, int m);
void writeDistanceAndResult(int n, double **distanceAndResult, int N, int D, double *testData, double **sampleData);
double computeDistance(int n, double *a, double *b);
int cmp(const void *a, const void *b);
void findMeet(double **distanceAndResult, double **sampleData, double **testData, int n, int N, int D);
void test(double **distanceAndResult);
void getResult(double ans);
double Search(int len, double *a);

#endif 

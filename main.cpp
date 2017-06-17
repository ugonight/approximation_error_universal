#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include"readData.h"

//平均
double average(double x[], int n) {
	double sum = 0;
	int i;
	for (i = 0; i<n; i++) {
		sum += x[i];
	}
	return sum / n;
}

//偏差
double deviation(double x[], int i, int n) {
	return x[i] - average(x, n);
}

//標準偏差
double standard_deviation(double x[], int n) {
	double sum = 0;
	int i;
	for (i = 0; i<n; i++) {
		sum += pow(deviation(x, i, n), 2);
	}
	return sqrt((double)(sum / 2));
}

//共分数	
double covariance(double x[], double y[], int n) {
	double sum = 0;
	int i;
	for (i = 0; i<n; i++) {
		sum += deviation(x, i, n) * deviation(y, i, n);
	}
	return sum / n;
}

//相関関数
double correlation_coefficient(double x[], double y[], int n) {
	return covariance(x, y, n) / (standard_deviation(x, n)*standard_deviation(y, n));
}

//課題2

//線形近似
void linear_approximation(double x[], double y[], double *a, double *b, int n) {
	int i;
	double sum_x, sum_y, sum_xy, sum_x2;
	sum_x = sum_y = sum_xy = sum_x2 = 0;

	for (i = 0; i<n; i++) {
		sum_x += x[i];
		sum_y += y[i];
		sum_xy += x[i] * y[i];
		sum_x2 += pow(x[i], 2);
	}

	*a = (n*sum_xy - sum_x*sum_y) / (n*sum_x2 - pow(sum_x, 2));
	*b = (sum_x2*sum_y - sum_xy*sum_x) / (n*sum_x2 - pow(sum_x, 2));
}

//近似誤差
double approximation_error(double x[], double y[], double a, double b, int n) {
	int i;
	double numerator, denominator;
	numerator = denominator = 0;

	for (i = 0; i<n; i++) {
		numerator += pow(y[i] - a*x[i] - b, 2);
		denominator += pow(deviation(y, i, n), 2);
	}

	return 1 - numerator / denominator;
}

//課題3

//多項式近似
void polynomial_approximation(double x[], double y[], double *a, double *b, double *c, int n) {
	int i;
	double sum_x, sum_y, sum_x2, sum_x3, sum_x4, sum_xy, sum_x2y, denominator;
	sum_x = sum_y = sum_x2 = sum_x3 = sum_x4 = sum_xy = sum_x2y = denominator = 0;

	for (i = 0; i<n; i++) {
		sum_x += x[i];
		sum_y += y[i];
		sum_x2 += pow(x[i], 2);
		sum_x3 += pow(x[i], 3);
		sum_x4 += pow(x[i], 4);
		sum_xy += x[i] * y[i];
		sum_x2y += pow(x[i], 2) * y[i];
	}

	denominator = 2 * sum_x*sum_x2*sum_x3 + n*sum_x2*sum_x4 - pow(sum_x, 2)*sum_x4 - n*pow(sum_x3, 2) - pow(sum_x2, 3);
	*c = (-pow(sum_x2, 2)*sum_x2y + sum_x*sum_x3*sum_x2y - sum_x*sum_x4*sum_xy + sum_x2*sum_x3*sum_xy - pow(sum_x3, 2)*sum_y + sum_x2*sum_x4*sum_y) / denominator;
	*b = (sum_x*sum_x2*sum_x2y - n*sum_x3*sum_x2y + n*sum_x4*sum_xy - pow(sum_x2, 2)*sum_xy + sum_x2*sum_x3*sum_y - sum_x*sum_x4*sum_y) / denominator;
	*a = (n*sum_x2*sum_x2y - pow(sum_x, 2)*sum_x2y + sum_x*sum_x2*sum_xy - n*sum_x3*sum_xy + sum_x*sum_x3*sum_y - pow(sum_x2, 2)*sum_y) / denominator;
}

//近似誤差
double approximation_error2(double x[], double y[], double a, double b, double c, int n) {
	int i;
	double numerator, denominator;
	numerator = denominator = 0;

	for (i = 0; i<n; i++) {
		numerator += pow(y[i] - a*pow(x[i], 2) - b*x[i] - c, 2);
		denominator += pow(deviation(y, i, n), 2);
	}

	return 1 - numerator / denominator;
}

//追加課題

//（万能？）近似誤差
Formula f;
double approximation_error_universal(double x[], double y[], int n, char* formula) {
	int i;
	double numerator, denominator;
	numerator = denominator = 0;

	for (i = 0; i<n; i++) {
		numerator += pow(y[i] - f.mathematical_analysis(formula, x[i]), 2);
		denominator += pow(deviation(y, i, n), 2);
	}

	return 1 - numerator / denominator;
}

int main(int argc,char *argv[]) {
	FILE *fp; // = fopen(argv[1], "r");
	fopen_s(&fp, "data/data01.txt", "r");
	Data *dp = readData(fp);
	int num = dp->num, i;
	double *x, *y;
	double a, b, c;

	x = (double*)malloc(num * sizeof(double));
	y = (double*)malloc(num * sizeof(double));
	for (i=0;i<num;i++) {
		x[i] = dp->data[i].x;
		y[i] = dp->data[i].y;
	}

	printf("課題1\n");
	printf("平均(x) : %lf\n", average(x,num));
	printf("平均(y) : %lf\n", average(y,num));
	printf("標準偏差(x) : %lf\n", standard_deviation(x,num));
	printf("標準偏差(y) : %lf\n", standard_deviation(y,num));
	printf("共分散 : %lf\n", covariance(x,y,num));
	printf("相関関数 : %lf\n", correlation_coefficient(x,y,num));

	printf("\n課題2\n");
	linear_approximation(x, y, &a, &b, num);
	printf("y = %lf x + %lf\n", a, b);
	printf("R2 = %lf\n", approximation_error(x, y, a, b, num));

	//課題3
	printf("\n課題3\n");
	polynomial_approximation(x, y, &a, &b, &c, num);
	printf("y = %lf x2 + %lf x + %lf\n", a, b, c);
	printf("R2 = %lf\n", approximation_error2(x, y, a, b, c, num));

	//Formula f;
	//char str[255] = "1 + 2 * 3 - ( x ^ 2 )";
	//printf("%s = %lf\n", str, f.mathematical_analysis(str, 5.0));
	//追加課題
	printf("\n追加課題\n");
	polynomial_approximation(x, y, &a, &b, &c, num);
	printf("y = %lf x2 + %lf x + %lf\n", a, b, c);
	char str[256];
	sprintf_s(str, 256, "%lf * x ^ 2 + %lf * x + %lf", a, b, c);	//パラメーターを数値に変換して式を作る
	printf("R2 = %lf\n", approximation_error_universal(x, y, num, str));
	
	free(x);
	free(y);
	free(dp);
	fclose(fp);

	system("pause");

	return 0;
}

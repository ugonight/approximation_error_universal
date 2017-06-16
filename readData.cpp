#include"readData.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

Data *readData(FILE *fp) {
	Data *result = (Data *)malloc(sizeof(Data));
	char str[255];
	int num, i;
	double x, y;

	//if (fp == NULL) {
	//	printf("ファイルが開けません¥n");
	//	return;
	//}
	
	fgets(str, 100, fp);
	num = atoi(str);
	result->num = num;
	result->data = (Datum *)malloc(sizeof(Datum) * num);

	i = x = y = 0;
	while (fgets(str, 255, fp)) {
		sscanf_s(str, "%lf %lf", &x , &y);
		result->data[i].x = x;
		result->data[i].y = y;
		i++;
	}

	return result;
}
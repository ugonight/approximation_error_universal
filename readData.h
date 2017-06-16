#pragma once

#include<stdio.h>

#define MAX 100

typedef struct {
	double	x;
	double	y;
}	Datum;

typedef struct {
	unsigned	num;
	Datum	*data;
}	Data;

Data *readData(FILE *fp);

class Formula 
{
public:
	Formula();
	double mathematical_analysis(char* str, double x);	//�������
private:
	char list[MAX][MAX];	//�������X�g

	void calculation_list(int s, int e);	//�������X�g�v�Z
	void shorten();	//�z����l�߂�
};
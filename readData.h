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
	double mathematical_analysis(char* str, double x);	//数式解析
private:
	char list[MAX][MAX];	//数式リスト

	void calculation_list(int s, int e);	//数式リスト計算
	void shorten();	//配列を詰める
};
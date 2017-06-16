#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include"readData.h"

Formula::Formula() {
	for (int i = 0; i < MAX; i++) {
		list[i][0] = '\0';	//������
	}
}

//�z����l�߂�
void Formula::shorten() {
	int i, j;
	for (i = 0; i < MAX; i++) {
		while (list[i][0] == '0') {
			for (j = i; list[j][0] != '\0'; j++) {
				strcpy_s(list[j], MAX, list[j + 1]);
			}
		}
	}
}

//�������X�g�v�Z
void  Formula::calculation_list(int s, int e) {
	int i, j;

	//������
	for (i = s; i < e; i++) {
		while (list[i][0] == '(') {
			for (j = i; j < e; j++) {
				if (list[j][0] == ')') {
					list[j][0] = '0'; list[i][0] = '0';
					calculation_list(i+1 , j-1);
					shorten();
				}
			}
		}
	}

	//�֐�
	for (i = s; i < e; i++) {
		while (list[i][0] == 'l') {	//�ΐ�
			sprintf_s(list[i], MAX, "%lf", log(atof(list[i + 1])));
			list[i + 1][0] = '0';
			shorten();
		}
		while (list[i][0] == 'e') {//�w���֐�
			sprintf_s(list[i], MAX, "%lf", exp(atof(list[i + 1])));
			list[i + 1][0] = '0';
			shorten();
		}
	}

	//�ׂ���E�ׂ���
	for (i = s; i < e; i++) {
		while (list[i][0] == '^') {
			sprintf_s(list[i - 1], MAX, "%lf", pow(atof(list[i - 1]), atof(list[i + 1])));
			list[i][0] = '0'; list[i + 1][0] = '0';
			shorten();
		}
		while (list[i][0] == 'r') {
			sprintf_s(list[i], MAX, "%lf", sqrt(atof(list[i + 1])));
			list[i + 1][0] = '0';
			shorten();
		}
	}

	//�|���Z�E����Z
	for (i = s; i < e; i++) {
		while (list[i][0] == '*') {
			sprintf_s(list[i - 1], MAX, "%lf", atof(list[i - 1]) * atof(list[i + 1]));
			list[i][0] = '0'; list[i + 1][0] = '0';
			shorten();
		}
		while (list[i][0] == '/') {
			sprintf_s(list[i - 1], MAX, "%lf", atof(list[i - 1]) / atof(list[i + 1]));
			list[i][0] = '0'; list[i + 1][0] = '0';
			shorten();
		}
	}

	//�����Z�E�����Z
	for (i = s; i < e; i++) {
		while (list[i][0] == '+') {
			sprintf_s(list[i - 1], MAX, "%lf", atof(list[i - 1]) + atof(list[i + 1]));
			list[i][0] = '0'; list[i + 1][0] = '0';
			shorten();
		}
		while (list[i][0] == '-') {
			sprintf_s(list[i - 1], MAX, "%lf", atof(list[i - 1]) - atof(list[i + 1]));
			list[i][0] = '0'; list[i + 1][0] = '0';
			shorten();
		}
	}
}

//�������
double Formula::mathematical_analysis(char* str, double x) {
	int i, i_num = 0, i_list = 0;
	double result = 0;

	//�������X�g�ɐ���
	for (i = 0; str[i] != '\0'; i++) {
		//�����i�p�����[�^�[�j
		if ((str[i] >= '0' && str[i] <= '9') || str[i] == '.') {
			list[i_list][i_num] = str[i];
			i_num++;
		}
		//�󔒁i���E���Z�I���j
		else if (str[i] == ' ') {
			if (i_num > 0) {	//���O������
				list[i_list][i_num] = '\0';
				i_list++;
				i_num = 0;
			}
		}
		//x
		else if (str[i] == 'x') {
			sprintf_s(list[i_list], MAX, "%lf", x);
			i_list++;
		}
		//���Z�q�E�֐�
		else {
			list[i_list][0] = str[i];
			list[i_list][1] = '\0';
			i_list++;
		}
	}
	if (i_num > 0) {
		list[i_list][i_num] = '\0';
		i_list++;
		i_num = 0;
	}

	//�������X�g���v�Z
	calculation_list(0, i_list);

	return atof(list[0]);
}
#include "DxLib.h"
#include <math.h>

#define GET_X(i) x + (w / maxX) * i
#define GET_Y(i) y + h - ((h / maxY)*i)

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	SetGraphMode(700, 480, 16);
	SetBackgroundColor(255, 255, 255);

	const int black = GetColor(0, 0, 0);
	const int x = 50, y = 30, w = 400, h = 400;
	const int maxX = 100, maxY = 100;
	const int dataNum = 1000;
	int fsize = GetFontSize();
	//ÉfÅ[É^Ç…çáÇÌÇπÇƒèëÇ´ä∑Ç¶
	const int id = 13;
	const double a = -0.029228, b = 54.078174/*,c = -190.101581*/;
	const double R = -0.000075, R2 = 0.001389;

	//ÉtÉ@ÉCÉãì«Ç›çûÇ›
	FILE *fp;
	double dataX[dataNum], dataY[dataNum]; char str[256];
	sprintf_s(str, "data/data%02d.txt", id);
	fopen_s(&fp, str, "r");
	fgets(str, 256, fp);
	for (int i = 0; i <  dataNum; i++) {
		fscanf_s(fp, "%lf %lf", &dataX[i], &dataY[i]);
	}
	fclose(fp);

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		//ògê¸
		DrawLine(x, y, x, y + h, black);
		DrawLine(x, y + h, x + w, y + h, black);
		DrawString(x + w + 50, y + h + 10, "x", black);
		DrawString(x - 20, 5, "y", black);
		for (int i = 0; i <= 10; i++) {
			DrawFormatString(x + (w / maxX) * (i * 10) - fsize / 2, y + h + 10, black, "%d", (maxX / 10)*i);
			DrawFormatString(x - 25, y + h - ((h / maxY)*(i * 10) + fsize / 2), black, "%d", (maxY / 10)*i);
		}
		DrawFormatString(x + w, 100, black, "ëää÷åWêî :\n %lf\nãﬂéóéÆ :\n %lf x + %lf\nåàíËåWêî :\n %lf", R, a, b, R2);
		//DrawFormatString(x + w, 100, black, "ëää÷åWêî :\n %lf\nãﬂéóéÆ :\n %lf x2 + %lf x +\n %lf\nåàíËåWêî :\n %lf", R, a, b, c, R2);

		//éUïzê}
		for (int i = 0; i <= dataNum; i++) {
			DrawPixel(GET_X(dataX[i]), GET_Y(dataY[i]), black);
		}

		//ãﬂéóê¸
		double posX, posY;
		for (int i = 0; i <= w; i++) {
			posX = (double)i / ((double)w / (double)maxX);
			posY = a * posX + b;
			//posY = a * pow(posX, 2) + b * posX + c;
			DrawPixel(x + i, GET_Y(posY), black);
		}
	}

	sprintf_s(str, "screenshot%02d.png", id);
	SaveDrawScreenToPNG(0, 0, 700, 480, str, 80);

	DxLib_End();
	return 0;
}

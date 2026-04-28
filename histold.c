#include "raylib.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 1920
#define HEIGHT 1080
#define FPS 144


double gauss(double x, double mu, double sigma) {
    return 0.5 * (1.0 + erf((x - mu) / (sigma * sqrt(2.0))));
}

double expo(double x, double mu, double sigma) {
	double lambda = 1 / mu;
    return 1 - exp(-lambda * x);
}


void histogram(int *data, int nTrials, int nBins, int start, int end, float delay, int maxh) {
	int freq[nBins];
	for (int nBin = 0; nBin < nBins; nBin++) freq[nBin] = 0;

    InitWindow(WIDTH, HEIGHT, "Histogram");
    SetTargetFPS(FPS);

    int i = 0;
    float timer = 0.0f;

    while (!WindowShouldClose()) {
        timer += GetFrameTime();

        if (timer >= delay && i < nTrials) {
            freq[(data[i] - start) * nBins / (end - start + 1)]++;
			i++;
            timer = 0.0f;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        for (int nBin = 0; nBin < nBins; nBin++) {
			int stepx = 1600/nBins;
            int barHeight = (900 * freq[nBin]) / maxh;
            DrawRectangle(160 + stepx * nBin, 990 - barHeight, stepx, barHeight, GREEN);
        }
        EndDrawing();
    }
    CloseWindow();
}


int *randomGenerator(double (*f) (double, double, double), int nTrials, int nBins, int start, int end, double mu, double sigma) {
	int *trials = malloc(nTrials * sizeof(int));
	srand((unsigned int) time(NULL));
	float step = (float) (end - start) / nBins;
	double x, y, a, b;
	double PMF;
	for (int i = 0; i < nTrials;) {
		x = start + ((double)rand() / RAND_MAX) * (end - start);
		y = (double) rand() / RAND_MAX;
		a = f(x - step / 2, mu, sigma);
		b = f(x + step / 2, mu, sigma);
		PMF = b - a;
		if (y < PMF) {
			trials[i] = (int) round(x);
			i++;
		}
	}
	return trials;
}

int main ()
{
	int nTrials = 10000;
	int nBins = 15;
	int start = -30;
	int end = 30;
	double mu = 0;
	double sigma = 10;
	int maxh = (int) sqrt(2*PI*sigma*sigma) * nTrials / nBins;
	int *data = randomGenerator(gauss, nTrials, nBins, start, end, mu, sigma);
	histogram(data, nTrials, nBins, start, end, 0, maxh / 10);

	return 0;
}

#include "raylib.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define WIDTH 1920
#define HEIGHT 1080
#define FPS 10000


double gauss(double x, double mu, double sigma) {
    return 0.5 * (1.0 + erf((x - mu) / (sigma * sqrt(2.0))));
}


double expon(double x, double mu, double sigma) {
	double lambda = sqrt(1 / sigma);
    return 1 - exp(-lambda * x);
}


double poisson(double x, double mu, double sigma) {
	if (x < 0) return 0.0;

	double lambda = mu;
    double sum = 1.0 / (x + 1);
    double term = sum;
    
    for (int n = 1; n < 100; n++) {
        term *= lambda / (x + 1 + n);
        sum += term;
        if (term < sum * 1e-14) break;
    }
    return 1.0 - exp(-lambda + (x + 1) * log(lambda) - lgamma(x + 1)) * sum;
}


void histogram(int *data, int nTrials, int nBins, int maxh) {
	int current, barHeight, i = 0, stepx = 1600 / nBins;
	int freq[nBins];
	for (int nBin = 0; nBin < nBins; nBin++) freq[nBin] = 0;

	InitWindow(WIDTH, HEIGHT, "Histogram");
    SetTargetFPS(FPS);

    while (!WindowShouldClose()) {
        if (i < nTrials) {
			current = data[i++];
            freq[current]++;
			barHeight = (900 * freq[current]) / maxh;
        }
		BeginDrawing();
        DrawRectangle(160 + stepx * current, 990 - barHeight, stepx, barHeight, GREEN);
        EndDrawing();
    }
    CloseWindow();
}

int lecture_sin() {
    double uni = rand() / (double) RAND_MAX;
    return (int) (acos(1 - 2 * uni) / PI * 300);
}

int *randomGenerator(double (*f) (double, double, double), int nTrials, int nBins, double start, double end, double mu, double sigma) {
	int *trials = malloc(nTrials * sizeof(int));
	srand(time(NULL));
	double step = (end - start) / nBins;
	double x;
	int index;
	double CDF[nBins + 1];

	for (int nBin = 0; nBin < nBins + 1; nBin++)
		CDF[nBin] = f(start + step * nBin, mu, sigma);

	for (int i = 0; i < nTrials;) {
		x = (double) rand() / RAND_MAX;
		if ((x > CDF[0]) && (x < CDF[nBins])) {
			for (int j = 0; j < nBins; j++) {
				if (x < CDF[j + 1]) {
					trials[i] = j;
					break;
				}
			}
			i++;
		}
	}
	return trials;
}

int main ()
{
	int nTrials = 50000;
	int nBins = 300;
	double start = 0;
	double end = 10;
	double mu = 0;
	double sigma = 1;
	int maxh = (int) (nTrials * (end-start) / sqrt(2 * PI) / sigma / (nBins));
	//int *data = randomGenerator(gauss, nTrials, nBins, start, end, mu, sigma);
	int data[nTrials];
	for (int i = 0; i < nTrials; i++) {
		data[i] = lecture_sin();
		printf("%d\n", data[i]);
	}
	histogram(data, nTrials, nBins, 250);

	return 0;
}
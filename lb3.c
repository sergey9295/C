#include "raylib.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define WIDTH 1024
#define HEIGHT 1024
#define FPS 10000


typedef struct {
	double *data;
	int nTrials;
	int nBins;
	double start;
	double end;
} dataPlot;


void histogram(dataPlot *dataMeta, int intensity) {
	double current, step = (dataMeta->end - dataMeta->start) / dataMeta->nBins;
	int underflow, overflow, nBin, nTrial = 0;
	double stepx = WIDTH / dataMeta->nBins;
	double stepy = HEIGHT / intensity;
	int freq[dataMeta->nBins];
	for (int nBin = 0; nBin < dataMeta->nBins; nBin++) freq[nBin] = 0;

	InitWindow(WIDTH, HEIGHT, "Histogram");
    SetTargetFPS(FPS);

    while (!WindowShouldClose()) {
        if (nTrial < dataMeta->nTrials) {
			current = dataMeta->data[nTrial++];
			if (current < dataMeta->start) underflow++;
			else if (current > dataMeta->end) overflow++;
			else{
				nBin = (int) ((current - dataMeta->start) / step);
            	freq[nBin]++;
				BeginDrawing();
        		DrawRectangle(stepx * nBin, HEIGHT - stepy * freq[nBin], stepx, stepy * freq[nBin], GREEN);
        		EndDrawing();
			}
        }
		BeginDrawing();
        EndDrawing();
    }
    CloseWindow();
}


double uniform() {
    return rand() / (double) RAND_MAX;
}


double lecture_sin() {
    return (acos(1 - 2 * uniform()));
}


double lecture_exp(double lambda) {
    return -log(uniform()) / lambda;
}


double angle(double E, double beta, double gamma, double momentum) {
	double costheta = uniform();
	double sintheta = sqrt(1 - costheta * costheta);
	return momentum * sintheta / (gamma * (momentum * costheta + beta * E));
}


void genData(double *data, double E, double detector, double avgt, int nTrials) {
	double c = 3e8;
	double mc2 = 493.6e6;
	double gamma = E / mc2;
	double beta = sqrt(1 - pow(gamma, -2));
	double velocity = c * beta;
	double momentum = sqrt(E * E - mc2 * mc2);
	double tgtheta;
	double dist;
	double t;

	for (int i = 0; i < nTrials;) {
		t = lecture_exp(1 / avgt);
		dist = detector - t * gamma * velocity;
		if (dist < 0) continue;
		tgtheta = angle(E, beta, gamma, momentum);
		data[i++] = dist * tgtheta;
		//data[i++] = t * gamma * velocity;
	}
}


int main ()
{
	double E = 7e10;
	double detector = 5;
	double avgt = 8.956e-11;

	int nTrials = 50000;
	int nBins = WIDTH / 4;
	double start = 0;
	double end = 0.04;
	double *data = malloc(nTrials * sizeof(double));

	//for (int i = 0; i < nTrials; i++) data[i] = lecture_exp(1);
	//for (int i = 0; i < nTrials; i++) data[i] = lecture_sin();

	genData(data, E, detector, avgt, nTrials);

	dataPlot dataMeta = {data, nTrials, nBins, start, end};
	histogram(&dataMeta, 255);

	return 0;
}
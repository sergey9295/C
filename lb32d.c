#include "raylib.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define WIDTH 1024
#define HEIGHT 1024
#define FPS 10000


typedef struct{
	double x;
	double y;
} Vec2;


typedef struct {
	Vec2 *data;
	int nTrials;
	Vec2 nBins;
	Vec2 start;
	Vec2 end;
} dataPlot;


Color GetColorPlease(int count, int intensity) {
    float saturation = (count < intensity) ? (float)count / intensity : 1;
    return (Color){0, (int)(255 * saturation), 0, 255};
}


void heatmap(dataPlot *dataMeta, int intensity) {
	Vec2 step = {(dataMeta->end.x - dataMeta->start.x) / dataMeta->nBins.x, (dataMeta->end.y - dataMeta->start.y) / dataMeta->nBins.y};
	Vec2 current;
	Vec2 nBin;
	Vec2 pixstep = {WIDTH / dataMeta->nBins.x, HEIGHT / dataMeta->nBins.y};
	int index, nTrial = 0;
	int nBins = dataMeta->nBins.x * dataMeta->nBins.y;
	int freq[nBins];
	for (int nBin = 0; nBin < nBins; nBin++) freq[nBin] = 0;

	InitWindow(WIDTH, HEIGHT, "Histogram");
    SetTargetFPS(FPS);

    while (!WindowShouldClose()) {
        if (nTrial < dataMeta->nTrials) {
			current = dataMeta->data[nTrial++];
			if (current.x > dataMeta->start.x && current.x < dataMeta->end.x && current.y > dataMeta->start.y && current.y < dataMeta->end.y) {
				nBin.x = ((current.x - dataMeta->start.x) / step.x);
				nBin.y = ((current.y - dataMeta->start.y) / step.y);
				index = (int) dataMeta->nBins.y * (int)(nBin.y) + (int)(nBin.x);
            	freq[index]++;
				BeginDrawing();
        		DrawRectangle(pixstep.x * nBin.x, pixstep.y * nBin.y, pixstep.x, pixstep.y, GetColorPlease(freq[index], intensity));
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


void genData(Vec2 *data, double E, double detector, double avgt, int nTrials) {
	double c = 3e8;
	double mc2 = 493.6e6;
	double gamma = E / mc2;
	double beta = sqrt(1 - pow(gamma, -2));
	double velocity = c * beta;
	double momentum = sqrt(E * E - mc2 * mc2);
	double tgtheta;
	double dist;
	double t;
	double r;
	double phi;

	for (int i = 0; i < nTrials;) {
		t = lecture_exp(1 / avgt);
		dist = detector - t * gamma * velocity;
		if (dist < 0) continue;
		tgtheta = angle(E, beta, gamma, momentum);
		r = dist * tgtheta;
		phi = uniform() * 2 * PI;
		Vec2 dot = {r * cos(phi), r * sin(phi)};
		data[i++] = dot;
		//printf("%.16f, %.16f\n", data[i - 1].x, data[i - 1].y);
	}
}


int main ()
{
	double E = 7e10;
	double detector = 5;
	double avgt = 8.956e-11;

	int nTrials = 50000;
	Vec2 nBins = {WIDTH / 4, HEIGHT / 4};
	Vec2 start = {-0.01, -0.01};
	Vec2 end   = { 0.01,  0.01};
	Vec2 *data = malloc(nTrials * sizeof(Vec2));

	genData(data, E, detector, avgt, nTrials);
	dataPlot dataMeta = {data, nTrials, nBins, start, end};
	heatmap(&dataMeta, 5);

	return 0;
}
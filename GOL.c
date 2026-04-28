#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "raylib.h"

#define WIDTH 1920
#define HEIGHT 1080
#define SIZE 20
#define VNUM 96
#define HNUM 54

int field_prev[VNUM][HNUM];
int field[VNUM][HNUM];
char *text = "Game of Life";

void copy() { 
    for (int i = 0; i < VNUM; i ++) {
        for (int j = 0; j < HNUM; j ++) {
            field_prev[i][j] = field[i][j];
        } 
    }
}


int neighbors(int a, int b) { 
	int count = 0;
    for (int i = -1; i <= 1; i ++) {
        for (int j = -1; j <= 1; j ++) {
			if (i == 0 && j == 0) continue;
  			count += field_prev[(i + a + VNUM) % VNUM][(j + b + HNUM) % HNUM];
		}	
	}
	return count;
}


void rule_check() { 
    int neig;
    for (int i = 0; i < VNUM; i ++) {
        for (int j = 0; j < HNUM; j ++) {
            neig = neighbors(i, j);
			if (field_prev[i][j]) {
                field[i][j] = (neig == 2 || neig == 3);
            } 
            else
                field[i][j] = (neig == 3);
        } 
    }
}


void drawBoard(){
	BeginDrawing();
	ClearBackground(RAYWHITE);	
    for (int i = 0; i < VNUM; i++) {
        for (int j = 0; j < HNUM; j++) {
            if (field_prev[i][j] == 1) {
				DrawRectangle(i * SIZE, j * SIZE, SIZE, SIZE, RED);
            }
		}
    }
	EndDrawing();
}


void click() {
	int x = GetMouseX();
	int y = GetMouseY();
	if (field_prev[x / SIZE][y / SIZE] == 1) 
		field_prev[x / SIZE][y / SIZE] = 1; 
	else
		field_prev[x / SIZE][y / SIZE] = 1; 	
}



int main () { 
    bool time_flow = false;
	
	InitWindow(WIDTH, HEIGHT, "Game of life");
	
    SetTargetFPS(144);
	
    while (!WindowShouldClose()) {
		if (IsKeyPressed(KEY_ENTER)) time_flow = !time_flow;

		if (!time_flow && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
			click();
		}

		if (time_flow) {
			rule_check();
    		copy();
		}	
		drawBoard();
	}
    CloseWindow();
    return 0;
}

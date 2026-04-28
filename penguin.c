#include <raylib.h>

#include <stdio.h>
#include <math.h>
#include <string.h>

#define WIDTH 1080
#define HEIGHT 1080
#define FPS 144

typedef struct {
    float x, y, z;
} Vec3;

Vec3 vert[3000];
int edges[10000][2];


int vertex_count = 0;
int edge_count = 0;

void load_data() {
    FILE *vFile = fopen("vertices.txt", "r");
    if (vFile == NULL) return;

    // Read until fscanf fails to find 3 floats or reaches end of file
    while (fscanf(vFile, " { %f , %f , %f } ,", 
           &vert[vertex_count].x, &vert[vertex_count].y, &vert[vertex_count].z) == 3) {
        vertex_count++;
    }
    fclose(vFile);

    FILE *eFile = fopen("edges.txt", "r");
    if (eFile == NULL) return;

    // Read until fscanf fails to find 2 ints
    while (fscanf(eFile, " { %d , %d } ,", 
           &edges[edge_count][0], &edges[edge_count][1]) == 2) {
        edge_count++;
    }
    fclose(eFile);
    
    printf("Loaded %d vertices and %d edges.\n", vertex_count, edge_count);
}


Vec3 project (Vec3 ver, float distance) {
	return (Vec3) {ver.x/(ver.z + distance), ver.y/(ver.z + distance), ver.z};
}


Vec3 rotate (Vec3 ver, float dx, float dy, float speedy, float speedx) {
	float c = cos(speedy), s = sin(speedy);
	float nx = (ver.x + dx) * c + ver.z * s;
	float ny = (ver.y + dy);
	float nz = (-ver.x + dx) * s + ver.z * c;

	c = cos(speedx), s = sin(speedx);
	float nx2 = nx;
	float ny2 = ny * c + nz * s;
	float nz2 = -ny * s + nz * c;

	return (Vec3) {nx2, ny2, nz2};
}


Vec3 transform (Vec3 ver) {
	return (Vec3) {(ver.x + 1) * WIDTH / 2, (-ver.y + 1) * HEIGHT / 2, ver.z};
}



int main ()
{
    load_data();
    float distance = 3;
	float t = 0;
	float dx = 0, dy = 0;
	InitWindow(WIDTH, HEIGHT, "Hello Raylib");

	while (!WindowShouldClose())
	{

		if (IsKeyDown(KEY_RIGHT)) dx += 0.001f;
        if (IsKeyDown(KEY_LEFT)) dx -= 0.001f;
        if (IsKeyDown(KEY_UP)) dy -= 0.001f;
        if (IsKeyDown(KEY_DOWN)) dy += 0.001f;
		if (IsKeyDown(KEY_SPACE)) dy = dx = 0.0f;


		distance -= GetMouseWheelMove()*0.1;

		BeginDrawing();
		ClearBackground(BLACK);
		for (int i = 0; i < edge_count; i++) {
			Vec3 v1 = transform(project(rotate(vert[edges[i][0]], dx, dy, t, 0), distance));
			Vec3 v2 = transform(project(rotate(vert[edges[i][1]], dx, dy, t, 0), distance));
			DrawLine(v1.x, v1.y, v2.x, v2.y, GREEN);
		}
		t += .0004;
		EndDrawing();
	}
	CloseWindow();
	return 0;
}

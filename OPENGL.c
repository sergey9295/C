#include "raylib.h"

#include <stdio.h>
#include <math.h>
#include <string.h>

#define WIDTH 1080
#define HEIGHT 1080
#define FPS 144


typedef struct {
    float x, y, z;
} Vec3;


typedef struct {
    float x, y;
} Vec2;


Vec3 vert[3000];
Vec3 buffer[3000];
int edges[10000][2];

int vertex_count = 0;
int edge_count = 0;

void load_data() {
    FILE *vFile = fopen("vertices3.txt", "r");

    while (fscanf(vFile, " { %f , %f , %f } ,", 
           &vert[vertex_count].x, &vert[vertex_count].y, &vert[vertex_count].z) == 3) {
		buffer[vertex_count] = vert[vertex_count];
        vertex_count++;
    }
    fclose(vFile);

    FILE *eFile = fopen("edges3.txt", "r");
    if (eFile == NULL) return;

    // Read until fscanf fails to find 2 ints
    while (fscanf(eFile, " { %d , %d } ,", 
           &edges[edge_count][0], &edges[edge_count][1]) == 2) {
        edge_count++;
    }
    fclose(eFile);
    
    printf("Loaded %d vertices and %d edges.\n", vertex_count, edge_count);
}


Vec2 transform2d (Vec2 ver) {
	return (Vec2) {(ver.x + 1) * WIDTH / 2, (-ver.y + 1) * HEIGHT / 2};
}


void transform(Vec2 ver[], int vc) {
	for (int i = 0; i < vc; i++) {
		ver[i] = transform2d(ver[i]);
	}
}


void modify(Vec3 ver[], Vec3 copy[], Vec3 dr, int vc) {
		for (int i = 0; i < vc; i++) {
			copy[i] = (Vec3) {copy[i].x + dr.x, copy[i].y + dr.y, copy[i].z + dr.z};
	}
}


Vec3 project3d (Vec3 ver) {
	return (Vec3) {(ver.x/ver.z + 1) * WIDTH / 2, (-ver.y/ver.z + 1) * HEIGHT / 2, 1};
}


void project(Vec3 ver[], int vc) {
	for (int i = 0; i < vc; i++) {
		ver[i] = project3d(ver[i]);
	}
}


Vec2 shift2d(Vec2 ver, Vec2 shift) {
	return (Vec2) {ver.x + shift.x, ver.y + shift.y};
}


Vec3 shift3d(Vec3 ver, Vec3 shift) {
	return (Vec3) {ver.x + shift.x, ver.y + shift.y, ver.z + shift.z};
}


void shift(Vec3 ver[], Vec3 copy[], Vec3 shift, int vc) {
	for (int i = 0; i < vc; i++) {
		copy[i] = shift3d(ver[i], shift);
	}
}


Vec2 scale2d(Vec2 ver, Vec2 scale) {
	return (Vec2) {ver.x * scale.x, ver.y * scale.y};
}


Vec3 scale3d(Vec3 ver, Vec3 scale) {
	return (Vec3) {ver.x * scale.x, ver.y * scale.y, ver.z * scale.z};
}


void scale(Vec3 ver[], Vec3 copy[], Vec3 scale, int vc) {
	for (int i = 0; i < vc; i++) {
		copy[i] = scale3d(ver[i], scale);
	}
}


Vec2 rotate2d (Vec2 ver, float radian) {
	float c = cos(radian), s = sin(radian);
	float nx = ver.x * c + ver.y * s;
	float ny = -ver.x * s + ver.y * c;
	return (Vec2) {nx, ny};
}


Vec3 rotate3d (Vec3 ver, Vec3 rotation) {
	float cx = cos(rotation.x), sx = sin(rotation.x);
	float cy = cos(rotation.y), sy = sin(rotation.y);
	float cz = cos(rotation.z), sz = sin(rotation.z);

	float nx = ver.x;
	float ny = ver.y * cx - ver.z * sx;
	float nz = ver.y * sx + ver.z * cx;

	float nx2 = nx * cy - nz * sy;
	float ny2 = ny;
	float nz2 = nx * sy + nz * cy;

	float nx3 = nx2 * cz - ny2 * sz;
	float ny3 = nx2 * sz + ny2 * cz;
	float nz3 = nz2;

	return (Vec3) {nx3, ny3, nz3};
}


void rotate(Vec3 ver[], Vec3 copy[], Vec3 rotation, int vc) {
	for (int i = 0; i < vc; i++) {
		copy[i] = rotate3d(ver[i], rotation);
	}
}


Vec2 reflect2d(Vec2 ver, Vec2 direction) {
    float theta = atan2(direction.y, direction.x);
    Vec2 loc = rotate2d(ver, theta);
    loc.y = -loc.y;
    return rotate2d(loc, -theta);
}


Vec3 reflect3d(Vec3 ver, Vec3 normal) {
    float len = sqrt(normal.x*normal.x + normal.y*normal.y + normal.z*normal.z);
    Vec3 n = {normal.x / len, normal.y / len, normal.z / len};

    // 2. Calculate dot product (ver . n)
    float dot = ver.x * n.x + ver.y * n.y + ver.z * n.z;

    // 3. Reflect: v' = v - 2 * dot * n
    return (Vec3) {
        ver.x - 2.0f * dot * n.x,
        ver.y - 2.0f * dot * n.y,
        ver.z - 2.0f * dot * n.z
    };
}


void reflect(Vec3 ver[], Vec3 copy[], Vec3 reflection, int vc) {
	for (int i = 0; i < vc; i++) {
		copy[i] = reflect3d(ver[i], reflection);
	}
}


void reg_poly2d(Vec2 arr[], int n, float rotation, float size) {
	float step = 2.0f * PI / n;
	int i = 0;
	while (i < n) {
		arr[i] = (Vec2) {cos(step * i) * size, sin(step * i) * size};
		i++;
	}
	for (i = 0; i < n; i++) {
		arr[i] = rotate2d(arr[i], rotation);
	}

}


void star_gen2d(Vec2 arr[], int n, float rotation, float size) {
	Vec2 outer[n];
	Vec2 inner[n];
	reg_poly2d(outer, n, rotation, size);
	reg_poly2d(inner, n, rotation +  PI/n, size * 0.5f);

	int i = 0, j = 0;
	while (i < n) {
		arr[j++] = inner[i];
		arr[j++] = outer[i];
		i++;
	}
}


void parallelogram (Vec2 arr[], Vec2 dir1, Vec2 dir2, float size) {
	arr[0] = (Vec2) {(-dir1.x / 2 - dir2.x / 2) * size, (-dir1.y / 2 - dir2.y / 2) * size};
	arr[1] = (Vec2) {( dir1.x / 2 - dir2.x / 2) * size, ( dir1.y / 2 - dir2.y / 2) * size};
	arr[2] = (Vec2) {( dir1.x / 2 + dir2.x / 2) * size, ( dir1.y / 2 + dir2.y / 2) * size};
	arr[3] = (Vec2) {(-dir1.x / 2 + dir2.x / 2) * size, (-dir1.y / 2 + dir2.y / 2) * size};
}


void display2d(Vec2 arr[], int n, Color color) {
	
	for (int i = 0; i < n - 1; i++) {
			Vec2 v1 = transform2d(arr[i]);
			Vec2 v2 = transform2d(arr[i + 1]);
			DrawLine(v1.x, v1.y, v2.x, v2.y, color);
		}
		Vec2 v1 = transform2d(arr[0]);
		Vec2 v2 = transform2d(arr[n - 1]);
		DrawLine(v1.x, v1.y, v2.x, v2.y, color);
}


void display(Vec3 v[], int e[][2], int vc, int ec, Color color) {
	BeginDrawing();
	ClearBackground(BLACK);
	for (int i = 0; i < ec; i++) {
		Vec3 v1 = v[e[i][0]];
		Vec3 v2 = v[e[i][1]];
		DrawLine(v1.x, v1.y, v2.x, v2.y, color);
	}
	EndDrawing();
}


int main ()
{
	float t = 0, dx = 0, dy = 0, dz = 3;
	load_data();


	InitWindow(WIDTH, HEIGHT, "C is better than Wolfram Mathematica");

	while (!WindowShouldClose())
	{
		if (IsKeyDown(KEY_RIGHT)) dx -= 0.001f;
        if (IsKeyDown(KEY_LEFT)) dx += 0.001f;
        if (IsKeyDown(KEY_UP)) dy -= 0.001f;
        if (IsKeyDown(KEY_DOWN)) dy += 0.001f;
		if (IsKeyDown(KEY_SPACE)) dz = dy = dx = 0.0f;

		dz -= GetMouseWheelMove()*0.1;

		Vec2 ver[10];
		Vec2 vers[10];

		//BeginDrawing();
		//ClearBackground(BLACK);
		//star_gen2d(ver, 5, 0, 0.5);
		//display2d(ver, 10, RED);
		//star_gen2d(ver, 5, 1, 0.5);
		//display2d(ver, 10, GREEN);
		//EndDrawing();

		shift(vert, buffer, (Vec3) {0, 0, 0}, vertex_count);
		rotate(buffer, buffer, (Vec3) {t, t* 0.1, 0}, vertex_count);
		reflect(buffer, buffer, (Vec3) {0, 0, 1}, vertex_count);
		modify(vert, buffer, (Vec3) {dx, dy, dz}, vertex_count);
		project(buffer, vertex_count);
		display(buffer, edges, vertex_count, edge_count, GREEN);

		t += 0.0001;
	}
	CloseWindow();
	return 0;
}

﻿#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include "Image.h"
#define PI 3.1415926535

int width, height;

Image* image;
Image* image2;

GLboolean ex1 = false;
GLboolean ex2 = false;

GLfloat Delta = 0.0;
GLfloat times = 0.0;
float index = 0;



// 1도는 0.0174533 라디안
#define DR 0.0174533
//그림 참고
// 
// 원을 봤을 때 오른쪽은 0~90 270~360 까지의 각도이고

#define P3 3*PI/2
// 왼쪽은 90~ 180이다.
#define P2 PI/2


int gameState = 0;
typedef struct {
    int w, a, d, s; // 앞 뒤 좌 우 버튼 상태를 저장하는 구조체
}ButtonKeys;

ButtonKeys Keys;
// 32 * 32 사이즈
int All_Textures[] = {          

    //벽 1
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    0,1,1,1,1,1,1,1, 0,1,1,1,1,1,1,1, 0,1,1,1,1,1,1,1, 0,1,1,1,1,1,1,1,
    0,1,1,1,1,1,1,1, 0,1,1,1,1,1,1,1, 0,1,1,1,1,1,1,1, 0,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    1,1,1,1,0,1,1,1, 1,1,1,1,0,1,1,1, 1,1,1,1,0,1,1,1, 1,1,1,1,0,0,0,0,
    1,1,1,1,0,1,1,1, 1,1,1,1,0,1,1,1, 1,1,1,1,0,1,1,1, 1,1,1,1,0,1,1,1,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    0,1,1,1,1,1,1,1, 0,1,1,1,1,1,1,1, 0,1,1,1,1,1,1,1, 0,1,1,1,1,1,1,1,

    0,1,1,1,1,1,1,1, 0,1,1,1,1,1,1,1, 0,1,1,1,1,1,1,1, 0,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    1,1,1,1,0,1,1,1, 1,1,1,1,0,1,1,1, 1,1,1,1,0,1,1,1, 1,1,1,1,0,0,0,0,
    1,1,1,1,0,1,1,1, 1,1,1,1,0,1,1,1, 1,1,1,1,0,1,1,1, 1,1,1,1,0,1,1,1,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    0,1,1,1,1,1,1,1, 0,1,1,1,1,1,1,1, 0,1,1,1,1,1,1,1, 0,1,1,1,1,1,1,1,
    0,1,1,1,1,1,1,1, 0,1,1,1,1,1,1,1, 0,1,1,1,1,1,1,1, 0,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

    1,1,1,1,0,1,1,1, 1,1,1,1,0,1,1,1, 1,1,1,1,0,1,1,1, 1,1,1,1,0,0,0,0,
    1,1,1,1,0,1,1,1, 1,1,1,1,0,1,1,1, 1,1,1,1,0,1,1,1, 1,1,1,1,0,1,1,1,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    0,1,1,1,1,1,1,1, 0,1,1,1,1,1,1,1, 0,1,1,1,1,1,1,1, 0,1,1,1,1,1,1,1,
    0,1,1,1,1,1,1,1, 0,1,1,1,1,1,1,1, 0,1,1,1,1,1,1,1, 0,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    0,1,1,1,1,1,1,1, 0,1,1,1,1,1,1,1, 0,1,1,1,1,1,1,1, 0,1,1,1,1,1,1,1,
    0,1,1,1,1,1,1,1, 0,1,1,1,1,1,1,1, 0,1,1,1,1,1,1,1, 0,1,1,1,1,1,1,1,

    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    1,1,1,1,0,1,1,1, 1,1,1,1,0,1,1,1, 1,1,1,1,0,1,1,1, 1,1,1,1,0,0,0,0,
    1,1,1,1,0,1,1,1, 1,1,1,1,0,1,1,1, 1,1,1,1,0,1,1,1, 1,1,1,1,0,1,1,1,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    0,1,1,1,1,1,1,1, 0,1,1,1,1,1,1,1, 0,1,1,1,1,1,1,1, 0,1,1,1,1,1,1,1,
    0,1,1,1,1,1,1,1, 0,1,1,1,1,1,1,1, 0,1,1,1,1,1,1,1, 0,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    0,1,1,1,1,1,1,1, 0,1,1,1,1,1,1,1, 0,1,1,1,1,1,1,1, 0,1,1,1,1,1,1,1,

    //벽 2
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
    0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
    0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
    0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
    0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
    0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
    0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
    0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
    0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
    0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
    0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    //벽 3
    1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,

    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,

    1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,

    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
    1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
    //문
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    0,0,0,1,1,1,1,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,1,1,1,1,0,0,0,
    0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,
    0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,
    0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,

    0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,
    0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,
    0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,
    0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,
    0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,
    0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,
    0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,
    0,0,0,1,1,1,1,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,1,1,1,1,0,0,0,

    0,0,0,0,0,0,0,0, 0,0,0,0,0,1,0,1, 1,0,1,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0, 0,0,1,1,1,1,0,1, 1,0,1,1,1,1,0,0, 0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,

    0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
    0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
    0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
    0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
    0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
    0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
    0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
    0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
};

//플레이어의 x y 위치와 플레이어 회전에 필요한 각도
float px, py, pdx, pdy, pa;

int mapX = 8, mapY = 8, mapS = 64;

float FixAng(float a) {
    if (a > 359) {
        a -= 360;
    }
    if (a < 0) {
        a += 360;
    }
    return a;
}
// 피타고라스 알고리즘
float dist(float ax, float ay, float bx, float by, float ang) {
    return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay))
        );
}
float degToRad(float a) {
    return a * PI / 180.0;
}
// 8 * 8 매트릭스로 맵을 구현
int mapW[] ={
 2,2,2,2,2,2,2,2,
 2,0,0,0,1,0,0,1,
 2,4,2,0,0,0,0,1,
 2,0,1,0,1,1,1,1,
 2,0,1,1,0,0,0,1,
 4,4,1,1,1,1,0,1,
 2,0,0,0,0,0,0,1,
 3,3,3,3,3,3,3,3,
};
void drawMap2D()
{
    int x, y, xo, yo;
    for (y = 0; y < mapY; y++){
        for (x = 0; x < mapX; x++){
            //벽은 흰색 빈 공간은 검은 색
            if (mapW[y * mapX + x] > 0) {
                glColor3f(1, 1, 1);
            }
            else {
                glColor3f(0, 0, 0);
            }


            xo = x * mapS; yo = y * mapS;

            glBegin(GL_QUADS);
            // 픽셀을 한개씩 더하거나 빼서 
            glVertex2f(0 + xo + 1, 0 + yo + 1);
            glVertex2f(0 + xo + 1, mapS + yo - 1);
            glVertex2f(mapS + xo - 1, mapS + yo - 1);
            glVertex2f(mapS + xo - 1, 0 + yo + 1);
            glEnd();
        }
    }
}
void drawPlayer2D(){
    glColor3f(1, 1, 0);
    glPointSize(8);
    glLineWidth(3);
    // 진행방향을 나타내는 꼭지 한개 만듬
    glBegin(GL_POINTS);
    glVertex2f(px, py);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(px, py);
    glVertex2f(px + pdx * 3, py + pdy * 3);
    glEnd();
}
// 벽에 닿으면 사라지는 레이저 만들기
// 수직을 기준으로 벽에 닿을 때 사라지는 레이저와 
// 수평을 기준으로 벽에 닿았을 때 사라지는 레이저를 만든 뒤
// 그 두개의 값 중 짧은 선을 사용해서 그리면 벽에 닿았을 때
// 무조건 사라지는 레이저를 만들 수 있다.
void drawRays3D() {

    //천장과 바닥을 칠하기
    glColor3f(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex2f(526, 0);
    glVertex2f(1006, 0);
    glVertex2f(1006, 160);
    glVertex2f(526, 160);
    glEnd();
    glColor3f(0.2, 0.2, 0.2);
    glBegin(GL_QUADS);
    glVertex2f(526, 160);
    glVertex2f(1006, 160);
    glVertex2f(1006, 320);
    glVertex2f(526, 320);
    glEnd();

    // 광선이 닿는 부분의 벽 값을 저장한다 ( 벽이 부딪혔는지 확인하고 부딪혔을 때 map[mp]좌표
    int vmt = 0, hmt = 0;
    int r, mx, my, mp, dof;
    float rx, ry, ra, xo, yo, disT;
    //플레이어의 각도에 맞춤 (ra = pa;)
    // 플레이어의 각도로 부터 30도 감소
    //ra는 레이저가 나가는 그 직선
    ra = pa - DR * 30;
    if (ra < 0) {
        ra += 2 * PI;
    }
    if (ra > 2 * PI) {
        ra -= 2 * PI;
    }

    // 60개의 라인을 그리고 마지막에 ra에 1도씩 추가하면 선이 늘어남 (좌우 30도)
    for (r = 0; r < 120; r++) {


        // 수평선 확인
        //atan을 이용해서(접선의 음수 역수가 필요
        dof = 0;
        // 수평에서 가장 짧은 거리를 찾는 disH
        float disH = 10000000, hx = px, hy = py;

        float aTan = -1 / tan(ra);
        // 수평 격자선을 확인해서 ray와 처음으로 닿는 x y 값을 찾습니다. (우리가 만든 8*8 격자선을 말하는 것)

              // ray가 위를 바라보는지 아래를 바라보고 있는지 확인

              // 위를 바라보고 있을 때
        if (ra > PI) {
            ry = (((int)py >> 6) << 6) - 0.0001;
            rx = (py - ry) * aTan + px;
            yo = -64;
            xo = -yo * aTan;
        }
        // 아래를 바라보고 있을 때
        if (ra < PI) {
            ry = (((int)py >> 6) << 6) + 64;
            rx = (py - ry) * aTan + px;
            yo = 64;
            xo = -yo * aTan;
        }
        // 수평을 바라보고 있을 때
        if (ra == 0 || ra == PI) {
            rx = px; ry = py; dof = 8;
        }


        // dof는 우리가 만날 수 있는 수평선을 의미한 것이고 8*8로 만들었기에 최대 8번까지 루프 하는 것
        while (dof < 8) {
            mx = (int)rx >> 6; my = (int)ry >> 6; mp = my * mapX + mx;
            // 벽을 쳤을 때 dof를 8로 만들어서 루프를 종료시키고 현재 벽에 닿은 좌표 (rx,ry) 플레이어 좌표(px,py) 피타고라스 알고리즘으로 그 두 좌표 사이의 거리 disH
            if (mp > 0 && mp < mapX * mapY && mapW[mp] > 0) { hmt = mapW[mp] - 1; hx = rx; hy = ry; disH = dist(px, py, hx, hy, ra); dof = 8; }
            // 만약 벽을 만나지 않고 그 다음 수평선에 닿게 된 거라면 한 번 더 rx 와 ry에 xo값을 더해서(벡터 덧셈) 벽에 닿거나(1에 닿거나)혹은 dof가 증가되서 8이 되면 끝
            else { rx += xo; ry += yo; dof += 1; }
        }
        // 알고리즘 설명
        // 우리가 벽에 대해서 첫 번재 수평 격자선을 확인하도록 지시한 뒤에 벽이 없다면 레이저 좌표(rx,ry)를 xo 값만큼 증가한 뒤에 다시 확인
        // 만약 벽이 있다면 루프를 종료한 뒤에 내 캐릭터 좌표부터 벽에 닿아 루프가 끝난 (rx,ry)좌표 까지 레이저를 만듭니다

        /*
        glColor3f(0, 1, 0);
        glLineWidth(3);
        glBegin(GL_LINES);
        glVertex2i(px, py);
        glVertex2i(rx, ry);
        glEnd();
        */


        // 수직선 확인

        //atan을 이용해서(접선의 음수 역수가 필요
        dof = 0;
        // 수직에서 가장 짧은 거리를 찾는 disV
        float disV = 10000000, vx = px, vy = py;
        float nTan = -tan(ra);
        // 수직 격자선을 확인해서 ray와 처음으로 닿는 x y 값을 찾습니다. (우리가 만든 8*8 격자선을 말하는 것)

              // ray가 좌우를 바라보고 있는지 확인
    //중요한 것은 수직은 수평과 x y 값이 반대여야 합니다.
              // 좌를 바라보고 있을 때
        if (ra > P2 && ra < P3) {
            rx = (((int)px >> 6) << 6) - 0.0001;
            ry = (px - rx) * nTan + py;
            xo = -64;
            yo = -xo * nTan;
        }
        // 우를 바라보고 있을 때
        if (ra < P2 || ra > P3) {
            rx = (((int)px >> 6) << 6) + 64;
            ry = (px - rx) * nTan + py;
            xo = 64;
            yo = -xo * nTan;
        } // 수직을 바라보고 있을 때
        if (ra == 0 || ra == PI) {
            rx = px; ry = py; dof = 8;
        }



        // dof는 우리가 만날 수 있는 수평선을 의미한 것이고 8*8로 만들었기에 최대 8번까지 루프 하는 것
        while (dof < 8) {
            mx = (int)(rx) >> 6; my = (int)(ry) >> 6; mp = my * mapX + mx;
            // 벽을 쳤을 때 dof를 8로 만들어서 루프를 종료시키고 현재 벽에 닿은 좌표 (rx,ry) 플레이어 좌표(px,py) 피타고라스 알고리즘으로 그 두 좌표 사이의 거리 disV
            if (mp > 0 && mp < mapX * mapY && mapW[mp] > 0) { hmt = mapW[mp] - 1; vx = rx; vy = ry; disV = dist(px, py, vx, vy, ra); dof = 8; }
            // 만약 벽을 만나지 않고 그 다음 수평선에 닿게 된 거라면 한 번 더 rx 와 ry에 xo값을 더해서(벡터 덧셈) 벽에 닿거나(1에 닿거나)혹은 dof가 증가되서 8이 되면 끝
            else { rx += xo; ry += yo; dof += 1; }
        }

        float shade = 1;
        // 수직과 수평의 거리를 비교해서 짧은 거리에 있는 좌표를 rx ry로 세팅 후 그리게 되면 벽을 나가는 일 없이 레이저 출력
        if (disV < disH) {
            hmt = vmt;
            rx = vx;
            ry = vy;
            disT = disV;
            shade = 0.5;
            glColor3f(1, 1, 1);
        }
        else if (disH < disV) {
            rx = hx;
            ry = hy;
            disT = disH;
            glColor3f(1.0, 1, 1);
        }
        // 알고리즘 설명
        // 우리가 벽에 대해서 첫 번재 수평 격자선을 확인하도록 지시한 뒤에 벽이 없다면 레이저 좌표(rx,ry)를 xo 값만큼 증가한 뒤에 다시 확인
        // 만약 벽이 있다면 루프를 종료한 뒤에 내 캐릭터 좌표부터 벽에 닿아 루프가 끝난 (rx,ry)좌표 까지 레이저를 만듭니다
        glLineWidth(1);
        glBegin(GL_LINES);
        glVertex2i(px, py);
        glVertex2i(rx, ry);
        glEnd();

        //3D로 만들기
        float ca = pa - ra;
        if (ca < 0) { ca += 2 * PI; }
        if (ca > 2 * PI) { ca -= 2 * PI; } disT = disT * cos(ca);

        // 320 * 160 픽셀로 크기 * 화면 높이 / 길이  
        // 픽셀 크기(64) * 화면 크기(320) / 짧은 광선 길이(disT)
        // 즉 광선의 거리가 길면 길수록 최종 적으로 라인의 높이가 짧아진다.
        // 높이를 320으로 제한해서 그 이상 못가게 제한
        float lineH = (mapS * 320) / disT;
        float ty_step = 32.0 / (float)lineH;
        float ty_off = 0;
        // 화면의 중심을 맞추기 위해서 
        //화면 높이에서 선의 높이(320)의 절반을 뺀 나머지 값 lineO를 구한다
        float lineO = 160 - lineH / 2;



        if (lineH > 320) {
            lineH = 320;
            // 화면의 중심으로 맞춰줌
            ty_off = (lineH - 320) / 2; lineH = 320;
        }

        int y;


        // 닿은 벽의 값 * 32한 값을 넣게되면
        // 레이저가 1이라는 벽에 닿았을 때는 hmt = map[mp] - 1 이므로 0~ 31번째 까지 출력
        // 레이저가 2라는 벽에 닿게 되면 +32가 됨으로 32 ~ 63까지 출력 이 되는 구조
        float ty = ty_off * ty_step + hmt * 32;
        // 현재 x 좌표를 반으로 나눈뒤 mod 32 한 수
        float tx;
        // 만약 180도를 넘으면 위 아래를 뒤집어야 합니다.
        if (shade == 1) { 
            tx = (int)(rx / 2.0) % 32; 
            if (ra > 180) { 
                tx = 31 - tx; 
            } 
        }
        else { tx = (int)(ry / 2.0) % 32; 
        if (ra > 90 && ra < 270) { 
            tx = 31 - tx; 
        } 
        }


        for (y = 0; y < lineH; y++) {
            // 계속 내가 입력한 텍스트를 입히게 함
            // 컬러처럼 쉐이더를 divt나 divh 중 크고 작은 것 중에서 설정해서 만듬
            // 높이 32
            float c = All_Textures[(int)(ty) * 32 + (int)(tx)] * shade;
            if (hmt == 0) { glColor3f(c / 2.0, c / 2.0, c / 2.0); }
            if (hmt == 1) { glColor3f(c / 3.0, c / 3, c / 3.0); }
            if (hmt == 2) { glColor3f(c / 2.0, c / 2.0, c); }
            if (hmt == 3) { glColor3f(c / 2, c / 2, c / 2); }

            glPointSize(8);
            glBegin(GL_POINTS);
            // 8번째 라인마다 라인을 그리고
            // 높이를 중앙으로 맞추기 위해서 
            // 높이를 lineO에서 lineH까지 
            glVertex2f(r * 8 + 530, lineO);
            glVertex2f(r * 8 + 530, y + lineO);
            glEnd();
            ty += ty_step;
        }
        //---draw floors---


        ra += DR / 2;
        if (ra < 0) {
            ra += 2 * PI;
        }
        if (ra > 2 * PI) {
            ra -= 2 * PI;
        }
    }
    ;

}

void init() {

    glClearColor(0, 0, 0, 0);
    px = 300; py = 300;
    pdx = cos(pa) * 5; pdy = sin(pa) * 5;

}
void MyTimer(int Value) {
    Delta = Delta + 0.01;
    printf("%f", Delta);
    glutPostRedisplay();
}
void MyTimer2(int Value) {
    times = times + 0.01;
    printf("%f", times);
    glutPostRedisplay();
}
void MyMainMenu(int entryID) {
    if (entryID == 1)
        ex1 = true;
    else if (entryID == 2)
        ex2 = true;
    else if (entryID == 3)
        exit(0);
    glutPostRedisplay();
}
void display() {


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);
    if (gameState == 0) {  // 게임 초기화
        init();
        index = 0;
        gameState = 1;
    }

    if (gameState == 1) {    // 3초뒤에 화면 나옴
        image = new Image("obj\\startImage.JPG");
        if (index >= 0.2) {
            gameState = 2;

        }

    }
    if (gameState == 2) {  // 게임 시작
        // C언어에선 sin cos 값을 라디안 값으로 받아서 0 ~ 360 대신 0 ~ 2PI로 사용된다
// 좌측으로 보낼 때 pa가 0보다 작으면 pa를 360도로 바꾼 뒤에 sin cos 값을 감소시키는 것으로 객체 회전
        if (Keys.a == 1) { pa -= 0.1; if (pa < 0) { pa += 2 * PI; } pdx = cos(pa) * 5; pdy = sin(pa) * 5; }

        // 만약 2파이를 초과하게 되면 0으로 설정
        // 좌측으로 보낼 때 pa가 360보다 크면 pa를 0도로 바꾼 뒤에 sin cos 값을 증가시키는 것으로 객체 회전
        if (Keys.d == 1) { pa += 0.1; if (pa > 2 * PI) { pa -= 2 * PI; } pdx = cos(pa) * 5; pdy = sin(pa) * 5; }

        // 내 플레이어로 부터 20정도 앞에 상자가 비어있으면 전진 아니면 멈춤


        // 내 플레이어로부터 x y 앞으로 20인 거리에서 공간이 비었는지 확인하고 공간이 비었으면 이동 1이 있으면 멈춤
        int xo = 0; if (pdx < 0) { xo = -20; }
        else { xo = 20; }                                    //x offset to check map

        int yo = 0; if (pdy < 0) { yo = -20; }
        else { yo = 20; }                                    //y offset to check map

        //ipx,y는 현재 내 플레이어가 있는 공간의 위치(8 * 8) 좌표 x y
        // 거기에 앞 뒤로 +- 20이 된 수를 설정한 다음에 이 수가 공간이 비었는지 확인
        int ipx = px / 64.0, ipx_add_xo = (px + xo) / 64.0, ipx_sub_xo = (px - xo) / 64.0;             //x position and offset
        int ipy = py / 64.0, ipy_add_yo = (py + yo) / 64.0, ipy_sub_yo = (py - yo) / 64.0;             //y position and offset

        if (Keys.w == 1)                                                                  //move forward
        {
            if (mapW[ipy * mapX + ipx_add_xo] == 0) { px += pdx; }
            if (mapW[ipy_add_yo * mapX + ipx] == 0) { py += pdy; }
        }
        if (Keys.s == 1)                                                                  //move backward
        {
            if (mapW[ipy * mapX + ipx_sub_xo] == 0) { px -= pdx; }
            if (mapW[ipy_sub_yo * mapX + ipx] == 0) { py -= pdy; }
        }

        drawMap2D();
        drawRays3D();
        drawPlayer2D();

        if (ex1) {
            gameState = 0;
            ex1 = false;
        }
        if (ex2) {
            gameState = 3;
            ex2 = false;
        }


        if ((int)px >> 6 == 6 && (int)py >> 6 == 1) {
            glutTimerFunc(120, MyTimer, 1);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClear(GL_STENCIL_BUFFER_BIT);
            glClearColor(1, 1, 1, 0);
            image2 = new Image("obj\\EndImage1.JPG");

            if (Delta >= 0.9) {
                gameState = 0;
            }
        }

    }
    if (gameState == 3) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClear(GL_STENCIL_BUFFER_BIT);
        glClearColor(1, 1, 1, 0);
        image = new Image("obj\\loseImage.JPG");
        glutTimerFunc(120, MyTimer2, 1);
        if (times >= 0.9) {
            exit(0);
        }
    }

    glutPostRedisplay();
    glutSwapBuffers();
}
void ButtonDown(unsigned char key, int x, int y) {
    if (key == 'a') { Keys.a = 1; }
    if (key == 'd') { Keys.d = 1; }
    if (key == 'w') { Keys.w = 1; }
    if (key == 's') { Keys.s = 1; }

    // 만약 내 앞에 있는 공간이 4라면 e를 눌렸을 때 0으로 만듭니다
    if (key == 'e')             //open doors
    {
        int xo = 0; if (pdx < 0) { xo = -30; }
        else { xo = 30; }
        int yo = 0; if (pdy < 0) { yo = -30; }
        else { yo = 30; }
        int ipx = px / 64.0, ipx_add_xo = (px + xo) / 64.0;
        int ipy = py / 64.0, ipy_add_yo = (py + yo) / 64.0;
        if (mapW[ipy_add_yo * mapX + ipx_add_xo] == 4) { mapW[ipy_add_yo * mapX + ipx_add_xo] = 0; }
    }
    printf("%d", Keys.a);
    glutPostRedisplay();
}
void ButtonUp(unsigned char key, int x, int y) {
    if (key == 'a') { Keys.a = 0; }
    if (key == 'd') { Keys.d = 0; }
    if (key == 'w') { Keys.w = 0; }
    if (key == 's') { Keys.s = 0; }
    glutPostRedisplay();
}

void MyIdle() {
    index = index + 0.001;
    glutPostRedisplay();
}



void resize(int w, int h) {
    // 사이즈가 1024,512 로 고정되게 설정
    glutReshapeWindow(1024, 512);
}


int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1024, 510);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("rayer map");
    gluOrtho2D(0, 1024, 510, 0);
    init();

    GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
    glutAddMenuEntry("다시 시작", 1);
    glutAddMenuEntry("패배", 2);
    glutAddMenuEntry("종료", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutKeyboardFunc(ButtonDown);
    glutKeyboardUpFunc(ButtonUp);
    glutIdleFunc(MyIdle);
    glutMainLoop();
}
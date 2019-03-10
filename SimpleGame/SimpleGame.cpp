/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <Windows.h>
#pragma comment(lib, "winmm.lib")
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include "ScnMgr.h"
#include <chrono>
#include <time.h>
#include "SaveLog.h"
#include "Global.h"

ScnMgr* Scn = NULL;

using namespace std;

DWORD PrevTime = 0;

auto chronobegin = chrono::high_resolution_clock::now();
auto chronoElapesed = chrono::high_resolution_clock::now() - chronobegin;

BOOL g_W = false;
BOOL g_A = false;
BOOL g_S = false;
BOOL g_D = false;

int g_Move = MOVE_NONE;

//주사율에 따른 그리기 (계속 그려준다.)
// 단위 : 시간 -> 초
//		  거리 -> m
void RenderScene(void)
{
	char* Log = new char;

	if (PrevTime == 0) {
		PrevTime = GetTickCount();
		return;
	}
	DWORD CurrTime = GetTickCount();
	DWORD ElapsedTime = CurrTime - PrevTime;
	PrevTime = CurrTime;
	float eTime = (float)ElapsedTime / 1000.f;
	chronoElapesed = chrono::high_resolution_clock::now() - chronobegin;	
	chronobegin = chrono::high_resolution_clock::now();


	Scn->Update(chrono::duration<double>(chronoElapesed).count());
	Scn->RenderScene();
	Scn->Move(g_Move);
	g_Move = MOVE_NONE;

	glutSwapBuffers();
}
void Idle(void)
{
	RenderScene();
}
void MouseInput(int button, int state, int x, int y)
{
	RenderScene();
}
void KeyDownInput(unsigned char key, int x, int y)
{

}
void KeyUpInput(unsigned char key, int x, int y)
{

}
void SpecialKeyDownInput(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		g_Move = MOVE_UP;
		break;
	case GLUT_KEY_DOWN:
		g_Move = MOVE_DOWN;
		break;
	case GLUT_KEY_LEFT:
		g_Move = MOVE_LEFT;
		break;
	case GLUT_KEY_RIGHT:
		g_Move = MOVE_RIGHT;
		break;
	default:
		break;
	}
}
void SpecialKeyUpInput(int key, int x, int y)
{
	g_Move = MOVE_NONE;
}
int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOWSIZE_X, WINDOWSIZE_Y);
	glutCreateWindow("Game Software Engineering KPU");
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	Scn = new ScnMgr();

	//랜더링 하는 함수를 넣어준다
	glutDisplayFunc(RenderScene);
	//가만히 있어도 RenderScene이 호출된다
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyDownInput);
	glutKeyboardUpFunc(KeyUpInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyDownInput);
	glutSpecialUpFunc(SpecialKeyUpInput);

	//루프를 돌면서 화면에 그리기 시작
	glutMainLoop();

    return 0;
}


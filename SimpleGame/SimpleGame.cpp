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

int g_Shoot = SHOOT_NONE;

//�ֻ����� ���� �׸��� (��� �׷��ش�.)
// ���� : �ð� -> ��
//		  �Ÿ� -> m
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
	//cout << chrono::duration<double>(chronoElapesed).count() << "��" << endl;

	//cout << "g_W = " << g_W;
	//cout << " g_A = " << g_A;
	//cout << " g_S = " << g_S;
	//cout << " g_D = " << g_D << endl;

	float ForceX = 0.f;
	float ForceY = 0.f;

	if (g_W)
		ForceY += 100.f;
	if (g_S)
		ForceY -= 100.f;
	if (g_D)
		ForceX += 100.f;
	if (g_A)
		ForceX -= 100.f;

	Scn->ApplyForce(ForceX, ForceY, chrono::duration<double>(chronoElapesed).count());
	Scn->Update(chrono::duration<double>(chronoElapesed).count());
	//Scn->Update(chrono::duration<double>(chronoElapesed).count());
	Scn->RenderScene();
	Scn->Shoot(g_Shoot);
	Scn->GarbageCollector();
	Scn->DoCollisionTest();

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

	switch (key)
	{
	case 'w':
		g_W = TRUE;
		break;
	case 'a': 
		g_A = TRUE;
		break;
	case 's': 
		g_S = TRUE;
		break;
	case 'd': 
		g_D = TRUE;
		break;
	default:
		break;
	}
}

void KeyUpInput(unsigned char key, int x, int y)
{

	switch (key)
	{
	case 'w':
		g_W = FALSE;
		break;
	case 'a':
		g_A = FALSE;
		break;
	case 's':
		g_S = FALSE;
		break;
	case 'd':
		g_D = FALSE;
		break;
	default:
		break;
	}
}

void SpecialKeyDownInput(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		g_Shoot = SHOOT_UP;
		break;
	case GLUT_KEY_DOWN:
		g_Shoot = SHOOT_DOWN;
		break;
	case GLUT_KEY_LEFT:
		g_Shoot = SHOOT_LEFT;
		break;
	case GLUT_KEY_RIGHT:
		g_Shoot = SHOOT_RIGHT;
		break;
	default:
		break;
	}
}

void SpecialKeyUpInput(int key, int x, int y)
{
	g_Shoot = SHOOT_NONE;
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
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

	//������ �ϴ� �Լ��� �־��ش�
	glutDisplayFunc(RenderScene);
	//������ �־ RenderScene�� ȣ��ȴ�
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyDownInput);
	glutKeyboardUpFunc(KeyUpInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyDownInput);
	glutSpecialUpFunc(SpecialKeyUpInput);

	//������ ���鼭 ȭ�鿡 �׸��� ����
	glutMainLoop();

    return 0;
}


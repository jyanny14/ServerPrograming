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
DWORD BulletTime = 0;
float FrameTime = 0;

int ScreenWidth = 1500;
int ScreenHeiht = 1000;

BOOL FrameProblem = false;

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

	//��� ��ǻ�Ͱ� �������� ����ġ�� ������ ��µǴ� ������ ����
	//�� ������ ���� �ϱ� ���� �� ��ǻ�Ϳ����� 0���� Ŭ���ؼ� ��������
	//������ �����ϰ� ��
	if (FrameProblem) 
	{
		if (PrevTime == 0) {
			PrevTime = GetTickCount();
			return;
		}
		DWORD CurrTime = GetTickCount();
		DWORD ElapsedTime = CurrTime - PrevTime;
		float eTime = (float)ElapsedTime / 1000.f;
		if (eTime < 0.014)
			return;
		PrevTime = CurrTime;
	}

	chronoElapesed = chrono::high_resolution_clock::now() - chronobegin;	
	chronobegin = chrono::high_resolution_clock::now();
	
	//cout << chrono::duration<double>(chronoElapesed).count() << "��" << endl;

	//cout << "g_W = " << g_W;
	//cout << " g_A = " << g_A;
	//cout << " g_S = " << g_S;
	//cout << " g_D = " << g_D << endl;

	float ForceX = 0.f;
	float ForceY = 0.f;
	float ForceZ = 0.f;
	float Amount = 100.f;

	if (g_W)
		ForceY += Amount;
	if (g_S)
		ForceY -= Amount;
	if (g_D)
		ForceX += Amount;
	if (g_A)
		ForceX -= Amount;



	Scn->ApplyForce(ForceX, ForceY, ForceZ, chrono::duration<double>(chronoElapesed).count());
	Scn->Update(chrono::duration<double>(chronoElapesed).count());
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
	case '0':
		FrameProblem = 1 - FrameProblem;
		break;
	case 'p':
		Scn->invincibilityClick();
	case ' ':
		Scn->RestartButtonClick();
		break;
	default:
		break;
	}

	Scn->WhatRotation(key);
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
	case ' ':
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
	glutInitWindowSize(ScreenWidth, ScreenHeiht);
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

	Scn = new ScnMgr(ScreenWidth, ScreenHeiht);

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


#include "stdafx.h"
#include "ScnMgr.h"
#include "Object.h"
#include <iostream>

using namespace std;

ScnMgr::ScnMgr() {

	// Initialize Renderer
	//랜더러는 캐릭터마다 하나가 아닌 창 마다 하나씩 존재
	//보통 하나만 필요

	for (int i = 0; i < MAX_OBJECTS; ++i) {
		m_Objects[i] = NULL;
	}
	g_Renderer = NULL;
	g_Renderer = new Renderer(WINDOWSIZE_X, WINDOWSIZE_Y);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	m_TestChess = g_Renderer->CreatePngTexture("./textures/Chess_pawn.png");
	m_TestChessBoard = g_Renderer->CreatePngTexture("./textures/Chess_Board.png");
	for (int i = 0; i < MAX_OBJECTS; ++i) {
		m_Objects[i] = NULL;
	}

	//Create Hero Object
	m_Objects[HERO_ID] = new Object();
	m_Objects[HERO_ID]->SetColor(10, 10, 10, 1);
	m_Objects[HERO_ID]->SetPos(-50, 0, 0);
	m_Objects[HERO_ID]->SetVel(0, 0);
	m_Objects[HERO_ID]->SetSize(100, 100);
	m_Objects[HERO_ID]->SetAccel(0, 0);
	m_Objects[HERO_ID]->SetMass(0.5);
	m_Objects[HERO_ID]->SetCoefFriction(10.f);
	m_Objects[HERO_ID]->SetKind(HERO_ID);

}

ScnMgr::~ScnMgr(){ 
	if (g_Renderer)
		delete g_Renderer;
	if (m_Objects[HERO_ID])
		delete m_Objects[HERO_ID];
}

void ScnMgr::RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//바탕색 설정
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

	g_Renderer->DrawTextureRectDepth(0, 0, 0, 800, 800, 1, 1, 1, 1,
		m_TestChessBoard, 1.f);

	for (int i = 0; i < MAX_OBJECTS; ++i) {
		//예외처리
		if (m_Objects[i] != NULL) {
			float x, y, z, sizeX, sizeY, red, green, blue, alpha, w, h;
			m_Objects[i]->GetPos(&x, &y, &z);
			m_Objects[i]->GetSize(&sizeX, &sizeY);
			m_Objects[i]->GetColor(&red, &green, &blue, &alpha);
			
			// Texture Test
			g_Renderer->DrawTextureRect(x, y, 0.f, sizeX, sizeY, red, green, blue, alpha,
				m_TestChess);

		}

	}

}

void ScnMgr::Update(float eTime) {

	for (int i = 0; i < MAX_OBJECTS; ++i) {
		if(m_Objects[i] != NULL)
			m_Objects[i]->Update(eTime);
	}
}

void ScnMgr::DoCollisionTest() {
	for (int i = 0; i < MAX_OBJECTS; ++i) 
	{
		if (m_Objects[i] == NULL)
		{
			continue;
		}
		for (int j = 0; j < MAX_OBJECTS; ++j) 
		{
			if (m_Objects[j] == NULL)
			{
				continue;
			}

			if (i == j)
			{
				continue;
			}

			float pX, pY, pZ;
			float sX, sY;
			float minX, minY, maxX, maxY;
			m_Objects[i]->GetPos(&pX, &pY, &pZ);
			m_Objects[i]->GetSize(&sX, &sY);
			minX = pX - sX / 2.f;
			maxX = pX + sX / 2.f;
			minY = pY - sY / 2.f;
			maxY = pY + sY / 2.f;


			//cout << j << endl;
			float pX1, pY1, pZ1;
			float sX1, sY1;
			float minX1, minY1, maxX1, maxY1;
			m_Objects[j]->GetPos(&pX1, &pY1, &pZ1);
			m_Objects[j]->GetSize(&sX1, &sY1);
			minX1 = pX1 - sX1 / 2.f;
			maxX1 = pX1 + sX1 / 2.f;
			minY1 = pY1 - sY1 / 2.f;
			maxY1 = pY1 + sY1 / 2.f;

			if (CollisionRec(minX, minY, maxX, maxY, minX1, minY1, maxX1, maxY1))
			{
				cout << "Collision\n" << endl;
			}
		}
	}
}

void ScnMgr::GarbageCollector() {
}

bool ScnMgr::CollisionRec(float minX, float minY, float maxX, float maxY,
	float min1X, float min1Y, float max1X, float max1Y) {


	if (maxX < min1X)
		return false;
	if (max1X < minX)
		return false;
	if (maxY < min1Y)
		return false;
	if (max1Y < minY)
		return false;

	return true;
}


void ScnMgr::ApplyForce(float x, float y, float eTime) {
	m_Objects[HERO_ID]->ApplyForce(x, y, eTime);
}

void ScnMgr::AddObject(float x, float y, float z,
	float sx, float sy,
	float vx, float vy) {
	int id = FindEmptyObjectSlot();
	if (id == -1) {
		std::cout << "Error no more Slot" << std::endl;
		return;
	}
	m_Objects[id] = new Object();
	m_Objects[id]->SetPos(x, y, z);
	m_Objects[id]->SetVel(vx, vy);
	m_Objects[id]->SetSize(sx, sy);
	m_Objects[id]->SetAccel(0.f, 0.f);
	m_Objects[id]->SetMass(1.f);
	m_Objects[id]->SetCoefFriction(10.f);
	m_Objects[id]->SetColor(0.f, 0.f, 0.f, 0.f);
	m_Objects[id]->SetKind(KIND_BULLET);
}

void ScnMgr::DeleteObject(int id) {
	if (m_Objects[id] != NULL) {
		delete m_Objects[id];
		m_Objects[id] = NULL;
	}
}

int ScnMgr::FindEmptyObjectSlot() {
	for (int i = 0; i < MAX_OBJECTS; ++i) {
		if (m_Objects[i] == NULL)
			return i;
	}
	std::cout << "no more slot" << std::endl;
	return -1;
}

void ScnMgr::Move(int key) {

	float PosX, PosY, PosZ;

	if (key == MOVE_NONE)
		return;
	if (m_Objects[0] == NULL)
		return;

	m_Objects[0]->GetPos(&PosX, &PosY, &PosZ);

	switch (key)
	{
	case MOVE_UP:
		if (PosY < 400)
			PosY += 100;
		break;
	case MOVE_DOWN:
		if (PosY > -300)
			PosY -= 100;
		break;
	case MOVE_LEFT:
		if (PosX > -350)
			PosX -= 100;
		break;
	case MOVE_RIGHT:
		if (PosX < 350)
			PosX += 100;
		break;
	default:
		break;
	}
	m_Objects[0]->SetPos(PosX, PosY, PosZ);

}

void ScnMgr::GetRenderer(Renderer* r) {
	r = g_Renderer;
}

void ScnMgr::GetObject(Object * o) {
	o = m_Objects[HERO_ID];
}


#include "stdafx.h"
#include "ScnMgr.h"
#include "Object.h"
#include <iostream>

using namespace std;

ScnMgr::ScnMgr(int width, int height) {

	// Initialize Renderer
	//랜더러는 캐릭터마다 하나가 아닌 창 마다 하나씩 존재
	//보통 하나만 필요

	for (int i = 0; i < MAX_OBJECTS; ++i) {
		m_Objects[i] = NULL;
	}

	//초기화
	g_Renderer = NULL;
	HeroBodyanimX = 0;
	HeroBodyanimY = 0;
	HeroHeadanimX = 0;
	HeroHeadanimY = 0;
	Boss1animX = 0;
	Boss1animY = 0;
	Boss1SlowAnim = 0;
	Boss1Patten = 0;
	PassNextMap = 0;

	Boss2Patten1 = 0;
	Boss2Patten2 = 0;

	Boss3animX = 0;
	Boss3animY = 0;
	Boss3SlowAnim = 0;
	Boss3Patten1 = 0;
	Boss3Patten2 = 0;
	Boss3Patten3 = 0;
	Boss3Patten3_Cooltime = 0;

	HeroBodytotalSeqX = 10;
	HeroBodytotalSeqY = 1;
	HeroHeadtotalSeqX = 2;
	HeroHeadtotalSeqY = 1;
	Boss1totalSeqX = 3;
	Boss1totalSeqY = 2;
	Boss3totalSeqX = 1;
	Boss3totalSeqY = 10;
	
	DeathanimX = 0;
	DeathanimY = 0;
	DeathtotalSeqX = 6;
	DeathtotalSeqY = 1;
	DeathSlowAnim = 0;

	MapState = START_MAP;

	ParticleTime = 0;

	RestartButton = 0;

	coolTime = 0.5f;

	g_Renderer = new Renderer(width, height);

	m_Sound = new Sound();

	//음악
	m_SoundBG = m_Sound->CreateSound("./Sound/OST.mp3");
	m_SoundHit = m_Sound->CreateSound("./Sound/Isaac_Hurt.mp3");
	m_SoundFire = m_Sound->CreateSound("./Sound/Shoot.mp3");
	m_SoundEnemyFire = m_Sound->CreateSound("./Sound/bloodshoot.mp3");
	m_SoundExplosion = m_Sound->CreateSound("./Sound/boss_explosions.mp3");
	m_SoundFinalBoss = m_Sound->CreateSound("./Sound/FinalBoss.mp3");
	m_SoundFinalBoss2 = m_Sound->CreateSound("./Sound/FinalBoss2.mp3");
	m_SoundFinalBoss3 = m_Sound->CreateSound("./Sound/FinalBoss3.mp3");

	m_Sound->PlaySound(m_SoundBG, true, 3.f);

	ScreenWidth = width;
	ScreenHeiht = height;

	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	//Test
	m_TestTexture = g_Renderer->CreatePngTexture("./textures/invisibleWall.png");

	//Map
	m_MapTexture = g_Renderer->CreatePngTexture("./textures/Room.png");
	m_MapTexture_2 = g_Renderer->CreatePngTexture("./textures/Room2.png");
	m_MapTexture_3 = g_Renderer->CreatePngTexture("./textures/Room3.png");
	m_MapTexture_4 = g_Renderer->CreatePngTexture("./textures/Room4.png");

	//Restart
	m_RestartTexture_1 = g_Renderer->CreatePngTexture("./textures/Death_Background1.png");
	m_RestartTexture_2 = g_Renderer->CreatePngTexture("./textures/Death_Background2.png");

	//Bullet
	m_BulletTexture = g_Renderer->CreatePngTexture("./textures/Snow.png");

	//Body
	m_HeroBodyLeftTexture = g_Renderer->CreatePngTexture("./textures/LeftMove.png");
	m_HeroBodyRightTexture = g_Renderer->CreatePngTexture("./textures/RightMove.png");
	m_HeroBodyUpTexture = g_Renderer->CreatePngTexture("./textures/BackMove.png");
	m_HeroBodyDownTexture = g_Renderer->CreatePngTexture("./textures/ForwardMove.png");

	//Head
	m_HeroHeadLeftTexture = g_Renderer->CreatePngTexture("./textures/LeftShoot.png");
	m_HeroHeadRightTexture = g_Renderer->CreatePngTexture("./textures/RightShoot.png");
	m_HeroHeadUpTexture = g_Renderer->CreatePngTexture("./textures/BackShoot.png");
	m_HeroHeadDownTexture = g_Renderer->CreatePngTexture("./textures/ForwardShoot.png");

	//HP
	m_FullHPTexture = g_Renderer->CreatePngTexture("./textures/Full.png");
	m_HalfHPTexture = g_Renderer->CreatePngTexture("./textures/Half.png");
	m_EmptyHPTexture = g_Renderer->CreatePngTexture("./textures/Empty.png");

	//Boss1
	m_Boss1Texture = g_Renderer->CreatePngTexture("./textures/Boss_1.png");

	//Boss2
	m_Boss2Texture = g_Renderer->CreatePngTexture("./textures/Boss_2.png");

	//Boss3
	m_Boss3Texture = g_Renderer->CreatePngTexture("./textures/Boss_3.png");
	m_Boss3P1Texture = g_Renderer->CreatePngTexture("./textures/Boss_3_Patten1.png");
	m_Boss3P2Texture = g_Renderer->CreatePngTexture("./textures/Boss_3_Patten2.png");
	m_Boss3P3Texture = g_Renderer->CreatePngTexture("./textures/Boss_3_Patten3.png");

	//Death
	m_ExplosionTexture = g_Renderer->CreatePngTexture("./textures/bloodExplosion2.png");

	//BossBullet
	m_BossBulletTexture = g_Renderer->CreatePngTexture("./textures/BossBullet.png");

	for (int i = 0; i < MAX_OBJECTS; ++i) {
		m_Objects[i] = NULL;
	}

	//Create Hero Object
	m_Objects[HERO_ID] = new Object();
	m_Objects[HERO_ID]->SetColor(1, 1, 1, 1);
	m_Objects[HERO_ID]->SetPos(0, 0, 20.f);
	m_Objects[HERO_ID]->SetVel(0, 0, 0);
	m_Objects[HERO_ID]->SetSize(0.5f, 0.5f, 0.5f);
	m_Objects[HERO_ID]->SetAccel(0, 0, 0);
	m_Objects[HERO_ID]->SetMass(0.5);
	m_Objects[HERO_ID]->SetCoefFriction(10.f);
	m_Objects[HERO_ID]->SetKind(HERO_ID);
	m_Objects[HERO_ID]->SetHP(6);

	//벽 생성
	//벽은 보이지 않고 그냥 배경의 벽 충돌을 재현하기 위한 것
	AddObject(ScreenWidth / 2 - 100, 0.f - 500, 0.f, 1, ScreenHeiht, 1, 0, 0, 0, KIND_BUILDING, 10000000, 0, 0);
	AddObject(-ScreenWidth / 2 + 100, 0.f, 0.f, 1, ScreenHeiht, 1, 0, 0, 0, KIND_BUILDING, 10000000, 0, 0);
	AddObject(0, ScreenHeiht / 2 - 100, 0.f, ScreenWidth, 1, 1, 0, 0, 0, KIND_BUILDING, 10000000, 0, 0);
	AddObject(0, -ScreenHeiht / 2 + 100, 0.f, ScreenWidth, 1, 1, 0, 0, 0, KIND_BUILDING, 10000000, 0, 0);

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
	//glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
	

	if (MapState == START_MAP)
	{
		g_Renderer->DrawTextureRectDepth(0.f, 0.f, 0.f, ScreenWidth, ScreenHeiht, 1, 1, 1, 1, m_MapTexture, 1);
	}
	else if (PassNextMap >= 4 && RestartButton == 0)
	{
		g_Renderer->DrawTextureRectDepth(0.f, 0.f, 0.f, ScreenWidth, ScreenHeiht, 1, 1, 1, 1, m_RestartTexture_1, 0);
		return;
	}
	else if (PassNextMap >= 4 && RestartButton == 1)
	{
		g_Renderer->DrawTextureRectDepth(0.f, 0.f, 0.f, ScreenWidth, ScreenHeiht, 1, 1, 1, 1, m_RestartTexture_2, 0);
		return;
	}
	else if(MapState == ENEMY_MAP)
	{
		g_Renderer->DrawTextureRectDepth(0.f, 0.f, 0.f, ScreenWidth, ScreenHeiht, 1, 1, 1, 1, m_MapTexture_2, 1);
	}
	else if (MapState == ENEMY_MAP_2)
	{
		g_Renderer->DrawTextureRectDepth(0.f, 0.f, 0.f, ScreenWidth, ScreenHeiht, 1, 1, 1, 1, m_MapTexture_3, 1);
	}
	else if (MapState == ENEMY_MAP_3)
	{
		g_Renderer->DrawTextureRectDepth(0.f, 0.f, 0.f, ScreenWidth, ScreenHeiht, 1, 1, 1, 1, m_MapTexture_4, 1);
	}

	for (int i = 0; i < MAX_OBJECTS; ++i) 
	{
		//예외처리
		if (m_Objects[i] != NULL) 
		{
			float x, y, z, sizeX, sizeY, sizeZ, red, green, blue, alpha, w, h;
			int kind;
			int RotState;
			int HP;
			m_Objects[i]->GetPos(&x, &y, &z);
			m_Objects[i]->GetSize(&sizeX, &sizeY, &sizeZ);
			m_Objects[i]->GetColor(&red, &green, &blue, &alpha);
			m_Objects[i]->GetKind(&kind);
			m_Objects[i]->GetRotState(&RotState);

			// Texture
			if (i == HERO_ID)
			{
				m_Objects[i]->GetHP(&HP);

				//Show HP
				//플레이어 체력은 하트 이미지로 보여준다.
				switch (HP)
				{
				case 0:
					g_Renderer->DrawTextureRectDepth(-550.0, 400.0, 0.f, 50, 50, 1, 1, 1, 1, m_EmptyHPTexture, 0);
					g_Renderer->DrawTextureRectDepth(-600.0, 400.0, 0.f, 50, 50, 1, 1, 1, 1, m_EmptyHPTexture, 0);
					g_Renderer->DrawTextureRectDepth(-650.0, 400.0, 0.f, 50, 50, 1, 1, 1, 1, m_EmptyHPTexture, 0);
					break;
				case 1:
					g_Renderer->DrawTextureRectDepth(-550.0, 400.0, 0.f, 50, 50, 1, 1, 1, 1, m_EmptyHPTexture, 0);
					g_Renderer->DrawTextureRectDepth(-600.0, 400.0, 0.f, 50, 50, 1, 1, 1, 1, m_EmptyHPTexture, 0);
					g_Renderer->DrawTextureRectDepth(-650.0, 400.0, 0.f, 50, 50, 1, 1, 1, 1, m_HalfHPTexture, 0);
					break;
				case 2:
					g_Renderer->DrawTextureRectDepth(-550.0, 400.0, 0.f, 50, 50, 1, 1, 1, 1, m_EmptyHPTexture, 0);
					g_Renderer->DrawTextureRectDepth(-600.0, 400.0, 0.f, 50, 50, 1, 1, 1, 1, m_EmptyHPTexture, 0);
					g_Renderer->DrawTextureRectDepth(-650.0, 400.0, 0.f, 50, 50, 1, 1, 1, 1, m_FullHPTexture, 0);
					break;
				case 3:
					g_Renderer->DrawTextureRectDepth(-550.0, 400.0, 0.f, 50, 50, 1, 1, 1, 1, m_EmptyHPTexture, 0);
					g_Renderer->DrawTextureRectDepth(-600.0, 400.0, 0.f, 50, 50, 1, 1, 1, 1, m_HalfHPTexture, 0);
					g_Renderer->DrawTextureRectDepth(-650.0, 400.0, 0.f, 50, 50, 1, 1, 1, 1, m_FullHPTexture, 0);
					break;
				case 4:
					g_Renderer->DrawTextureRectDepth(-550.0, 400.0, 0.f, 50, 50, 1, 1, 1, 1, m_EmptyHPTexture, 0);
					g_Renderer->DrawTextureRectDepth(-600.0, 400.0, 0.f, 50, 50, 1, 1, 1, 1, m_FullHPTexture, 0);
					g_Renderer->DrawTextureRectDepth(-650.0, 400.0, 0.f, 50, 50, 1, 1, 1, 1, m_FullHPTexture, 0);
					break;
				case 5:
					g_Renderer->DrawTextureRectDepth(-550.0, 400.0, 0.f, 50, 50, 1, 1, 1, 1, m_HalfHPTexture, 0);
					g_Renderer->DrawTextureRectDepth(-600.0, 400.0, 0.f, 50, 50, 1, 1, 1, 1, m_FullHPTexture, 0);
					g_Renderer->DrawTextureRectDepth(-650.0, 400.0, 0.f, 50, 50, 1, 1, 1, 1, m_FullHPTexture, 0);
					break;
				case 6:
					g_Renderer->DrawTextureRectDepth(-550.0, 400.0, 0.f, 50, 50, 1, 1, 1, 1, m_FullHPTexture, 0);
					g_Renderer->DrawTextureRectDepth(-600.0, 400.0, 0.f, 50, 50, 1, 1, 1, 1, m_FullHPTexture, 0);
					g_Renderer->DrawTextureRectDepth(-650.0, 400.0, 0.f, 50, 50, 1, 1, 1, 1, m_FullHPTexture, 0);
					break;
				default:
					break;
				}

				//cout << "x = " << x << " y = " << y << " z = " << z << endl;

				//문에 접근했을 때 다음 방으로 갈 수 있는 조건
				if (x >= 550 && -50 <= y && y <= 50)
				{
					//다음 방에 가면 몬스터를 넣어준다.
					if (MapState == START_MAP)
					{
						MapState = ENEMY_MAP;
						PassNextMap = 1;

						AddObject(0.f, 0.f, 0.f, 1.f, 1.f, 0.f,
							0.f, 0.f, 0.f,
							KIND_ENEMY,
							ENEMY_HP, 0, MOVE_DOWN);

						m_Objects[i]->SetPos(-500.0, y, z);
						m_Objects[i]->SetVel(0, 0, 0);
					}
					else if (MapState == ENEMY_MAP && PassNextMap == 2)
					{
						MapState = ENEMY_MAP_2;

						AddObject(0.f, 0.f, 0.f, 1.f, 1.f, 0.f,
							0.f, 0.f, 0.f,
							KIND_ENEMY2,
							ENEMY2_HP, 0, MOVE_DOWN);

						m_Objects[i]->SetPos(-500.0, y, z);
						m_Objects[i]->SetVel(0, 0, 0);
					}
					else if (MapState == ENEMY_MAP_2 && PassNextMap == 3)
					{
						MapState = ENEMY_MAP_3;

						AddObject(0.f, 300, 0.f, 4.f, 4.f, 0.f,
							0.f, 0.f, 0.f,
							KIND_ENEMY3,
							ENEMY3_HP, 0, MOVE_DOWN);

						m_Objects[i]->SetPos(-500.0, y, z);
						m_Objects[i]->SetVel(0, 0, 0);
					}
				}
				switch (RotState)
				{
				case MOVE_RIGHT:
					g_Renderer->DrawTextureRectSeqXYHeight(x + (10 - (HeroBodyanimX * 2)), y, z, sizeX, sizeY, red, green, blue, alpha,
						m_HeroBodyRightTexture, HeroBodyanimX, HeroBodyanimY, HeroBodytotalSeqX, HeroBodytotalSeqY, z);

					g_Renderer->DrawTextureRectSeqXYDepth(x, y + 55, z, sizeX, sizeY, red, green, blue, alpha,
						m_HeroHeadRightTexture, HeroHeadanimX, HeroHeadanimY, HeroHeadtotalSeqX, HeroHeadtotalSeqY, 0);
					break;
				case MOVE_LEFT:
					g_Renderer->DrawTextureRectSeqXYHeight(x + (10 - (HeroBodyanimX * 2)), y, z, sizeX, sizeY, red, green, blue, alpha,
						m_HeroBodyLeftTexture, HeroBodyanimX, HeroBodyanimY, HeroBodytotalSeqX, HeroBodytotalSeqY, z);

					g_Renderer->DrawTextureRectSeqXYDepth(x, y + 55, z - 35, sizeX, sizeY, red, green, blue, alpha,
						m_HeroHeadLeftTexture, HeroHeadanimX, HeroHeadanimY, HeroHeadtotalSeqX, HeroHeadtotalSeqY, 0);

					break;
				case MOVE_DOWN:
					g_Renderer->DrawTextureRectSeqXYHeight(x + (10 - (HeroBodyanimX * 2)), y, z, sizeX, sizeY, red, green, blue, alpha,
						m_HeroBodyDownTexture, HeroBodyanimX, HeroBodyanimY, HeroBodytotalSeqX, HeroBodytotalSeqY, z);

					g_Renderer->DrawTextureRectSeqXYDepth(x, y + 55, z, sizeX, sizeY, red, green, blue, alpha,
						m_HeroHeadDownTexture, HeroHeadanimX, HeroHeadanimY, HeroHeadtotalSeqX, HeroHeadtotalSeqY, 0);
					break;
				case MOVE_UP:
					g_Renderer->DrawTextureRectSeqXYHeight(x + (10 - (HeroBodyanimX * 2)), y, z, sizeX, sizeY, red, green, blue, alpha,
						m_HeroBodyUpTexture, HeroBodyanimX, HeroBodyanimY, HeroBodytotalSeqX, HeroBodytotalSeqY, z);

					g_Renderer->DrawTextureRectSeqXYDepth(x, y + 55, z, sizeX, sizeY, red, green, blue, alpha,
						m_HeroHeadUpTexture, HeroHeadanimX, HeroHeadanimY, HeroHeadtotalSeqX, HeroHeadtotalSeqY, 0);
					break;
				default:
					break;
				}

				if (HeroBodyanimX >= HeroBodytotalSeqX - 1) {
					HeroBodyanimX = 0;
					HeroBodyanimY++;
					HeroBodyanimY %= HeroBodytotalSeqY;
				}
				else
					HeroBodyanimX++;

			}
			else if(kind == KIND_BUILDING)
			{
				//투명한 건물
				g_Renderer->DrawTextureRectDepth(x, y, z, sizeX, sizeY, red, green, blue, alpha, m_TestTexture, 1);
			}
			else if (kind == KIND_BULLET)
			{
				//DrawTextureRectDepth를 이용해서 그리니 높이가 잘 표현되지 않는 것 같음 그래서 사용한 switch문
				switch (RotState)
				{
				case MOVE_RIGHT:
					g_Renderer->DrawParticle(x, y, z,
						1,
						1, 1, 1, 1,
						-0.1, -0.1,
						m_BulletTexture, ParticleTime);
					y -= 0.3;
					m_Objects[i]->SetPos(x, y, z);
					break;
				case MOVE_LEFT:
					g_Renderer->DrawParticle(x, y, z,
						1,
						1, 1, 1, 1,
						0.1, -0.1,
						m_BulletTexture, ParticleTime);
					y -= 0.3;
					m_Objects[i]->SetPos(x, y, z);
					break;
				case MOVE_DOWN:
					g_Renderer->DrawParticle(x, y, z,
						1,
						1, 1, 1, 1,
						0, 0.1,
						m_BulletTexture, ParticleTime);
					y += 0.3;
					m_Objects[i]->SetPos(x, y, z);
					break;
				case MOVE_UP:
					g_Renderer->DrawParticle(x, y, z,
						1,
						1, 1, 1, 1,
						0, -0.1,
						m_BulletTexture, ParticleTime);
					y -= 0.3;
					m_Objects[i]->SetPos(x, y, z);
					break;
				default:
					break;
				}
				g_Renderer->DrawTextureRectDepth(x, y, z, sizeX, sizeY, red, green, blue, alpha, m_BulletTexture, 0);
			}
			else if (kind == KIND_ENEMY)
			{
				m_Objects[i]->GetHP(&HP);			
				g_Renderer->DrawSolidRectGauge(0, 400, 0, 500, 50, 1, 0, 0, 1, 1, (float)((float)HP/ (float)ENEMY_HP));
				g_Renderer->DrawTextureRectSeqXYDepth(x, y, z, sizeX, sizeY, red, green, blue, alpha,
					m_Boss1Texture, Boss1animX, Boss1animY, Boss1totalSeqX, Boss1totalSeqY, 0);

				Boss1SlowAnim++;

				if (Boss1SlowAnim >= 15)
				{
					if (Boss1animX >= Boss1totalSeqX - 2) {
						Boss1animX = 0;
						Boss1animY++;
						Boss1animY %= Boss1totalSeqY;
					}
					else
						Boss1animX++;

					if (Boss1animX == 1 && Boss1animY == 1)
					{
						Boss1Shoot();
					}

					Boss1SlowAnim = 0;
				}

			}
			else if (kind == KIND_ENEMY_BULLET)
			{
				switch (RotState)
				{
				case MOVE_RIGHT:
					g_Renderer->DrawParticle(x, y, z,
						1,
						1, 1, 1, 1,
						-0.1, -0.1,
						m_BossBulletTexture, ParticleTime);
					y -= 0.3;
					m_Objects[i]->SetPos(x, y, z);
					break;
				case MOVE_LEFT:
					g_Renderer->DrawParticle(x, y, z,
						1,
						1, 1, 1, 1,
						0.1, -0.1,
						m_BossBulletTexture, ParticleTime);
					y -= 0.3;
					m_Objects[i]->SetPos(x, y, z);
					break;
				case MOVE_DOWN:
					g_Renderer->DrawParticle(x, y, z,
						1,
						1, 1, 1, 1,
						0, 0.1,
						m_BossBulletTexture, ParticleTime);
					y += 0.3;
					m_Objects[i]->SetPos(x, y, z);
					break;
				case MOVE_UP:
					g_Renderer->DrawParticle(x, y, z,
						1,
						1, 1, 1, 1,
						0, -0.1,
						m_BossBulletTexture, ParticleTime);
					y -= 0.3;
					m_Objects[i]->SetPos(x, y, z);
					break;
				default:
					break;
				}
				g_Renderer->DrawTextureRectDepth(x, y, z, sizeX, sizeY, red, green, blue, alpha, m_BossBulletTexture, 0);
			}
			else if (kind == KIND_ENEMY2)
			{
				m_Objects[i]->GetHP(&HP);
				g_Renderer->DrawSolidRectGauge(0, 400, 0, 500, 50, 1, 0, 0, 1, 1, (float)((float)HP / (float)ENEMY2_HP));
				g_Renderer->DrawTextureRectDepth(x, y, z, sizeX, sizeY, red, green, blue, alpha, m_Boss2Texture, 0);
			
				Boss2Patten1++;
				Boss2Patten2++;

				if (Boss2Patten1 > 50)
				{
					Boss2Move(i);
					Boss2Patten1 = 0;
				}
				if (Boss2Patten2 > 100)
				{
					Boss2Shoot(x, y, z);
					Boss2Patten2 = 0;
				}

			}
			else if (kind == KIND_ENEMY2_BULLET) 
			{
				g_Renderer->DrawTextureRectDepth(x, y, z, sizeX, sizeY, red, green, blue, alpha, m_Boss2Texture, 0);
			
				if (Boss2Patten1 > 40)
				{
					Boss2Move(i);
				}
			}
			else if (kind == KIND_ENEMY3) 
			{
				m_Objects[i]->GetHP(&HP);
				g_Renderer->DrawSolidRectGauge(0, 400, 0, 500, 50, 1, 0, 0, 1, 1, (float)((float)HP / (float)ENEMY3_HP));
				g_Renderer->DrawTextureRectSeqXYDepth(x, y, z, sizeX, sizeY, red, green, blue, alpha,
					m_Boss3Texture, Boss3animX, Boss3animY, Boss3totalSeqX, Boss3totalSeqY, 0);

				Boss3SlowAnim++;
				Boss3Patten1++;
				Boss3Patten2++;
				Boss3Patten3++;

				if (Boss3SlowAnim >= 10)
				{
					if (Boss3animX >= Boss3totalSeqX - 1) {
						Boss3animX = 0;
						Boss3animY++;
						Boss3animY %= Boss3totalSeqY;
					}
					else
						Boss3animX++;

					Boss3SlowAnim = 0;
				}

				if (Boss3Patten1 >= 200) 
				{
					Boss3Patten1Start();
					m_Sound->PlaySound(m_SoundFinalBoss, false, 3.f);
					Boss3Patten1 = 0;
				}
				if (Boss3Patten2 >= 150)
				{
					Boss3Patten2Start();
					m_Sound->PlaySound(m_SoundFinalBoss2, false, 3.f);
					Boss3Patten2 = 0;
				}
				if (Boss3Patten3 >= 500)
				{
					Boss3Patten3Start();
					m_Sound->PlaySound(m_SoundFinalBoss3, false, 3.f);
					Boss3Patten3 = 0;
				}
			}
			else if (kind == KIND_ENEMY3_Patten1) 
			{
				g_Renderer->DrawTextureRectDepth(x, y, z, sizeX, sizeY, red, green, blue, alpha, m_Boss3P1Texture, 0);
			}
			else if (kind == KIND_ENEMY3_Patten2)
			{
				g_Renderer->DrawTextureRectDepth(x, y, z, sizeX, sizeY, red, green, blue, alpha, m_Boss3P2Texture, 0);
			}
			else if (kind == KIND_ENEMY3_Patten3)
			{
				int ShootNow = 0;
				g_Renderer->DrawTextureRectDepth(x, y, z, sizeX, sizeY, red, green, blue, alpha, m_Boss3P3Texture, 0);

				Boss3Patten3_Cooltime++;
				ShootNow = Boss3Patten3_Cooltime % 200;
				if (ShootNow == 0)
				{
					Boss3Shoot(x, y, z);
				}
			}
			else if (kind == KIND_DEATH_EFFACT) 
			{
				g_Renderer->DrawTextureRectSeqXYDepth(x, y, z, sizeX, sizeY, red, green, blue, alpha,
					m_ExplosionTexture, DeathanimX, DeathanimY, DeathtotalSeqX, DeathtotalSeqY, 0);

				DeathSlowAnim++;

				if (DeathSlowAnim >= 10)
				{
					if (DeathanimX >= DeathtotalSeqX - 1) {
						DeathanimX = 0;
						DeathanimY++;
						DeathanimY %= DeathtotalSeqY;
					}
					else
						DeathanimX++;

					DeathSlowAnim = 0;
					DeleteObject(i);
					continue;
				}
			}
		}

	}
	//배경 파티클
	ParticleTime+= 0.01;
	g_Renderer->DrawParticleClimate(
		0, 0, 0,
		5,
		1, 1, 1, 1,
		-1, 1,
		m_BulletTexture, ParticleTime, ParticleTime
	);

}

void ScnMgr::Update(float eTime) 
{

	for (int i = 0; i < MAX_OBJECTS; ++i) {
		if (m_Objects[i] != NULL) 
		{
			m_Objects[i]->Update(eTime);
		}
	}
}

void ScnMgr::DoCollisionTest() {
	for (int i = 0; i < MAX_OBJECTS; ++i) 
	{
		if (m_Objects[i] == NULL)
		{
			continue;
		}

		int CollisionCount = 0;

		for (int j = i+1; j < MAX_OBJECTS; ++j) 
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
			float sX, sY, sZ;
			float minX, minY, minZ, maxX, maxY, maxZ;
			m_Objects[i]->GetPos(&pX, &pY, &pZ);
			m_Objects[i]->GetSize(&sX, &sY, &sZ);
			minX = pX - sX / 2.f;
			maxX = pX + sX / 2.f;
			minY = pY - sY / 2.f;
			maxY = pY + sY / 2.f;
			minZ = pZ - sZ / 2.f;
			maxZ = pZ + sZ / 2.f;


			//cout << j << endl;
			float pX1, pY1, pZ1;
			float sX1, sY1, sZ1;
			float minX1, minY1, minZ1, maxX1, maxY1, maxZ1;
			m_Objects[j]->GetPos(&pX1, &pY1, &pZ1);
			m_Objects[j]->GetSize(&sX1, &sY1, &sZ1);
			minX1 = pX1 - sX1 / 2.f;
			maxX1 = pX1 + sX1 / 2.f;
			minY1 = pY1 - sY1 / 2.f;
			maxY1 = pY1 + sY1 / 2.f;
			minZ1 = pZ1 - sZ1 / 2.f;
			maxZ1 = pZ1 + sZ1 / 2.f;

			//if (CollisionRec(minX, minY, maxX, maxY, minX1, minY1, maxX1, maxY1))
			//{
			//	//cout << "Collision\n" << endl;
			//	CollisionCount++;
			//}

			if (CollisionBox(minX, minY, minZ, maxX, maxY, maxZ, 
				minX1, minY1, minZ1, maxX1, maxY1, maxZ1))
			{
				//cout << "Collision\n" << endl;
				CollisionCount++;
				ProcessCollision(i, j);
			}
		}

		if (CollisionCount > 0)
		{
			m_Objects[i]->SetColor(1, 1, 1, 1);
		}
		else
		{
			m_Objects[i]->SetColor(1, 1, 1, 1);
		}
	}
}

void ScnMgr::GarbageCollector() {
	float x, y, z;
	int hp;
	int kind;
	float mag;
	float Vx, Vy, Vz;
	float Sx, Sy, Sz;
	float widthMeter = ScreenWidth;
	float heightMeter = ScreenHeiht;

	for (int i = 0; i < MAX_OBJECTS; ++i) {
		if (m_Objects[i] != NULL && i == HERO_ID)
		{
			m_Objects[i]->GetHP(&hp);
			m_Objects[i]->GetPos(&x, &y, &z);

			if (hp <= 0)
			{
				PassNextMap = 4;
			}

			//혹시 화면을 넘어가는 버그가 생겨버렸을 시 재시작 위치로 보내버린다.
			if (x > widthMeter / 2 || x < -widthMeter / 2 || y > heightMeter / 2 || y < -heightMeter / 2)
			{
				PassNextMap = 4;
			}

		}
		else if (m_Objects[i] != NULL && i != HERO_ID)
		{
			m_Objects[i]->GetPos(&x, &y, &z);
			m_Objects[i]->GetHP(&hp);
			m_Objects[i]->GetSize(&Sx, &Sy, &Sz);
			m_Objects[i]->GetKind(&kind);
			m_Objects[i]->GetMass(&mag);
			m_Objects[i]->GetVel(&Vx, &Vy, &Vz);

			if (x > widthMeter / 2 || x < -widthMeter / 2 || y > heightMeter / 2 || y < -heightMeter / 2)
			{
				DeleteObject(i);
				continue;
			}

			if (kind == KIND_BULLET || kind == KIND_ENEMY || kind == KIND_ENEMY2 
				|| kind == KIND_ENEMY_BULLET || kind == KIND_ENEMY2_BULLET || kind == KIND_ENEMY3) {
				if (hp <= 0)
				{
					if (kind == KIND_ENEMY2_BULLET)
					{
						DeathEffect(x, y, z, 1, 1, 200);
						m_Sound->PlaySound(m_SoundExplosion, false, 3.f);
					}

					if (kind == KIND_ENEMY || kind == KIND_ENEMY2 || kind == KIND_ENEMY3)
					{
						PassNextMap++;
						m_Sound->PlaySound(m_SoundExplosion, false, 3.f);
						if (kind == KIND_ENEMY3)
						{
							DeathEffect(x, y, z, 10, 10, 10);
						}
						else
						{
							DeathEffect(x, y, z, 5, 5, 200);
						}
					}
					DeleteObject(i);
					continue;
				}
				if (PassNextMap >= 4)
				{
					DeleteObject(i);
					continue;
				}
			}

			if (kind == KIND_BULLET || kind == KIND_ENEMY_BULLET)
			{
				if (mag < FLT_EPSILON)
				{
					DeleteObject(i);
					continue;
				}
				if (Vx == 0 && Vy == 0 && Vz == 0)
				{
					DeleteObject(i);
					continue;
				}
			}

			if (kind == KIND_ENEMY2_BULLET)
			{
				if (PassNextMap >= 3)
				{
					DeleteObject(i);
					continue;
				}
			}

			if (kind == KIND_ENEMY3_Patten1 || kind == KIND_ENEMY3_Patten2 || kind == KIND_ENEMY3_Patten3)
			{
				if (PassNextMap >= 4)
				{
					DeleteObject(i);
					continue;
				}
			}
		}
	}
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

bool ScnMgr::CollisionBox(float minX, float minY, float minZ, float maxX, float maxY, float maxZ,
	float min1X, float min1Y, float min1Z, float max1X, float max1Y, float max1Z) {


	if (maxX < min1X)
		return false;
	if (max1X < minX)
		return false;
	if (maxY < min1Y)
		return false;
	if (max1Y < minY)
		return false;
	if (maxZ < min1Z)
		return false;
	if (max1Z < minZ)
		return false;

	return true;
}


void ScnMgr::ApplyForce(float x, float y, float z, float eTime) {
	int state;
	m_Objects[HERO_ID]->GetState(&state);

	if (state == STATE_AIR)
	{
		z = 0.f;
	}
	m_Objects[HERO_ID]->ApplyForce(x, y, z, eTime);
}

void ScnMgr::AddObject(float x, float y, float z,
	float sx, float sy, float sz,
	float vx, float vy, float vz,
	int kind, int hp, int state, int Rotation) {

	int id = FindEmptyObjectSlot();
	if (id == -1)
	{
		std::cout << "Error no more Slot" << std::endl;
		return;
	}

	m_Objects[id] = new Object();
	m_Objects[id]->SetPos(x, y, z);
	m_Objects[id]->SetVel(vx, vy, vz);
	m_Objects[id]->SetSize(sx, sy, sz);
	m_Objects[id]->SetAccel(0.f, 0.f, 0.f);
	m_Objects[id]->SetMass(1.f);
	m_Objects[id]->SetCoefFriction(10.f);
	m_Objects[id]->SetColor(0.f, 0.f, 0.f, 0.f);
	m_Objects[id]->SetKind(kind);
	m_Objects[id]->SetHP(hp);
	m_Objects[id]->SetState(state);
	m_Objects[id]->SetRotState(Rotation);
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

void ScnMgr::Shoot(int key) {

	if (key == SHOOT_NONE)
	{
		HeroHeadanimX = 0;
		return;
	}
	
	if (!m_Objects[HERO_ID]->CanFireBullet())
	{
		return;
	}

	if (HeroHeadanimX >= HeroHeadtotalSeqX - 1) {
		HeroHeadanimX = 0;
		HeroHeadanimY++;
		HeroHeadanimY %= HeroHeadtotalSeqY;
	}
	else
	{
		HeroHeadanimX++;
	}

	float amount = 300.f;
	float rightShoot = 0.f, upShoot = 0.f;
	float bvX, bvY, bvZ;
	int Roation;
	bvX = 0.f;
	bvY = 0.f;
	bvZ = 0.f;

	switch (key)
	{
	case SHOOT_UP:
		m_Objects[HERO_ID]->SetRotState(SHOOT_UP);
		Roation = SHOOT_UP;
		RestartButton = 0;
		bvX = 0.f;
		bvY = amount;
		upShoot = 50.f;
		break;
	case SHOOT_DOWN:
		m_Objects[HERO_ID]->SetRotState(SHOOT_DOWN);
		Roation = SHOOT_DOWN;
		RestartButton = 1;
		bvX = 0.f;
		bvY = -amount;
		upShoot = -50.f;
		break;
	case SHOOT_RIGHT:
		m_Objects[HERO_ID]->SetRotState(SHOOT_RIGHT);
		Roation = SHOOT_RIGHT;
		bvX = amount;
		bvY = 0.f;
		rightShoot = 50.f;
		break;
	case SHOOT_LEFT:
		m_Objects[HERO_ID]->SetRotState(SHOOT_LEFT);
		Roation = SHOOT_LEFT;
		bvX = -amount;
		bvY = 0.f;
		rightShoot = -50.f;
		break;
	default:
		break;
	}

	float pX, pY, pZ;
	m_Objects[HERO_ID]->GetPos(&pX, &pY, &pZ);
	pX += rightShoot;
	pY += upShoot;

	float vX, vY, vZ;
	m_Objects[HERO_ID]->GetVel(&vX, &vY, &vZ);
	bvX += vX;
	bvY += vY;
	bvZ += vZ;

	AddObject(pX, pY + 45, 0, 0.1, 0.1, 0.1, bvX, bvY, bvZ, KIND_BULLET, 20, STATE_AIR, Roation);

	m_Objects[HERO_ID]->InitBulletCooltime();

	m_Sound->PlaySound(m_SoundFire, false, 3.f);
}

void ScnMgr::GetRenderer(Renderer* r) {
	r = g_Renderer;
}

void ScnMgr::GetObject(Object * o) {
	o = m_Objects[HERO_ID];
}

void ScnMgr::ProcessCollision(int i, int j) {

	if (m_Objects[i] == NULL || m_Objects[j] == NULL)
		return;

	Object *ob1 = m_Objects[i];
	Object *ob2 = m_Objects[j];

	int kind1, kind2;
	float VelX, VelY, VelZ;
	float VelX2, VelY2, VelZ2;
	ob1->GetKind(&kind1);
	ob2->GetKind(&kind2);

	if (kind1 == KIND_BUILDING && kind2 == KIND_BULLET)
	{
		int hp;
		ob2->GetHP(&hp);
		hp = 0;
		ob2->SetHP(hp);
	}
	else if (kind1 == KIND_BULLET && kind2 == KIND_BUILDING)
	{
		int hp;
		ob1->GetHP(&hp);
		hp = 0;
		ob1->SetHP(hp);
	}
	else if (kind1 == KIND_HERO && kind2 == KIND_BUILDING)
	{
		ob1->GetVel(&VelX, &VelY, &VelZ);
		VelX *= -1.f;
		VelY *= -1.f;
		ob1->SetVel(VelX, VelY, VelZ);
	}
	else if (kind1 == KIND_ENEMY2 && kind2 == KIND_BUILDING)
	{
		ob1->GetVel(&VelX, &VelY, &VelZ);
		VelX *= -1.f;
		VelY *= -1.f;
		ob1->SetVel(VelX, VelY, VelZ);
	}
	else if (kind1 == KIND_BUILDING && kind2 == KIND_ENEMY2)
	{
		ob2->GetVel(&VelX, &VelY, &VelZ);
		VelX *= -1.f;
		VelY *= -1.f;
		ob2->SetVel(VelX, VelY, VelZ);
	}
	else if (kind1 == KIND_ENEMY2_BULLET && kind2 == KIND_BUILDING)
	{
		ob1->SetHP(0);
	}
	else if (kind1 == KIND_BUILDING && kind2 == KIND_ENEMY2_BULLET)
	{
		ob2->SetHP(0);
	}
	else if (kind1 == KIND_HERO && kind2 == KIND_ENEMY)
	{
		float m1, m2;
		float rVx1, rVy1, rVz1, rVx2, rVy2, rVz2;
		int HP;

		ob1->GetHP(&HP);
		ob1->GetVel(&VelX, &VelY, &VelZ);
		VelX *= -1.f;
		VelY *= -1.f;
		HP--;
		ob1->SetHP(HP);
		ob1->SetVel(VelX, VelY, VelZ);
		m_Sound->PlaySound(m_SoundHit, false, 3.f);
	}
	else if (kind1 == KIND_HERO && kind2 == KIND_ENEMY_BULLET)
	{
		int hp1, hp2;
		ob1->GetHP(&hp1);
		ob2->GetHP(&hp2);

		hp1 -= hp2;
		hp2 = 0;

		ob1->SetHP(hp1);
		ob2->SetHP(hp2);
		m_Sound->PlaySound(m_SoundHit, false, 3.f);
	}
	else if (kind1 == KIND_HERO && kind2 == KIND_ENEMY2)
	{
		float m1, m2;
		float rVx1, rVy1, rVz1, rVx2, rVy2, rVz2;
		int HP;

		ob1->GetHP(&HP);
		ob1->GetVel(&VelX, &VelY, &VelZ);
		ob2->GetVel(&VelX2, &VelY2, &VelZ2);
		VelX *= -1.f;
		VelY *= -1.f;
		VelX2 *= -1.f;
		VelY2 *= -1.f;
		HP--;
		ob1->SetHP(HP);
		ob1->SetVel(VelX, VelY, VelZ);
		ob2->SetVel(VelX2, VelY2, VelZ2);
		m_Sound->PlaySound(m_SoundHit, false, 3.f);
	}
	else if (kind1 == KIND_HERO && kind2 == KIND_ENEMY2_BULLET)
	{
		int hp1, hp2;
		ob1->GetHP(&hp1);
		ob2->GetHP(&hp2);

		hp1 -= hp2;
		hp2 = 0;

		ob1->SetHP(hp1);
		ob2->SetHP(hp2);
		m_Sound->PlaySound(m_SoundHit, false, 3.f);
	}
	else if (kind1 == KIND_ENEMY && kind2 == KIND_BULLET)
	{
		int hp1, hp2;
		ob1->GetHP(&hp1);
		ob2->GetHP(&hp2);

		hp1 -= hp2;
		hp2 = 0;

		ob1->SetHP(hp1);
		ob2->SetHP(hp2);
	}
	else if (kind1 == KIND_BULLET && kind2 == KIND_ENEMY)
	{
		int hp1, hp2;
		ob1->GetHP(&hp1);
		ob2->GetHP(&hp2);

		hp2 -= hp1;
		hp1 = 0;

		ob1->SetHP(hp1);
		ob2->SetHP(hp2);
	}
	else if (kind1 == KIND_ENEMY2 && kind2 == KIND_BULLET)
	{
		int hp1, hp2;
		ob1->GetHP(&hp1);
		ob2->GetHP(&hp2);

		hp1 -= hp2;
		hp2 = 0;

		ob1->SetHP(hp1);
		ob2->SetHP(hp2);
	}
	else if (kind1 == KIND_BULLET && kind2 == KIND_ENEMY2)
	{
		int hp1, hp2;
		ob1->GetHP(&hp1);
		ob2->GetHP(&hp2);

		hp2 -= hp1;
		hp1 = 0;

		ob1->SetHP(hp1);
		ob2->SetHP(hp2);
	}
	else if (kind1 == KIND_ENEMY2_BULLET && kind2 == KIND_BULLET)
	{
		int hp1, hp2;
		ob1->GetHP(&hp1);
		ob2->GetHP(&hp2);

		hp1 -= hp2;
		hp2 = 0;

		ob1->SetHP(hp1);
		ob2->SetHP(hp2);
	}
	else if (kind1 == KIND_BULLET && kind2 == KIND_ENEMY2_BULLET)
	{
		int hp1, hp2;
		ob1->GetHP(&hp1);
		ob2->GetHP(&hp2);

		hp2 -= hp1;
		hp1 = 0;

		ob1->SetHP(hp1);
		ob2->SetHP(hp2);
	}
	else if (kind1 == KIND_ENEMY2 && kind2 == KIND_ENEMY2_BULLET)
	{
		int hp1, hp2;
		ob1->GetHP(&hp1);
		ob2->GetHP(&hp2);

		hp1 -= hp2;
		hp2 = 0;

		ob1->SetHP(hp1);
		ob2->SetHP(hp2);
	}
	else if (kind1 == KIND_ENEMY2_BULLET && kind2 == KIND_ENEMY2)
	{
		int hp1, hp2;
		ob1->GetHP(&hp1);
		ob2->GetHP(&hp2);

		hp2 -= hp1;
		hp1 = 0;

		ob1->SetHP(hp1);
		ob2->SetHP(hp2);
	}
	else if (kind1 == KIND_HERO && kind2 == KIND_ENEMY3)
	{
		float m1, m2;
		float rVx1, rVy1, rVz1, rVx2, rVy2, rVz2;
		int HP;

		ob1->GetHP(&HP);
		ob1->GetVel(&VelX, &VelY, &VelZ);
		VelX *= -1.f;
		VelY *= -1.f;
		HP--;
		ob1->SetHP(HP);		
		ob1->SetVel(VelX, VelY, VelZ);

		m_Sound->PlaySound(m_SoundHit, false, 3.f);


	}
	else if (kind1 == KIND_HERO && kind2 == KIND_ENEMY3_Patten1) 
	{
		int hp1, hp2;
		ob1->GetHP(&hp1);
		ob2->GetHP(&hp2);

		if (hp2 == 0)
			return;

		hp1 -= hp2;
		hp2 = 0;

		ob1->SetHP(hp1);
		ob2->SetHP(hp2);
	
		m_Sound->PlaySound(m_SoundHit, false, 3.f);
	}
	else if (kind1 == KIND_HERO && kind2 == KIND_ENEMY3_Patten2)
	{
		int hp1, hp2;
		ob1->GetHP(&hp1);
		ob2->GetHP(&hp2);

		if (hp2 == 0)
			return;

		hp1 -= hp2;
		hp2 = 0;

		ob1->SetHP(hp1);
		ob2->SetHP(hp2);
		m_Sound->PlaySound(m_SoundHit, false, 3.f);
	}
	else if (kind1 == KIND_ENEMY3 && kind2 == KIND_BULLET)
	{
		int hp1, hp2;
		ob1->GetHP(&hp1);
		ob2->GetHP(&hp2);

		hp1 -= hp2;
		hp2 = 0;

		ob1->SetHP(hp1);
		ob2->SetHP(hp2);
	}
	else if (kind1 == KIND_BULLET && kind2 == KIND_ENEMY3)
	{
		int hp1, hp2;
		ob1->GetHP(&hp1);
		ob2->GetHP(&hp2);

		hp2 -= hp1;
		hp1 = 0;

		ob1->SetHP(hp1);
		ob2->SetHP(hp2);
	}
}

void ScnMgr::WhatRotation(unsigned char key)
{
	switch (key)
	{
	case 'w':
		m_Objects[HERO_ID]->SetRotState(MOVE_UP);
		break;
	case 'a':
		m_Objects[HERO_ID]->SetRotState(MOVE_LEFT);
		break;
	case 's':
		m_Objects[HERO_ID]->SetRotState(MOVE_DOWN);
		break;
	case 'd':
		m_Objects[HERO_ID]->SetRotState(MOVE_RIGHT);
		break;
	default:
		break;
	}
}

void ScnMgr::Boss1Shoot()
{
	if(Boss1Patten != 0)
		AddObject(-100, 0, 0, 0.3, 0.3, 0.3, -500, 0, 0, KIND_ENEMY_BULLET, 1, STATE_AIR, SHOOT_LEFT);
	if (Boss1Patten != 1)
		AddObject(0, 100, 0, 0.3, 0.3, 0.3, 0, 500, 0, KIND_ENEMY_BULLET, 1, STATE_AIR, SHOOT_DOWN);
	if (Boss1Patten != 2)
		AddObject(100, 0, 0, 0.3, 0.3, 0.3, 500, 0, 0, KIND_ENEMY_BULLET, 1, STATE_AIR, SHOOT_RIGHT);
	if (Boss1Patten != 3)
		AddObject(0, -100, 0, 0.3, 0.3, 0.3, 0, -500, 0, KIND_ENEMY_BULLET, 1, STATE_AIR, SHOOT_UP);

	Boss1Patten++;
	Boss1Patten %= 4;
	m_Sound->PlaySound(m_SoundEnemyFire, false, 3.f);
}

void ScnMgr::Boss2Shoot(float x, float y, float z)
{
	AddObject(x - 100, y, z, 0.5, 0.5, 0.5, -500, 0, 0, KIND_ENEMY2_BULLET, 1, STATE_AIR, SHOOT_LEFT);
	AddObject(x, y + 100, z, 0.5, 0.5, 0.5, 0, 500, 0, KIND_ENEMY2_BULLET, 1, STATE_AIR, SHOOT_DOWN);
	AddObject(x + 100, y, z, 0.5, 0.5, 0.5, 500, 0, 0, KIND_ENEMY2_BULLET, 1, STATE_AIR, SHOOT_RIGHT);
	AddObject(x, y - 100, z, 0.5, 0.5, 0.5, 0, -500, 0, KIND_ENEMY2_BULLET, 1, STATE_AIR, SHOOT_UP);
}

void ScnMgr::Boss2Move(int id)
{
	float VelX, VelY, VelZ;

	VelX = float(rand() % 500 - 250);
	VelY = float(rand() % 500 - 250);
	VelZ = 0;

	m_Objects[id]->SetVel(VelX, VelY, VelZ);
}

void ScnMgr::Boss3Patten1Start()
{
	float x, y, z;

	m_Objects[HERO_ID]->GetPos(&x, &y, &z);

	AddObject(x, 450, z, 1.0f, 1.0f, 1.0f, 0, -500, 0, KIND_ENEMY3_Patten1, 1, STATE_AIR, MOVE_DOWN);
}

void ScnMgr::Boss3Patten2Start()
{
	float x, y, z;

	m_Objects[HERO_ID]->GetPos(&x, &y, &z);

	AddObject(700, y, z, 1.0f, 1.0f, 1.0f, -700, 0, 0, KIND_ENEMY3_Patten2, 1, STATE_AIR, MOVE_DOWN);
}

void ScnMgr::Boss3Patten3Start()
{
	float x, y, z;

	m_Objects[HERO_ID]->GetPos(&x, &y, &z);

	if(x > 0)
		AddObject(x - 100, y, z, 0.5f, 0.5f, 0.5f, 0, 0, 0, KIND_ENEMY3_Patten3, 1, STATE_AIR, MOVE_DOWN);
	else
		AddObject(x + 100, y, z, 0.5f, 0.5f, 0.5f, 0, 0, 0, KIND_ENEMY3_Patten3, 1, STATE_AIR, MOVE_DOWN);
}

void ScnMgr::Boss3Shoot(float x, float y, float z)
{
	AddObject(x - 100, y, 0, 0.3, 0.3, 0.3, -500, 0, 0, KIND_ENEMY_BULLET, 1, STATE_AIR, SHOOT_LEFT);
	AddObject(x, y + 100, 0, 0.3, 0.3, 0.3, 0, 500, 0, KIND_ENEMY_BULLET, 1, STATE_AIR, SHOOT_DOWN);
	AddObject(x + 100, y, 0, 0.3, 0.3, 0.3, 500, 0, 0, KIND_ENEMY_BULLET, 1, STATE_AIR, SHOOT_RIGHT);
	AddObject(x, y - 100, 0, 0.3, 0.3, 0.3, 0, -500, 0, KIND_ENEMY_BULLET, 1, STATE_AIR, SHOOT_UP);
	m_Sound->PlaySound(m_SoundEnemyFire, false, 3.f);
}

void ScnMgr::RestartButtonClick()
{
	if (PassNextMap >= 4)
	{
		if (RestartButton == 1)
		{
			MapState = START_MAP;
			PassNextMap = 0;
			m_Objects[HERO_ID]->SetPos(0, 0, 20.f);
			m_Objects[HERO_ID]->SetVel(0, 0, 0);
			m_Objects[HERO_ID]->SetHP(6);
		}
		else if(RestartButton == 0)
		{
			exit(0);
		}
	}

}

void ScnMgr::invincibilityClick()
{
	int hp;
	m_Objects[HERO_ID]->GetHP(&hp);

	if (hp > 6)
	{
		m_Objects[HERO_ID]->SetHP(6);
	}
	else
	{
		m_Objects[HERO_ID]->SetHP(100000);
	}
}

void ScnMgr::DeathEffect(float x, float y, float z,
	float sx, float sy, float sz)
{
	AddObject(x, y, z, sx, sy, sz, 0, 0, 0, KIND_DEATH_EFFACT, 1, STATE_GROUND, SHOOT_DOWN);
}
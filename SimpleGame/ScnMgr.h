#pragma once
#include "Renderer.h"
#include "Global.h"
#include "Sound.h"

class ScnMgr {
	class Renderer *g_Renderer;
	
	GLuint m_TestTexture;

	GLuint m_Boss1Texture;
	GLuint m_Boss2Texture;
	GLuint m_Boss3Texture;
	GLuint m_Boss3P1Texture;
	GLuint m_Boss3P2Texture;
	GLuint m_Boss3P3Texture;
	GLuint m_BossBulletTexture;

	GLuint m_HeroBodyLeftTexture;
	GLuint m_HeroBodyRightTexture;
	GLuint m_HeroBodyUpTexture;
	GLuint m_HeroBodyDownTexture;

	GLuint m_HeroHeadLeftTexture;
	GLuint m_HeroHeadRightTexture;
	GLuint m_HeroHeadUpTexture;
	GLuint m_HeroHeadDownTexture;	

	GLuint m_MapTexture;
	GLuint m_MapTexture_2;
	GLuint m_MapTexture_3;
	GLuint m_MapTexture_4;

	GLuint m_RestartTexture_1;
	GLuint m_RestartTexture_2;

	GLuint m_BulletTexture;

	GLuint m_ExplosionTexture;

	GLuint m_FullHPTexture;
	GLuint m_HalfHPTexture;
	GLuint m_EmptyHPTexture;

	class Object *m_Objects[MAX_OBJECTS];
	int HeroBodyanimX, HeroBodyanimY;
	int HeroHeadanimX, HeroHeadanimY;
	int HeroBodytotalSeqX, HeroBodytotalSeqY;
	int HeroHeadtotalSeqX, HeroHeadtotalSeqY;

	int Boss1animX, Boss1animY;
	int Boss1totalSeqX, Boss1totalSeqY;
	int Boss1SlowAnim;
	int Boss1Patten;

	int Boss2Patten1;
	int Boss2Patten2;

	int Boss3animX, Boss3animY;
	int Boss3totalSeqX, Boss3totalSeqY;
	int Boss3SlowAnim;
	int Boss3Patten1;
	int Boss3Patten2;
	int Boss3Patten3;
	int Boss3Patten3_Cooltime;

	int DeathanimX, DeathanimY;
	int DeathtotalSeqX, DeathtotalSeqY;
	int DeathSlowAnim;


	float coolTime;
	int ScreenWidth;
	int ScreenHeiht;
	int MapState;
	int PassNextMap;
	
	float ParticleTime;

	int RestartButton;

	Sound *m_Sound;

	int m_SoundBG = 0;
	int m_SoundHit = 0;
	int m_SoundFire = 0;
	int m_SoundEnemyFire = 0;
	int m_SoundExplosion = 0;
	int m_SoundFinalBoss = 0;
	int m_SoundFinalBoss2 = 0;
	int m_SoundFinalBoss3 = 0;

public:
	ScnMgr(int width, int height);
	~ScnMgr();
	void RenderScene(void);
	void Update(float eTime);
	void DoCollisionTest();
	void ApplyForce(float x, float y, float z, float eTime);
	void Shoot(int key);
	void AddObject(float x, float y, float z,
		float sx, float sy, float sz,
		float vx, float vy, float vz,
		int kind, int hp, int state, int Rotation);
	int FindEmptyObjectSlot();
	void DeleteObject(int id);
	void GarbageCollector();

	bool CollisionRec(float minX, float minY, float maxX, float maxY,
		float min1X, float min1Y, float max1X, float max1Y);
	bool CollisionBox(float minX, float minY, float minZ, float maxX, float maxY, float maxZ,
		float min1X, float min1Y, float min1Z, float max1X, float max1Y, float max1Z);
	void GetRenderer(class Renderer* r);
	void GetObject(class Object* o);

	void ProcessCollision(int i, int j);
	
	void Boss1Shoot();
	
	void Boss2Shoot(float x, float y, float z);
	void Boss2Move(int id);

	void Boss3Shoot(float x, float y, float z);
	void Boss3Patten1Start();
	void Boss3Patten2Start();
	void Boss3Patten3Start();
	
	void RestartButtonClick();
	void invincibilityClick();

	void DeathEffect(float x, float y, float z, float sx, float sy, float sz);

	//캐릭터의 방향 상태
	void WhatRotation(unsigned char key);
};
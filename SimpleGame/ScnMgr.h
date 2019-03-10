#pragma once
#include "Renderer.h"
#include "Global.h"

class ScnMgr {
	class Renderer *g_Renderer;
	//class Object *ob;
	GLuint m_TestTexture;
	class Object *m_Objects[MAX_OBJECTS];
	int animX, animY;
public:
	ScnMgr();
	~ScnMgr();
	void RenderScene(void);
	void Update(float eTime);
	void DoCollisionTest();
	void ApplyForce(float x, float y, float eTime);
	void Shoot(int key);
	void AddObject(float x, float y, float z,
		float sx, float sy,
		float vx, float vy);
	int FindEmptyObjectSlot();
	void DeleteObject(int id);
	void GarbageCollector();

	bool CollisionRec(float minX, float minY, float maxX, float maxY,
		float min1X, float min1Y, float max1X, float max1Y);
	void GetRenderer(class Renderer* r);
	void GetObject(class Object* o);
};
#pragma once

#include "stdafx.h"
#include "Object.h"
#include "Global.h"
#include <math.h>
#include <float.h>

Object::Object() 
{
	BulletCoolTime = 0.0f;
	BulletTime = 0.2f;
	RotState = 4;
}
Object::~Object() {}

void Object::SetPos(float x, float y, float z) {
	PosX = x;
	PosY = y;
	PosZ = z;
}
void Object::SetVel(float x, float y, float z) {
	VelX = x;
	VelY = y;
	VelZ = z;
}
void Object::SetColor(float R, float G, float B, float A) {
	Red = R;
	Green = G;
	Blue = B;
	Alpha = A;
}
void Object::SetSize(float SX, float SY, float SZ) {
	SizeX = SX * 100;
	SizeY = SY * 100;
	SizeZ = SZ * 100;
}

void Object::GetPos(float *x, float *y, float *z) {
	*x = PosX;
	*y = PosY;
	*z = PosZ;
}
void Object::GetVel(float *x, float *y, float *z) {
	*x = VelX;
	*y = VelY;
	*z = VelZ;
}
void Object::GetColor(float *R, float *G, float *B, float *A) {
	*R = Red;
	*G = Green;
	*B = Blue;
	*A = Alpha;
}
void Object::GetSize(float *SX, float *SY, float *SZ) {
	*SX = SizeX;
	*SY = SizeY;
	*SZ = SizeZ;
}

void Object::SetAccel(float x, float y, float z) {
	AccelX = x;
	AccelY = y;
	AccelZ = z;
}
void Object::GetAccel(float *x, float *y, float *z) {
	*x = AccelX;
	*y = AccelY;
	*z = AccelZ;
}

void Object::SetMass(float M) {
	Mass = M;
}

void Object::GetMass(float *M) {
	*M = Mass;
}

void Object::SetCoefFriction(float F) {
	CoefFriction = F;
}

void Object::GetCoefFriction(float *F) {
	*F = CoefFriction;
}

void Object::SetKind(int K) {
	Kind = K;
}

void Object::GetKind(int *K) {
	*K = Kind;
}

void Object::SetHP(int H) {
	HP = H;
}

void Object::GetHP(int *H) {
	*H = HP;
}

void Object::SetState(int s)
{
	State = s;
}

void Object::GetState(int *s)
{
	*s = State;
}

void Object::SetRotState(int r)
{
	RotState = r;
}

void Object::GetRotState(int *r)
{
	*r = RotState;
}

void Object::InitBulletCooltime()
{
	BulletCoolTime = BulletTime;
}

bool Object::CanFireBullet()
{
	if (BulletCoolTime <= 0.f)
	{
		return true;
	}
	return false;
}

void Object::Update(float eTime) {

	// 총알 쿨타임
	// process colltime
	BulletCoolTime -= eTime;
	if (BulletCoolTime <= 0.f)
	{
		BulletCoolTime = -1.f;
	}

	//마찰력 구현
	//플레이어는 나는 고양이이기 때문에 Z값을 업데이트 하지 않는다.
	//float magVel = sqrtf(VelX*VelX + VelY * VelY + VelZ * VelZ);
	float magVel = sqrtf(VelX*VelX + VelY * VelY);
	float localVelX = VelX / magVel;
	float localVelY = VelY / magVel;
	//float localVelZ = VelZ / magVel;
	float fricX = -localVelX;
	float fricY = -localVelY;
	//float fricZ = -localVelZ;
	//수직 항력
	float Friction = CoefFriction * Mass * GRAVITY;

	fricX *= Friction;
	fricY *= Friction;
	//fricZ *= Friction;

	// 발생 가능한 오차안에 드는가? (0인가?)
	if (magVel < FLT_EPSILON)
	{
		localVelX = 0;
		localVelY = 0;
		//localVelZ = 0;
	}
	else {
		float accX = fricX / Mass;
		float accY = fricY / Mass;
		//float accZ = fricZ / Mass;

		float afterVelX = VelX + accX * eTime;
		float afterVelY = VelY + accY * eTime;
		//float afterVelZ = VelZ + accZ * eTime;

		if (afterVelX * VelX < 0.f)
			VelX = 0.f;
		else
			VelX = afterVelX;

		if (afterVelY * VelY < 0.f)
			VelY = 0.f;
		else
			VelY = afterVelY;

		//if (afterVelZ * VelZ < 0.f)
		//	VelZ = 0.f;
		//else
		//	VelZ = afterVelZ;


		//VelZ = VelZ - GRAVITY * eTime * 100;
		//if (PosZ <= 0 && VelZ <= 0)
		//{
		//	PosZ = 0;
		//	VelZ = 0;
		//}

	}

	//시간에 따라 위치는 속도에 맞게 바뀜
	PosX = PosX + VelX * (eTime);
	PosY = PosY + VelY * (eTime);
	//PosZ = PosZ + VelZ * (eTime);

	//속도는 시간에 따라 가속도에 비례해서 바뀜
	VelX = VelX + AccelX * (eTime);
	VelY = VelY + AccelY * (eTime);
	//VelZ = VelZ + AccelZ * (eTime);

	//if (PosZ > 0.f)
	//{
	//	State = STATE_AIR;
	//}
	//else
	//{
	//	State = STATE_GROUND;
	//	VelZ = 0.f;
	//	PosZ = 0.f;
	//}

}


void Object::ApplyForce(float x, float y, float z, float eTime) {
	
	//가속도는 무게만큼 줄고
	AccelX = x / Mass;
	AccelY = y / Mass;
	AccelZ = z / Mass;

	VelX = VelX + AccelX * (eTime);
	VelY = VelY + AccelY * (eTime);
	VelZ = VelZ + AccelZ * 0.1f;

	AccelX = 0;
	AccelY = 0;
	AccelZ = 0;
}


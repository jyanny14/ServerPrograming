#pragma once

#include "stdafx.h"
#include "Object.h"
#include <math.h>
#include <float.h>

Object::Object() {}
Object::~Object() {}

void Object::SetPos(float x, float y, float z) {
	PosX = x;
	PosY = y;
	PosZ = z;
}
void Object::SetVel(float x, float y) {
	VelX = x;
	VelY = y;
}
void Object::SetColor(float R, float G, float B, float A) {
	Red = R;
	Green = G;
	Blue = B;
	Alpha = A;
}
void Object::SetSize(float SX, float SY) {
	SizeX = SX;
	SizeY = SY;
}

void Object::GetPos(float *x, float *y, float *z) {
	*x = PosX;
	*y = PosY;
	*z = PosZ;
}
void Object::GetVel(float *x, float *y) {
	*x = VelX;
	*y = VelY;
}
void Object::GetColor(float *R, float *G, float *B, float *A) {
	*R = Red;
	*G = Green;
	*B = Blue;
	*A = Alpha;
}
void Object::GetSize(float *SX, float *SY) {
	*SX = SizeX;
	*SY = SizeY;
}

void Object::SetAccel(float x, float y) {
	AccelX = x;
	AccelY = y;
}
void Object::GetAccel(float *x, float *y) {
	*x = AccelX;
	*y = AccelY;
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

void Object::Update(float eTime) {

	//마찰력 구현
	float magVel = sqrtf(VelX*VelX + VelY*VelY);
	float localVelX = VelX / magVel;
	float localVelY = VelY / magVel;
	float fricX = -localVelX;
	float fricY = -localVelY;
	float Friction = CoefFriction * Mass * 9.8;

	fricX *= Friction;
	fricY *= Friction;

	// 발생 가능한 오차안에 드는가? (0인가?)
	if (magVel < FLT_EPSILON)
	{
		localVelX = 0;
		localVelY = 0;
	}
	else {
		float accX = fricX / Mass;
		float accY = fricY / Mass;

		float afterVelX = VelX + accX * eTime;
		float afterVelY = VelY + accY * eTime;

		if (afterVelX * VelX < 0.f)
			VelX = 0.f;
		else
			VelX = afterVelX;
		if (afterVelY * VelY < 0.f)
			VelY = 0.f;
		else
			VelY = afterVelY;
	}

	//시간에 따라 위치는 속도에 맞게 바뀜
	PosX = PosX + VelX * (eTime);
	PosY = PosY + VelY * (eTime);

	//속도는 시간에 따라 가속도에 비례해서 바뀜
	VelX = VelX + AccelX * (eTime);
	VelY = VelY + AccelY * (eTime);
}


void Object::ApplyForce(float x, float y, float eTime) {
	
	//가속도는 무게만큼 줄고
	AccelX = x / Mass;
	AccelY = y / Mass;

	VelX = VelX + AccelX * (eTime);
	VelY = VelY + AccelY * (eTime);

	AccelX = 0;
	AccelY = 0;
}


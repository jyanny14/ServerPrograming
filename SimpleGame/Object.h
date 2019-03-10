#pragma once

class Object {
public:

	Object();
	~Object();

	void SetPos(float x, float y, float z);
	void SetVel(float x, float y);
	void SetAccel(float x, float y);
	void SetColor(float R, float G, float B, float A);
	void SetSize(float SX, float SY);
	void SetMass(float M);
	void SetCoefFriction(float F);
	void SetKind(int K);

	void GetPos(float *x, float *y, float *z);
	void GetVel(float *x, float *y);
	void GetAccel(float *x, float *y);
	void GetColor(float *R, float *G, float *B, float *A);
	void GetSize(float *SX, float *SY);
	void GetMass(float *M);
	void GetCoefFriction(float *F);
	void GetKind(int *K);

	void Update(float eTime);
	void ApplyForce(float x, float y, float eTime);

private:
	float PosX, PosY, PosZ;
	float VelX, VelY;
	float AccelX, AccelY;
	float Mass;
	float CoefFriction;
	float SizeX;
	float SizeY;
	float Red, Green, Blue, Alpha;
	//미사일을 발사 중인가?
	int Fire;

	// 오브젝트 특성
	int Kind;
};

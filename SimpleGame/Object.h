#pragma once

class Object {
public:

	Object();
	~Object();

	void SetPos(float x, float y, float z);
	void SetVel(float x, float y, float z);
	void SetAccel(float x, float y, float z);
	void SetColor(float R, float G, float B, float A);
	void SetSize(float SX, float SY, float SZ);
	void SetMass(float M);
	void SetCoefFriction(float F);
	void SetKind(int K);
	void SetHP(int H);
	void SetState(int s);
	void SetRotState(int r);

	void GetPos(float *x, float *y, float *z);
	void GetVel(float *x, float *y, float *z);
	void GetAccel(float *x, float *y, float *z);
	void GetColor(float *R, float *G, float *B, float *A);
	void GetSize(float *SX, float *SY, float *SZ);
	void GetMass(float *M);
	void GetCoefFriction(float *F);
	void GetKind(int *K);
	void GetHP(int *H);
	void GetState(int *s);
	void GetRotState(int *r);

	void Update(float eTime);
	void ApplyForce(float x, float y, float z, float eTime);

	void InitBulletCooltime();
	bool CanFireBullet();

private:
	float PosX, PosY, PosZ;
	float VelX, VelY, VelZ;
	float AccelX, AccelY, AccelZ;
	float Mass;
	float CoefFriction;
	float SizeX, SizeY, SizeZ;
	float Red, Green, Blue, Alpha;
	int HP;
	//미사일을 발사 중인가?
	int Fire;

	// 오브젝트 특성
	int Kind;
	int State;

	float BulletCoolTime;
	float BulletTime;

	// 어느 방향으로 이동중인가
	int RotState;
};

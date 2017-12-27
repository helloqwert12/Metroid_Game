#pragma once
#ifndef _GATE_H
#define _GATE_H_
#include "Sprite.h"
#include "Collision.h"
#include "Parameters.h"
#include "GameObject.h"
#include "trace.h"
#include "Camera.h"

enum GATE_STATE {  //State of Gate
	OPEN,
	CLOSE
};
class Gate : public GameObject
{
protected:
	Sprite * left_gate; //Left sprite Gate

	GATE_STATE state;
public:
	Gate();
	Gate(LPD3DXSPRITE spriteHandler, World * manager);
	~Gate();


	void InitSprites();
	void InitPostition();

	GATE_STATE GetState();
	void SetState(GATE_STATE value);

	//================ OVERRIDE VIRTUAL METHOD ==================
	void Update(int t);
	void Render();
	void Destroy();
	//================= END OVERRIDE VIRTUAL METHOD =============
};
#endif // !_GATE_H
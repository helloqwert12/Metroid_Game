#pragma once
#include "GameObject.h"
#include "Parameters.h"
class MotherBrain : public GameObject
{
protected:
	World * manager;

	Sprite * unbroken;
	Sprite * broken;
	MOTHERBRAIN_STATE state;
public:
	MotherBrain(LPD3DXSPRITE spriteHandler, World * manager);
	~MotherBrain();

	//============= OVERRIDE VIRTUAL METHOD ==================
	void Update();
	void Render();
	//============= END OVERRIDE VIRTUAL METHOD ==============
};


#pragma once
#ifndef  __STARSHIP__
#define  __STARSHIP__
#include "DisplayObject.h"
class StarShip : public DisplayObject
{
public:
	StarShip();

	~StarShip();
	void Draw() override;
	void Update() override;
	void Clean() override;

private:
};


#endif

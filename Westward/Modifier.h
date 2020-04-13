#pragma once
#include "enums.h"
class Modifier
{
public:
	Modifier(Attributes e, int d,float v);
	~Modifier();
	void Tick();
	bool CheckExpire();
	Attributes getAtt();
	float getValue();
private:
	Attributes effect;
	int duration;
	float value;
};


#include "Modifier.h"

Modifier::Modifier(Attributes e, int d, float v) {

	effect = e;
	duration = d;
	value = v;

}

Modifier::~Modifier() {

}

Attributes Modifier::getAtt() {
	return effect;
}

float Modifier::getValue() {
	return value;
}

void Modifier::Tick() {
	duration--;
}

bool Modifier::CheckExpire() {
	if (duration == 0) {
		return true;
	}
	return false;
}
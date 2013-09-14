#include "TouchEvent.h"

TouchEvent::TouchEvent(float x, float y, Type type)
: mX(x), mY(y), mType(type) {}

float TouchEvent::getX() const {
	return mX;
}

float TouchEvent::getY() const {
	return mY;
}

TouchEvent::Type TouchEvent::getType() const {
	return mType;
}

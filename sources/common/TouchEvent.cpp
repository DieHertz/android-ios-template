#include "TouchEvent.h"

TouchEvent::TouchEvent(float x, float y, Type type, int index)
: mX(x), mY(y), mType(type), mIndex(index) {}

float TouchEvent::getX() const {
	return mX;
}

float TouchEvent::getY() const {
	return mY;
}

TouchEvent::Type TouchEvent::getType() const {
	return mType;
}

int TouchEvent::getIndex() const {
    return mIndex;
}

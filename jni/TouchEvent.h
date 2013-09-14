#ifndef TouchEvent_h
#define TouchEvent_h

class TouchEvent {
public:
	enum Type {
		Down,
		Up,
		Move,
		Cancel
	};

	TouchEvent(float x, float y, Type type);

	float getX() const;
	float getY() const;
	Type getType() const;

private:
	float mX;
	float mY;
	Type mType;
};

#endif /* TouchEvent_h */

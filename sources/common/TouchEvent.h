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

    TouchEvent(float x, float y, Type type, int index);

    float getX() const;
    float getY() const;
    Type getType() const;
    int getIndex() const;

    bool isAccepted() { return mAccepted; }
    void accept() { mAccepted = true; }
    void ignore() { mAccepted = false; }

private:
    float mX;
    float mY;
    Type mType;
    int mIndex;
    bool mAccepted = false;
};

#endif /* TouchEvent_h */

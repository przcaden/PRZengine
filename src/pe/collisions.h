
#ifndef COLLISIONS_H_
#define COLLISIONS_H_

struct Vec {
    float x;
    float y;
    Vec(float x, float y);

    Vec& operator-(const Vec& v);
    Vec& operator/(float i);
    Vec& operator*(float i);
};

class Object {
private:
protected:
	float restitution;
	float mass;
	float inv_mass;
private:
	Vec* position;
	Vec* velocity;
public:
    float getx();
	float gety();
	Vec pos();
	float getinv();
	float getmass();
	Vec getvel();
	float res();
	void setvel(Vec vel);
	virtual ~Object();
};

class Circle : public Object {
private:
	float radius;
public:
	Circle(float rad, float res);
	float rad();
};

#endif
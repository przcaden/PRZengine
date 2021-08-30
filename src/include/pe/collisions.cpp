#include <cmath>

// Basic vector
struct Vec {
	float x;
	float y;
	Vec(float _x, float _y) { x = _x; y = _y; }

	// Overload ops
	Vec& operator-(const Vec& v) {
		x = this->x - v.x;
		y = this->y - v.y;
		return *this;
	}
	Vec& operator/(float i) {
		x = x / i;
		y = y / i;
		return *this;
	}
	Vec& operator*(float i) {
		x = x * i;
		y = y * i;
		return *this;
	}
};

// Parent class for any object type
class Object {
protected:
	float restitution;
	float mass;
	float inv_mass;
private:
	Vec* position;
	Vec* velocity;
public:
	float getx() { return position->x; }
	float gety() { return position->y; }
	Vec pos() { return *position; }
	float getinv() { return inv_mass; }
	float getmass() { return mass; }
	Vec getvel() { return *velocity; }
	float res() { return restitution; }
	void setvel(Vec vel) { velocity = &vel; }
	virtual ~Object() {
		if (velocity->x != 0 || velocity->y != 0)
			delete velocity;
		if (position->x != 0 || position->y != 0)
			delete position;
	}
};

// Class for circles, child of object
class Circle : public Object {
private:
	float radius;
public:
	Circle(float rad, float res) {
		radius = rad;
		restitution = res;
		mass = 5 * rad; // random equation
		if (mass == 0)
			inv_mass = 0;
		else inv_mass = 1 / mass;
	}
	float rad() { return radius; }
};

// Checks if two circles begin to intercept.
bool circleIntercept(Circle a, Circle b) {
	float r = pow(a.rad() + b.rad(), 2);
	return r < (pow(a.getx() - b.getx(), 2) + pow(a.gety() - b.gety(), 2)); // r < distance between a and b
}

// Run following function upon collision
void rebound(Object a, Object b) {
	Vec rv = b.getvel() - a.getvel(); // rebounding velocity
	Vec norm = rv / sqrt(pow(rv.x, 2) + pow(rv.y, 2)); // normal vector
	float nv = (rv.x * norm.x) + (rv.y * norm.y); // velocity along normal direction

	if (nv > 0)
		return;

	float e = std::min(a.res(), b.res()); // determine restitution

	// Determine impulse vector
	float j = -(1 + e) * nv;
	j /= (a.getinv()) + (b.getinv()); // scalar
	Vec impulse = norm * j;

	// Apply distributed impulse to objects
	Vec newvel_a = a.getvel() - (impulse * a.getinv());
	Vec newvel_b = b.getvel() - (impulse * b.getinv());
	a.setvel(newvel_a);
	b.setvel(newvel_b);
}

// Holds data for collisions
struct Manifold {
	Object* a;
	Object* b;
	float pen; // penetration
	Vec normal; // normal vector to collision
};

bool circlevcircle(Manifold* m) {
	Circle* a = dynamic_cast<Circle*>(m->a); // assuming both a and b are circles
	Circle* b = dynamic_cast<Circle*>(m->b);

	Vec n = a->pos() - b->pos(); // vec between a and b
	float r = pow(a->rad() + b->rad(), 2);

	// Check if circles have collided
	if (pow(n.x, 2) + pow(n.y, 2) > r)
		return false;

	// Create manifold
	float d = sqrt(pow(n.x, 2) + pow(n.y, 2));
	if (d == 0) {
		m->pen = a->rad();
		m->normal = Vec(1, 0);
	}
	else {
		m->pen = r - d;
		m->normal = n / d; // may need revision
	}
	return true;
}

#ifndef _YMKANGCAMERA_2015EX07_HH
#define _YMKANGCAMERA_2015EX07_HH

class CCamera {
	// camera properties
	float up[3];
	float forward[3];
	float right[3];
	float loc[3];

	//methods
public:
	CCamera(); // constructor

	void setGLCamera(); // set gl camera with properties
	void moveForward(float d);
	void moveRight(float d);
	void moveUp(float d);
	void rotate(float angle);

};

#endif
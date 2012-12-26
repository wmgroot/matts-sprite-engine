#ifndef CAMERACLASS
#define CAMERACLASS

using namespace std;

class Camera
{
public:
	Camera(void);
	~Camera(void);

	bool init();
	void update();

	double x, y;
};

#endif

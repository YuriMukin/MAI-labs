#include <vector>
#include <GLFW/glfw3.h>

class renderer
{
public:
	renderer(GLdouble Points[], int np);

private:
	GLdouble* bPointSet;
	GLdouble* nPointSet;
	int num_pairs;

	void draw();
	void rotate(int of);
	void offset(int of);
	void Scale(int of);
	void newVertSet();
	bool isRight(int of);
};
#ifdef _MSC_VER
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION


#include <glfw3.h>
#include <stb_image.h>
//#include <font.h>
#include <Vec2.h>
#include <list>
//#include <random>
#include <sprite.h>
using namespace std;

ltex_t *createTexture(const char *filename, int *width, int *height);
void scaleBall(float &ballScale, const float &from, const float &to, const float &step, const float &deltaTime, bool &shrinkBall);
int main() {

	// Inicializamos GLFW
	if (!glfwInit()) {
		cout << "Error: No se ha podido inicializar GLFW" << endl;
		return -1;
	}
	atexit(glfwTerminate);
	// Creamos la ventana
	glfwWindowHint(GLFW_RESIZABLE, true);
	GLFWwindow* window = glfwCreateWindow(800, 600, "Programacion 2D", nullptr, nullptr);
	if (!window) {
		cout << "Error: No se ha podido crear la ventana" << endl;
		return -1;
	}
	// Activamos contexto de OpenGL
	glfwMakeContextCurrent(window);
	// Inicializamos LiteGFX
	lgfx_setup2d(800, 600);

	int widthBall		= 100;
	int heightBall		= 100;
	int widthCircle		= 16;
	int heightCircle	= 16;

	Sprite ballSprite	= Sprite(createTexture("./data/ball.png", &widthBall, &heightBall), 1, 1);
	ballSprite.setPosition(Vec2(0, 0));
	ballSprite.setBlend(BLEND_ALPHA);
	ballSprite.setFps(1);
	ballSprite.setSize(Vec2(widthBall, heightBall));
	ballSprite.setPivot(Vec2(0.5f, 0.5f));

	Sprite circleSprite = Sprite(createTexture("./data/circle.png", &widthCircle, &heightCircle), 1, 1);
	circleSprite.setPosition(Vec2(0, 0));
	circleSprite.setBlend(BLEND_ALPHA);
	circleSprite.setFps(1);
	circleSprite.setSize(Vec2(widthCircle, heightCircle));
	circleSprite.setPivot(Vec2(0.5f, 0.5f));
	
	double lastTime = glfwGetTime();
	double xposMouse = 0;
	double yposMouse = 0;
	double xposBall = 0;
	double yposBall = 0;
	float angle=0;
	Vec2 ballPosition;
	Vec2 circlePosition;
	Vec2 mousePos;
	bool shrinkBall = false;
	float ballScale = 1;
	float ballScaleFrom = 0.9;
	float ballScaleTo = 1.1;
	float ballScaleStep = 0.25;

	while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		// Actualizamos delta
		float deltaTime = static_cast<float>(glfwGetTime() - lastTime);
		lastTime = glfwGetTime();

		// Actualizamos tamaño de ventana
		int screenWidth, screenHeight;
		glfwGetWindowSize(window, &screenWidth, &screenHeight);
		lgfx_setviewport(0, 0, screenWidth, screenHeight);
		lgfx_clearcolorbuffer(0, 0, 0);
		glfwGetCursorPos(window, &xposMouse, &yposMouse);
		mousePos = Vec2(xposMouse, yposMouse);

		ballPosition = Vec2(screenWidth / 4, screenHeight / 2);
		ballSprite.setPosition(ballPosition);
		ballSprite.setCollisionType(COLLISION_CIRCLE);
		scaleBall(ballScale, ballScaleFrom, ballScaleTo, ballScaleStep, deltaTime, shrinkBall);
		
		ballSprite.setScale(Vec2(ballScale, ballScale));

		circleSprite.setPosition(mousePos);
		circleSprite.setCollisionType(COLLISION_CIRCLE);
		
		if (circleSprite.collides(ballSprite)) {
			//cout << "Collide!";
			ballSprite.setColor(1, 0, 0, 1);
			circleSprite.setColor(1, 0, 0, 1);
		}
		else {
			ballSprite.setColor(1, 1, 1, 1);
			circleSprite.setColor(1, 1, 1, 1);
		}

		ballSprite.update(deltaTime);
		ballSprite.draw();

		circleSprite.update(deltaTime);
		circleSprite.draw();
		
		
		// Actualizamos ventana y eventos
		glfwSwapBuffers(window);
		glfwPollEvents();


	}

	return 0;
}

ltex_t* createTexture(const char *filename, int *width, int *height) {

	unsigned char* buffer = stbi_load(filename, width, height, nullptr, 4);

	if (buffer != NULL) {
	}
	else {
		cout << "buffer empty";
	}

	ltex_t* tex = ltex_alloc(*width, *height, 0);

	ltex_setpixels(tex, buffer);

	stbi_image_free(buffer);

	return tex;
	//ltex_free(ltex_t* tex);

}

void scaleBall(float &ballScale, const float &from, const float &to, const float &step, const float &deltaTime, bool &shrinkBall) { //Make general 
	if (shrinkBall) {
		ballScale -= step * deltaTime;
		if (ballScale <= from) {
			ballScale = from;
			shrinkBall = false;
		}
	}
	else {
		ballScale += step * deltaTime;
		if (ballScale >= to) {
			ballScale = to;
			shrinkBall = true;
		}

	}

}

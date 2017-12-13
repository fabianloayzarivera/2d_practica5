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
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
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
	//glfwSetMouseButtonCallback(window, mouse_button_callback);
	// Activamos contexto de OpenGL
	glfwMakeContextCurrent(window);
	// Inicializamos LiteGFX
	lgfx_setup2d(800, 600);

	int widthBall		= 100;
	int heightBall		= 100;
	int widthBox		= 100;
	int heightBox		= 100;
	int widthBee		= 80;
	int heightBee		= 92;
	int widthCircle		= 16;
	int heightCircle	= 16;
	int widthRect		= 16;
	int heightRect		= 16;
	int mouseButton		= 1;
	double lastTime = glfwGetTime();
	double xposMouse = 0;
	double yposMouse = 0;
	double xposBall = 0;
	double yposBall = 0;
	float angle = 0;
	Vec2 ballPosition = Vec2(0, 0);
	Vec2 boxPosition = Vec2(0, 0);
	Vec2 beePosition = Vec2(0, 0);
	Vec2 mousePos;
	bool shrinkBall = false;
	bool shrinkBox = false;
	float ballScale = 1;
	float ballScaleFrom = 0.9;
	float ballScaleTo = 1.1;
	float ballScaleStep = 0.25;
	float boxScale = 1;
	float boxScaleFrom = 0.9;
	float boxScaleTo = 1.1;
	float boxScaleStep = 0.25;

	ltex_t *circleTexture = createTexture("./data/circle.png", &widthCircle, &heightCircle);
	ltex_t *rectTexture = createTexture("./data/rect.png", &widthRect, &heightRect);
	ltex_t *beeTexture = createTexture("./data/bee.png", &widthBee, &heightBee);

	//BALL///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Sprite ballSprite	= Sprite(createTexture("./data/ball.png", &widthBall, &heightBall), 1, 1);
	ballSprite.setPosition(Vec2(0, 0));
	ballSprite.setBlend(BLEND_ALPHA);
	ballSprite.setFps(1);
	ballSprite.setSize(Vec2(widthBall, heightBall));
	ballSprite.setPivot(Vec2(0.5f, 0.5f));
	ballSprite.setScale(Vec2(1, 1));
	ballSprite.setCollisionType(COLLISION_CIRCLE);
	
	//Mouse Sprite///////////////////////////////////////////////////////////////////////////////////////////////////////////
	Sprite mouseSprite = Sprite(circleTexture, 1, 1);
	mouseSprite.setPosition(Vec2(0, 0));
	mouseSprite.setBlend(BLEND_ALPHA);
	mouseSprite.setFps(1);
	mouseSprite.setSize(Vec2(widthCircle, heightCircle));
	mouseSprite.setPivot(Vec2(0.5f, 0.5f));
	mouseSprite.setScale(Vec2(1, 1));
	mouseSprite.setCollisionType(COLLISION_CIRCLE);	

	//BOX///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Sprite boxSprite = Sprite(createTexture("./data/box.png", &widthBox, &heightBox), 1, 1);
	boxSprite.setPosition(Vec2(0, 0));
	boxSprite.setBlend(BLEND_ALPHA);
	boxSprite.setFps(1);
	boxSprite.setSize(Vec2(widthBox, heightBox));
	boxSprite.setPivot(Vec2(0.5f, 0.5f));
	boxSprite.setScale(Vec2(1, 1));
	boxSprite.setCollisionType(COLLISION_RECT);

	//BEE///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Sprite beeSprite = Sprite(beeTexture, 1, 1);
	beeSprite.setPosition(Vec2(0, 0));
	beeSprite.setBlend(BLEND_ALPHA);
	beeSprite.setFps(1);
	beeSprite.setSize(Vec2(widthBee, heightBee));
	beeSprite.setPivot(Vec2(0.5f, 0.5f));
	beeSprite.setScale(Vec2(1, 1));
	beeSprite.setCollisionType(COLLISION_PIXELS);
	
	
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
		mouseSprite.setPosition(mousePos);
		mouseSprite.setScale(Vec2(1, 1));
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			//cout << "Left Click!";
			mouseSprite.setPosition(mousePos);
			mouseSprite.setTexture(circleTexture);
			mouseSprite.setSize(Vec2(widthCircle, heightCircle));
			mouseSprite.setCollisionType(COLLISION_CIRCLE);
			mouseSprite.setScale(Vec2(1, 1));
		}
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
			//cout << "Right Click!";
			mouseSprite.setPosition(mousePos);
			mouseSprite.setTexture(rectTexture);
			mouseSprite.setSize(Vec2(widthRect, heightRect));
			mouseSprite.setCollisionType(COLLISION_RECT);
			mouseSprite.setScale(Vec2(1, 1));
		}
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
			//cout << "Middle Click!";
		}
		ballPosition = Vec2(screenWidth / 4, screenHeight / 2);
		ballSprite.setPosition(ballPosition);
		scaleBall(ballScale, ballScaleFrom, ballScaleTo, ballScaleStep, deltaTime, shrinkBall);		
		ballSprite.setScale(Vec2(ballScale, ballScale));

		boxPosition = Vec2((screenWidth / 4) * 3, screenHeight / 2);
		boxSprite.setPosition(boxPosition);
		scaleBall(boxScale, boxScaleFrom, boxScaleTo, boxScaleStep, deltaTime, shrinkBox);
		boxSprite.setScale(Vec2(boxScale, boxScale));

		beePosition = Vec2((screenWidth / 4) * 2, screenHeight / 2);
		beeSprite.setPosition(beePosition);
		
		
		//cout << "Ball Top Left: " << ballSprite.getTopLeft().x << " , " << ballSprite.getTopLeft().y <<endl;

		if (mouseSprite.collides(ballSprite)) {
			//cout << "Collide!";
			ballSprite.setColor(1, 0, 0, 1);
			mouseSprite.setColor(1, 0, 0, 1);
		}
		else if (mouseSprite.collides(boxSprite)) {
			boxSprite.setColor(1, 0, 0, 1);
			mouseSprite.setColor(1, 0, 0, 1);
		}
		else {
			ballSprite.setColor(1, 1, 1, 1);
			boxSprite.setColor(1, 1, 1, 1);
			mouseSprite.setColor(1, 1, 1, 1);
		}


		ballSprite.update(deltaTime);
		ballSprite.draw();

		boxSprite.update(deltaTime);
		boxSprite.draw();

		beeSprite.update(deltaTime);
		beeSprite.draw();

		mouseSprite.update(deltaTime);
		mouseSprite.draw();	

		

		//cout << "Box Top Left: " << boxSprite.getTopLeft().x << " , " << boxSprite.getTopLeft().y << "Box Pos: " << boxSprite.getPosition().x << " , " << boxSprite.getPosition().y << endl;
		//lgfx_drawrect(boxSprite.getTopLeft().x, boxSprite.getTopLeft().y, boxSprite.getScaledSize().x, boxSprite.getScaledSize().y);
		/*lgfx_setcolor(0, 1, 0, 0.5f);
		lgfx_drawrect(mouseSprite.getTopLeft().x, mouseSprite.getTopLeft().y, mouseSprite.getScaledSize().x, mouseSprite.getScaledSize().y);
		lgfx_drawrect(boxSprite.getTopLeft().x, boxSprite.getTopLeft().y, boxSprite.getScaledSize().x, boxSprite.getScaledSize().y);
		mouseSprite.setColor(1, 1, 1, 1);*/
		

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



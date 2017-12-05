#include <sprite.h>

Sprite::Sprite(const ltex_t* tex, int hframes, int vframes) {
	texture = tex;
	horizontalFrames = hframes;
	verticalFrames = vframes;
	position = Vec2(0, 0);
	scale = Vec2(1, 1);
	size = Vec2(0, 0);
	pivot = Vec2(0,0);
	currentFrame = 0;
	red = 1;
	blue = 1;
	green = 1;
	alpha = 1;

}

const ltex_t* Sprite::getTexture() const {return texture;}
void Sprite::setTexture(const ltex_t* tex) { texture = tex; }


lblend_t Sprite::getBlend() const { return blend; }
void Sprite::setBlend(lblend_t mode) { blend = mode; }

float Sprite::getRed() const { return red; }
float Sprite::getGreen() const { return green; }
float Sprite::getBlue() const { return blue; }
float Sprite::getAlpha() const { return alpha; }
void Sprite::setColor(float r, float g, float b, float a) { red = r; green = g; blue = b; alpha = a; }

const Vec2& Sprite::getPosition() const { return position; }
void Sprite::setPosition(const Vec2& pos) { position = pos; }

float Sprite::getAngle() const { return angle; }
void Sprite::setAngle(float a) { angle = a; }

const Vec2& Sprite::getScale() const { return scale; }
void Sprite::setScale(const Vec2& s) { scale = s; }


// Tamaño de un frame multiplicado por la escala
Vec2 Sprite::getSize() const { return Vec2(texture->width, texture->height); }
void Sprite::setSize(const Vec2& s) { size = s; };

// Este valor se pasa a ltex_drawrotsized en el pintado
// para indicar el pivote de rotación
const Vec2& Sprite::getPivot() const { return pivot; }
void Sprite::setPivot(const Vec2& p) { pivot = p; }

int Sprite::getHframes() const { return horizontalFrames; }
int Sprite::getVframes() const { return verticalFrames; }
void Sprite::setFrames(int hframes, int vframes) { horizontalFrames = hframes; verticalFrames = vframes; }


// Veces por segundo que se cambia el frame de animación
int Sprite::getFps() const { return fps; }
void Sprite::setFps(int f) { fps = f; }


// Frame actual de animación
float Sprite::getCurrentFrame() const { return currentFrame; }
void Sprite::setCurrentFrame(int frame) { currentFrame = frame;}

void Sprite::update(float deltaTime) {
	float frame = getCurrentFrame() + fps * deltaTime;
	currentFrame = frame;
	
}

void Sprite::draw() const {

	float frameWidth = texture->width / horizontalFrames;
	float widthRatio = 1.0f / horizontalFrames;
	float u0 = widthRatio * static_cast<int>(currentFrame);
	float u1 = u0 + widthRatio;
	lgfx_setblend(blend);
	lgfx_setcolor(red, green, blue, alpha);
	ltex_drawrotsized(texture, position.x, position.y, angle, pivot.x, pivot.y, frameWidth * scale.x, texture->height * scale.x, u0, 0, u1, 1);
}

void Sprite::setCollisionType(CollisionType type) {
	switch (type)
	{
	/*case COLLISION_NONE:
		break;*/
	case COLLISION_CIRCLE:
		delete(collider);
		CircleCollider *col = new CircleCollider(position, (size.x * scale.x) > (size.y * scale.y) ? (size.x * scale.x) /2 : (size.y * scale.y) /2);
		collider = col;
		colliderType = type;
		break;
	/*case COLLISION_RECT:
		break;
	case COLLISION_PIXELS:
		break;*/
	/*default:
		break;*/
	}
};

CollisionType    Sprite::getCollisionType() const { return colliderType; };
const Collider*  Sprite::getCollider() const { return collider; };
bool             Sprite::collides(const Sprite& other) const { return collider->collides(*(other.getCollider()));};
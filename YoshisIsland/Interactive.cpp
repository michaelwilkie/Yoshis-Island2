#include "Interactive.h"
#ifdef DEBUG
#  define D(x) std::cout << x 
#else
#  define D(x)
#endif // DEBUG
Interactive::Interactive(float x, float y, double ang)
{
	loc = POINT(x, y);
	vector<Texture> spriteTable;
	VECTOR velocity = VECTOR(0, 0);
	VECTOR gravity = VECTOR(0, 5);
	angle = ang;
}
Interactive::Interactive(POINT location, double ang)
{
	loc = location;
	vector<Texture> spriteTable;
	VECTOR velocity = VECTOR(0, 0);
	VECTOR gravity = VECTOR(0, 5);
	angle = ang;
}

Interactive::~Interactive()
{

}
double Interactive::getAngle()
{
	return angle;
}
void Interactive::setAngle(double ang)
{
	angle = ang;
}
void Interactive::frameAdvance()
{
	if (frame > FRAMELIMIT)
	{
		frame = -1;
	}
	frame++;
}

void Interactive::setFramelimit(int f)
{
	FRAMELIMIT = f;
	frame = 0;
}
int Interactive::getFramelimit()
{
	return FRAMELIMIT;
}
Texture& Interactive::getTexture()
{
	return texture;
}
void Interactive::render(int x, int y, SDL_Renderer *renderer, SDL_Rect* clip, SDL_Point* center, SDL_RendererFlip flip)
{
	texture.render(x, y, renderer, clip, angle, center, flip);
	D("Interactive rendered");
}
#ifndef SPRITECLASS
#define SPRITECLASS

#include <map>

class SpriteSheet;

struct SpriteData{

	SpriteData(){
		xOffset = 0;
		yOffset = 0;
		sheetRows = 1;
		sheetCols = 1;
		fWidth = 32;
		fHeight = 32;
		xInc = 1;
		yInc = 1;
		x0 = 0;
		x1 = 1;
		y0 = 0;
		y1 = 1;

		currentFrame = 0;
		frameStart = 0;
		frameCount = 1;
		currentCycle = 0;
		cyclesPerFrame = 0;
		loop = false;
		flipHorizontal = false;
		flicker = false;
	}

	void init(int fs, int fc, int cpf){
		frameStart = fs;
		frameCount = fc;
		cyclesPerFrame = cpf;
		currentFrame = frameStart;
		currentCycle = 0;

		xInc = 1.0f / (float)sheetCols;
		yInc = 1.0f / (float)sheetRows;

		calculateTextureCoords();
	}

	void calculateTextureCoords(){
		int r = currentFrame / sheetRows;
		int c = currentFrame % sheetRows;

		y0 = r * yInc;
		x0 = c * xInc;
		y1 = (r + 1) * yInc;
		x1 = (c + 1) * xInc;
	}

	int xOffset, yOffset;
	int sheetRows, sheetCols;
	int fWidth, fHeight;
	float x0, y0, x1, y1;		// spritesheet texture coordinates
	float xInc, yInc;			// texture coordinate increments

	int currentFrame, frameStart, frameCount;
	int currentCycle, cyclesPerFrame;
	bool loop, active, flipHorizontal, flicker;
};

class Sprite
{
public:
	Sprite(void);
	~Sprite(void);

	void init(SpriteSheet *ss);
	void update();
	void addAnimation(const string& name, int frameStart, int frameCount, int cyclesPerFrame, bool loop);
	void addAnimation(const string& name, int frameStart, int frameCount, int cyclesPerFrame, int sheetRows, int sheetColumns, bool loop);
	void startAnimation(const string& name);
	void startFlicker();
	void stopFlicker();

	int x, y;				// draw position
	
	string currentSprite;
	map<string, SpriteData> spriteMap;
	SpriteSheet *spriteSheet;

	int flickerCounter;
	bool active, updated, drawn, overrideCoordinates, flickerVanish;
};

#endif

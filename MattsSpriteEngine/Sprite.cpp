#include "Sprite.h"
#include "SpriteSheet.h"
//#include "Renderer.h"

Sprite::Sprite(void){
	spriteSheet = NULL;

	currentSprite = "";

	flickerVanish = false;
	flickerCounter = 0;
	overrideCoordinates = false;
}

Sprite::~Sprite(void){
}

void Sprite::init(SpriteSheet *ss){
	spriteSheet = ss;

	active = true;
	updated = false;
	drawn = false;
}

void Sprite::addAnimation(const string& name, int frameStart, int frameCount, int cyclesPerFrame, bool loop = false){
	addAnimation(name, frameStart, frameCount, cyclesPerFrame, spriteSheet->frameData.y, spriteSheet->frameData.x, loop);
}

void Sprite::addAnimation(const string& name, int frameStart, int frameCount, int cyclesPerFrame, int sheetRows, int sheetColumns, bool loop = false){
	SpriteData sd;
	sd.sheetRows = sheetRows;
	sd.sheetCols = sheetColumns;
	sd.fWidth = spriteSheet->frameData.w / sheetColumns;
	sd.fHeight = spriteSheet->frameData.h / sheetRows;
	sd.loop = loop;
	sd.init(frameStart, frameCount, cyclesPerFrame);

	spriteMap[name] = sd;
}

void Sprite::startAnimation(const string& name){
	//spriteMap[currentSprite].active = false;
	currentSprite = name;
	spriteMap[currentSprite].currentFrame = spriteMap[currentSprite].frameStart;
	spriteMap[currentSprite].currentCycle = 0;
	//spriteMap[currentSprite].active = true;
}

void Sprite::update(){

	SpriteData& sd = spriteMap[currentSprite];

	if(sd.cyclesPerFrame > 0){

		if(++sd.currentCycle == sd.cyclesPerFrame){
			++sd.currentFrame;
			sd.currentFrame = (sd.currentFrame - sd.frameStart) % sd.frameCount + sd.frameStart;
			sd.currentCycle = 0;
			sd.calculateTextureCoords();
		}
	}

	if(sd.flicker){
		++flickerCounter;
		if(flickerCounter >= 2){
			flickerVanish = !flickerVanish;
			flickerCounter = 0;
		}
	}

	updated = true;
	drawn = false;
}

void Sprite::startFlicker(){
	spriteMap[currentSprite].flicker = true;
	flickerVanish = true;
	flickerCounter = 0;
}

void Sprite::stopFlicker(){
	spriteMap[currentSprite].flicker = false;
	flickerVanish = false;
}

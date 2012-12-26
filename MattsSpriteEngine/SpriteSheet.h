#ifndef SHEETCLASS
#define SHEETCLASS

#include <string>

#include <SDL/SDL.h>

struct SDL_Surface;

class SpriteSheet
{
public:
	SpriteSheet(void);
	~SpriteSheet(void);

	bool load(std::string &fileName);
	unsigned int createTextureFromSurface(SDL_Surface* surface);
	bool unload();

	void setFrameData(int x, int y, int w, int h);

	//SDL_Surface *image;
	unsigned int texID;

	// x = # of columns, y = # of rows
	// w = frame width, h = frame height
	SDL_Rect frameData;
	int frameCount;
};

#endif

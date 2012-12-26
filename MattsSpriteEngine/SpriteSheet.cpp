#include "SpriteSheet.h"

#include <GL/glew.h>
#include <gl/GL.h>
#include <SDL/SDL_image.h>

SpriteSheet::SpriteSheet(void){
	//image = NULL;
	texID = 0;
	frameData.x = 4;
	frameData.y = 4;
	frameData.w = 16;
	frameData.h = 16;
	frameCount = frameData.x * frameData.y;
}

SpriteSheet::~SpriteSheet(void){
}

bool SpriteSheet::load(std::string &fileName){

	//Temp image that's loaded
    SDL_Surface* loadedImage = NULL;
    
    //Load the image using SDL_image
    loadedImage = IMG_Load(fileName.c_str());

	texID = createTextureFromSurface(loadedImage);
    
    //If the image loaded
    if(loadedImage != NULL){

        //Create an optimized image
        //image = SDL_DisplayFormatAlpha(loadedImage);
        //Free the old image
        SDL_FreeSurface(loadedImage);
    }
	else{
		return false;
	}

	return true;
}

GLuint SpriteSheet::createTextureFromSurface(SDL_Surface* surface) {
	GLint bytesPerPixel;
	GLenum textureFormat;
	GLuint spriteTexture;

	bytesPerPixel = surface->format->BytesPerPixel;
	// has alpha channel
	if(bytesPerPixel == 4) {
		if(surface->format->Rmask == 0x000000ff)
			textureFormat = GL_RGBA;
		else
			textureFormat = GL_BGRA;
	}
	// no alpha channel
	else if (bytesPerPixel == 3) {
		if(surface->format->Rmask == 0x000000ff)
			textureFormat = GL_RGB;
		else
			textureFormat = GL_BGR;
	}
	else {
		printf("MUKYUUU~ Invalid number of bytes per pixel.\n");
		printf("Bytes per pixel: %d\n", bytesPerPixel);
	}

	// make GL texture
	glGenTextures(1, &spriteTexture);
	glBindTexture(GL_TEXTURE_2D, spriteTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	gluBuild2DMipmaps(GL_TEXTURE_2D, bytesPerPixel, surface->w, surface->h, textureFormat, GL_UNSIGNED_BYTE, surface->pixels);

	return spriteTexture;
}

bool SpriteSheet::unload(){
	//SDL_FreeSurface(image);
	return true;
}

void SpriteSheet::setFrameData(int x, int y, int w, int h){
	frameData.x = x;
	frameData.y = y;
	frameData.w = w;
	frameData.h = h;
	frameCount = frameData.x * frameData.y;
}

#ifndef SPRITE_H_
#define SPRITE_H_

#include <SDL.h>
#include <iostream>


using std::cout;
using std::endl;
using std::string;

class Sprite {

public:
	Sprite();
	Sprite(string file);
	Sprite(string file, int frameCount, float frameTime);
	~Sprite();

	void Open(string file);
	void SetClip(int x, int y, int w, int h);
	void Render(int x, int y);
	void Render(int x, int y, float angle);
	int GetHeight();
	int GetWidth();
	bool IsOpen();
	string GetFile();

	void SetScaleX(float scale);
	void SetScaleY(float scale);
	void SetScale(float scale);

	void RenderFlipped(int x, int y);

	void Update(float dt);
	void SetFrame(int frame);
	void SetFrameCount(int frameCount);
	void SetAnimationTimes(int times);
	void SetFrameTime(float frameTime);
	bool IsAnimationFinished();
	void SetAlpha(int);
	void FadeIn(int inc = 1);
	void FadeOut(int dec = 1);
	void FadeToValue(int);

private:
	SDL_Texture* texture;
	SDL_Rect clipRect;
	SDL_Rect dstRect;
	int width;
 	int height;

	float scaleY;
	float scaleX;

	int frameCount;
	int currentFrame;
	float timeElapsed;
	float frameTime;
	int times;
	int timesCounter;
	string file;

	int fadeValue;
    int fadeModifyer;
    uint8_t actualAlpha;
	bool fadingIn;
	bool fadingOut;
	bool fadingToValue;
	void _fadeIn();
	void _fadeOut();
	void _fadeToValue();
};

#endif

/*
 * Sprite.h
 *
 *  Created on: 12 de mar de 2016
 *      Author: Caio
 */

#ifndef SPRITE_H_
#define SPRITE_H_

#include <SDL.h>
#include <iostream>

using namespace std;
class Sprite {
public:
	Sprite();
	Sprite(string file);
	~Sprite();
	void Open(string file);
	void SetClip(int x, int y, int w, int h);
	void Render(int x, int y);
	void Render(int x, int y, float angle);
	int GetHeight();
	int GetWidth();
	bool IsOpen();

	void SetScaleX(float scale);
	void SetScaleY(float scale);
	void SetScale(float scale);

	void RenderFlipped(int x, int y);

	void Update(float dt);
	void SetFrame(int frame);
	void SetFrameCount(int frameCount);
	void SetFrameTime(float frameTime);
	void SetAlpha()
	Sprite(string file, int frameCount, float frameTime);

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
};

#endif /* SPRITE_H_ */

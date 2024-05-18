#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_ttf.h>
#include <array>

class GameWindow {
	public:
		GameWindow(int width, int height);
		~GameWindow();
		//void render();
		SDL_Renderer* getRenderer();
		void render(const std::array<unsigned char, 0x8000>& processedMemory);
		SDL_Texture* createTextTexture(SDL_Renderer* renderer, const uint8_t* text, SDL_Color textColor);
		// SDL_Texture* createTextTexture(SDL_Renderer* renderer, const std::string& text, SDL_Color textColor, TTF_Font* font);

	private:
		int screenWidth;
		int screenHeight;
		SDL_Window* window;
		SDL_Renderer* renderer;
		TTF_Font* font;
};

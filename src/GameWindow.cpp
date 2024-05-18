#include "GameWindow.hpp"

GameWindow::GameWindow(int width, int height) : screenWidth(width), screenHeight(height)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "Error al inicializar SDL: " << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}

	window = SDL_CreateWindow("Gameboy Emulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		std::cerr << "Error al crear la ventana: " << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		std::cerr << "Error al crear el renderer: " << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}
	if (TTF_Init() == -1) {
        std::cerr << "Error al inicializar SDL_ttf: " << TTF_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Carga la fuente de texto
    font = TTF_OpenFont("./doc/Arial.ttf", 24);
    if (font == nullptr) {
        std::cerr << "Error al cargar la fuente de texto: " << TTF_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
}

GameWindow::~GameWindow()
{
	if (font != nullptr) {
        TTF_CloseFont(font);
    }

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

SDL_Renderer* GameWindow::getRenderer() {
	return this->renderer;
}

void GameWindow::render(const std::array<unsigned char, 0x8000>& processedMemory) {
    // Limpia el renderizador
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    // Renderiza el contenido de la memoria en la pantalla
    SDL_Color textColor = { 0, 0, 0, 255 };
    SDL_Texture* textTexture = createTextTexture(renderer, processedMemory.data(), textColor);
    if (textTexture != nullptr) {
        // Obtiene las dimensiones de la textura de texto
        int textWidth, textHeight;
        SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);

        // Calcula la posición para centrar el texto en la ventana
        int x = (screenWidth - textWidth) / 2;
        int y = (screenHeight - textHeight) / 2;

        // Renderiza la textura de texto en la ventana
        SDL_Rect renderQuad = { x, y, textWidth, textHeight };
        SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad);

        // Libera la textura de texto
        SDL_DestroyTexture(textTexture);
    }

    // Actualiza la ventana SDL
    SDL_RenderPresent(renderer);
}

SDL_Texture* GameWindow::createTextTexture(SDL_Renderer* renderer, const uint8_t* text, SDL_Color textColor) {
    // Crea una superficie de texto a partir de los datos de la memoria
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, reinterpret_cast<const char*>(text), textColor);
    if (textSurface == nullptr) {
        std::cerr << "Error al crear la superficie de texto: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    // Crea una textura de texto a partir de la superficie
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == nullptr) {
        std::cerr << "Error al crear la textura de texto: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    // Libera la superficie de texto
    SDL_FreeSurface(textSurface);

    return textTexture;
}
#include "GameWindow.hpp"
#include "LoadRoom.hpp"
#include "MemoryMap.hpp"
#include "CPU.hpp"

#define DEBUG true

int main() {
    GameWindow window(640, 480);
    MemoryMap memory;
    CPU cpu(memory); // Suponiendo que ya tienes la instancia de la CPU

    LoadRoom loader(memory);

    // Main loop
    bool quit = false;
    bool romLoaded = false;
    while (!quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                // Si se presiona la tecla 'L', carga la ROM
                if (e.key.keysym.sym == SDLK_l) {
                    loader.loadROM("./doc/roms/Pokemon_Rouge.gb");
                    romLoaded = true;
                }
            }
        }

        // Si la ROM ha sido cargada, comienza a ejecutar la CPU
        if (romLoaded) {
            cpu.executeNextInstruction();
            window.render(memory.getProcessedMemory());
        }
    }

    return 0;
}
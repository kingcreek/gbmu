#pragma once

#include <cstdint>
#include "MemoryMap.hpp"
#include "Constants.hpp"
#include <iostream>

class CPU {
public:
    CPU(MemoryMap& memory);
    void executeNextInstruction();
	void handleInterrupts();

private:
    MemoryMap& memory;
    // Registros de la CPU
    uint16_t PC; // Contador de programa
	uint16_t SP; // Puntero de pila
    uint8_t A, F; // Acumulador y Registro de banderas
    uint8_t B, C, D, E, H, L; // Registros generales
};
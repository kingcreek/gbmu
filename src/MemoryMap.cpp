#include "MemoryMap.hpp"

MemoryMap::MemoryMap() {
    // Inicializa las regiones de memoria
    memory.fill(0);
}

uint8_t MemoryMap::read(uint16_t address) {
    return memory[address];
}

void MemoryMap::write(uint16_t address, uint8_t value) {
    memory[address] = value;
}

uint16_t MemoryMap::read16(uint16_t address) {
    // Lee un valor de 16 bits de la memoria en la dirección especificada
    return (memory[address + 1] << 8) | memory[address];
}

void MemoryMap::write16(uint16_t address, uint16_t value) {
    // Escribe un valor de 16 bits en la memoria en la dirección especificada
    memory[address] = value & 0xFF;
    memory[address + 1] = (value >> 8) & 0xFF;
}
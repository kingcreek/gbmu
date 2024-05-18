#include "LoadRoom.hpp"

LoadRoom::LoadRoom(MemoryMap& memory) : memory(memory) {}

void LoadRoom::loadROM(const std::string& filepath) {
    std::ifstream romFile(filepath, std::ios::binary);
    if (!romFile.is_open()) {
        std::cerr << "Error: Failed to open ROM file." << std::endl;
        return;
    }

    // Leer la ROM y escribir los datos en el MemoryMap
    uint16_t address = 0x0000;
    uint8_t data;
    while (romFile.read(reinterpret_cast<char*>(&data), sizeof(data))) {
        memory.write(address, data);
        address++;
    }

    std::cout << "ROM loaded successfully." << std::endl;
    romFile.close();
}
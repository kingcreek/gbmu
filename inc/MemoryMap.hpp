#pragma once

#include <array>
#include <cstdint>

class MemoryMap {
	public:
		MemoryMap();

		// Métodos para leer y escribir en las regiones de memoria
		uint8_t read(uint16_t address);
		void write(uint16_t address, uint8_t value);
		uint16_t read16(uint16_t address);
    	void write16(uint16_t address, uint16_t value);
		const std::array<uint8_t, 0x10000>& getProcessedMemory() const {
			return memory;
		}
		
	private:
		std::array<uint8_t, 0x10000> memory;
		//0x0000 - 0x00FF : Boot ROM then interrupt table
		//0x0000 - 0x3FFF : Bank0, always the same memory, cannot be switched out later
		//0x4000 - 0x7FFF : Bank N, for bank switching
		//0x8000 - 0x9FFF : Tile RAM
		//0x9800 - 0x9FFF : Background Map
		//0xA000 - 0xBFFF : Cartridge RAM
		//0xC000 - 0xDFFF : Working RAM
		//0xE000 - 0xFDFF : Echo RAM
		//0xFE00 - 0xFE9F : Object Attribute Memory
		//0xFEA0 - 0xFEFF : Unused
		//0xFF00 - 0xFF7F : I/O registers
		//0xFF80 - 0xFFFE : High RAM Area
		//0xFFFF : Interrupt Enabled Register
};
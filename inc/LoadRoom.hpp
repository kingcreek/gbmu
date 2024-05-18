#pragma once

#include <iostream>
#include <fstream>
#include "MemoryMap.hpp"

class LoadRoom {
public:
    LoadRoom(MemoryMap& memory);
    void loadROM(const std::string& filepath);

private:
    MemoryMap& memory;
};
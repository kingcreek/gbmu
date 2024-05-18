#include "CPU.hpp"

CPU::CPU(MemoryMap& memory) : memory(memory), PC(0x100), SP(0xFFFE) {
    // Inicializa los registros de la CPU
    A = 0x01;
    F = 0xB0;
    B = 0x00;
    C = 0x13;
    D = 0x00;
    E = 0xD8;
    H = 0x01;
    L = 0x4D;
}

void CPU::executeNextInstruction() {
    // Obtiene la siguiente instrucción de la memoria
    uint8_t opcode = memory.read(PC);
    
    if (DEBUG)
        std::cout << opcode << std::endl;
    // Incrementa el contador de programa
    PC++;

    // Decodifica y ejecuta la instrucción
    switch (opcode) {
        // NOP
        case 0x00:
            // No hace nada
            break;
        // LD BC, nn
        case 0x01:
            C = memory.read(PC++);
            B = memory.read(PC++);
            break;
        // LD (BC), A
        case 0x02:
            memory.write((B << 8) | C, A);
            break;
        // LD B, n
        case 0x06:
            B = memory.read(PC++);
            break;
        // LD C, n
        case 0x0E:
            C = memory.read(PC++);
            break;
        // INC B
        case 0x04:
            B++;
            break;
        // DEC B
        case 0x05:
            B--;
            break;
        // ADD A, n
        case 0xC6:
            A += memory.read(PC++);
            break;
        // SUB n
        case 0xD6:
            A -= memory.read(PC++);
            break;
        // AND n
        case 0xE6:
            A &= memory.read(PC++);
            break;
        // OR n
        case 0xF6:
            A |= memory.read(PC++);
            break;
        // XOR n
        case 0xEE:
            A ^= memory.read(PC++);
            break;
        // JP nn
        case 0xC3:
            PC = memory.read16(PC);
            break;
        // JR n
        case 0x18:
            PC += static_cast<int8_t>(memory.read(PC++));
            break;
        // CALL nn
        case 0xCD:
            memory.write16(--SP, PC);
            PC = memory.read16(PC);
            break;
        default:
            // Instrucción no reconocida
            break;
    }
}

void CPU::handleInterrupts() {
    // Comprueba si hay alguna interrupción activa
    uint8_t interruptFlags = memory.read(0xFF0F);
    uint8_t interruptEnabled = memory.read(0xFFFF);
    uint8_t triggeredInterrupts = interruptFlags & interruptEnabled;

    if (triggeredInterrupts) {
        // Temporalmente desactiva las interrupciones
        memory.write(0xFFFF, 0x00);

        // Maneja las interrupciones activas una por una
        for (int i = 0; i < 5; ++i) {
            if (triggeredInterrupts & (1 << i)) {
                // Limpia la bandera de interrupción
                memory.write(0xFF0F, interruptFlags & ~(1 << i));

                // Guarda la dirección actual del programa en la pila
                memory.write16(--SP, PC);

                // Salta a la dirección de la rutina de interrupción
                PC = 0x0040 + i * 8;
            }
        }
    }
}

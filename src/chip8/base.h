#ifndef BASE_H
#define BASE_H

#include <cstdint>
#include <fstream>
#include <chrono>
#include <random>
#include <cstring>

const unsigned int START_ADDRESS = 0x200;
const unsigned int FONT_START_ADDRESS = 0x50;
const unsigned int FONT_SIZE = 80;
const unsigned int DISPLAY_WIDTH = 64;
const unsigned int DISPLAY_HEIGHT = 32;

class Chip8 {

public:
  Chip8();

  int8_t V[16]; // general registers for the emulator. V0-Vf
  uint8_t memory[4096];
  uint8_t DT; // delay timer
  uint8_t ST; // soudn timer
  uint8_t key_pad[16];

  int16_t I; // used so store addresses, most of the lower 12 bits are used..
  int16_t PC; // program counter -> store the currently executing address
  int16_t SP; // stack pointer -> tompost level of the stack.
  int16_t stack[16];
  const int16_t ROMTOP = 512;
  uint16_t opcode;

  uint32_t display[DISPLAY_WIDTH * DISPLAY_HEIGHT];

  const uint8_t fonts[FONT_SIZE] = {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // -> 0
    0x20, 0x60, 0x20, 0x20, 0x70, // -> 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // -> 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // -> 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // -> 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // -> 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // -> 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // -> 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // -> 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // -> 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // -> A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // -> B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // -> C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // -> D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // -> E
    0xF0, 0x80, 0xF0, 0x80, 0x80, // -> F
    };

  std::default_random_engine rand_gen;
  std::uniform_int_distribution<uint8_t> rand_byte;

  void load_rom(const char* filename);
  void cycle();

  // instructions
  void INS_00E0(); // CLS
  void INS_00EE(); // RET
  void INS_1nnn(); // JP addr
  void INS_2nnn(); // CALL addr
  void INS_3xkk(); // SNE Vx == kk
  void INS_4xkk(); // SNE Vx != kk
  void INS_5xy0(); // SE Vx == Vy
  void INS_6xkk(); // set Vx = kk
  void INS_7xkk(); // set Vx = Vx + kk
  void INS_8xy0(); // set Vx = Vy
  void INS_8xy1(); // set Vx = Vx OR Vy
  void INS_8xy2(); // set Vx = Vx AND Vy
  void INS_8xy3(); // set Vx = Vx XOR Vy
  void INS_8xy4(); // set Vx = Vx- Vy, set VF = carry
  void INS_8xy5(); // set Vx = Vx - Vy, set VF = NOT borrow
  void INS_8xy6(); // set Vx = Vx SHR 1
  void INS_8xy7(); // set Vx = Vy - Vx, set VF = NOT borrow
  void INS_8xyE(); // set Vx = Vx SHL 1
  void INS_9xy0(); // SNE Vx != Vy
  void INS_Annn(); // set I = nnn
  void INS_Bnnn(); // JMP nnn + V0
  void INS_Cxxx(); // set Vx = rand byte AND kk
  void INS_Dxyn(); // display & mem loc I at (Vx, Vy), set VF = collision
  void INS_Ex9E(); // SKP Vx
  void INS_ExA1(); // SKNP Vx
  void INS_Fx07(); // set Vx = delay timer value
  void INS_Fx0A(); // Key Press in Vx
  void INS_Fx15(); // set DT = Vx
  void INS_Fx18(); // set ST = Vx
  void INS_Fx1E(); // set I = I + Vx
  void INS_Fx29(); // set I = loc of sprite for digit Vx
  void INS_Fx33(); // store BCD rep of Vx in mem locations I, I+1, and I+2
  void INS_Fx55(); // store reg V0-VF at loc I
  void INS_Fx65(); // read reg V0-Vf at loc I
};

#endif
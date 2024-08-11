#include "base.h"

void Chip8::load_rom(const char* filename) {

  std::ifstream file(filename, std::ios::binary | std::ios::ate);

  if (file.is_open()) {
    // creates a buffer in size of the file.
    std::streampos size = file.tellg();
    char* buffer = new char[size];

    // goes back to the beginning of the file and then fills the buffer
    file.seekg(0, std::ios::beg);
    file.read(buffer, size);
    file.close();
    
    for (long i = 0; i < size; ++i) {
      memory[START_ADDRESS + i] = buffer[i];
    }

    delete[] buffer;
  }
}

Chip8::Chip8()
  : randGen(std::chrono::system_clock::now().time_since_epoch().count()) {

  PC = START_ADDRESS;

  for (unsigned int i = 0; i < FONT_SIZE; ++i){
    memory[FONT_START_ADDRESS + i] = fonts[i];
  }

  randByte = std::uniform_int_distribution<uint8_t>(0, 255U);
}

Chip8::INS_00E0() {
  memset(display, 0, sizeof(display));
}

Chip8::INS_00EE() {
  --SP;
  PC = stack[SP];
}

// u declares its an unsigned integer
Chip8::INS_1nnn() {
  uint16_t address = opcode & 0x0FFFu;
  PC = address;
}

Chip8::INS_2nnn() {
  uint16_t address = opcode & 0x0FFFu;
  stack[SP] = PC;
  ++SP;
  PC = address;
}

// 8u -> shift right by 8 bits
// opcode = 0x1234
// every Vx refers to a different Vx register 0-F
// byte holds the keywork kk
Chip8::INS_3xkk() {
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t byte = opcode & 0x00FFu;
  if (V[Vx] == byte) {
    PC += 2;
  }
}

Chip8::INS_4xkk() {
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t byte = opcode & 0x00FFu;
  if (V[Vx] != byte) {
    PC += 2;
  }
}

Chip8::INS_5xy0() {
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t Vy = (opcode & 0x00F0u) >> 4u;
  if (V[Vx] == V[Vy]) {
    PC += 2;
  }
}

Chip8::INS_6xkk() {
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t byte = opcode & 0x00F0u;
  V[Vx] = byte;
}

Chip8::INS_7xkk() {
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t byte = opcode & 0x00F0u;
  V[Vx] += byte;
}

Chip8::INS_8xy0() {
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t Vy = (opcode & 0x00F0u) >> 4u;
  V[Vx] = V[Vy];
}

Chip8::INS_8xy1() {
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t Vy = (opcode & 0x00F0u) >> 4u;
  V[Vx] != V[Vy];
}

Chip8::INS_8xy2() {
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t Vy = (opcode & 0x00F0u) >> 4u;
  V[Vx] &= V[Vy];
}

Chip8::INS_8xy3() {
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t Vy = (opcode & 0x00F0u) >> 4u;
  V[Vx] ^= V[Vy];
}

Chip8::INS_8xy4() {
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t Vy = (opcode & 0x00F0u) >> 4u;
  uint16_t sum = V[Vx] + V[Vy];
  if (sum > 255u) {
    V[0xF] = 1;
  } else {
    V[0xF] = 0;
  }
  V[Vx] = sum & 0xFFu;
}

Chip8::INS_8xy5() {
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t Vy = (opcode & 0x00F0u) >> 4u;
  if (V[Vx] > V[Vy]) {
    V[0xF] = 1;
  } else {
    V[0xF] = 0;
  }
  V[Vx] -= V[Vy];
}

Chip8::INS_8xy6() {
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  V[0xF] = (V[Vx] & 0x1u);
  V[Vx] >>= 1;
}

Chip8::INS_8xy7() {
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t Vy = (opcode & 0x00F0u) >> 4u;
  if (V[Vy] > V[Vx]) {
    V[0xF] = 1;
  } else {
    V[0xF] = 0;
  }
  V[Vx] = V[Vy] - V[Vx];
}

Chip8::INS_8xyE() {
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  V[0xF] = (V[Vx] & 0x80u) >> 7u;
  V[Vx] <<= 1;
}

Chip8::INS_9xy0() {
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t Vy = (opcode & 0x00F0u) >> 4u;
  if (V[Vx] != V[Vy]) {
    PC += 2;
  }
}

Chip8::INS_Annn() {
  uint16_t address = opcode & 0x0FFFu;
  I = address;
}

Chip8::INS_Bnnn() {
  uint16_t address = opcode & 0x0FFFu
  PC = v[0] + address;
}

Chip8::INS_Cxxx() {
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t byte = opcode & 0x00FFu;
  V[Vx] = randByte(randGen) & byte;
}

Chip8::INS_Dxyn() {
  return 0;
}
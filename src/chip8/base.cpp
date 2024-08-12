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
  : rand_gen(std::chrono::system_clock::now().time_since_epoch().count()) {

  PC = START_ADDRESS;

  for (unsigned int i = 0; i < FONT_SIZE; ++i){
    memory[FONT_START_ADDRESS + i] = fonts[i];
  }

  rand_byte = std::uniform_int_distribution<uint8_t>(0, 255U);
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
  V[Vx] = rand_byte(rand_gen) & byte;
}

Chip8::INS_Dxyn() {
  uint8_t Vx = (opcode & 0x0F00u) >> 8u; // Vx = 2
  uint8_t Vy = (opcode & 0x00F0u) >> 4u; // Vy = 3
  uint8_t h = opcode & 0x000Fu; // h = 4

  uint8_t x = V[Vx] % 64;
  uint8_t y = V[Vy] % 32;

  V[0xF] = 0;

  for (unsigned int row = 0; row < h; ++row) {
    uint8_t sprite_byte = memory[I + row];

    for (unsigned int col = 0; col < 8; ++col) { // one sprite is  bits
      uint8_t sprite_pixel = sprite_byte & (0x80u >> col); // shifts to most sig bit by the size of col
      uint32_t* display_pixel = &display[(y + row) * DISPLAY_WIDTH + (x + col)]; // gives coordinates.
      if (sprite_pixel) {
        if (*display_pixel == 0xFFFFFFFF) { // checking if thers already a col of pixels, to avoid collision
          V[0xF] = 1;
        }
        *display_pixel ^= 0xFFFFFFFF; // simplay XORing the result.
      }
    }
  }
}

Chip8::INS_Ex9E() {
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8t key = V[Vx];
  if (key_pad[key]) {
    PC += 2;
  }
}

Chip8::INS_ExA1() {
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t key = V[Vx];
  if (!key_pad[key]) {
    PC += 2;
  }
}

Chip8::INS_Fx07() {
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  V[Vx] = DT;
}

Chip8::INS_Fx0A() {
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;

  if (key_pad[0]) {
    V[Vx] = 0;
  } else if (key_pad[1]) {
    V[Vx] = 1;
  } else if (key_pad[2]) {
    V[Vx] = 2;
  } else if (key_pad[3]) {
    V[Vx] = 3;
  } else if (key_pad[4]) {
    V[Vx] = 4;
  } else if (key_pad[5]) {
    V[Vx] = 5;
  } else if (key_pad[6]) {
    V[Vx] = 6;
  } else if (key_pad[7]) {
    V[Vx] = 7;
  } else if (key_pad[8]) {
    V[Vx] = 8;
  } else if (key_pad[9]) {
    V[Vx] = 9;
  } else if (key_pad[10]) {
    V[Vx] = 10;
  } else if (key_pad[11]) {
    V[Vx] = 11;
  } else if (key_pad[12]) {
    V[Vx] = 12;
  } else if (key_pad[13]) {
    V[Vx] = 13;
  } else if (key_pad[14]) {
    V[Vx] = 14;
  } else if (key_pad[15]) {
    V[Vx] = 15;
  } else {
    PC -= 2;
  }
}

Chip8::INS_Fx15() {
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  DT = V[Vx];
}

Chip8::INS_Fx18() {
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  ST = V[Vx];
}

Chip8::INS_Fx1E() {
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  I += V[Vx];
}

Chip8::INS_Fx29() {
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t digit = V[Vx];
  I = FONT_START_ADDRESS + (5 * digit);
}

Chip8::INS_Fx33() {
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t value = V[Vx];

  memory[I + 2] = value % 10;
  value /= 10;

  memory[I + 1] = value % 10;
  value /= 10;

  memory[I] = value % 10;
}

Chip8::INS_Fx55() {
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  for (uint8_t i = 0; i <= Vx; ++i) {
    memory[I +i] = V[i];
  }
}

Chip8::INS_Fx65() {
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  for (uint8_t i = 0; i <= Vx; ++i) {
    V[i] = memory[I +i];
  }
}
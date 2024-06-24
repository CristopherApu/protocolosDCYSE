#ifndef SLIP_H
#define SLIP_H

#include <vector>

const unsigned char END = 0xC0;
const unsigned char ESC = 0xDB;
const unsigned char ESC_END = 0xDC;
const unsigned char ESC_ESC = 0xDD;

std::vector<unsigned char> slip_codificar(const std::vector<unsigned char>& input);
std::vector<unsigned char> slip_decodificar(const std::vector<unsigned char>& input);

#endif // SLIP_H
#ifndef SLIP_H
#define SLIP_H

#include <vector>

// Definición de los caracteres especiales SLIP
#define END     0xC0
#define ESC     0xDB
#define ESC_END 0xDC
#define ESC_ESC 0xDD

std::vector<unsigned char> slip_encode(const std::vector<unsigned char>& input);
std::vector<unsigned char> slip_decode(const std::vector<unsigned char>& input);

#endif // SLIP_H
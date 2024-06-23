#ifndef SLIP_H
#define SLIP_H

#include <vector>

#define END 0300
#define ESC 0333
#define ESC_END 0334
#define ESC_ESC 0335

std::vector<unsigned char> slip_encode(const std::vector<unsigned char>& input);
std::vector<unsigned char> slip_decode(const std::vector<unsigned char>& input);

#endif // SLIP_H

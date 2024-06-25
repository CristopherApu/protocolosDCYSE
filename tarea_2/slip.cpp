#include "slip.h"
#include <cstddef>

std::vector<unsigned char> slip_encode(const std::vector<unsigned char>& input) {
    std::vector<unsigned char> output;
    output.push_back(END);
    for (unsigned char byte : input) {
        if (byte == END) {
            output.push_back(ESC);
            output.push_back(ESC_END);
        } else if (byte == ESC) {
            output.push_back(ESC);
            output.push_back(ESC_ESC);
        } else {
            output.push_back(byte);
        }
    }
    output.push_back(END);
    return output;
}

std::vector<unsigned char> slip_decode(const std::vector<unsigned char>& input) {
    std::vector<unsigned char> output;
    bool escape = false;
    for (size_t i = 1; i < input.size() - 1; ++i) {
        if (escape) {
            if (input[i] == ESC_END) {
                output.push_back(END);
            } else if (input[i] == ESC_ESC) {
                output.push_back(ESC);
            }
            escape = false;
        } else if (input[i] == ESC) {
            escape = true;
        } else {
            output.push_back(input[i]);
        }
    }
    return output;
}
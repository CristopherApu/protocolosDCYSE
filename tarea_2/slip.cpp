#include "slip.h"

std::vector<unsigned char> slip_encode(const std::vector<unsigned char>& input) {
    std::vector<unsigned char> output;
    for (auto byte : input) {
        switch (byte) {
            case END:
                output.push_back(ESC);
                output.push_back(ESC_END);
                break;
            case ESC:
                output.push_back(ESC);
                output.push_back(ESC_ESC);
                break;
            default:
                output.push_back(byte);
        }
    }
    output.push_back(END);
    return output;
}

std::vector<unsigned char> slip_decode(const std::vector<unsigned char>& input) {
    std::vector<unsigned char> output;
    for (size_t i = 0; i < input.size(); ++i) {
        if (input[i] == ESC) {
            ++i;
            if (input[i] == ESC_END) {
                output.push_back(END);
            } else if (input[i] == ESC_ESC) {
                output.push_back(ESC);
            }
        } else {
            output.push_back(input[i]);
        }
    }
    return output;
}
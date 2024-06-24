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
                break;
        }
    }
    output.push_back(END);
    return output;
}

std::vector<unsigned char> slip_decode(const std::vector<unsigned char>& input) {
    std::vector<unsigned char> output;
    bool escaped = false;
    
    for (auto byte : input) {
        if (escaped) {
            if (byte == ESC_END) {
                output.push_back(END);
            } else if (byte == ESC_ESC) {
                output.push_back(ESC);
            }
            escaped = false;
        } else {
            if (byte == ESC) {
                escaped = true;
            } else {
                output.push_back(byte);
            }
        }
    }
    return output;
}
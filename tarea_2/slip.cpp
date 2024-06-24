#include "slip.h"

std::vector<unsigned char> slip_codificar(const std::vector<unsigned char>& input) {
    std::vector<unsigned char> output;
    output.push_back(END); // Marca de inicio

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

    output.push_back(END); // Marca de fin
    return output;
}

std::vector<unsigned char> slip_decodificar(const std::vector<unsigned char>& input) {
    std::vector<unsigned char> output;
    bool escapando = false;

    for (size_t i = 0; i < input.size(); ++i) {
        if (!escapando) {
            if (input[i] == ESC) {
                escapando = true;
            } else if (input[i] == END) {
                // Fin del paquete, terminamos la decodificación
                break;
            } else {
                output.push_back(input[i]);
            }
        } else {
            if (input[i] == ESC_END) {
                output.push_back(END);
            } else if (input[i] == ESC_ESC) {
                output.push_back(ESC);
            }
            escapando = false;
        }
    }

    return output;
}
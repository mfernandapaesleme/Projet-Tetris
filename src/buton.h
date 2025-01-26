#pragma once
#include "window.h"
#include "raylib.h"
#include <string>

class Button {
private:
    Rectangle button;       // Retângulo do botão
    Color color;            // Cor do botão
    std::string text;       // Texto do botão
    int fontSize = 24;      // Tamanho da fonte
    Color textColor = BLACK; // Cor do texto

public:
    Button(Vector2 position, Vector2 size, Color _color, std::string _text);
    ~Button();
    void render(); // Declaração da função render
    bool isClicked(Vector2 mousePosition);
};


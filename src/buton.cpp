#include "buton.h"
#include <iostream>

Button::Button(Vector2 position, Vector2 size, Color _color, std::string _text)
    : color(_color), text(_text) {
    button.x = position.x;
    button.y = position.y;
    button.width = size.x;
    button.height = size.y;
}

Button::~Button() {}

void Button::render() {
    DrawRectangleRec(button, color); // Desenha o botão
    DrawRectangleLinesEx(button, 1, BLACK); // Desenha a borda preta

    // Centraliza o texto no botão
    int textWidth = MeasureText(text.c_str(), fontSize);
    int textHeight = fontSize;

    Vector2 textPosition = {
        button.x + (button.width - textWidth) / 2,
        button.y + (button.height - textHeight) / 2
    };

    DrawText(text.c_str(), textPosition.x, textPosition.y, fontSize, textColor);
}

bool Button::isClicked(Vector2 mousePosition) {
    return CheckCollisionPointRec(mousePosition, button) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
  }
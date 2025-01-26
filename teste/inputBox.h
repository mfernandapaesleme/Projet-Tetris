#include "raylib.h"
#include <string>

class InputBox {
private:
    Rectangle box;            // Retângulo para a caixa de entrada
    std::string input;        // String de entrada do usuário
    bool isActive;            // Indica se a caixa de entrada está ativa
    int fontSize;             // Tamanho da fonte
    Color boxColor;           // Cor da caixa
    Color outlineColor;       // Cor do contorno
    Color textColor;          // Cor do texto
    Font font;                // Fonte personalizada

public:
    InputBox(Vector2 position, Vector2 size) {
        box.x = position.x;
        box.y = position.y;
        box.width = size.x;
        box.height = size.y;

        isActive = false;
        input = "";
        fontSize = 24;
        boxColor = WHITE;
        outlineColor = BLACK;
        textColor = BLACK;

        font = LoadFont("Font/arial.ttf"); // Certifique-se de que o arquivo existe
        if (!font.texture.id) {
            TraceLog(LOG_ERROR, "Font not loaded");
        }
    }

    ~InputBox() {
        UnloadFont(font); // Liberar a fonte ao destruir a classe
    }

    void render() {
        // Desenhar a caixa
        DrawRectangleRec(box, boxColor);
        DrawRectangleLinesEx(box, 1, outlineColor);

        // Exibir o texto da entrada
        Vector2 textPosition = { box.x + 5, box.y + (box.height - fontSize) / 2 };
        DrawTextEx(font, input.c_str(), textPosition, fontSize, 2, textColor);

        // Exibir um cursor piscando se a caixa estiver ativa
        if (isActive) {
            float cursorX = textPosition.x + MeasureTextEx(font, input.c_str(), fontSize, 2).x + 2;
            float cursorY = textPosition.y;
            DrawRectangle(cursorX, cursorY, 2, fontSize, textColor);
        }
    }

    void handleInput() {
        // Verificar se o botão esquerdo do mouse foi pressionado
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mousePos = GetMousePosition();
            isActive = CheckCollisionPointRec(mousePos, box);
        }

        // Se a caixa está ativa, processar entrada do teclado
        if (isActive) {
            int key = GetCharPressed();

            while (key > 0) {
                // Remover o último caractere no caso de "backspace"
                if (key == KEY_BACKSPACE && !input.empty()) {
                    input.pop_back();
                }
                // Adicionar caracteres válidos
                else if (key >= 32 && key <= 126) { // Caracteres ASCII imprimíveis
                    input += static_cast<char>(key);
                }
                key = GetCharPressed(); // Obter o próximo caractere
            }
        }
    }

    std::string getInput() const {
        return input;
    }

    bool isFilled() const {
        return !input.empty();
    }
};

#include "menu.h"
#include <iostream>

void Menu::render() {
    // Clear the screen (Raylib)
    ClearBackground(RAYWHITE);

    // Render the buttons and input box
    hostButton.render();
    joinButton.render();
    ipInputBox.render();

    DrawText("Press Enter to Start", 10, 10, 20, DARKGRAY);
}

GameState Menu::update() {
    GameState currentState = GameState::NO_CHANGE;
    Vector2 mousePosition = GetMousePosition();  // Raylib equivalent of getting mouse position

    // Check for mouse button press and handle events
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        std::cout << "Mouse button pressed" << std::endl;

        // Host button click
        if (hostButton.isClicked(mousePosition)) {
            std::cout << "Host button clicked" << std::endl;
            currentState = GameState::WAITING_FOR_CONNECTION;
        }

        // Join button click
        if (joinButton.isClicked(mousePosition) && ipInputBox.isFilled()) {
            std::cout << "Join button clicked" << std::endl;
            std::cout << "IP Address: " << ipInputBox.getInput() << std::endl;
            currentState = GameState::SEARCHING_FOR_SERVER;
        }
    }

    // Handle keyboard input for text box (input box is assumed to be using Raylib for input)
    ipInputBox.handleInput();  // Update this method to work without SFML events

    // Check for 'Enter' key press to start the game or exit the menu
    if (IsKeyPressed(KEY_ENTER)) {
        if (ipInputBox.isFilled()) {
            currentState = GameState::SEARCHING_FOR_SERVER; // Or whatever logic you want when Enter is pressed
        } else {
            currentState = GameState::WAITING_FOR_CONNECTION; // If nothing entered, continue to waiting state
        }
    }

    return currentState;
}


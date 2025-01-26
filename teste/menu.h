#include "raylib.h"
#include <string>
#include "buton.h"
#include "inputBox.h"
#include "State.h" 

class Menu {
private:
    Button hostButton = Button({100, 100}, {200, 50}, GREEN, "Host");
    Button joinButton = Button({100, 200}, {200, 50}, GREEN, "Join");
    InputBox ipInputBox = InputBox({100, 300}, {200, 50});
    
public:
    Menu() {}
    ~Menu() {}

    void render();

    GameState update();

    std::string getIp() {
        return ipInputBox.getInput();
    }
};

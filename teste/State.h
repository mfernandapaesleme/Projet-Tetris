#pragma once

enum class GameState {
    NO_CHANGE,
    START_SCREEN,
    PLAYING,
    GAME_OVER,
    WAITING_FOR_CONNECTION,
    SEARCHING_FOR_SERVER,
    YOU_WON
};
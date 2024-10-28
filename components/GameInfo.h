#ifndef CPP3_BRICKGAME_V2_0_1_GAMEINFO_H
#define CPP3_BRICKGAME_V2_0_1_GAMEINFO_H

typedef enum {
    Start,
    Pause,
    Terminate,
    Left,
    Right,
    Up,
    Down,
    Action
} UserAction_t;

typedef enum {
    ArrowUp = 0403,
    ArrowDown = 0402,
    ArrowLeft = 0404,
    ArrowRight = 0405,
    ENTER = '\n',
    QUIT = 'q',
    PAUSE = 'p',
    ACTION = ' '
} Keys;

typedef enum {
    Launch,
    Spawn,
    Moving,
    Eating,
    Shifting,
    Win,
    GameOver
} GameState_t;

typedef struct {
    int **field;
    int **next;
    int score;
    int high_score;
    int level;
    int speed;
    int pause;
} GameInfo_t;

#endif //CPP3_BRICKGAME_V2_0_1_GAMEINFO_H

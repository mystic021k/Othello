#include <QPoint>

#pragma once
class OthelloEngine
{
public:
    const int CONTINUE = 0;
    const int TIE = 100;
    const int BLACK_WIN = 101;
    const int WHITE_WIN = 102;
    OthelloEngine();
    void newGame();
    bool blackTurn(int x, int y);
    bool whiteTurn(int x, int y);
    int checkResult();
    void calcBlackValues();
    void calcWhiteValues();
    int getBoardNum(int x, int y);
    int getBlackValue(int x, int y);
    int getWhiteValue(int x, int y);
    int getBlackCount();
    int getWhiteCount();
private:
    const QPoint directions[8] = {QPoint(1, 0), QPoint(1, 1), QPoint(0, 1), QPoint(-1, 1), QPoint(-1, 0), QPoint(-1, -1), QPoint(0, -1), QPoint(1, -1)};
    int board[8][8];
    int black_values[8][8];
    int white_values[8][8];
    int black_count;
    int white_count;
};


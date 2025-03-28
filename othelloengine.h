#include <QPoint>
#include <QList>

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
    int getBlackValue(int x, int y);
    int getWhiteValue(int x, int y);
    int getBlackCount();
    int getWhiteCount();
    int getBoardSize();
    QList<QList<int>> getBoardData();
    QList<QPoint> getBlackMoves();
    QList<QPoint> getWhiteMoves();
private:
    void calcBlackWhiteValues();
    const int board_size = 8;
    const QPoint directions[8] = {QPoint(1, 0), QPoint(1, 1), QPoint(0, 1), QPoint(-1, 1), QPoint(-1, 0), QPoint(-1, -1), QPoint(0, -1), QPoint(1, -1)};
    QList<QList<int>> board;
    QList<QList<int>> black_values;
    QList<QList<int>> white_values;
    int black_count;
    int white_count;
};


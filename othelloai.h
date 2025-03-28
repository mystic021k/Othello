#include "othelloengine.h"

#pragma once
class OthelloAI
{
public:
    OthelloAI();
    OthelloAI(OthelloEngine* oengine);
    bool doBlackTurn();
    bool doWhiteTurn();
private:
    OthelloEngine* engine;
    const int max_round = 7;
    const QPoint directions[8] = { QPoint(1, 0), QPoint(1, 1), QPoint(0, 1), QPoint(-1, 1), QPoint(-1, 0), QPoint(-1, -1), QPoint(0, -1), QPoint(1, -1) };
    int alphabetaBlackNode(QList<QList<int>> tmpboard, int alpha, int beta, int level = 1, int limit = INT_MAX);
    int alphabetaWhiteNode(QList<QList<int>> tmpboard, int alpha, int beta, int level = 1, int limit = INT_MAX);
    QList<QPoint> testMoves(QList<QList<int>> tmpboard, int color);
    QList<QList<int>> testPlayMoveBoard(QList<QList<int>> tmpboard, int color, int x, int y);
    int testCompute(QList<QList<int>> tmpboard);
};

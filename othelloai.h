#include "othelloengine.h"

#pragma once
class OthelloAI
{
private:
    OthelloEngine* engine;
public:
    OthelloAI();
    OthelloAI(OthelloEngine* oengine);
    bool doBlackTurn();
    bool doWhiteTurn();
};

#include "othelloai.h"

OthelloAI::OthelloAI()
{
}

OthelloAI::OthelloAI(OthelloEngine* oengine)
{
    this->engine = oengine;
}

bool OthelloAI::doBlackTurn()
{
    engine->calcBlackValues();
    int max_value = 0;
    int dx = -1, dy = -1;
    for(int y = 0;y < 8;y++)
    {
        for(int x = 0;x < 8;x++)
        {
            if(engine->getBlackValue(x, y) > max_value)
            {
                max_value = engine->getBlackValue(x, y);
                dx = x;
                dy = y;
            }
        }
    }
    if(dx >= 0 && dy >= 0)
    {
        return engine->blackTurn(dx, dy);
    }
    else
    {
        return false;
    }
}

bool OthelloAI::doWhiteTurn()
{
    engine->calcWhiteValues();
    int max_value = 0;
    int dx = -1, dy = -1;
    for(int y = 0;y < 8;y++)
    {
        for(int x = 0;x < 8;x++)
        {
            if(engine->getWhiteValue(x, y) > max_value)
            {
                max_value = engine->getWhiteValue(x, y);
                dx = x;
                dy = y;
            }
        }
    }
    if(dx >= 0 && dy >= 0)
    {
        return engine->whiteTurn(dx, dy);
    }
    else
    {
        return false;
    }
}

#include "othelloengine.h"

#include <QList>

OthelloEngine::OthelloEngine()
{
}

void OthelloEngine::newGame()
{
    for(int y = 0;y < 8;y++)
    {
        for(int x = 0;x < 8;x++)
        {
            board[y][x] = 0;
        }
    }
    board[3][4] = 1;
    board[4][3] = 1;
    board[4][4] = 2;
    board[3][3] = 2;
    black_count = 2;
    white_count = 2;
}

bool OthelloEngine::blackTurn(int x, int y)
{
    calcBlackValues();
    if(black_values[y][x] <= 0)
    {
        return false;
    }
    QList<QPoint> replacePoints;
    for(int i = 0;i < 8;i++)
    {
        QList<QPoint> dReplacePoints;
        int px = x + directions[i].x(), py = y + directions[i].y();
        while(px >= 0 && px < 8 && py >= 0 && py < 8)
        {
            if(board[py][px] == 0)
            {
                break;
            }
            if(board[py][px] == 1)
            {
                replacePoints.append(dReplacePoints);
                break;
            }
            if(board[py][px] == 2)
            {
                dReplacePoints.append(QPoint(px, py));
            }
            px = px + directions[i].x();
            py = py + directions[i].y();
        }
    }
    if(replacePoints.size() > 0)
    {
        for(int p = 0;p < replacePoints.size();p++)
        {
            board[replacePoints.value(p).y()][replacePoints.value(p).x()] = 1;
        }
        board[y][x] = 1;
        black_count += replacePoints.size() + 1;
        white_count -= replacePoints.size();
        return true;
    }
    else
    {
        return false;
    }
}

bool OthelloEngine::whiteTurn(int x, int y)
{
    calcWhiteValues();
    if(white_values[y][x] <= 0)
    {
        return false;
    }
    QList<QPoint> replacePoints;
    for(int i = 0;i < 8;i++)
    {
        QList<QPoint> dReplacePoints;
        int px = x + directions[i].x(), py = y + directions[i].y();
        while(px >= 0 && px < 8 && py >= 0 && py < 8)
        {
            if(board[py][px] == 0)
            {
                break;
            }
            if(board[py][px] == 2)
            {
                replacePoints.append(dReplacePoints);
                break;
            }
            if(board[py][px] == 1)
            {
                dReplacePoints.append(QPoint(px, py));
            }
            px = px + directions[i].x();
            py = py + directions[i].y();
        }
    }
    if(replacePoints.size() > 0)
    {
        for(int p = 0;p < replacePoints.size();p++)
        {
            board[replacePoints.value(p).y()][replacePoints.value(p).x()] = 2;
        }
        board[y][x] = 2;
        white_count += replacePoints.size() + 1;
        black_count -= replacePoints.size();
        return true;
    }
    else
    {
        return false;
    }
}

int OthelloEngine::checkResult()
{
    if(white_count <= 0)
    {
        return BLACK_WIN;
    }
    if(black_count <= 0)
    {
        return WHITE_WIN;
    }
    if(black_count + white_count == 64)
    {
        if(black_count > white_count)
        {
            return BLACK_WIN;
        }
        if(white_count > black_count)
        {
            return WHITE_WIN;
        }
        if(black_count == white_count)
        {
            return TIE;
        }
    }
    return CONTINUE;
}

void OthelloEngine::calcBlackValues()
{
    for(int y = 0;y < 8;y++)
    {
        for(int x = 0;x < 8;x++)
        {
            if(board[y][x] != 0)
            {
                black_values[y][x] = 0;
                continue;
            }
            int value_count = 0;
            for(int i = 0;i < 8;i++)
            {
                int d_value_count = 0;
                int px = x + directions[i].x(), py = y + directions[i].y();
                while(px >= 0 && px < 8 && py >= 0 && py < 8)
                {
                    if(board[py][px] == 0)
                    {
                        break;
                    }
                    if(board[py][px] == 1)
                    {
                        value_count += d_value_count;
                        break;
                    }
                    if(board[py][px] == 2)
                    {
                        d_value_count++;
                    }
                    px = px + directions[i].x();
                    py = py + directions[i].y();
                }
            }
            black_values[y][x] = value_count;
        }
    }
}

void OthelloEngine::calcWhiteValues()
{
    for(int y = 0;y < 8;y++)
    {
        for(int x = 0;x < 8;x++)
        {
            if(board[y][x] != 0)
            {
                white_values[y][x] = 0;
                continue;
            }
            int value_count = 0;
            for(int i = 0;i < 8;i++)
            {
                int d_value_count = 0;
                int px = x + directions[i].x(), py = y + directions[i].y();
                while(px >= 0 && px < 8 && py >= 0 && py < 8)
                {
                    if(board[py][px] == 0)
                    {
                        break;
                    }
                    if(board[py][px] == 2)
                    {
                        value_count += d_value_count;
                        break;
                    }
                    if(board[py][px] == 1)
                    {
                        d_value_count++;
                    }
                    px = px + directions[i].x();
                    py = py + directions[i].y();
                }
            }
            white_values[y][x] = value_count;
        }
    }
}

int OthelloEngine::getBoardNum(int x, int y)
{
    return board[y][x];
}

int OthelloEngine::getBlackValue(int x, int y)
{
    return black_values[y][x];
}

int OthelloEngine::getWhiteValue(int x, int y)
{
    return white_values[y][x];
}

int OthelloEngine::getBlackCount()
{
    return black_count;
}

int OthelloEngine::getWhiteCount()
{
    return white_count;
}
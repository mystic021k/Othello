#include "othelloengine.h"
#include <QList>

OthelloEngine::OthelloEngine()
{
}

void OthelloEngine::newGame()
{
    board = QList<QList<int>>();
    for(int y = 0;y < board_size;y++)
    {
        QList<int> line = QList<int>();
        for(int x = 0;x < board_size;x++)
        {
            line.append(0);
        }
        board.append(line);
    }
    board[board_size / 2 - 1][board_size / 2] = 1;
    board[board_size / 2][board_size / 2 - 1] = 1;
    board[board_size / 2][board_size / 2] = 2;
    board[board_size / 2 - 1][board_size / 2 - 1] = 2;
    black_count = 2;
    white_count = 2;
    calcBlackWhiteValues();
}

bool OthelloEngine::blackTurn(int x, int y)
{
    if(black_values[y][x] <= 0)
    {
        return false;
    }
    QList<QPoint> replacePoints;
    for(int i = 0;i < 8;i++)
    {
        QList<QPoint> dReplacePoints;
        int px = x + directions[i].x(), py = y + directions[i].y();
        while(px >= 0 && px < board_size && py >= 0 && py < board_size)
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
        calcBlackWhiteValues();
        return true;
    }
    else
    {
        return false;
    }
}

bool OthelloEngine::whiteTurn(int x, int y)
{
    if(white_values[y][x] <= 0)
    {
        return false;
    }
    QList<QPoint> replacePoints;
    for(int i = 0;i < 8;i++)
    {
        QList<QPoint> dReplacePoints;
        int px = x + directions[i].x(), py = y + directions[i].y();
        while(px >= 0 && px < board_size && py >= 0 && py < board_size)
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
        calcBlackWhiteValues();
        return true;
    }
    else
    {
        return false;
    }
}

int OthelloEngine::checkResult()
{
    if(getBlackMoves().size() <= 0 && getWhiteMoves().size() <= 0)
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

int OthelloEngine::getBoardSize()
{
    return board_size;
}

QList<QList<int>> OthelloEngine::getBoardData()
{
    return board;
}

QList<QPoint> OthelloEngine::getBlackMoves()
{
    QList<QPoint> moves = QList<QPoint>();
    for (int y = 0; y < board_size; y++)
    {
        for (int x = 0; x < board_size; x++)
        {
            if (black_values[y][x] > 0)
            {
                moves.append(QPoint(x, y));
            }
        }
    }
    return moves;
}

QList<QPoint> OthelloEngine::getWhiteMoves()
{
    QList<QPoint> moves = QList<QPoint>();
    for (int y = 0; y < board_size; y++)
    {
        for (int x = 0; x < board_size; x++)
        {
            if (white_values[y][x] > 0)
            {
                moves.append(QPoint(x, y));
            }
        }
    }
    return moves;
}

void OthelloEngine::calcBlackWhiteValues()
{
    black_values = QList<QList<int>>();
    white_values = QList<QList<int>>();
    for (int y = 0; y < board_size; y++)
    {
        QList<int> black_line = QList<int>();
        QList<int> white_line = QList<int>();
        for (int x = 0; x < board_size; x++)
        {
            if (board[y][x] != 0)
            {
                black_line.append(0);
                white_line.append(0);
                continue;
            }
            int b_value_count = 0;
            for (int i = 0; i < 8; i++)
            {
                int d_value_count = 0;
                int px = x + directions[i].x(), py = y + directions[i].y();
                while (px >= 0 && px < board_size && py >= 0 && py < board_size)
                {
                    if (board[py][px] == 0)
                    {
                        break;
                    }
                    if (board[py][px] == 1)
                    {
                        b_value_count += d_value_count;
                        break;
                    }
                    if (board[py][px] == 2)
                    {
                        d_value_count++;
                    }
                    px = px + directions[i].x();
                    py = py + directions[i].y();
                }
            }
            black_line.append(b_value_count);
            int w_value_count = 0;
            for (int i = 0; i < 8; i++)
            {
                int d_value_count = 0;
                int px = x + directions[i].x(), py = y + directions[i].y();
                while (px >= 0 && px < board_size && py >= 0 && py < board_size)
                {
                    if (board[py][px] == 0)
                    {
                        break;
                    }
                    if (board[py][px] == 2)
                    {
                        w_value_count += d_value_count;
                        break;
                    }
                    if (board[py][px] == 1)
                    {
                        d_value_count++;
                    }
                    px = px + directions[i].x();
                    py = py + directions[i].y();
                }
            }
            white_line.append(w_value_count);
        }
        black_values.append(black_line);
        white_values.append(white_line);
    }
}

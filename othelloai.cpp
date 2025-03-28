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
    QList<QList<int>> boardData = engine->getBoardData();
    QList<QPoint> moves = testMoves(boardData, PLAYER_BLACK);
    if (moves.size() <= 0)
    {
        return false;
    }
    int pos = -1;
    int val = INT_MIN;
    for (int m = 0; m < moves.size(); m++)
    {
        int m_val = alphabetaBlackNode(testPlayMoveBoard(boardData, PLAYER_BLACK, moves[m].x(), moves[m].y()), INT_MIN, INT_MAX, 2, max_round);
        if (m_val > val)
        {
            pos = m;
            val = m_val;
        }
    }
    return engine->blackTurn(moves[pos].x(), moves[pos].y());
}

bool OthelloAI::doWhiteTurn()
{
    QList<QList<int>> boardData = engine->getBoardData();
    QList<QPoint> moves = testMoves(boardData, PLAYER_WHITE);
    if (moves.size() <= 0)
    {
        return false;
    }
    int pos = -1;
    int val = INT_MAX;
    for (int m = 0; m < moves.size(); m++)
    {
        int m_val = alphabetaWhiteNode(testPlayMoveBoard(boardData, PLAYER_WHITE, moves[m].x(), moves[m].y()), INT_MIN, INT_MAX, 2, max_round);
        if (m_val < val)
        {
            pos = m;
            val = m_val;
        }
    }
    int a = pos;
    return engine->whiteTurn(moves[pos].x(), moves[pos].y());
}

int OthelloAI::alphabetaBlackNode(QList<QList<int>> tmpboard, int alpha, int beta, int level, int limit)
{
    QList<QPoint> tmp_moves = testMoves(tmpboard, PLAYER_BLACK);
    if (tmp_moves.size() <= 0)
    {
        return testCompute(tmpboard);
    }
    QList<int> tmp_utilities = QList<int>();
    for (int m = 0; m < tmp_moves.size(); m++)
    {
        tmp_utilities.append(testCompute(testPlayMoveBoard(tmpboard, PLAYER_BLACK, tmp_moves[m].x(), tmp_moves[m].y())));
    }
    QList<QPoint> moves = QList<QPoint>();
    while (tmp_moves.size() > 0)
    {
        int pos = -1;
        int val = INT_MIN;
        for (int m = 0; m < tmp_moves.size(); m++)
        {
            if (tmp_utilities[m] > val)
            {
                pos = m;
                val = tmp_utilities[m];
            }
        }
        moves.append(tmp_moves[pos]);
        tmp_moves.removeAt(pos);
        tmp_utilities.removeAt(pos);
    }
    int compile_value = INT_MIN;
    for (int mm = 0; mm < moves.size(); mm++)
    {
        QPoint m_move = moves[mm];
        if (level < limit)
        {
            int next_value = alphabetaWhiteNode(testPlayMoveBoard(tmpboard, PLAYER_BLACK, m_move.x(), m_move.y()), alpha, beta, level + 1, limit);
            if (next_value > compile_value)
            {
                compile_value = next_value;
            }
        }
        else
        {
            int new_compile_value = testCompute(tmpboard);
            if (new_compile_value > compile_value)
            {
                compile_value = new_compile_value;
            }
        }
        if (compile_value >= beta)
        {
            return compile_value;
        }
        if (compile_value >= alpha)
        {
            alpha = compile_value;
        }
    }
    return compile_value;
}

int OthelloAI::alphabetaWhiteNode(QList<QList<int>> tmpboard, int alpha, int beta, int level, int limit)
{
    QList<QPoint> tmp_moves = testMoves(tmpboard, PLAYER_WHITE);
    if (tmp_moves.size() <= 0)
    {
        return testCompute(tmpboard);
    }
    QList<int> tmp_utilities = QList<int>();
    for (int m = 0; m < tmp_moves.size(); m++)
    {
        tmp_utilities.append(testCompute(testPlayMoveBoard(tmpboard, PLAYER_WHITE, tmp_moves[m].x(), tmp_moves[m].y())));
    }
    QList<QPoint> moves = QList<QPoint>();
    while (tmp_moves.size() > 0)
    {
        int pos = -1;
        int val = INT_MAX;
        for (int m = 0; m < tmp_moves.size(); m++)
        {
            if (tmp_utilities[m] < val)
            {
                pos = m;
                val = tmp_utilities[m];
            }
        }
        moves.append(tmp_moves[pos]);
        tmp_moves.removeAt(pos);
        tmp_utilities.removeAt(pos);
    }
    int compile_value = INT_MAX;
    for (int mm = 0; mm < moves.size(); mm++)
    {
        QPoint m_move = moves[mm];
        if (level < limit)
        {
            int next_value = alphabetaBlackNode(testPlayMoveBoard(tmpboard, PLAYER_WHITE, m_move.x(), m_move.y()), alpha, beta, level + 1, limit);
            if (next_value < compile_value)
            {
                compile_value = next_value;
            }
        }
        else
        {
            int new_compile_value = testCompute(tmpboard);
            if (new_compile_value < compile_value)
            {
                compile_value = new_compile_value;
            }
        }
        if (compile_value <= alpha)
        {
            return compile_value;
        }
        if (compile_value <= beta)
        {
            beta = compile_value;
        }
    }
    return compile_value;
}

QList<QPoint> OthelloAI::testMoves(QList<QList<int>> tmpboard, int color)
{
    QList<QPoint> test_black_moves = QList<QPoint>();
    QList<QPoint> test_white_moves = QList<QPoint>();
    for (int y = 0; y < engine->getBoardSize(); y++)
    {
        for (int x = 0; x < engine->getBoardSize(); x++)
        {
            if (tmpboard[y][x] != 0)
            {
                continue;
            }
            int b_value_count = 0;
            for (int i = 0; i < 8; i++)
            {
                int d_value_count = 0;
                int px = x + directions[i].x(), py = y + directions[i].y();
                while (px >= 0 && px < engine->getBoardSize() && py >= 0 && py < engine->getBoardSize())
                {
                    if (tmpboard[py][px] == 0)
                    {
                        break;
                    }
                    if (tmpboard[py][px] == PLAYER_BLACK)
                    {
                        b_value_count += d_value_count;
                        break;
                    }
                    if (tmpboard[py][px] == PLAYER_WHITE)
                    {
                        d_value_count++;
                    }
                    px = px + directions[i].x();
                    py = py + directions[i].y();
                }
            }
            if (b_value_count > 0)
            {
                test_black_moves.append(QPoint(x, y));
            }
            int w_value_count = 0;
            for (int i = 0; i < 8; i++)
            {
                int d_value_count = 0;
                int px = x + directions[i].x(), py = y + directions[i].y();
                while (px >= 0 && px < engine->getBoardSize() && py >= 0 && py < engine->getBoardSize())
                {
                    if (tmpboard[py][px] == 0)
                    {
                        break;
                    }
                    if (tmpboard[py][px] == PLAYER_WHITE)
                    {
                        w_value_count += d_value_count;
                        break;
                    }
                    if (tmpboard[py][px] == PLAYER_BLACK)
                    {
                        d_value_count++;
                    }
                    px = px + directions[i].x();
                    py = py + directions[i].y();
                }
            }
            if (w_value_count > 0)
            {
                test_white_moves.append(QPoint(x, y));
            }
        }
    }
    if (color == PLAYER_BLACK)
    {
        return test_black_moves;
    }
    if (color == PLAYER_WHITE)
    {
        return test_white_moves;
    }
    return QList<QPoint>();
}

QList<QList<int>> OthelloAI::testPlayMoveBoard(QList<QList<int>> tmpboard, int color, int x, int y)
{
    QList<QPoint> replacePoints;
    if (color == PLAYER_BLACK)
    {
        for (int i = 0; i < 8; i++)
        {
            QList<QPoint> dReplacePoints;
            int px = x + directions[i].x(), py = y + directions[i].y();
            while (px >= 0 && px < engine->getBoardSize() && py >= 0 && py < engine->getBoardSize())
            {
                if (tmpboard[py][px] == 0)
                {
                    break;
                }
                if (tmpboard[py][px] == PLAYER_BLACK)
                {
                    replacePoints.append(dReplacePoints);
                    break;
                }
                if (tmpboard[py][px] == PLAYER_WHITE)
                {
                    dReplacePoints.append(QPoint(px, py));
                }
                px = px + directions[i].x();
                py = py + directions[i].y();
            }
        }
        if (replacePoints.size() > 0)
        {
            for (int p = 0; p < replacePoints.size(); p++)
            {
                tmpboard[replacePoints.value(p).y()][replacePoints.value(p).x()] = PLAYER_BLACK;
            }
            tmpboard[y][x] = PLAYER_BLACK;
        }
    }
    if (color == PLAYER_WHITE)
    {
        for (int i = 0; i < 8; i++)
        {
            QList<QPoint> dReplacePoints;
            int px = x + directions[i].x(), py = y + directions[i].y();
            while (px >= 0 && px < engine->getBoardSize() && py >= 0 && py < engine->getBoardSize())
            {
                if (tmpboard[py][px] == 0)
                {
                    break;
                }
                if (tmpboard[py][px] == PLAYER_WHITE)
                {
                    replacePoints.append(dReplacePoints);
                    break;
                }
                if (tmpboard[py][px] == PLAYER_BLACK)
                {
                    dReplacePoints.append(QPoint(px, py));
                }
                px = px + directions[i].x();
                py = py + directions[i].y();
            }
        }
        if (replacePoints.size() > 0)
        {
            for (int p = 0; p < replacePoints.size(); p++)
            {
                tmpboard[replacePoints.value(p).y()][replacePoints.value(p).x()] = PLAYER_WHITE;
            }
            tmpboard[y][x] = PLAYER_WHITE;
        }
    }
    return tmpboard;
}

int OthelloAI::testCompute(QList<QList<int>> tmpboard)
{
    int size = 0;
    for (int y = 0; y < engine->getBoardSize(); y++)
    {
        for (int x = 0; x < engine->getBoardSize(); x++)
        {
            if (tmpboard[y][x] == PLAYER_BLACK)
            {
                size += 1;
            }
            else if (tmpboard[y][x] == PLAYER_WHITE)
            {
                size -= 1;
            }
        }
    }
    return size;
}

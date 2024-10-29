#include "othello.h"
#include "othelloai.h"
#include "qgamehelpdlg.h"
#include <QMessageBox>

Othello::Othello(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.graphicsView, SIGNAL(set_piece(QPoint*)), this, SLOT(playerSetPiece(QPoint*)));
    connect(ui.action_black, SIGNAL(triggered()), this, SLOT(playerTakeBlack()));
    connect(ui.action_white, SIGNAL(triggered()), this, SLOT(playerTakeWhite()));
    connect(ui.action_duel, SIGNAL(triggered()), this, SLOT(playerToPlayer()));
    connect(ui.action_pass, SIGNAL(triggered()), this, SLOT(passPlayer()));
    connect(ui.action_about, SIGNAL(triggered()), this, SLOT(showAbout()));
    connect(ui.action_help, SIGNAL(triggered()), this, SLOT(showHelp()));
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimer()));
    playerTakeBlack();
}

Othello::~Othello()
{}

void Othello::paintBoard()
{
    if (engine != nullptr)
    {
        int minLength = this->width() <= this->height() - 56 ? this->width() : this->height() - 56;
        minLength -= 24;
        int pieceRoughSize = (minLength - minLength % 80) / 8;
        pieceSize = pieceRoughSize - pieceRoughSize % 10;
        leftStart = (this->width() - pieceSize * 8) / 2;
        topStart = (this->height() - 56 - pieceSize * 8) / 2;
        QGraphicsScene* scene = new QGraphicsScene(this);
        QPen backPen;
        backPen.setColor(Qt::black);
        backPen.setWidth(9);
        backPen.setStyle(Qt::SolidLine);
        QBrush backBrush;
        backBrush.setColor(Qt::darkGreen);
        backBrush.setStyle(Qt::SolidPattern);
        scene->addRect(leftStart - 6, topStart - 6, pieceSize * 8 + 12, pieceSize * 8 + 12, backPen, backBrush);
        for (int s = 0; s <= 8; s++)
        {
            QPen linePen;
            linePen.setColor(Qt::black);
            linePen.setStyle(Qt::SolidLine);
            scene->addLine(leftStart, topStart + s * pieceSize, leftStart + 8 * pieceSize, topStart + s * pieceSize, linePen);
            scene->addLine(leftStart + s * pieceSize, topStart, leftStart + s * pieceSize, topStart + 8 * pieceSize, linePen);
        }
        for (int y = 0; y < 8; y++)
        {
            for (int x = 0; x < 8; x++)
            {
                QPoint centerPos = QPoint(leftStart + x * pieceSize + pieceSize / 2, topStart + y * pieceSize + pieceSize / 2);
                int chessRadius = pieceSize * 0.4;
                if (engine->getBoardNum(x, y) == 1)
                {
                    QPen piecePen;
                    piecePen.setStyle(Qt::NoPen);
                    QRadialGradient radialGrad(QPointF(centerPos.x() - chessRadius / 4, centerPos.y() - chessRadius / 4), chessRadius);
                    radialGrad.setColorAt(0, Qt::darkGray);
                    radialGrad.setColorAt(1, Qt::black);
                    QBrush pieceBrush(radialGrad);
                    scene->addEllipse(centerPos.x() - chessRadius, centerPos.y() - chessRadius, chessRadius * 2, chessRadius * 2, piecePen, pieceBrush);
                }
                if (engine->getBoardNum(x, y) == 2)
                {
                    QPen piecePen;
                    piecePen.setStyle(Qt::NoPen);
                    QRadialGradient radialGrad(QPointF(centerPos.x() - chessRadius / 12, centerPos.y() - chessRadius / 12), chessRadius);
                    radialGrad.setColorAt(0, Qt::white);
                    radialGrad.setColorAt(0.8, Qt::white);
                    radialGrad.setColorAt(1, Qt::lightGray);
                    QBrush pieceBrush(radialGrad);
                    scene->addEllipse(centerPos.x() - chessRadius, centerPos.y() - chessRadius, chessRadius * 2, chessRadius * 2, piecePen, pieceBrush);
                }
            }
        }
        ui.graphicsView->setScene(scene);
    }
}

void Othello::checkResult()
{
    int gameResult = engine->checkResult();
    if(gameResult == engine->CONTINUE)
    {
        return;
    }
    QMessageBox msgBox;
    msgBox.setWindowTitle(QString::fromUtf8("黑白棋"));
    if(gameResult == engine->TIE)
    {
        msgBox.setText(QString::fromUtf8("　不分胜负　　　"));
        ui.statusBar->showMessage(QString::fromUtf8("不分胜负"));
    }
    if(gameResult == engine->BLACK_WIN)
    {
        msgBox.setText(QString::fromUtf8("　黑棋胜利　　　"));
        ui.statusBar->showMessage(QString::fromUtf8("黑棋胜利"));
    }
    if(gameResult == engine->WHITE_WIN)
    {
        msgBox.setText(QString::fromUtf8("　白棋胜利　　　"));
        ui.statusBar->showMessage(QString::fromUtf8("白棋胜利"));
    }
    isFinished = true;
    timer->stop();
    msgBox.exec();
    changeButtonState(true);
}

void Othello::playerSetPiece(QPoint* pos)
{
    if (isFinished)
    {
        return;
    }
    if (playerOrComputer[currentTurn] != 1)
    {
        return;
    }
    int x = (int)floor((pos->x() - leftStart) / pieceSize);
    int y = (int)floor((pos->y() - topStart) / pieceSize);
    bool doSuccess = false;
    if (currentTurn == 0)
    {
        doSuccess = engine->blackTurn(x, y);
    }
    if (currentTurn == 1)
    {
        doSuccess = engine->whiteTurn(x, y);
    }
    if (!doSuccess)
    {
        return;
    }
    paintBoard();
    nextTurn();
    checkResult();
}

void Othello::resizeEvent(QResizeEvent* event)
{
    ui.graphicsView->setGeometry(0, 0, this->width(), this->height() - 56);
    paintBoard();
}

void Othello::startGame()
{
    engine = new OthelloEngine();
    engine->newGame();
    currentTurn = 0;
    isFinished = false;
    paintBoard();
    setStatusMsg();
    timer->start(0);
    timer->setInterval(1000);
}

void Othello::nextTurn()
{
    currentTurn++;
    currentTurn = currentTurn % 2;
    if (buttonEnabled)
    {
        changeButtonState(false);
    }
    setStatusMsg();
}

void Othello::changeButtonState(bool enabled)
{
    ui.action_black->setEnabled(enabled);
    ui.action_white->setEnabled(enabled);
    ui.action_duel->setEnabled(enabled);
    buttonEnabled = enabled;
}

void Othello::setStatusMsg()
{
    if (currentTurn == 0)
    {
        ui.statusBar->showMessage(QString::fromUtf8("黑棋走"));
    }
    else if (currentTurn == 1)
    {
        ui.statusBar->showMessage(QString::fromUtf8("白棋走"));
    }
}

void Othello::onTimer()
{
    if (isFinished)
    {
        return;
    }
    if (playerOrComputer[currentTurn] == 0)
    {
        if (currentTurn == 0)
        {
            OthelloAI* ai = new OthelloAI(engine);
            ai->doBlackTurn();
            paintBoard();
            nextTurn();
            checkResult();
        }
        else if (currentTurn == 1)
        {
            OthelloAI* ai = new OthelloAI(engine);
            ai->doWhiteTurn();
            paintBoard();
            nextTurn();
            checkResult();
        }
    }
}

void Othello::playerTakeBlack()
{
    playerOrComputer[0] = 1;
    playerOrComputer[1] = 0;
    startGame();
}

void Othello::playerTakeWhite()
{
    playerOrComputer[0] = 0;
    playerOrComputer[1] = 1;
    startGame();
}

void Othello::playerToPlayer()
{
    playerOrComputer[0] = 1;
    playerOrComputer[1] = 1;
    startGame();
}

void Othello::passPlayer()
{
    if (!isFinished)
    {
        if (playerOrComputer[currentTurn] == 1)
        {
            nextTurn();
        }
    }
}

void Othello::showAbout()
{
    QMessageBox::about(this, QString(), "Version 1.0.1\r\n2024.10.29");
}

void Othello::showHelp()
{
    QGameHelpDlg dlg;
    dlg.exec();
}

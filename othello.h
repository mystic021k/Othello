#pragma once

#include <QtWidgets/QMainWindow>
#include <QTimer>
#include "othelloengine.h"
#include "ui_othello.h"

class Othello : public QMainWindow
{
    Q_OBJECT

public:
    Othello(QWidget *parent = nullptr);
    ~Othello();

    void paintBoard();
    void checkResult();
    void resizeEvent(QResizeEvent* event);
    void startGame();
    void nextTurn();
    void changeButtonState(bool enabled);
    void setStatusMsg();
public slots:
    void playerSetPiece(QPoint *pos);
    void onTimer();
    void playerTakeBlack();
    void playerTakeWhite();
    void playerToPlayer();
    void passPlayer();
    void showAbout();
    void showHelp();
private:
    Ui::OthelloClass ui;
    OthelloEngine* engine;
    QTimer* timer;
    int pieceSize;
    int leftStart;
    int topStart;
    int currentTurn;
    int playerOrComputer[2] = { 0, 0 };
    bool isFinished = false;
    bool buttonEnabled = true;
};

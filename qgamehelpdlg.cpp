#include "qgamehelpdlg.h"

QGameHelpDlg::QGameHelpDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	ui.textBrowser->setHtml(QString::fromUtf8("<b>游戏的目标</b><br><br>游戏的棋盘上有64个可以放置黑白棋子的方格。游戏的目标是使棋盘上自己颜色的棋子数超过对手的棋子数。<br>该游戏非常复杂，其名称就暗示着结果的好坏可能会迅速变化。<br>当游戏双方都不能再按规则移动棋子时，游戏就结束了。通常，游戏结束时棋盘上会摆满了棋子。结束时谁的棋子最多谁就是赢家。<br><br><b>玩法</b><br><br>每次游戏开始时，棋盘上已经放好了四颗棋子。其中两颗是黑棋，另两颗是白棋。黑棋总是先走。<br>当您的棋子在某一直线方向包围了对手的棋子时，就可以翻转这些棋子的颜色，使它们成为您方的颜色。例如，如果您执黑棋，并且看到在一排白棋的某一端是一颗黑棋，那么当您将一颗黑棋放在这一排的另一端时，所有的白棋都将翻转并变为黑棋！<br>所有的直线方向均有效：水平、垂直或对角线方向。<br>走棋的唯一规则是只能走包围并翻转对手的棋子。每一回合都必须至少翻转一颗对手的宝石。<br>按规则不能再走棋时，这一回合输掉。计算机会自动将控制权交给对方。<br><br><b>得分</b><br><br>游戏的计分方法非常简单。游戏过程中随时都显示黑棋数与白棋数。结束时棋数最多的一方就是赢家。<br>游戏进行过程中，每一回合的得分都可能会发生急剧的变化。然而那正是游戏的乐趣所在！<br><br><b>策略与技巧</b><br><br>请注意，游戏期间，位置比点数更重要！要着眼于长远利益，因为点数的领先很可能是暂时的。<br>有些玩家在大多数游戏中喜欢占据中间的位置，而使对手占据一组棋子的外缘。然后在游戏要结束时他们可以将棋子放在棋盘边缘的任意位置，并可在几个回合中翻转许多棋子。<br>最终，您希望占据棋盘的边缘位置，这样对手就不能在您的棋子的外部放置棋子了。基于这一原因，您要尽量避开与边缘紧邻的位置。边缘位置上占据两个棋位比较好。<br>四个角上是必须争取占据的好位置，因为无法移开这些位置上的棋子。<br>截断对手的防线时，请检查每一个可能的方向。例如，白棋可能占据了从上到下的一整排，但您可以在水平或对角线方向破坏这一排。<br>有时只需放置一颗棋子就可以在多个方向上翻转对手的许多棋子。要时刻寻找这样的机会。<br>设法使自己走一步时，牵制着对手无法移动任何棋子！这样可以在一排中连续走两步。<br>"));
}

QGameHelpDlg::~QGameHelpDlg()
{}

void QGameHelpDlg::resizeEvent(QResizeEvent* event)
{
	ui.textBrowser->setGeometry(0, 0, this->width(), this->height());
}

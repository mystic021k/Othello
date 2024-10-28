#pragma once

#include <QDialog>
#include "ui_gamehelp.h"

class QGameHelpDlg : public QDialog
{
	Q_OBJECT

public:
	QGameHelpDlg(QWidget *parent = nullptr);
	~QGameHelpDlg();

	void resizeEvent(QResizeEvent* event);

private:
	Ui::QGameHelpDlgClass ui;
};

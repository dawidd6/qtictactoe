#ifndef QTICTACTOE_MENU_H
#define QTICTACTOE_MENU_H

#include <QPushButton>
#include <QGridLayout>

#include "Window.h"

class Menu : public QWidget
{
	Q_OBJECT
	private:
		QVBoxLayout layout;
	public:
		QPushButton play_single;
		QPushButton play_2v2;
		QPushButton play_multi;
	public:
		Menu(Window *window);
};

#endif

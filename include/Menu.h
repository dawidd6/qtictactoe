#ifndef QTICTACTOE_MENU_H
#define QTICTACTOE_MENU_H

#include <QPushButton>
#include <QGridLayout>

class Menu : public QWidget
{
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

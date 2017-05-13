#ifndef QTICTACTOE_MENU_H
#define QTICTACTOE_MENU_H

class Menu
{
	private:
		QWidget widget;
		QVBoxLayout layout;
	public:
		QPushButton play_single;
		QPushButton play_2v2;
		QPushButton play_multi;

	public:
		Menu(Window *window);
		void stop();
		void run();
};

#endif

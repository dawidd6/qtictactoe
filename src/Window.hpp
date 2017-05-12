#ifndef QTICTACTOE_WINDOW_HPP
#define QTICTACTOE_WINDOW_HPP

class Window
{
	protected:
		QWidget window;
		QGridLayout grid;
		QMenuBar menu;
		QMenu entry;
		QAction action;
	public:
		Window();
		void show();
};

#endif

#ifndef QTICTACTOE_WINDOW_H
#define QTICTACTOE_WINDOW_H

class Window : public QWidget
{
	public:
		QStackedLayout layout;
		QMenuBar menubar;
		QMenu help;
		QMenu game;
		QAction about;
		QAction return_to_menu;
	public:
		Window();
};

#endif

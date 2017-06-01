#pragma once

class Game;

class Window : public QWidget
{
	public:
		QStackedLayout layout;
		QMenuBar menubar;
		QMenu menu;
		QAction about;
		QAction return_to_menu;
	public:
		Window(Game *game);
		void handleAbout();
};

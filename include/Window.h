#pragma once

class Game;

class Window : public QMainWindow
{
	private:
		QMenuBar menubar;
		QMenu menu;
		QAction about;
		QAction return_to_menu;
	public:
		Window(Game *game);
		void handleAbout();
		void setReturnEnabled(bool enable);
};

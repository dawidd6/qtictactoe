#pragma once

class CGame;

class CWindow : public QMainWindow
{
	private:
		QMenuBar menubar;
		QMenu menu;
		QAction about;
		QAction return_to_menu;
	public:
		CWindow(CGame *game);
		void handleAbout();
		void setReturnEnabled(bool enable);
};

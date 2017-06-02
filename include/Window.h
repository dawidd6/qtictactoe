#pragma once

class CGame;

class CWindow : public QWidget
{
	public:
		QStackedLayout layout;
		QMenuBar menubar;
		QMenu menu;
		QAction about;
		QAction return_to_menu;
	public:
		CWindow(CGame *game);
		void handleAbout();
};

#pragma once

class CGame;

class CWindow : public QWidget
{
	private:
		QStackedLayout layout;
		QMenuBar menubar;
		QMenu menu;
		QAction about;
		QAction return_to_menu;
	public:
		CWindow(CGame *game);
		void handleAbout();
		void addToLayout(QWidget *child);
		void removeFromLayout(QWidget *child);
};

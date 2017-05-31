#pragma once

#include <QPushButton>
#include <QStackedLayout>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>

#include "Menu.h"
#include "Game.h"

class Window : public QWidget
{
	Q_OBJECT
	public:
		QStackedLayout layout;
		QMenuBar menubar;
		QMenu menu;
		QAction about;
		QAction return_to_menu;
	private slots:
		void handleAbout();
	public:
		Window(Game *game);
};

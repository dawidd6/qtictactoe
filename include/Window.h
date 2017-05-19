#ifndef QTICTACTOE_WINDOW_H
#define QTICTACTOE_WINDOW_H

#include <QPushButton>
#include <QStackedLayout>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>

class Window : public QWidget
{
	Q_OBJECT
	public:
		QStackedLayout layout;
		QMenuBar menubar;
		QMenu menu;
		QAction about;
		QAction return_to_menu;
	public slots:
		void handleAbout();
	public:
		Window();
};

#endif

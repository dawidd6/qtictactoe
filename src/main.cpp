#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QStackedLayout>
#include <QLabel>
#include <QMenuBar>
#include <QAction>
#include <QPainter>

#include "Board.h"
#include "Window.h"

/* TESTING CLASSESS */
/*class Menu
{
	private:
		QWidget widget_menu;
		QVBoxLayout box_menu;
		QPushButton play_single("Play Singleplayer");
		QPushButton play_2v2("Play 2v2");
		QPushButton play_multi("Play Multiplayer");

	public:
		Menu(Window &window);
		
};*/


/* FUNCTIONS */
/* CONSTRUCTORS */
/*Menu::Menu()
{
	play_2v2.setFixedSize(305, 40);
	play_single.setFixedSize(305, 40);
	play_multi.setFixedSize(305, 40);
	widget_game.setLayout(&grid_game);
	widget_menu.setLayout(&box_menu);
	box_menu.setAlignment(Qt::AlignTop);
	box_menu.setSpacing(50);
	layout.addWidget(&widget_game);
	layout.addWidget(&widget_menu);
	menubar.addMenu(&help);
	help.addAction(&about);
	
}*/


/* MAIN */
int main(int argc, char *argv[])
{
	/* VARIABLES */
	//QMessageBox::about(&window, "About", "QTicTacToe");
	QApplication a(argc, argv);
	Window window;
	Board board(&window);
	window.show();
	return a.exec();
}

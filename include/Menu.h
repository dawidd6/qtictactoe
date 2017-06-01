#pragma once

class Menu : public QWidget
{
	private:
		QGridLayout layout;
		QPushButton play_single;
		QPushButton play_2v2;
		QPushButton play_multi;
	public:
		Menu(Window *window, Game *game);
};

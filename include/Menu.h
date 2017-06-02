#pragma once

class CMenu : public QWidget
{
	private:
		QGridLayout layout;
		QPushButton play_single;
		QPushButton play_2v2;
		QPushButton play_multi;
	public:
		CMenu(CWindow *window, CGame *game);
};

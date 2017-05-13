#ifndef QTICTACTOE_WINDOW_H
#define QTICTACTOE_WINDOW_H

#include "Board.h"

class Window : public QWidget
{
	private:
		QStackedLayout layout;
		QMenuBar menubar;
	public:
		Window();
		friend class Board;
};

#endif

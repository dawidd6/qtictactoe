#ifndef QTICTACTOE_GAME_HPP
#define QTICTACTOE_GAME_HPP

class Game : public Board
{
	protected:
		bool xnow;
		char win;
		QPushButton restart;
		QLabel turn;
		QLabel current_icon;
		QSize current_size;
	public:
		Game();
		void markDisabledAll();
		void paintLine(QLabel &label, int angle, int len, QPointF point);
		void addToGrid();
};

#endif

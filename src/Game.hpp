#ifndef QTICTACTOE_GAME_HPP
#define QTICTACTOE_GAME_HPP

class Game
{
	protected:
		QWidget window;
		QGridLayout grid;
		QMenuBar menu_bar;
		QMenu menu_options;
		QAction action_language;

		QPushButton restart;
		QLabel turn;
		QLabel current_icon;
		QSize current_size;
		bool xnow;
		char win;

		QPushButton button[9];
		QFrame line[4];
		QIcon o_icon;
		QSize o_size;
		QIcon x_icon;
		QSize x_size;
		char button_str[9];
		int rows;
		int columns;

		QPicture left_pi;
		QPicture right_pi;
		QPicture horizon_pi;
		QPicture vertical_pi;

		QLineF right_angle;
		QLineF left_angle;
		QLineF horizon_angle;
		QLineF vertical_angle;

		QLabel left_line;
		QLabel right_line;
		QLabel horizon_line;
		QLabel vertical_line;

		QPainter right_painter;
		QPainter left_painter;
		QPainter horizon_painter;
		QPainter vertical_painter;
	public:
		Game();
		void markDisabledAll();
		void show();
		void setWindowDetails();
		void setMenuDetails();
		void setGridDetails();
		void setLineDetails();
		void addToGrid();
		void paintLine(QLabel &label, int angle, int len, QPointF point);
};

#endif

#ifndef QTICTACTOE_BOARD_HPP
#define QTICTACTOE_BOARD_HPP

class Board : public Window
{
	protected:
		int symbols_thickness;
		char button_str[3][3];
		QIcon x_icon;
		QIcon o_icon;
		QSize x_size;
		QSize o_size;
		QPushButton button[3][3];
		QFrame line[4];

		QLabel left_line;
		QLabel right_line;
		QLabel horizon_line;
		QLabel vertical_line;

	public:
		Board();
		void paintCross(QIcon &icon);
		void paintCircle(QIcon &icon);
		void setGridDetails();
		void setLineDetails();
		void setButtonsDetails();
		void addToGrid();
};

#endif

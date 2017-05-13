#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QMenuBar>
#include <QAction>
#include <QPainter>
#include <QPicture>
#include <QMessageBox>

/* FUNCTIONS */
void markDisabledAll(QPushButton button[3][3])
{
	for(int x = 0; x < 3; x++) for(int y = 0; y < 3; y++)
		button[x][y].setDisabled(true);
}


void paintCross(QIcon &icon, QSize &size, const int &thickness)
{
	QPixmap pic(size);
	pic.fill(Qt::transparent);

	QPainter painter(&pic);
	painter.setPen(QPen(Qt::black, thickness));
	painter.setRenderHint(QPainter::Antialiasing);

	QLineF angleline;
	angleline.setLine(7, 7, 93, 93);
	painter.drawLine(angleline);
	angleline.setLine(7, 93, 93, 7);
	painter.drawLine(angleline);

	painter.end();
	icon.addPixmap(pic);
}

void paintCircle(QIcon &icon, QSize &size, const int &thickness)
{
	QPixmap pic(size);
	pic.fill(Qt::transparent);

	QPainter painter(&pic);
	painter.setPen(QPen(Qt::black, thickness));
	painter.setRenderHint(QPainter::Antialiasing);

	painter.drawEllipse(QPointF(50, 50), 45, 45);

	painter.end();
	icon.addPixmap(pic);
}

void paintLine(QLabel &label, int angle, int len, QPointF point, const int &thickness)
{
	QPicture pic;
	QLineF angleline;
	QPainter painter(&pic);

	painter.setPen(QPen(Qt::black, thickness));
	painter.setRenderHint(QPainter::Antialiasing);

	angleline.setP1(point);
	angleline.setAngle(angle);
	angleline.setLength(len);

	painter.drawLine(angleline);
	painter.end();

	label.setPicture(pic);
}


/* MAIN */
int main(int argc, char *argv[])
{
	/* VARIABLES */
	QApplication a(argc, argv);
	QWidget window;
	QGridLayout grid;
	QMenuBar menubar;
	QMenu help("Help");
	QAction about("About", &help);

	bool xnow = true;
	char win = 'n';
	QPushButton restart("Restart");
	QLabel turn("Whose turn:");
	QLabel current_icon;
	QSize current_size(30, 30);

	int thickness = 8;
	char button_str[3][3];
	int rows = 0;
	int columns = 0;

	QIcon x_icon;
	QIcon o_icon;
	QSize x_size(100, 100);
	QSize o_size(100, 100);
	QPushButton button[3][3];
	QFrame line[4];

	QLabel left_line;
	QLabel right_line;
	QLabel horizon_line;
	QLabel vertical_line;

	/* PAINT STUFF */
	paintCross(x_icon, x_size, thickness);
	paintCircle(o_icon, o_size, thickness);
	paintLine(vertical_line, 90, 298, QPointF(112, 0), thickness);
	paintLine(horizon_line, 0, 298, QPointF(0, 100), thickness);
	paintLine(left_line, 45, 420, QPointF(0, 100), thickness);
	paintLine(right_line, -45, 420, QPointF(0, 100), thickness);

	/* INITS */
	current_icon.setPixmap(x_icon.pixmap(current_size));
	restart.setFocusPolicy(Qt::NoFocus);
	window.setWindowTitle("QTicTacToe");
	window.setWindowFlags(Qt::Window);
	window.setFixedSize(0, 0);
	window.setLayout(&grid);
	grid.setMenuBar(&menubar);
	grid.setSpacing(0);
	grid.setRowMinimumHeight(5, 20);
	grid.setRowMinimumHeight(6, 40);
	menubar.addMenu(&help);
	help.addAction(&about);
	line[0].setFrameShape(QFrame::HLine);
	line[1].setFrameShape(QFrame::HLine);
	line[2].setFrameShape(QFrame::VLine);
	line[3].setFrameShape(QFrame::VLine);
	line[0].setLineWidth(2);
	line[1].setLineWidth(2);
	line[2].setLineWidth(2);
	line[3].setLineWidth(2);
	for(int x = 0; x < 3; x++) for(int y = 0; y < 3; y++)
	{
		button[x][y].setFixedSize(100, 100);
		button[x][y].setFlat(true);
		button[x][y].setFocusPolicy(Qt::NoFocus);
	}

	/* CONNECTS */
	QObject::connect(&about, &QAction::triggered, [&]
	{
		qDebug("action");
		QMessageBox::about(&window, "About", "QTicTacToe");
	});

	QObject::connect(&restart, &QPushButton::clicked, [&]
	{
		xnow = true;
		win = 'n';
		current_icon.setPixmap(x_icon.pixmap(current_size));
		for(int x = 0; x < 3; x++) for(int y = 0; y < 3; y++)
		{
			button_str[x][y] = '0';
			button[x][y].setEnabled(true);
			button[x][y].setIcon(QIcon());
		}
		grid.removeWidget(&left_line);
		grid.removeWidget(&right_line);
		grid.removeWidget(&horizon_line);
		grid.removeWidget(&vertical_line);
		left_line.hide();
		right_line.hide();
		horizon_line.hide();
		vertical_line.hide();
	});

	for(int x = 0; x < 3; x++) for(int y = 0; y < 3; y++)
	{
		QObject::connect(&button[x][y], &QPushButton::clicked, [&, x, y]
		{
			if(xnow)
			{
				button[x][y].setIcon(x_icon);
				button[x][y].setIconSize(x_size);
				button_str[x][y] = 'x';
				current_icon.setPixmap(o_icon.pixmap(current_size));
				xnow = false;
			}
			else
			{
				button[x][y].setIcon(o_icon);
				button[x][y].setIconSize(o_size);
				button_str[x][y] = 'o';
				current_icon.setPixmap(x_icon.pixmap(current_size));
				xnow = true;
			}
			button[x][y].setDisabled(true);

			//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
			if(button_str[0][0] == 'x' && button_str[0][1] == 'x' && button_str[0][2] == 'x')
			{
				grid.addWidget(&horizon_line, 0, 0, 1, 5, Qt::AlignJustify);
				horizon_line.show();
				markDisabledAll(button);
			}
			else if(button_str[1][0] == 'x' && button_str[1][1] == 'x' && button_str[1][2] == 'x')
			{
				grid.addWidget(&horizon_line, 2, 0, 1, 5, Qt::AlignJustify);
				horizon_line.show();
				markDisabledAll(button);
			}
			else if(button_str[2][0] == 'x' && button_str[2][1] == 'x' && button_str[2][2] == 'x')
			{
				grid.addWidget(&horizon_line, 4, 0, 1, 5, Qt::AlignJustify);
				horizon_line.show();
				markDisabledAll(button);
			}
			/*else if(button_str[0] == 'x' && button_str[3] == 'x' && button_str[6] == 'x')
			{
				grid.addWidget(&vertical_line, 0, 0, 5, 1, Qt::AlignJustify);
				vertical_line.show();
				markDisabledAll();
			}
			else if(button_str[1] == 'x' && button_str[4] == 'x' && button_str[7] == 'x')
			{
				grid.addWidget(&vertical_line, 0, 2, 5, 1, Qt::AlignJustify);
				vertical_line.show();
				markDisabledAll();
			}
			else if(button_str[2] == 'x' && button_str[5] == 'x' && button_str[8] == 'x')
			{
				grid.addWidget(&vertical_line, 0, 4, 5, 1, Qt::AlignJustify);
				vertical_line.show();
				markDisabledAll();
			}
			else if(button_str[0] == 'x' && button_str[4] == 'x' && button_str[8] == 'x')
			{
				grid.addWidget(&right_line, 0, 0, 5, 5, Qt::AlignJustify);
				right_line.show();
				markDisabledAll();
			}
			else if(button_str[2] == 'x' && button_str[4] == 'x' && button_str[6] == 'x')
			{
				grid.addWidget(&left_line, 0, 0, 5, 5, Qt::AlignJustify);
				left_line.show();
				markDisabledAll();
			}
			// OOOOOOOOOOOOOOOOOOOOOOOOOOO
			if(button_str[0] == 'o' && button_str[1] == 'o' && button_str[2] == 'o')
			{
				grid.addWidget(&horizon_line, 0, 0, 1, 5, Qt::AlignJustify);
				horizon_line.show();
				markDisabledAll();
			}
			else if(button_str[3] == 'o' && button_str[4] == 'o' && button_str[5] == 'o')
			{
				grid.addWidget(&horizon_line, 2, 0, 1, 5, Qt::AlignJustify);
				horizon_line.show();
				markDisabledAll();
			}
			else if(button_str[6] == 'o' && button_str[7] == 'o' && button_str[8] == 'o')
			{
				grid.addWidget(&horizon_line, 4, 0, 1, 5, Qt::AlignJustify);
				horizon_line.show();
				markDisabledAll();
			}
			else if(button_str[0] == 'o' && button_str[3] == 'o' && button_str[6] == 'o')
			{
				grid.addWidget(&vertical_line, 0, 0, 5, 1, Qt::AlignJustify);
				vertical_line.show();
				markDisabledAll();
			}
			else if(button_str[1] == 'o' && button_str[4] == 'o' && button_str[7] == 'o')
			{
				grid.addWidget(&vertical_line, 0, 2, 5, 1, Qt::AlignJustify);
				vertical_line.show();
				markDisabledAll();
			}
			else if(button_str[2] == 'o' && button_str[5] == 'o' && button_str[8] == 'o')
			{
				grid.addWidget(&vertical_line, 0, 4, 5, 1, Qt::AlignJustify);
				vertical_line.show();
				markDisabledAll();
			}
			else if(button_str[0] == 'o' && button_str[4] == 'o' && button_str[8] == 'o')
			{
				grid.addWidget(&right_line, 0, 0, 5, 5, Qt::AlignJustify);
				right_line.show();
				markDisabledAll();
			}
			else if(button_str[2] == 'o' && button_str[4] == 'o' && button_str[6] == 'o')
			{
				grid.addWidget(&left_line, 0, 0, 5, 5, Qt::AlignJustify);
				left_line.show();
				markDisabledAll();
			}*/

		});
	}

	/* GRID ADDONS */
	grid.addWidget(&turn, 6, 0);
	grid.addWidget(&current_icon, 6, 2);
	grid.addWidget(&restart, 6, 4, Qt::AlignRight);
	for(int x = 0; x < 3; x++) for(int y = 0; y < 3; y++)
	{
		if(columns == 5)
		{
			rows++;
			columns = 0;
		}
		if(columns == 1 || columns == 3)
		{
			grid.addWidget(&line[2], 0, 1, 5, 1);
			grid.addWidget(&line[3], 0, 3, 5, 1);
			columns++;
		}
		if(rows == 1 || rows == 3)
		{
			grid.addWidget(&line[0], 1, 0, 1, 5);
			grid.addWidget(&line[1], 3, 0, 1, 5);
			rows++;
		}
		grid.addWidget(&button[x][y], rows, columns);
		columns++;
	}

	/* SHOW AND RUN */
	window.show();
	return a.exec();
}

#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QMainWindow>
#include <QString>
#include <QFont>

int main(int argc, char *argv[])
{
	/* IMPORTANT */
	//order of variables DO matter
	QApplication a(argc, argv);
	QWidget window; //MainWindow, but with GridLayout, QMainWindow has it's own Layout
	QGridLayout grid;
	QPushButton button[9];
	QFont font("Liberation Sans", 80, QFont::ExtraLight);
	int rows = 0;
	int columns = 0;
	
	window.setLayout(&grid);
	window.setWindowTitle("QTicTacToe");
	window.setFixedSize(0, 0);
	grid.setSpacing(2);

	for(int i = 0; i < 9; i++)
	{
		if(columns == 3)
		{
			rows++;
			columns = 0;
		}
		button[i].setFixedSize(100, 100);
		button[i].setText(QString::number(i));
		button[i].setFont(font);
		grid.addWidget(&button[i], rows, columns);
		columns++;
	}

	/*int i = 0;
	QObject::connect(&button1, &QPushButton::clicked, [&button1, &i]
	{
		i++;
		QString txt = "clicked " + QString::number(i) + " times";
		if(i == 20) txt = "klikkkk";
		button1.setText(txt);
	});*/

	window.show();
	return a.exec();
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QVBoxLayout>
#include "ViewerWidget.h"
// --------------------------------------------
namespace Ui {
class MainWindow;
}
// --------------------------------------------
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

public:
	void resizeEvent(QResizeEvent *);

private slots:
	void on_btnLoadPointCloud_clicked();


private:
	Ui::MainWindow *ui = nullptr;
	ViewerWidget* mGlW = nullptr;
	QVBoxLayout *mVerticalLayout = nullptr;
};
// --------------------------------------------
#endif // MAINWINDOW_H

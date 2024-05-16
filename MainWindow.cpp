#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFileDialog>
// --------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	mGlW = new ViewerWidget(ui->wdgView);
	mGlW->setVisible(true);
	mGlW->setFocus();

	mVerticalLayout = new QVBoxLayout(ui->centralwidget);
	mVerticalLayout->addWidget(ui->wdgView);
	mVerticalLayout->addWidget(ui->wdgSettings);
	mVerticalLayout->setStretch(0, 1);
	mVerticalLayout->setStretch(1, 0);
}
// --------------------------------------------
MainWindow::~MainWindow()
{
	delete mGlW;
	delete mVerticalLayout;
	delete ui;
}
// --------------------------------------------
void MainWindow::resizeEvent(QResizeEvent *)
{
	if(mGlW != nullptr)
		mGlW->setGeometry(0, 0, ui->wdgView->width(), ui->wdgView->height());
}
// --------------------------------------------
void MainWindow::on_btnLoadPointCloud_clicked()
{
	if(mGlW == nullptr)
		return;

	QString csvFileName;
	csvFileName = QFileDialog::getOpenFileName(this, tr("Open Csv point cloud"), "", "Csv (*.csv)");

	if(csvFileName == "")
		return;

	mGlW->loadPointCloudFromFile(csvFileName);
}
// --------------------------------------------

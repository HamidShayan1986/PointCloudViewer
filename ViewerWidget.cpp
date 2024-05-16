#include <QtOpenGL>
#include "ViewerWidget.h"
#include <QtOpenGL>
// --------------------------------------------
QOpenGLFunctions* glFunc = nullptr;
// --------------------------------------------
ViewerWidget::ViewerWidget(QWidget *parent,
						   int swapInterval,
						   int msaaSamples,
						   bool swapDoubleBuffer)
	: QOpenGLWidget(parent)
{
	//------------------
	QSurfaceFormat reqFormat;
	reqFormat.setSwapBehavior(swapDoubleBuffer ? QSurfaceFormat::DoubleBuffer : QSurfaceFormat::SingleBuffer);
	reqFormat.setSamples(msaaSamples);
	reqFormat.setSwapInterval(swapInterval);
	setFormat(reqFormat);
	//------------------
	startTimer(50);
	//------------------
	float distance = 1500;
	mCamera.setPositions(QVector3D(distance, 0, 0), QVector3D(0, 0, 0), QVector3D(0, 0, 1));
}
// --------------------------------------------
ViewerWidget::~ViewerWidget()
{
}
// --------------------------------------------
void ViewerWidget::timerEvent(QTimerEvent *)
{
	update();
}
// --------------------------------------------
void ViewerWidget::initializeGL()
{   
	if(glFunc == nullptr)
	{
		glFunc = new QOpenGLFunctions();
		glFunc->initializeOpenGLFunctions();
	}

		glFunc->glEnable(GL_DEPTH_TEST);
}
// --------------------------------------------
void ViewerWidget::paintGL()
{
	glFunc->glClearColor(0, 0, 0, 1);
	glFunc->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	QMatrix4x4 viewProjMat = mCamera.mProjectionMatrix * mCamera.mViewMatrix;
	mPointCloud.draw(viewProjMat);
}
// --------------------------------------------
void ViewerWidget::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height);
	mCamera.makePerspectiveRhFOV(45, (float)width/height, 1, 100000);
}
// --------------------------------------------
void ViewerWidget::mousePressEvent(QMouseEvent *e)
{
	mPrevSelectedPoint = e->pos();

	this->setFocus();
}
// --------------------------------------------
void ViewerWidget::mouseMoveEvent(QMouseEvent *e)
{
	float rotFactor = 0.2;
	QPoint dPos = e->pos() - mPrevSelectedPoint;

	if(e->buttons() & Qt::LeftButton)
	{
		mCamera.rotateCameraTargetAroundBodyZ(-dPos.x() * rotFactor);
		mCamera.rotateCameraTargetAroundBodyRight(-dPos.y() * rotFactor);
	}

	mPrevSelectedPoint = e->pos();
}
// --------------------------------------------
void ViewerWidget::wheelEvent(QWheelEvent *e)
{
	mCamera.moveCameraBodyAndTargetAlongViewVector(10*e->delta()/120);
}
// --------------------------------------------
void ViewerWidget::keyPressEvent(QKeyEvent *e)
{
	moveCameraByKeboard(e->key());
}
// --------------------------------------------
void ViewerWidget::moveCameraByKeboard(int key)
{
	float moveFactor = 10;

	if (key == Qt::Key_W)
		mCamera.moveCameraBodyAndTargetAlongViewVector(moveFactor);
	if (key == Qt::Key_S)
		mCamera.moveCameraBodyAndTargetAlongViewVector(-moveFactor);
	if (key == Qt::Key_A)
		mCamera.moveCameraBodyAndTargetAlongRightVector(-moveFactor);
	if (key == Qt::Key_D)
		mCamera.moveCameraBodyAndTargetAlongRightVector(moveFactor);
	if (key == Qt::Key_E)
		mCamera.moveCameraBodyAndTargetAlongUpVector(moveFactor);
	if (key == Qt::Key_Q)
		mCamera.moveCameraBodyAndTargetAlongUpVector(-moveFactor);
}
// --------------------------------------------
void ViewerWidget::loadPointCloudFromFile(const QString &csvFileName)
{
	makeCurrent();
	mPointCloud.loadFromFile(csvFileName);
}
// --------------------------------------------

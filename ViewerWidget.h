#ifndef VIEWERWIDGET_H
#define VIEWERWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include "PointCloud.h"
#include "Camera.h"

extern QOpenGLFunctions* glFunc;
// --------------------------------------------
class ViewerWidget : public QOpenGLWidget // , protected QOpenGLFunctions
{
	Q_OBJECT

public:
	///
	/// \brief Constructor
	///
	/// \param parent: Parent widget
	/// \param swapInterval: Swap interval
	/// \param msaaSamples: Sample count for multi-sample anti-aliasing
	/// \param swapDoubleBuffer: Enables double buffering
	///
	/// \note To turn off vsync, set swapInterval to 0. For normal vsync set it to 1.
	/// \note To turn off msaa set msaaSamples to 0. Otherwise set it to 1/2/4/8/16/...
	///
	ViewerWidget(QWidget *parent = nullptr,
				 int swapInterval = 1,
				 int msaaSamples = 4,
				 bool swapDoubleBuffer = true);

	~ViewerWidget();

protected:
	void timerEvent(QTimerEvent *event);
	void mousePressEvent(QMouseEvent*);
	void mouseMoveEvent(QMouseEvent*);
	void wheelEvent(QWheelEvent*e);

	void keyPressEvent(QKeyEvent *e);

protected:
	void moveCameraByKeboard(int key);

protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);

public:
	///
	/// \brief Loads point cloud
	/// \param csvFileName CSV file name
	///
	void loadPointCloudFromFile(const QString &csvFileName);

private :
	/// \brief Point cloud
	PointCloud mPointCloud;

	/// \brief Camera
	Camera mCamera;

	/// \brief Prev. selected point on widget
	QPoint mPrevSelectedPoint;
};
// --------------------------------------------
#endif // VIEWERWIDGET_H

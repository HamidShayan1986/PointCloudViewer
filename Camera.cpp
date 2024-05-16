#include "Camera.h"
//----------------------------------------------------------------------------------
Camera::Camera()
{
	mBody = QVector3D(1, 0, 0);
	mTarget = QVector3D(0, 0, 0);

	mUpVector = QVector3D(0, 0, 1);

    setPositions(mBody, mTarget, mUpVector);
}
//----------------------------------------------------------------------------------
Camera::~Camera()
{
}
//----------------------------------------------------------------------------------
void Camera::setPositions(const QVector3D& camBody, const QVector3D& camTarget, const QVector3D& camUpVector)
{
    mBody = camBody;
    mTarget = camTarget;
    mUpVector = camUpVector;

    if(camBody == camTarget)
		mBody = camBody + QVector3D(.1, .1, .1);


	mUpVector.normalize();

    mViewVector = mTarget - mBody;
	mViewVector.normalize();

	mRightVector = QVector3D::crossProduct(mViewVector, mUpVector);
	mRightVector.normalize();

    //refine upVector (to prevent noises in moving and rotation of camera)
	mUpVector = QVector3D::crossProduct(mRightVector, mViewVector);

	mViewMatrix.setToIdentity();
	mViewMatrix.lookAt(mBody, mTarget, mUpVector);
}
//----------------------------------------------------------------------------------
void Camera::makePerspectiveRhFOV(float fovYInDegree, float aspectRatio, float zNear, float zFar)
{
	fovYInDegree = fovYInDegree;

	mProjectionMatrix.setToIdentity();
	mProjectionMatrix.perspective(fovYInDegree, aspectRatio, zNear, zFar);
}
//----------------------------------------------------------------------------------
//rotates camera's target around vector (body+upVector).
void Camera::rotateCameraTargetAroundBodyZ(float angleInDegree)
{
	QMatrix4x4 t;
	t.setToIdentity();
	t.translate(mBody); // moveBack
	t.rotate(angleInDegree, QVector3D(0, 0, 1));//rotateAroundZ
	t.translate(-mBody); // moveToOrigin

	mTarget = t * mTarget;
	QVector4D u = t * QVector4D(mUpVector, 0);
	mUpVector = QVector3D(u.x(), u.y(), u.z());

	setPositions(mBody, mTarget, mUpVector);
}
//----------------------------------------------------------------------------------
//rotates camera's target around vector (body+orthoVector)
void Camera::rotateCameraTargetAroundBodyRight(float angleInDegree)
{
	QMatrix4x4 t;
	t.setToIdentity();
	t.translate(mBody); // moveBack
	t.rotate(angleInDegree, mRightVector);//rotate
	t.translate(-mBody); // moveToOrigin

	mTarget = t * mTarget;
	QVector4D u = t * QVector4D(mUpVector, 0);
	mUpVector = QVector3D(u.x(), u.y(), u.z());

	setPositions(mBody, mTarget, mUpVector);
}
//----------------------------------------------------------------------------------
void Camera::moveCameraBodyAndTargetAlongVector(QVector3D v, float length)
{
	if(length == 0)
		return;//done

	//Normalize Vector [to ensure]
	v.normalize();

	//Make Translation Vector
	QVector3D trVect = v * length;

	//Translate Body and Target Of Camera
	QMatrix4x4 t;
	t.setToIdentity();
	t.translate(trVect);

	mBody = t * mBody;
	mTarget = t * mTarget;

	setPositions(mBody, mTarget, mUpVector);
}
//----------------------------------------------------------------------------------
void Camera::moveCameraBodyAndTargetAlongViewVector(float length)
{
    moveCameraBodyAndTargetAlongVector(mViewVector, length);
}
//----------------------------------------------------------------------------------
void Camera::moveCameraBodyAndTargetAlongRightVector(float length)
{
    moveCameraBodyAndTargetAlongVector(mRightVector, length);
}
//----------------------------------------------------------------------------------
void Camera::moveCameraBodyAndTargetAlongUpVector(float length)//along Saved up
{
    moveCameraBodyAndTargetAlongVector(mUpVector, length);
}
//----------------------------------------------------------------------------------

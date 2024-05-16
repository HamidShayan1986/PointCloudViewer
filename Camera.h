#ifndef CAMERA_H
#define CAMERA_H

#include <QMatrix4x4>
#include <QVector3D>

class LineBundle;
//------------------------------------------------------

///
/// \brief Camera
///
class Camera
{
public:
    ///
    /// \brief Parameters of camera position
    ///
	QVector3D mBody;
	QVector3D mTarget;
	QVector3D mUpVector;
	QVector3D mViewVector;
	QVector3D mRightVector; /*read only*/ // upVector × viewVector  (for balancing camera)

    ///
    /// \brief View matrix
    ///
	QMatrix4x4 mViewMatrix;

    ///
	/// \brief Projection Matrix
    ///
	QMatrix4x4 mProjectionMatrix;

public:
	///
	/// \brief Constructor
	///
	Camera();

	///
	/// \brief Destructor
	///
	~Camera();

    ///
    /// \brief Sets position
    ///
	void setPositions(const QVector3D &camBody, const QVector3D &camTarget, const QVector3D &camUpVector);

    ///
    /// \brief Sets perspective projection
    /// \param fovYInDegree Vertical field of view
    /// \param aspectRatio Aspect ratio
    /// \param zNear Near plane
    /// \param zFar Far plane
    ///
	void makePerspectiveRhFOV(float fovYInDegree, float aspectRatio, float zNear = 0.01, float zFar = 1e6);
    //======================================================================================

    ///
    /// \brief rotates camera's body around Z vector.
    /// \param pivot Pivot of rotation
    /// \param angleInDegree Angle in degrees
    ///
	void rotateCameraBodyAroundZ(QVector3D pivot, float angleInDegree);

    ///
    /// \brief rotates camera's body around Z vector. Target is used as pivot (target.x, target.y, 1).
    /// \param angleInDegree Angle in degrees
    ///
    void rotateCameraBodyAroundTargetZ(float angleInDegree);

    ///
    /// \brief rotates camera's target around Z vector.
    /// \param angleInDegree Angle in degrees
    ///
    void rotateCameraTargetAroundBodyZ(float angleInDegree);

    ///
    /// \brief rotates camera's target around right vector.  Body is used as pivot.
    /// \param angleInDegree Angle in degrees
    ///
    void rotateCameraTargetAroundBodyRight(float angleInDegree);


    ///
    /// \brief Moves Body along view vector
    /// \param length Length
    /// \return Exceeding target
    /// \note if moving cause body exceeding target, nothing occured and true is returned, else, body is moved and false is returned
    ///
    bool moveCameraBodyAlongViewVector(float length);


    ///
    /// \brief Moves camera body and target along vector
    /// \param v Vector
    /// \param length Length
    ///
	void moveCameraBodyAndTargetAlongVector(QVector3D v, float length);

    ///
    /// \brief Moves camera body and target along view vector
    /// \param length Length
    ///
    void moveCameraBodyAndTargetAlongViewVector(float length);

    ///
    /// \brief Moves camera body and target along right vector
    /// \param length Length
    ///
    void moveCameraBodyAndTargetAlongRightVector(float length);

    ///
    /// \brief Moves camera body and target along up vector
    /// \param length Length
    ///
    void moveCameraBodyAndTargetAlongUpVector(float length);
};
//------------------------------------------------------

#endif // CAMERA_H

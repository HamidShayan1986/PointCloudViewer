#ifndef POINTCLOUD_H
#define	POINTCLOUD_H

#include <vector>

#include <QOpenGLWidget>
#include <QVector3D>
//=============================================================
///
/// \brief Vertex format containing position
///
struct PositionVertex
{
	///
	/// \brief Position
	///
	float mX = 0;
	float mY = 0;
	float mZ = 0;

	///
	/// \brief Constructor
	/// \param x X component
	/// \param y Y component
	/// \param z Z component
	///
	PositionVertex(float mX = 0, float mY = 0, float mZ = 0);
};
//=============================================================
///
/// \brief Sub part of point cloud
///
struct PointCloudSubPart
{
    ///
    /// \brief Constructor
    ///
	PointCloudSubPart();

    ///
    /// \brief Destructor
    ///
	~PointCloudSubPart();

    ///
    /// \brief Fills VBO and IBO
    ///
    void fillBuffers();

    ///
    /// \brief The VBO
    ///
    GLuint mVertexBuffer = 0;

    ///
    /// \brief The IBO
    ///
    GLuint mIndexBuffer = 0;

    ///
    /// \brief Local vertex array
    ///
	std::vector<PositionVertex> mVertices;

    ///
    /// \brief Local index array
    ///
    std::vector<unsigned int> mIndices;

    ///
    /// \brief Minimum Position of bounding box
    ///
	QVector3D mMinPos;

    ///
    /// \brief Maximum Position of bounding box
    ///
	QVector3D mMaxPos;
};
//=============================================================
///
/// \brief Point Cloud
///
class PointCloud
{
    friend class Selection3D;
public:
    ///
    /// \brief Constructor
    ///
	PointCloud();

    ///
    /// \brief Destructor
    ///
	virtual ~PointCloud();

    ///
	/// \brief Loads point cloud
	/// \param glWin OpenGl widget which loads the point cloud
	/// \param csvFileName CSV file name
    /// \return Success
    ///
	bool loadFromFile(const QString &csvFileName);

	///
	/// \brief Draws point cloud
	/// \param viewProjMat Projection Matrix * View Matrix
	///
	virtual void draw(const QMatrix4x4 &viewProjMat);

	///
	/// \brief Draws point cloud
    /// \param viewProjMat Projection Matrix * View Matrix
    /// \param worldMat World Matrix
    ///
	virtual void draw(const QMatrix4x4 &viewProjMat, QMatrix4x4 &worldMat);

    ///
	/// \brief Returns \ref mSubParts
    ///
	std::vector<PointCloudSubPart>& subParts();

protected:
    ///
    /// \brief Clears all
    ///
    void clear();

    ///
	/// \brief Parts of point cloud
    ///
	std::vector<PointCloudSubPart> mSubParts;
};
//------------------------------------------------------

#endif	//  POINTCLOUD_H


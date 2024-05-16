#include "PointCloud.h"
#include "ShaderPrograms.h"
#include <QFile>
#include <QOpenGLFunctions>

//------------------------------------------------------
extern QOpenGLFunctions* glFunc;
//=============================================================
PositionVertex::PositionVertex(float x, float y, float z)
{
	mX = x;
	mY = y;
	mZ = z;
}
//=============================================================
PointCloudSubPart::PointCloudSubPart()
	:
	  mMinPos(99999, 99999, 99999),
	  mMaxPos(-99999, -99999, -99999)
{
	mVertexBuffer = 0;
	mIndexBuffer = 0;
}
//--------------------------------------------------------------------------
PointCloudSubPart::~PointCloudSubPart()
{
	if (mVertexBuffer != 0)
	{
		glFunc->glDeleteBuffers(1, &mVertexBuffer);
		mVertexBuffer = 0;
	}

	if (mIndexBuffer != 0)
	{
		glFunc->glDeleteBuffers(1, &mIndexBuffer);
		mIndexBuffer = 0;
	}
}
//--------------------------------------------------------------------------
void PointCloudSubPart::fillBuffers()
{
	if(mVertexBuffer == 0)
	{
		glFunc->glGenBuffers(1, &mVertexBuffer);
		glFunc->glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
		glFunc->glBufferData(GL_ARRAY_BUFFER, sizeof(PositionVertex) * mVertices.size(), mVertices.data(), GL_STATIC_DRAW);
	}
	else
	{
		glFunc->glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
		glFunc->glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(PositionVertex) * mVertices.size(), mVertices.data());
	}

	if(mIndexBuffer == 0)
	{
		glFunc->glGenBuffers(1, &mIndexBuffer);
		glFunc->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
		glFunc->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mIndices.size(), mIndices.data(), GL_STATIC_DRAW);
	}
	else
	{
		glFunc->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
		glFunc->glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(unsigned int) * mIndices.size(), mIndices.data());
	}
}
//=============================================================
PointCloud::PointCloud()
{
}
//--------------------------------------------------------------------------
PointCloud::~PointCloud()
{
	clear();
}
//--------------------------------------------------------------------------
void PointCloud::clear()
{
	mSubParts.clear();
}
//--------------------------------------------------------------------------
bool PointCloud::loadFromFile(const QString& csvFileName)
{
	// csvFileName.replace("/", "\");

	QFile csvFile(csvFileName);

	if (!csvFile.open(QIODevice::ReadOnly))
		return false;

	clear();

	//Load points
	const int MAX_POINTS_PER_SUB_PART = 1000;
	int loadedPointCount = 0;

	QTextStream inStream(&csvFile);

	while(true)
	{
		QString line = inStream.readLine();

		QStringList tokens = line.split(',');

		if(tokens.size() != 3)
			break;

		// New subpart
		if(loadedPointCount % MAX_POINTS_PER_SUB_PART == 0)
			mSubParts.push_back(PointCloudSubPart());

		PointCloudSubPart& subPart = mSubParts.back();

		PositionVertex vert(tokens[0].toFloat(), tokens[1].toFloat(), tokens[2].toFloat());

		subPart.mIndices.push_back(subPart.mVertices.size()); // one index per vertex
		subPart.mVertices.push_back(vert);

		subPart.mMinPos.setX(qMin(subPart.mMinPos.x(), vert.mX));
		subPart.mMinPos.setY(qMin(subPart.mMinPos.y(), vert.mY));
		subPart.mMinPos.setZ(qMin(subPart.mMinPos.z(), vert.mZ));

		subPart.mMaxPos.setX(qMax(subPart.mMaxPos.x(), vert.mX));
		subPart.mMaxPos.setY(qMax(subPart.mMaxPos.y(), vert.mY));
		subPart.mMaxPos.setZ(qMax(subPart.mMaxPos.z(), vert.mZ));

		loadedPointCount++;
	}

	csvFile.close();

	return true;
}
//--------------------------------------------------------------------------
void PointCloud::draw(const QMatrix4x4& viewProjMat)
{
	QMatrix4x4 worldMat;
	worldMat.setToIdentity();
	draw(viewProjMat, worldMat);
}
//--------------------------------------------------------------------------
void PointCloud::draw(const QMatrix4x4 &viewProjMat, QMatrix4x4 &worldMat)
{
	ShaderProgram_FixedColorPoint* shaderProg = ShaderProgram_FixedColorPoint::instance();
	shaderProg->mShaderProgram.bind();

	glPointSize(5);

	const int POS_LOC = 0;

	glFunc->glEnableVertexAttribArray(POS_LOC);

	for (unsigned int i = 0; i < mSubParts.size() ; i++)
	{
		if(mSubParts[i].mVertexBuffer == 0)
			mSubParts[i].fillBuffers();

		QMatrix4x4 worldViewProjMat = viewProjMat * worldMat;
		glFunc->glUniformMatrix4fv(shaderProg->mVars.mWorldViewProjMatrix, 1, GL_FALSE, worldViewProjMat.data());

		glFunc->glUniform4f(shaderProg->mVars.mFixedColor, 1, 0, 0, 1); // red color

		glFunc->glBindBuffer(GL_ARRAY_BUFFER, mSubParts[i].mVertexBuffer);
		glFunc->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mSubParts[i].mIndexBuffer);

		glFunc->glVertexAttribPointer(POS_LOC, 3, GL_FLOAT, GL_FALSE, sizeof(PositionVertex), 0);

		glFunc->glDrawElements(GL_POINTS, (GLsizei)mSubParts[i].mIndices.size(), GL_UNSIGNED_INT, 0);
	}

	glFunc->glDisableVertexAttribArray(POS_LOC);
}
//--------------------------------------------------------------------------
std::vector<PointCloudSubPart> &PointCloud::subParts()
{
	return mSubParts;
}
//--------------------------------------------------------------------------


#ifndef COMMON_PREDEFINEDSHADERPROGRAMS_H
#define COMMON_PREDEFINEDSHADERPROGRAMS_H

#include <QOpenGLShaderProgram>


//------------------------------------------------------
///
/// \brief Base of shader program
///
class ShaderProgram_Base
{
protected:
    ///
    /// \brief Creates shader program
    /// \param ins ShaderProgram_Base
    /// \param vertFileName Vertex shader file name
    /// \param fragFileName Fragment shader file name
    /// \return
    ///
    static bool createShaderProgram(ShaderProgram_Base* ins,
                                    const char *vertFileName,
                                    const char *fragFileName);

    ///
    /// \brief Creates shader program
    /// \param ins ShaderProgram_Base
    /// \param vertFileName Vertex shader file name
    /// \param fragFileName Fragment shader file name
    /// \param geoFileName Geometry shader file name
    /// \return
    ///
    static bool createShaderProgram(ShaderProgram_Base* ins,
                                    const char *vertFileName,
                                    const char *fragFileName,
                                    const char *geoFileName);

public:
    QOpenGLShaderProgram mShaderProgram;
};
//------------------------------------------------------
///
/// \brief Shader for Point
///
class ShaderProgram_FixedColorPoint : public ShaderProgram_Base
{
private:
	ShaderProgram_FixedColorPoint() = default;

public:
	static ShaderProgram_FixedColorPoint* instance();

public:
    struct ShaderVariableLocations
    {
		GLint mFixedColor = -1;
		GLint mWorldViewProjMatrix = -1;
    } mVars;
};
//------------------------------------------------------

#endif // COMMON_PREDEFINEDSHADERPROGRAMS_H

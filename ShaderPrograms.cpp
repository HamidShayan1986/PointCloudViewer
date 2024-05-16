#include "ShaderPrograms.h"


//------------------------------------------------------
bool ShaderProgram_Base::createShaderProgram(ShaderProgram_Base *ins,
                                             const char *vertFileName,
                                             const char *fragFileName)
{
    if(ins == nullptr)
        return false;

    if(!ins->mShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, vertFileName))
    {
        printf("Vert. Shader Error: %s\n", &(ins->mShaderProgram.log().toStdString())[0]);
        return false;
    }
    else if(!ins->mShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, fragFileName))
    {
        printf("Frag. Shader Error: %s\n", &(ins->mShaderProgram.log().toStdString())[0]);
        return false;
    }
    else if(!ins->mShaderProgram.link())
    {
        printf("Shader Link Error: %s\n", &(ins->mShaderProgram.log().toStdString())[0]);
        return false;
    }

    return true;
}
//------------------------------------------------------
bool ShaderProgram_Base::createShaderProgram(ShaderProgram_Base *ins, const char *vertFileName, const char *fragFileName, const char *geoFileName)
{
    if(ins == nullptr)
        return false;

    if(!ins->mShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, vertFileName))
    {
        printf("Vert. Shader Error: %s\n", &(ins->mShaderProgram.log().toStdString())[0]);
        return false;
    }
    else if(!ins->mShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, fragFileName))
    {
        printf("Frag. Shader Error: %s\n", &(ins->mShaderProgram.log().toStdString())[0]);
        return false;
    }
    else if(!ins->mShaderProgram.addShaderFromSourceFile(QOpenGLShader::Geometry, geoFileName))
    {
        printf("Geo. Shader Error: %s\n", &(ins->mShaderProgram.log().toStdString())[0]);
        return false;
    }
    else if(!ins->mShaderProgram.link())
    {
        printf("Shader Link Error: %s\n", &(ins->mShaderProgram.log().toStdString())[0]);
        return false;
    }

    return true;
}
//------------------------------------------------------
ShaderProgram_FixedColorPoint *ShaderProgram_FixedColorPoint::instance()
{
	static ShaderProgram_FixedColorPoint* ins = nullptr;

    if(ins == nullptr)
    {
		ins = new ShaderProgram_FixedColorPoint();

		if(createShaderProgram(ins, ":/Shaders/Point.vert", ":/Shaders/Point.frag"))
        {
			ins->mVars.mFixedColor  = ins->mShaderProgram.uniformLocation("fixedColor");
            ins->mVars.mWorldViewProjMatrix = ins->mShaderProgram.uniformLocation("worldViewProjMat");
        }
    }

    return ins;
}
//------------------------------------------------------

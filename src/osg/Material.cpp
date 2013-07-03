/* -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2006 Robert Osfield
 *
 * This library is open source and may be redistributed and/or modified under
 * the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or
 * (at your option) any later version.  The full license is in LICENSE file
 * included with this distribution, and on the openscenegraph.org website.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * OpenSceneGraph Public License for more details.
*/
#include <osg/Material>
#include <osg/BoundsChecking>
#include <osg/Notify>
#include <osg/State>

using namespace osg;

Material::Material()
{
    _colorMode = OFF;

    _ambientFrontAndBack = true;
    _ambientFront.set(0.2f, 0.2f, 0.2f, 1.0f);
    _ambientBack.set(0.2f, 0.2f, 0.2f, 1.0f);

    _diffuseFrontAndBack = true;
    _diffuseFront.set(0.8f, 0.8f, 0.8f, 1.0f);
    _diffuseBack.set(0.8f, 0.8f, 0.8f, 1.0f);

    _specularFrontAndBack = true;
    _specularFront.set(0.0f, 0.0f, 0.0f, 1.0f);
    _specularBack.set(0.0f, 0.0f, 0.0f, 1.0f);

    _emissionFrontAndBack = true;
    _emissionFront.set(0.0f, 0.0f, 0.0f, 1.0f);
    _emissionBack.set(0.0f, 0.0f, 0.0f, 1.0f);

    _shininessFrontAndBack = true;
    _shininessFront = 0.0f;
    _shininessBack = 0.0f;

    createBuiltUniforms();
}


Material::~Material()
{
}

Material& Material:: operator = (const Material& rhs)
{
    if (&rhs==this) return *this;

    _colorMode= rhs._colorMode;
    _ambientFrontAndBack= rhs._ambientFrontAndBack;
    _ambientFront= rhs._ambientFront;
    _ambientBack= rhs._ambientBack;
    _diffuseFrontAndBack= rhs._diffuseFrontAndBack;
    _diffuseFront= rhs._diffuseFront;
    _diffuseBack= rhs._diffuseBack;
    _specularFrontAndBack= rhs._specularFrontAndBack;
    _specularFront= rhs._specularFront;
    _specularBack= rhs._specularBack;
    _emissionFrontAndBack= rhs._emissionFrontAndBack;
    _emissionFront= rhs._emissionFront;
    _emissionBack= rhs._emissionBack;
    _shininessFrontAndBack= rhs._shininessFrontAndBack;
    _shininessFront= rhs._shininessFront;
    _shininessBack= rhs._shininessBack;

    // Update uniforms
    _colorModeFrontUniform->set(colorModeToUniformValue(_colorMode));
    _colorModeBackUniform->set(colorModeToUniformValue(_colorMode));
    _ambientFrontUniform->set(_ambientFront);
    _ambientBackUniform->set(_ambientBack);
    _diffuseFrontUniform->set(_diffuseFront);
    _diffuseBackUniform->set(_diffuseBack);
    _specularFrontUniform->set(_specularFront);
    _specularBackUniform->set(_specularBack);
    _emissionFrontUniform->set(_emissionFront);
    _emissionBackUniform->set(_emissionBack);
    _shininessFrontUniform->set(_shininessFront);
    _shininessBackUniform->set(_shininessBack);

    return *this;
}

void Material::createBuiltUniforms()
{
    _colorModeFrontUniform = new Uniform("osg_FrontMaterial.colorMode", colorModeToUniformValue(_colorMode));
    _colorModeBackUniform  = new Uniform("osg_BackMaterial.colorMode",  colorModeToUniformValue(_colorMode));
    _ambientFrontUniform   = new Uniform("osg_FrontMaterial.ambient",   _ambientFront);
    _ambientBackUniform    = new Uniform("osg_BackMaterial.ambient",    _ambientBack);
    _diffuseFrontUniform   = new Uniform("osg_FrontMaterial.diffuse",   _diffuseFront);
    _diffuseBackUniform    = new Uniform("osg_BackMaterial.diffuse",    _diffuseBack);
    _specularFrontUniform  = new Uniform("osg_FrontMaterial.specular",  _specularFront);
    _specularBackUniform   = new Uniform("osg_BackMaterial.specular",   _specularBack);
    _emissionFrontUniform  = new Uniform("osg_FrontMaterial.emission",  _emissionFront);
    _emissionBackUniform   = new Uniform("osg_BackMaterial.emission",   _emissionBack);
    _shininessFrontUniform = new Uniform("osg_FrontMaterial.shininess", _shininessFront);
    _shininessBackUniform  = new Uniform("osg_BackMaterial.shininess",  _shininessBack);

    // Set DYNAMIC data variance on Uniforms
    _colorModeFrontUniform->setDataVariance(DYNAMIC);
    _colorModeBackUniform->setDataVariance(DYNAMIC);
    _ambientFrontUniform->setDataVariance(DYNAMIC);
    _ambientBackUniform->setDataVariance(DYNAMIC);
    _diffuseFrontUniform->setDataVariance(DYNAMIC);
    _diffuseBackUniform->setDataVariance(DYNAMIC);
    _specularFrontUniform->setDataVariance(DYNAMIC);
    _specularBackUniform->setDataVariance(DYNAMIC);
    _emissionFrontUniform->setDataVariance(DYNAMIC);
    _emissionBackUniform->setDataVariance(DYNAMIC);
    _shininessFrontUniform->setDataVariance(DYNAMIC);
    _shininessBackUniform->setDataVariance(DYNAMIC);
}

void Material::setColorMode(ColorMode mode)
{
    _colorMode = mode;
	int uniformValue = colorModeToUniformValue(_colorMode);
    _colorModeFrontUniform->set(uniformValue);
    _colorModeBackUniform->set(uniformValue);
}

int Material::colorModeToUniformValue(ColorMode mode)
{
	int result = 0;
	
	switch (mode)
	{
		case AMBIENT :
			result = 1;
			break;
		case DIFFUSE :
			result = 2;
			break;
		case SPECULAR :
			result = 3;
			break;
		case EMISSION :
			result = 4;
			break;
		case AMBIENT_AND_DIFFUSE :
			result = 5;
			break;
		default :
			result = 0;
			break;
	}
	
	return result;
}

void Material::setAmbient(Face face, const Vec4& ambient )
{
    switch(face)
    {
        case(FRONT):
            _ambientFrontAndBack = false;
            _ambientFront = ambient;
            //clampArray4BetweenRange(_ambientFront,0.0f,1.0f,"osg::Material::setAmbient(..)");
            _ambientFrontUniform->set(ambient);
            break;
        case(BACK):
            _ambientFrontAndBack = false;
            _ambientBack = ambient;
            //clampArray4BetweenRange(_ambientBack,0.0f,1.0f,"Material::setAmbient(..)");
            _ambientBackUniform->set(ambient);
            break;
        case(FRONT_AND_BACK):
            _ambientFrontAndBack = true;
            _ambientFront = ambient;
            //clampArray4BetweenRange(_ambientFront,0.0f,1.0f,"Material::setAmbient(..)");
            _ambientBack = _ambientFront;
            _ambientFrontUniform->set(ambient);
            _ambientBackUniform->set(ambient);
            break;
        default:
            OSG_NOTICE<<"Notice: invalid Face passed to Material::setAmbient()."<<std::endl;
    }
}


const Vec4& Material::getAmbient(Face face) const
{
    switch(face)
    {
        case(FRONT):
            return _ambientFront;
        case(BACK):
            return _ambientBack;
        case(FRONT_AND_BACK):
            if (!_ambientFrontAndBack)
            {
                OSG_NOTICE<<"Notice: Material::getAmbient(FRONT_AND_BACK) called on material "<< std::endl;
                OSG_NOTICE<<"        with separate FRONT and BACK ambient colors."<< std::endl;
            }
            return _ambientFront;
    }
    OSG_NOTICE<<"Notice: invalid Face passed to Material::getAmbient()."<< std::endl;
    return _ambientFront;
}


void Material::setDiffuse(Face face, const Vec4& diffuse )
{
    switch(face)
    {
        case(FRONT):
            _diffuseFrontAndBack = false;
            _diffuseFront = diffuse;
            //clampArray4BetweenRange(_diffuseFront,0.0f,1.0f,"Material::setDiffuse(..)");
            _diffuseFrontUniform->set(diffuse);
            break;
        case(BACK):
            _diffuseFrontAndBack = false;
            _diffuseBack = diffuse;
            //clampArray4BetweenRange(_diffuseBack,0.0f,1.0f,"Material::setDiffuse(..)");
            _diffuseBackUniform->set(diffuse);
            break;
        case(FRONT_AND_BACK):
            _diffuseFrontAndBack = true;
            _diffuseFront = diffuse;
            //clampArray4BetweenRange(_diffuseFront,0.0f,1.0f,"Material::setDiffuse(..)");
            _diffuseBack = _diffuseFront;
            _diffuseFrontUniform->set(diffuse);
            _diffuseBackUniform->set(diffuse);
            break;
        default:
            OSG_NOTICE<<"Notice: invalid Face passed to Material::setDiffuse()."<< std::endl;
            break;
    }
}


const Vec4& Material::getDiffuse(Face face) const
{
    switch(face)
    {
        case(FRONT):
            return _diffuseFront;
        case(BACK):
            return _diffuseBack;
        case(FRONT_AND_BACK):
            if (!_diffuseFrontAndBack)
            {
                OSG_NOTICE<<"Notice: Material::getDiffuse(FRONT_AND_BACK) called on material "<< std::endl;
                OSG_NOTICE<<"        with separate FRONT and BACK diffuse colors."<< std::endl;
            }
            return _diffuseFront;
    }
    OSG_NOTICE<<"Notice: invalid Face passed to Material::getDiffuse()."<< std::endl;
    return _diffuseFront;
}


void Material::setSpecular(Face face, const Vec4& specular )
{
    switch(face)
    {
        case(FRONT):
            _specularFrontAndBack = false;
            _specularFront = specular;
            //clampArray4BetweenRange(_specularFront,0.0f,1.0f,"Material::setSpecular(..)");
            _specularFrontUniform->set(specular);
            break;
        case(BACK):
            _specularFrontAndBack = false;
            _specularBack = specular;
            //clampArray4BetweenRange(_specularBack,0.0f,1.0f,"Material::setSpecular(..)");
            _specularBackUniform->set(specular);
            break;
        case(FRONT_AND_BACK):
            _specularFrontAndBack = true;
            _specularFront = specular;
            //clampArray4BetweenRange(_specularFront,0.0f,1.0f,"Material::setSpecular(..)");
            _specularBack = _specularFront;
            _specularFrontUniform->set(specular);
            _specularBackUniform->set(specular);
            break;
        default:
            OSG_NOTICE<<"Notice: invalid Face passed to Material::setSpecular()."<< std::endl;
            break;
    }
}


const Vec4& Material::getSpecular(Face face) const
{
    switch(face)
    {
        case(FRONT):
            return _specularFront;
        case(BACK):
            return _specularBack;
        case(FRONT_AND_BACK):
            if (!_specularFrontAndBack)
            {
                OSG_NOTICE<<"Notice: Material::getSpecular(FRONT_AND_BACK) called on material "<< std::endl;
                OSG_NOTICE<<"        with separate FRONT and BACK specular colors."<< std::endl;
            }
            return _specularFront;
    }
    OSG_NOTICE<<"Notice: invalid Face passed to Material::getSpecular()."<< std::endl;
    return _specularFront;
}


void Material::setEmission(Face face, const Vec4& emission )
{
    switch(face)
    {
        case(FRONT):
            _emissionFrontAndBack = false;
            _emissionFront = emission;
            //clampArray4BetweenRange(_emissionFront,0.0f,1.0f,"Material::setEmission(..)");
            _emissionFrontUniform->set(emission);
            break;
        case(BACK):
            _emissionFrontAndBack = false;
            _emissionBack = emission;
            //clampArray4BetweenRange(_emissionBack,0.0f,1.0f,"Material::setEmission(..)");
            _emissionBackUniform->set(emission);
            break;
        case(FRONT_AND_BACK):
            _emissionFrontAndBack = true;
            _emissionFront = emission;
            //clampArray4BetweenRange(_emissionFront,0.0f,1.0f,"Material::setEmission(..)");
            _emissionBack = _emissionFront;
            _emissionFrontUniform->set(emission);
            _emissionBackUniform->set(emission);
            break;
        default:
            OSG_NOTICE<<"Notice: invalid Face passed to Material::setEmission()."<< std::endl;
            break;
    }
}


const Vec4& Material::getEmission(Face face) const
{
    switch(face)
    {
        case(FRONT):
            return _emissionFront;
        case(BACK):
            return _emissionBack;
        case(FRONT_AND_BACK):
            if (!_emissionFrontAndBack)
            {
                OSG_NOTICE<<"Notice: Material::getEmission(FRONT_AND_BACK) called on material "<< std::endl;
                OSG_NOTICE<<"        with separate FRONT and BACK emission colors."<< std::endl;
            }
            return _emissionFront;
    }
    OSG_NOTICE<<"Notice: invalid Face passed to Material::getEmission()."<< std::endl;
    return _emissionFront;
}


void Material::setShininess(Face face, float shininess )
{
    clampBetweenRange(shininess,0.0f,128.0f,"Material::setShininess()");

    switch(face)
    {
        case(FRONT):
            _shininessFrontAndBack = false;
            _shininessFront = shininess;
            _shininessFrontUniform->set(shininess);
            break;
        case(BACK):
            _shininessFrontAndBack = false;
            _shininessBack = shininess;
            _shininessBackUniform->set(shininess);
            break;
        case(FRONT_AND_BACK):
            _shininessFrontAndBack = true;
            _shininessFront = shininess;
            _shininessBack = shininess;
            _shininessFrontUniform->set(shininess);
            _shininessBackUniform->set(shininess);
            break;
        default:
            OSG_NOTICE<<"Notice: invalid Face passed to Material::setShininess()."<< std::endl;
            break;
    }
}


float Material::getShininess(Face face) const
{
    switch(face)
    {
        case(FRONT):
            return _shininessFront;
        case(BACK):
            return _shininessBack;
        case(FRONT_AND_BACK):
            if (!_shininessFrontAndBack)
            {
                OSG_NOTICE<<"Notice: Material::getShininess(FRONT_AND_BACK) called on material "<< std::endl;
                OSG_NOTICE<<"        with separate FRONT and BACK shininess colors."<< std::endl;
            }
            return _shininessFront;
    }
    OSG_NOTICE<<"Notice: invalid Face passed to Material::getShininess()."<< std::endl;
    return _shininessFront;
}

void Material::setTransparency(Face face,float transparency)
{
   //clampBetweenRange(transparency,0.0f,1.0f,"Material::setTransparency()");

   if (face==FRONT || face==FRONT_AND_BACK)
   {
        _ambientFront[3] = 1.0f-transparency;
        _diffuseFront[3] = 1.0f-transparency;
        _specularFront[3] = 1.0f-transparency;
        _emissionFront[3] = 1.0f-transparency;

        // Update uniforms
        _ambientFrontUniform->set(_ambientFront);
        _diffuseFrontUniform->set(_diffuseFront);
        _specularFrontUniform->set(_specularFront);
        _emissionFrontUniform->set(_emissionFront);
    }

    if (face==BACK || face==FRONT_AND_BACK)
    {
        _ambientBack[3] = 1.0f-transparency;
        _diffuseBack[3] = 1.0f-transparency;
        _specularBack[3] = 1.0f-transparency;
        _emissionBack[3] = 1.0f-transparency;

        // Update uniforms
        _ambientBackUniform->set(_ambientBack);
        _diffuseBackUniform->set(_diffuseBack);
        _specularBackUniform->set(_specularBack);
        _emissionBackUniform->set(_emissionBack);
    }
}

void Material::setAlpha(Face face,float alpha)
{
   clampBetweenRange(alpha,0.0f,1.0f,"Material::setAlpha()");

   if (face==FRONT || face==FRONT_AND_BACK)
   {
        _ambientFront[3] = alpha;
        _diffuseFront[3] = alpha;
        _specularFront[3] = alpha;
        _emissionFront[3] = alpha;

        // Update uniforms
        _ambientFrontUniform->set(_ambientFront);
        _diffuseFrontUniform->set(_diffuseFront);
        _specularFrontUniform->set(_specularFront);
        _emissionFrontUniform->set(_emissionFront);
    }

    if (face==BACK || face==FRONT_AND_BACK)
    {
        _ambientBack[3] = alpha;
        _diffuseBack[3] = alpha;
        _specularBack[3] = alpha;
        _emissionBack[3] = alpha;

        // Update uniforms
        _ambientBackUniform->set(_ambientBack);
        _diffuseBackUniform->set(_diffuseBack);
        _specularBackUniform->set(_specularBack);
        _emissionBackUniform->set(_emissionBack);
    }
}

void Material::apply(State& state) const
{
	state.applyShaderCompositionUniform(_colorModeFrontUniform);
	state.applyShaderCompositionUniform(_colorModeBackUniform);
	state.applyShaderCompositionUniform(_ambientFrontUniform);
	state.applyShaderCompositionUniform(_ambientBackUniform);
	state.applyShaderCompositionUniform(_diffuseFrontUniform);
	state.applyShaderCompositionUniform(_diffuseBackUniform);
	state.applyShaderCompositionUniform(_specularFrontUniform);
	state.applyShaderCompositionUniform(_specularBackUniform);
	state.applyShaderCompositionUniform(_emissionFrontUniform);
	state.applyShaderCompositionUniform(_emissionBackUniform);
	state.applyShaderCompositionUniform(_shininessFrontUniform);
	state.applyShaderCompositionUniform(_shininessBackUniform);

#ifdef OSG_GL_FIXED_FUNCTION_AVAILABLE

#ifdef OSG_GL1_AVAILABLE
    if (_colorMode==OFF)
    {
        glDisable(GL_COLOR_MATERIAL);

        glColor4fv(_diffuseFront.ptr());
    }
    else
    {
        glColorMaterial(GL_FRONT_AND_BACK,(GLenum)_colorMode);
        glEnable(GL_COLOR_MATERIAL);
        switch(_colorMode)
        {
            case(AMBIENT): glColor4fv(_ambientFront.ptr()); break;
            case(DIFFUSE): glColor4fv(_diffuseFront.ptr()); break;
            case(SPECULAR): glColor4fv(_specularFront.ptr()); break;
            case(EMISSION): glColor4fv(_emissionFront.ptr()); break;
            case(AMBIENT_AND_DIFFUSE): glColor4fv(_diffuseFront.ptr()); break;
            case(OFF): break;
        }
    }
#endif

    if (_colorMode!=AMBIENT && _colorMode!=AMBIENT_AND_DIFFUSE)
    {
        if (_ambientFrontAndBack)
        {
            glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, _ambientFront.ptr() );
        }
        else
        {
            glMaterialfv( GL_FRONT, GL_AMBIENT, _ambientFront.ptr() );
            glMaterialfv( GL_BACK, GL_AMBIENT, _ambientBack.ptr() );
        }
    }

    if (_colorMode!=DIFFUSE && _colorMode!=AMBIENT_AND_DIFFUSE)
    {
        if (_diffuseFrontAndBack)
        {
            glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, _diffuseFront.ptr() );
        }
        else
        {
            glMaterialfv( GL_FRONT, GL_DIFFUSE, _diffuseFront.ptr() );
            glMaterialfv( GL_BACK, GL_DIFFUSE, _diffuseBack.ptr() );
        }
    }

    if (_colorMode!=SPECULAR)
    {
        if (_specularFrontAndBack)
        {
            glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, _specularFront.ptr() );
        }
        else
        {
            glMaterialfv( GL_FRONT, GL_SPECULAR, _specularFront.ptr() );
            glMaterialfv( GL_BACK, GL_SPECULAR, _specularBack.ptr() );
        }
    }

    if (_colorMode!=EMISSION)
    {
        if (_emissionFrontAndBack)
        {
            glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION, _emissionFront.ptr() );
        }
        else
        {
            glMaterialfv( GL_FRONT, GL_EMISSION, _emissionFront.ptr() );
            glMaterialfv( GL_BACK, GL_EMISSION, _emissionBack.ptr() );
        }
    }

    if (_shininessFrontAndBack)
    {
        glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, _shininessFront );
    }
    else
    {
        glMaterialf( GL_FRONT, GL_SHININESS, _shininessFront );
        glMaterialf( GL_BACK, GL_SHININESS, _shininessBack );
    }
#else
    OSG_NOTICE<<"Warning: Material::apply(State&) - not supported."<<std::endl;
#endif
}

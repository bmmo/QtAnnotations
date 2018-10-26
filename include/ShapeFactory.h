#ifndef _INCLUDE_SHAPE_FACTORY_H_
#define _INCLUDE_SHAPE_FACTORY_H_

#include <osg/Geode>
#include <osg/Vec3f>

class ShapeFactory 
{

public:

	static osg::ref_ptr<osg::Geode> Sphere(const osg::Vec3f& center, float radius, const osg::Vec4f& color);		
	static osg::ref_ptr<osg::Geode> Quad(const osg::Vec3f& center, float width, float height, const osg::Vec4f& color);

};


#endif

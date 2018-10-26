#include <ShapeFactory.h>

#include <osg/StateSet>
#include <osg/ShapeDrawable>
#include <osg/Shape>

osg::ref_ptr<osg::Geode> ShapeFactory::Sphere(const osg::Vec3f& center, float radius, const osg::Vec4f& color)
{

	osg::Sphere* sphere = new osg::Sphere(center, radius);
	osg::ShapeDrawable* d = new osg::ShapeDrawable(sphere);

	d->setColor(color);

	osg::Geode* g = new osg::Geode;
	g->addDrawable(d);

	return g;

}


osg::ref_ptr<osg::Geode> ShapeFactory::Quad(const osg::Vec3f& center, float width, float height, const osg::Vec4f& color) 
{

	osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;

	vertices->push_back(center + osg::Vec3f(0.f, 0.f, 0.f));
	vertices->push_back(center + osg::Vec3f(width, 0.f, 0.f));
	vertices->push_back(center + osg::Vec3f(width, height, 0.f));
	vertices->push_back(center + osg::Vec3f(0.f, height, 0.f));

	osg::ref_ptr<osg::Geometry> quad_geom = new osg::Geometry;
	osg::ref_ptr<osg::DrawArrays> quad_da = new osg::DrawArrays(osg::PrimitiveSet::QUADS,0,4);

	osg::ref_ptr<osg::Vec4Array> quad_colors = new osg::Vec4Array;
	quad_colors->push_back(color);

	quad_geom->setVertexArray(vertices.get());
	quad_geom->addPrimitiveSet(quad_da.get());
	quad_geom->setColorArray(quad_colors.get(), osg::Array::BIND_OVERALL);

	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(quad_geom);

	return geode;

}

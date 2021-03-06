//
// Created by kev on 23/01/17.
//

#ifndef ROLLER_COSTER_ROLLPATH_HPP
#define ROLLER_COSTER_ROLLPATH_HPP
#include <Drawable.hpp>

using namespace glimac;

class RollPath : public Drawable{
private:
    std::vector<Geometry::Vertex> list_point;

public:
    Geometry::Vertex getPointCurve(float time);

    void init(const FilePath&);

    void init_texture();

    void init_vbo();

    void init_vao();

    void init_index();

    void draw();

    void duplicate_vertex();

    void free();
};

#endif //ROLLER_COSTER_ROLLPATH_HPP

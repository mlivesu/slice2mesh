#include "slice2plc.h"

void slice2plc(DrawableSlicedObj<> & obj, DrawableTrimesh<> & plc)
{
    std::vector<vec3d> verts;
    std::vector<uint>  polys;

    if(obj.size()<2) return;

    initialize();
    edge_wise_intersections();

    mesh_vertical(tris, labels);
    mesh_horizontal(tris, labels);

    for(V_data p : v_list)
    {
        coords.push_back(p.pos.x());
        coords.push_back(p.pos.y());
        coords.push_back(p.pos.z());
    }
}

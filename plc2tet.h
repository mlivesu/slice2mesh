#ifndef PLC2TET_H
#define PLC2TET_H

#include <cinolib/meshes/meshes.h>
#include <cinolib/drawable_sliced_object.h>
#include "common.h"

void plc2tet(const DrawableTrimesh<>   & plc,
             const DrawableSlicedObj<> & obj,
             const std::string         & flags,
                   DrawableTetmesh<>   & m);

#endif // PLC2TET_H

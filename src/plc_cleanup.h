#ifndef PLC_CLEANUP_H
#define PLC_CLEANUP_H

#include <cinolib/meshes/trimesh.h>

void cleanup_plc(cinolib::Trimesh<> & plc, const float min_len);

#endif // PLC_CLEANUP_H

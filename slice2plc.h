#ifndef SLICE2PLC_H
#define SLICE2PLC_H

#include <cinolib/drawable_sliced_object.h>
#include "common.h"

void slice2plc(const DrawableSlicedObj<> & obj,
                     DrawableTrimesh<>   & plc);

#endif // SLICE2PLC_H

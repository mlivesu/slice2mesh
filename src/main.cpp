#include <QApplication>
#include <cinolib/meshes/meshes.h>
#include <cinolib/gui/qt/qt_gui_tools.h>

#include <cinolib/sliced_object.h>
#include <cinolib/string_utilities.h>
#include <cinolib/profiler.h>
#include "common.h"
#include "slice2plc.h"
#include "plc2tet.h"
#include "plc_cleanup.h"

using namespace cinolib;

// default parameters
double      hatch_thickness = 0.01;
bool        export_plc      = false;
bool        export_tetmesh  = true;
std::string tetgen_flags    = "QT1e-13";
std::string base_name;

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

void set_parameters(int argc, char *argv[])
{
    base_name = get_file_name(argv[1], false);

    for(int i=2; i<argc; ++i)
    {
        if(strcmp(argv[i], "-plc") == 0)
        {
            export_plc = true;
            std::cout << "info: export PLC" << std::endl;
        }
        if(strcmp(argv[i], "-plc-only") == 0)
        {
            export_plc     = true;
            export_tetmesh = false;
            std::cout << "info: export ONLY the PLC" << std::endl;
        }
        if(strcmp(argv[i], "-hatch") == 0 && i+1<argc)
        {
            hatch_thickness = atof(argv[++i]);
            std::cout << "info: set hatch thickness to " << hatch_thickness << std::endl;
        }
        if(strcmp(argv[i], "-tetflags") == 0 && i+1<argc)
        {
            tetgen_flags.append(argv[++i]);
            std::cout << "info: set tetgen flags to " << tetgen_flags << std::endl;
        }
    }
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        std::cout << "                                                                                       " << std::endl;
        std::cout << "expected usage: slice2mesh input.cli [flags]                                           " << std::endl;
        std::cout << "                                                                                       " << std::endl;
        std::cout << "Flags:                                                                                 " << std::endl;
        std::cout << "  -hatch    h  thicken 1D hatches by h amount and mesh them (default h=0.01)           " << std::endl;
        std::cout << "  -tetflags f  use f flags when calling tetgen to produce the tetmesh (default f=\"Q\")" << std::endl;
        std::cout << "  -plc         export the PLC as a non-manifold triangle mesh                          " << std::endl;
        std::cout << "  -plc-only    export ONLY the PLC                                                     " << std::endl;
        //std::cout << "  -subsmp   f  slice subsampling. consider only one every f slices\n\n                 " << std::endl;
        return -1;
    }

    set_parameters(argc,argv);

    Profiler profiler;

    profiler.push("Create Sliced Obj");
    SlicedObj<> obj(argv[1], hatch_thickness);
    profiler.pop();

    obj.save((base_name+"_slices.off").c_str());
    if(obj.num_slices()<2)
    {
        std::cerr << "ERROR: less than two slices were found!" << std::endl;
        exit(0);
    }

    QApplication app(argc,argv);

    DrawableTrimesh<> plc;
    profiler.push("slice2plc");
    slice2plc(obj, plc);
    profiler.pop();
    if(export_plc) plc.save((base_name+".off").c_str());

    cleanup_plc(plc, obj.slice_avg_thickness()*0.1);
    plc.show_mesh_flat();
    plc.show_marked_edge(true);
    plc.show_marked_edge_width(10);
    plc.updateGL();
    GLcanvas gui;
    gui.push_obj(&plc);
    gui.show();

    // CMD+1 to show mesh controls.
    SurfaceMeshControlPanel<DrawableTrimesh<>> panel(&plc, &gui);
    QApplication::connect(new QShortcut(QKeySequence(Qt::CTRL+Qt::Key_1), &gui), &QShortcut::activated, [&](){panel.show();});

    Tetmesh<> m;
    if(export_tetmesh)
    {
        profiler.push("plc2mesh");
        plc2tet(plc, obj, tetgen_flags.c_str(), m);
        profiler.pop();
        m.save((base_name+".mesh").c_str());
    }

    return app.exec();
}

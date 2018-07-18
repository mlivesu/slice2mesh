#include <QApplication>
#include <cinolib/gui/qt/qt_gui_tools.h>
#include <cinolib/drawable_sliced_object.h>
#include <cinolib/string_utilities.h>
#include "common.h"
#include "slice2plc.h"
#include "plc2tet.h"

using namespace cinolib;

// default parameters
double      hatch_thickness = 0.01;
bool        export_plc      = false;
bool        export_tetmesh  = true;
std::string tetgen_flags    = "Q";
std::string base_name;

//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

void set_parameters(int argc, char *argv[])
{
    base_name = get_file_name(argv[1], false);

    for(int i=2; i<argc; ++i)
    {
        if(strcmp(argv[i], "-vp") == 0)
        {
            export_plc = true;
            std::cout << "info: export PLC" << std::endl;
        }
        if(strcmp(argv[i], "-vp-only") == 0)
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
            tetgen_flags = std::string(argv[++i]);
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
        std::cout << "  -vp          export the PLC as a non-manifold triangle mesh                          " << std::endl;
        std::cout << "  -vp-only     export ONLY the PLC                                                     " << std::endl;
        //std::cout << "  -subsmp   f  slice subsampling. consider only one every f slices\n\n                 " << std::endl;
        return -1;
    }

    QApplication a(argc, argv);
    set_parameters(argc,argv);

    DrawableSlicedObj<> obj(argv[1], hatch_thickness);

    if(obj.num_slices()<2)
    {
        std::cerr << "ERROR: less than two slices were found!" << std::endl;
        exit(0);
    }

    DrawableTrimesh<> plc;
    slice2plc(obj, plc);
    if(export_plc) plc.save((base_name+".obj").c_str());

    DrawableTetmesh<> m;
    if(export_tetmesh)
    {
        plc2tet(plc, obj, tetgen_flags.c_str(), m);
        m.save((base_name+".mesh").c_str());
    }

    GLcanvas gui;
    gui.push_obj(&obj);
    gui.push_obj(&plc);
    gui.push_obj(&m);
    gui.show();

    obj.show_mesh(false);
    plc.show_mesh(false);

    // CMD+1 to show Sliced Obj  visual controls.
    // CMD+2 to show PLC         visual controls.
    // CMD+3 to show Tetmesh     visual controls.
    SurfaceMeshControlPanel<DrawableSlicedObj<>> panel_obj(&obj, &gui);
    SurfaceMeshControlPanel<DrawableTrimesh<>>   panel_plc(&plc, &gui);
    VolumeMeshControlPanel<DrawableTetmesh<>>    panel_tet(&m, &gui);
    QApplication::connect(new QShortcut(QKeySequence(Qt::CTRL+Qt::Key_1), &gui), &QShortcut::activated, [&](){panel_obj.show();});
    QApplication::connect(new QShortcut(QKeySequence(Qt::CTRL+Qt::Key_2), &gui), &QShortcut::activated, [&](){panel_plc.show();});
    QApplication::connect(new QShortcut(QKeySequence(Qt::CTRL+Qt::Key_3), &gui), &QShortcut::activated, [&](){panel_tet.show();});

    return a.exec();
}

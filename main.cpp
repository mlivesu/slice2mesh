#include <QApplication>
#include <cinolib/gui/qt/qt_gui_tools.h>
#include <cinolib/drawable_sliced_object.h>
#include "common.h"
#include "slice2plc.h"
#include "plc2tet.h"

using namespace cinolib;

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DrawableSlicedObj<> obj(argv[1]);

    if(obj.num_slices()<2)
    {
        std::cerr << "ERROR: less than two slices were found!" << std::endl;
        exit(0);
    }

    DrawableTrimesh<> plc;
    slice2plc(obj, plc);

    DrawableTetmesh<> m;
    plc2tet(plc, obj, "Qq", m);

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

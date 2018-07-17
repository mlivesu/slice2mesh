#include <QApplication>
#include <cinolib/gui/qt/qt_gui_tools.h>
#include <cinolib/drawable_sliced_object.h>
#include <cinolib/tetgen_wrap.h>
#include "common.h"
#include "slice2plc.h"

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
    tetgen_wrap(plc, "q", m);
    m.updateGL();

    GLcanvas gui;
    gui.push_obj(&m);
    gui.show();

    // CMD+1 to show PLC visual controls.
    SurfaceMeshControlPanel<DrawableTrimesh<>> panel(&plc, &gui);
    QApplication::connect(new QShortcut(QKeySequence(Qt::CTRL+Qt::Key_1), &gui), &QShortcut::activated, [&](){panel.show();});

    // CMD+2 to show Tetmesh visual controls.
    VolumeMeshControlPanel<DrawableTetmesh<>> panel2(&m, &gui);
    QApplication::connect(new QShortcut(QKeySequence(Qt::CTRL+Qt::Key_2), &gui), &QShortcut::activated, [&](){panel2.show();});

    return a.exec();
}

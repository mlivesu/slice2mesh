#include <QApplication>
#include <cinolib/gui/qt/qt_gui_tools.h>
#include <cinolib/drawable_sliced_object.h>
#include "common.h"
#include "slice2plc.h"

using namespace cinolib;

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DrawableSlicedObj<> obj(argv[1]);

    GLcanvas gui;
    gui.push_obj(&obj);
    gui.show();

    DrawableTrimesh<> plc;
    slice2plc(obj, plc);

    // CMD+1 to show visual controls.
    SurfaceMeshControlPanel<DrawableSlicedObj<>> panel(&obj, &gui);
    QApplication::connect(new QShortcut(QKeySequence(Qt::CTRL+Qt::Key_1), &gui), &QShortcut::activated, [&](){panel.show();});

    return a.exec();
}

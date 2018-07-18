TEMPLATE        = app
TARGET          = slice2mesh
QT             += core opengl
CONFIG         += c++11
CONFIG         -= app_bundle
CINOLIB_PATH    = /Users/cino/Documents/research/devel/lib/CinoLib
INCLUDEPATH    += $$CINOLIB_PATH/external/eigen
INCLUDEPATH    += $$CINOLIB_PATH/include
DEPENDPATH     += $$CINOLIB_PATH/include
QMAKE_CXXFLAGS += -Wno-deprecated-declarations # gluQuadric gluSphere and gluCylinde are deprecated in macOS 10.9

# ------------------------------------ #
# ------------- SOURCES -------------- #
# ------------------------------------ #
SOURCES += main.cpp
SOURCES += plc2tet.cpp
SOURCES += trianglulate.cpp
SOURCES += edge_processing.cpp
SOURCES += slice2plc.cpp
#
HEADERS += common.h
HEADERS += plc2tet.h
HEADERS += trianglulate.h
HEADERS += edge_processing.h
HEADERS += slice2plc.h

# ------------------------------------ #
# ------- EXTERNAL DEPENDENCIES ------ #
# ------------------------------------ #
DEFINES        += CINOLIB_USES_OPENGL
DEFINES        += CINOLIB_USES_QT
DEFINES        += CINOLIB_USES_BOOST
#
DEFINES        += CINOLIB_USES_VTK
INCLUDEPATH    += /usr/local/include/vtk-7.1
QMAKE_LFLAGS   *= -L/usr/local/lib
LIBS           += -lvtkCommonCore-7.1 -lvtkCommonDataModel-7.1 -lvtkIOCore-7.1 -lvtkIOLegacy-7.1 -lvtkIOXML-7.1
QMAKE_CXXFLAGS += -Wno-inconsistent-missing-override # shows up in vtk7...
#
DEFINES        += CINOLIB_USES_TRIANGLE
LIBS           += -ltriangle
INCLUDEPATH    *= /usr/local/include
#
DEFINES        += CINOLIB_USES_TETGEN
DEFINES        += TETLIBRARY
LIBS           += -ltet
INCLUDEPATH    *= /usr/local/include

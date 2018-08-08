TEMPLATE        = app
TARGET          = slice2mesh
QT             += core
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
DEFINES        += CINOLIB_USES_TRIANGLE
LIBS           += -ltriangle
INCLUDEPATH    *= /usr/local/include
#
DEFINES        += CINOLIB_USES_TETGEN
DEFINES        += TETLIBRARY
LIBS           += -ltet
INCLUDEPATH    *= /usr/local/include

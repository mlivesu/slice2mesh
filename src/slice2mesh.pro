CINOLIB_PATH = /Users/cino/Documents/research/devel/lib/CinoLib
TEMPLATE     = app
TARGET       = slice2mesh
QT          += core
CONFIG      += c++11
CONFIG      -= app_bundle
INCLUDEPATH += $$CINOLIB_PATH/external/eigen
INCLUDEPATH += $$CINOLIB_PATH/include

# ------------------------------------ #
# ------------- SOURCES -------------- #
# ------------------------------------ #
SOURCES += main.cpp
SOURCES += plc2tet.cpp
SOURCES += trianglulate.cpp
SOURCES += edge_processing.cpp
SOURCES += slice2plc.cpp
HEADERS += common.h
HEADERS += plc2tet.h
HEADERS += trianglulate.h
HEADERS += edge_processing.h
HEADERS += slice2plc.h

# ------------------------------------ #
# ------- EXTERNAL DEPENDENCIES ------ #
# ------------------------------------ #
DEFINES     += CINOLIB_USES_BOOST
INCLUDEPATH *= /usr/local/include
#
DEFINES     += CINOLIB_USES_TRIANGLE
LIBS        += -L/usr/local/lib -ltriangle
#
DEFINES     += CINOLIB_USES_TETGEN
DEFINES     += TETLIBRARY
LIBS        += -L/usr/local/lib -ltet

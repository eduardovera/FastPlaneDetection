TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    utils.h \
    settings.h \
    octree.h

win32 {
    INCLUDEPATH += "$(OPENCV_INCLUDE_DIR)" \

    CONFIG(debug,debug|release) {
        LIBS += -L"$(OPENCV_LIB_DIR)" \
            -lopencv_core$(OPENCV_VERSION)d \
            -lopencv_highgui$(OPENCV_VERSION)d \
            -lopencv_imgproc$(OPENCV_VERSION)d \
            -lopencv_features2d$(OPENCV_VERSION)d \
            -lopencv_calib3d$(OPENCV_VERSION)d \
            -lopencv_contrib$(OPENCV_VERSION)d
    }

    CONFIG(release,debug|release) {
        DEFINES += QT_NO_WARNING_OUTPUT QT_NO_DEBUG_OUTPUT
        LIBS += -L"$(OPENCV_LIB_DIR)" \
            -lopencv_core$(OPENCV_VERSION) \
            -lopencv_highgui$(OPENCV_VERSION) \
            -lopencv_imgproc$(OPENCV_VERSION) \
            -lopencv_features2d$(OPENCV_VERSION) \
            -lopencv_calib3d$(OPENCV_VERSION) \
            -lopencv_contrib$(OPENCV_VERSION)
    }
}

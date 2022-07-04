QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -v
#LIBS += -fopenmp

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../src/NerualNetworkMLP/main.cpp \
#    ../src/NerualNetworkMLP/CustomWidget/qpainter.cpp \
    ../src/NerualNetworkMLP/Model/GNN/GNN.cpp \
    ../src/NerualNetworkMLP/Model/GNN/Neuron.cpp \
    ../src/NerualNetworkMLP/Model/GNN/Layer.cpp \
    ../src/NerualNetworkMLP/Model/Matrix.cpp \
    ../src/NerualNetworkMLP/Model/ActivateFunction.cpp \
    ../src/NerualNetworkMLP/View/viewapplication.cpp

HEADERS += \
#    ../src/NerualNetworkMLP/CustomWidget/qpainter.h \
    ../src/NerualNetworkMLP/Model/ActivateFunction.h \
    ../src/NerualNetworkMLP/Model/Matrix.h \
    ../src/NerualNetworkMLP/Model/Dataset.h \
    ../src/NerualNetworkMLP/Model/GNN/GNN.h \
    ../src/NerualNetworkMLP/Model/GNN/Neuron.h \
    ../src/NerualNetworkMLP/Model/constantValues.h \
    ../src/NerualNetworkMLP/Model/GNN/Layer.h \
    ../src/NerualNetworkMLP/View/viewapplication.h

FORMS += \
    ../src/NerualNetworkMLP/View/viewapplication.ui


RESOURCES += \
    ../src/NerualNetworkMLP/Resources/resources.qrc

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../src/NerualNetworkMLP/main.cpp \
    ../src/NerualNetworkMLP/Model/GNN/GNN.cpp \
    ../src/NerualNetworkMLP/Model/GNN/Neuron.cpp \
    ../src/NerualNetworkMLP/Model/GNN/Layer.cpp \
    ../src/NerualNetworkMLP/Model/MNN/Matrix.cpp \
    ../src/NerualNetworkMLP/Model/ActivateFunction.cpp \
    ../src/NerualNetworkMLP/Model/Dataset.cpp \
    ../src/NerualNetworkMLP/Model/MNN/MNN.cpp \
    ../src/NerualNetworkMLP/View/mainwindow.cpp \
    ../src/NerualNetworkMLP/View/DrawScene.cpp \
    ../src/NerualNetworkMLP/View/qcustomplot/qcustomplot.cpp \
    ../src/NerualNetworkMLP/View/PlotArea.cpp \
    ../src/NerualNetworkMLP/Controller/Controller.cpp \
    ../src/NerualNetworkMLP/View/ErrorDialog.cpp

HEADERS += \
    ../src/NerualNetworkMLP/Model/MNN/Matrix.h \
    ../src/NerualNetworkMLP/Model/GNN/GNN.h \
    ../src/NerualNetworkMLP/Model/GNN/Neuron.h \
    ../src/NerualNetworkMLP/Model/GNN/Layer.h  \
    ../src/NerualNetworkMLP/Model/Dataset.h \
    ../src/NerualNetworkMLP/Model/constantValues.h \
    ../src/NerualNetworkMLP/Model/ActivateFunction.h \
    ../src/NerualNetworkMLP/Model/MNN/MNN.h \
    ../src/NerualNetworkMLP/Model/Metrics.h \
    ../src/NerualNetworkMLP/Model/INerualNetwork.h \
    ../src/NerualNetworkMLP/View/mainwindow.h \
    ../src/NerualNetworkMLP/View/DrawScene.h \
    ../src/NerualNetworkMLP/View/qcustomplot/qcustomplot.h \
    ../src/NerualNetworkMLP/View/PlotArea.h \
    ../src/NerualNetworkMLP/Controller/Controller.h \
    ../src/NerualNetworkMLP/View/ErrorDialog.h

FORMS += \
    ../src/NerualNetworkMLP/View/mainwindow.ui \
    ../src/NerualNetworkMLP/View/PlotArea.ui \
    ../src/NerualNetworkMLP/View/ErrorDialog.ui

#FORMS += \
#    ../src/NerualNetworkMLP/View/viewapplication.ui

ICON = ../src/network.icns

#RESOURCES += \
#    ../src/NerualNetworkMLP/Resources/resources.qrc

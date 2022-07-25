QT       += core gui

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
    ../src/NerualNetworkMLP/Model/MNN/MNN.cpp

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
    ../src/NerualNetworkMLP/Model/INerualNetwork.h

#FORMS += \
#    ../src/NerualNetworkMLP/View/viewapplication.ui


#RESOURCES += \
#    ../src/NerualNetworkMLP/Resources/resources.qrc

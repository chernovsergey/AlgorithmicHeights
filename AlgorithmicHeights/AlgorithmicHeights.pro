TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
CONFIG += thread
SOURCES += main.cpp \
    test.cpp
HEADERS += \
    Lists/List.h \
    Sortings/Sortings.h \
    Heaps/BinaryHeap.h \
    Algorithms/Sortings/Sortings.h \
    DataStructures/Heaps/BinaryHeap.h \
    DataStructures/Lists/List.h \
    Algorithms/OrderStatistics/OrderStatistics.h \
    Algorithms/Sortings/Partials.h


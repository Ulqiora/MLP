#pragma once
#include <chrono>
struct Metrics {
    struct Solutions {
        int tp;
        int fp;
        int tn;
        int fn;
    };
    double precision;
    double recall;
    double accuracy;
    double fMeasure;
    Solutions solutions;
    int64_t seconds;
    void reset() {
        solutions.fn = 0;
        solutions.tp = 0;
        solutions.fp = 0;
        solutions.tn = 0;
        accuracy = 0;
    }
};

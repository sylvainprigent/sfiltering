/// \file SConvolve.h
/// \brief SConvolve class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2019

#pragma once

#include <string>
#include "sfilteringExport.h"

#include "simage/SImage.h"
#include "simage/SImageFilter.h"

/// \class SConvolve
/// \brief Convolve an image with another (smaller) image (called kernel)
class SFILTERING_EXPORT SConvolve : public SImageFilter{

public:
    SConvolve();
    ~SConvolve();

public:
    void setKernel(SImage* kernel);
    void setKernel(float* buffer, unsigned int sx, unsigned int sy, unsigned int sz = 1, unsigned int st = 1);

public:
    void run();

protected:
    void checkKernelSize();

protected:
    float* m_kernel;
    int m_ksx;
    int m_ksy;
    int m_ksz;
    int m_kst;
};

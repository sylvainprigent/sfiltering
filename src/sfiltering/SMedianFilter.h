/// \file SMedianFilter.h
/// \brief SMedianFilter class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2020

#pragma once

#include <string>
#include "sfilteringExport.h"

#include "simage/SImage.h"
#include "simage/SImageFilter.h"

/// \class SMedianFilter
/// \brief Smooth an image by replacing each pixel with the median value of it neighbors.
class SFILTERING_EXPORT SMedianFilter : public SImageFilter{

public:
    SMedianFilter();
    ~SMedianFilter();

public:
    void setRadius(unsigned int rx, unsigned int ry, unsigned int rz = 0, unsigned int rt = 0);

public:
    void run();

protected:
    int m_rx;
    int m_ry;
    int m_rz;
    int m_rt;
};

/// \file SVarianceFilter.h
/// \brief SVarianceFilter class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2020

#pragma once

#include <string>
#include "sfilteringExport.h"

#include "simage/SImage.h"
#include "simage/SImageFilter.h"

/// \class SVarianceFilter
/// \brief Calculate the image local variance by replacing each pixel with the variance of it neighbors.
class SFILTERING_EXPORT SVarianceFilter : public SImageFilter{

public:
    SVarianceFilter();
    ~SVarianceFilter();

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

/// \file SMeanFilter.h
/// \brief SMeanFilter class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2019

#pragma once

#include <string>
#include "sfilteringExport.h"

#include "simage/SImage.h"
#include "simage/SImageFilter.h"

/// \class SMeanFilter
/// \brief Smooth an image by replacing each pixel with the mean of it neighbors.
class SFILTERING_EXPORT SMeanFilter : public SImageFilter{

public:
    SMeanFilter();
    ~SMeanFilter();

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

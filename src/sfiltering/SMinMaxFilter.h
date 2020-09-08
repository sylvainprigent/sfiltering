/// \file SMinMaxFilter.h
/// \brief SMinMaxFilter class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2019

#pragma once

#include <string>
#include "sfilteringExport.h"

#include "simage/SImage.h"
#include "simage/SImageFilter.h"

/// \class SMinMaxFilter
/// \brief Calculate the image local variance by replacing each pixel with the variance of it neighbors.
class SFILTERING_EXPORT SMinMaxFilter : public SImageFilter{

public:
    SMinMaxFilter();
    ~SMinMaxFilter();

public:
    void setDirection(std::string value);
    void setRadius(unsigned int rx, unsigned int ry, unsigned int rz = 0, unsigned int rt = 0);

public:
    void run();

protected:
    std::string m_direction;
    int m_rx;
    int m_ry;
    int m_rz;
    int m_rt;
};

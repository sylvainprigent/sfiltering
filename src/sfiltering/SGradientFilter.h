/// \file SGradientFilter.h
/// \brief SGradientFilter class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2020

#pragma once

#include <string>

#include "sfilteringExport.h"

#include "simage/SImage.h"
#include "simage/SImageDimension.h"
#include "simage/SImageFilter.h"

/// \class SGradientFilter
/// \brief Calculate the gradient of an image.
class SFILTERING_EXPORT SGradientFilter : public SImageFilter{

public:
    SGradientFilter();
    ~SGradientFilter();

public:
    void setDimension(std::string dimension = SImageDimension::XY);

public:
    void run();

protected:
    void runXY();
    void runXYZ();
    void runXYT();
    void runXYZT();

protected:
    std::string m_dimension;
};

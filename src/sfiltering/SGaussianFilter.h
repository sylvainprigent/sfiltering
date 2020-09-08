/// \file SGaussianFilter.h
/// \brief SGaussianFilter class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2020

#pragma once

#include <string>
#include "sfilteringExport.h"

#include "simage/SImage.h"
#include "simage/SImageFilter.h"

/// \class SGaussianFilter
/// \brief Smooth an image by applying a gaussian filter on each 2D slices individualy.
class SFILTERING_EXPORT SGaussianFilter : public SImageFilter{

public:
    SGaussianFilter();
    ~SGaussianFilter();

public:
    void setSigma(float sigma);

public:
    void run();

protected:
    float m_sigma;
};

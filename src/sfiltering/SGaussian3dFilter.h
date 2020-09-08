/// \file SGaussian3dFilter.h
/// \brief SGaussian3dFilter class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2020

#pragma once

#include <string>
#include "sfilteringExport.h"

#include "simage/SImage.h"
#include "simage/SImageFilter.h"

/// \class SGaussian3dFilter
/// \brief Smooth an image by applying a 3D gaussian filter.
class SFILTERING_EXPORT SGaussian3dFilter : public SImageFilter{

public:
    SGaussian3dFilter();
    ~SGaussian3dFilter();

public:
    void setSigmaX(float sigmaX);
    void setSigmaY(float sigmaY);
    void setSigmaZ(float sigmaZ);

public:
    void run();

protected:
    float m_sigmaX;
    float m_sigmaY;
    float m_sigmaZ;
};

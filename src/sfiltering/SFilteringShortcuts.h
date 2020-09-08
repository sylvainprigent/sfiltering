/// \file SCoreShortcuts.h
/// \brief SCoreShortcuts class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2020

#pragma once

#include "simage/SImage.h"

/// \namespace SImg
/// \brief Shortut function to call modules functionalities
namespace SImg{

    SImage* convolve(SImage* image, SImage* kernel);
    SImage* gaussian3dFilter(SImage* image, float sigmaX, float sigmaY, float sigmaZ);
    SImage* gaussian2dFilter(SImage* image, float sigma);
    SImage* gradientMagnitude(SImage* image, std::string dimension);
    SImage* meanFilter(SImage* image, int radiusX, int radiusY, int radiusZ, int radiusT);
    SImage* medianFilter(SImage* image, int radiusX, int radiusY, int radiusZ, int radiusT);
    SImage* minMaxFilter(SImage* image, int radiusX, int radiusY, int radiusZ, int radiusT);
    SImage* varianceFilter(SImage* image, int radiusX, int radiusY, int radiusZ, int radiusT);

}

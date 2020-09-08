/// \file SCoreShortcuts.cpp
/// \brief SCoreShortcuts class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2020

#include "SFilteringShortcuts.h"

#include "SConvolve.h"
#include "SGaussian3dFilter.h"
#include "SGaussianFilter.h"
#include "SGradientFilter.h"
#include "SMeanFilter.h"
#include "SMedianFilter.h"
#include "SMinMaxFilter.h"
#include "SVarianceFilter.h"

namespace SImg {

SImage* convolve(SImage* image, SImage* kernel){
    SConvolve process;
    process.setInput(image);
    process.setKernel(kernel);
    process.run();
    return process.getOutput();
}

SImage* gaussian3dFilter(SImage* image, float sigmaX, float sigmaY, float sigmaZ){
    SGaussian3dFilter process;
    process.setInput(image);
    process.setSigmaX(sigmaX);
    process.setSigmaY(sigmaY);
    process.setSigmaZ(sigmaZ);
    process.run();
    return process.getOutput();
}

SImage* gaussian2dFilter(SImage* image, float sigma){
    SGaussianFilter process;
    process.setInput(image);
    process.setSigma(sigma);
    process.run();
    return process.getOutput();
}

SImage* gradientMagnitude(SImage* image, std::string dimension){
    SGradientFilter process;
    process.setInput(image);
    process.setDimension(dimension);
    process.run();
    return process.getOutput();
}

SImage* meanFilter(SImage* image, int radiusX, int radiusY, int radiusZ, int radiusT){
    SMeanFilter process;
    process.setInput(image);
    process.setRadius(radiusX, radiusY, radiusZ, radiusT);
    process.run();
    return process.getOutput();
}

SImage* medianFilter(SImage* image, int radiusX, int radiusY, int radiusZ, int radiusT){
    SMedianFilter process;
    process.setInput(image);
    process.setRadius(radiusX, radiusY, radiusZ, radiusT);
    process.run();
    return process.getOutput();
}

SImage* minMaxFilter(SImage* image, int radiusX, int radiusY, int radiusZ, int radiusT){
    SMinMaxFilter process;
    process.setInput(image);
    process.setRadius(radiusX, radiusY, radiusZ, radiusT);
    process.run();
    return process.getOutput();
}

SImage* varianceFilter(SImage* image, int radiusX, int radiusY, int radiusZ, int radiusT){
    SVarianceFilter process;
    process.setInput(image);
    process.setRadius(radiusX, radiusY, radiusZ, radiusT);
    process.run();
    return process.getOutput();
}

}

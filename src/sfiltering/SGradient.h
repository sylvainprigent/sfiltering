/// \file gradient.h
/// \brief gradient class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2020

#pragma once

#include <vector>

#include "sfilteringExport.h"

#include "simage/SImageProcess.h"
#include "simage/SImage.h"

/// \class gradient
/// \brief Calculate image gradient norm on all an image.
class SFILTERING_EXPORT SGradient : public SImageProcess{

public:
    SGradient();
    ~SGradient();

public:
    void run();
    std::vector<SImage*> getOutput();
    SImage* getL2();
    SImage* getL1();
    float getNormL1();
    float getNormL2();

protected:
    void calculate2DGradient();
    void calculate3DGradient();

public:
    std::vector<SImage*> m_gradients;
    float m_normL1;
    float m_normL2;

};

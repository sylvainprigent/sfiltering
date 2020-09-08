/// \file SGradientFilter.cpp
/// \brief SGradientFilter class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2019

#include "SGradientFilter.h"
#include "score/SException.h"
#include "math.h"

#ifdef SL_USE_OPENMP
#include "omp.h"
#endif

SGradientFilter::SGradientFilter() : SImageFilter(){
    m_processName = "SGradientFilter";
    m_processPrecision = 32;
    m_processZ = true;
    m_processT = true;
    m_processC = true;

    m_dimension = SImageDimension::XY;
}

SGradientFilter::~SGradientFilter(){

}

void SGradientFilter::setDimension(std::string dimension){
    m_dimension = dimension;
}

void SGradientFilter::run(){

    if ( m_dimension == SImageDimension::XY ){
        this->runXY();
    }
    else if ( m_dimension == SImageDimension::XYZ ){
        this->runXYZ();
    }
    else if ( m_dimension == SImageDimension::XYT ){
        this->runXYT();
    }
    else if ( m_dimension == SImageDimension::XYZT ){
        this->runXYZT();
    }

}

void SGradientFilter::runXY(){
    // image info
    int sx = int(m_input->getSizeX());
    int sy = int(m_input->getSizeY());
    int sz = int(m_input->getSizeZ());
    int st = int(m_input->getSizeT());
    int sc = int(m_input->getSizeC());

    float* inputBuffer = dynamic_cast<SImageFloat*>(m_input)->getBuffer();
    float* outputBuffer = new float[m_input->getBufferSize()];
    float x_m1, x_p1, y_m1, y_p1;
    for (int c = 0 ; c < sc ; c++){
#pragma omp parallel for
        for (int x = 1 ; x < sx-1 ; x++){
            for (int y = 1 ; y < sy-1 ; y++){
                for (int z = 0 ; z < sz ; z++){
                    for (int t = 0 ; t < st ; t++){
                        x_m1 = inputBuffer[c + sc*(t + st*(z + sz*(y + sy*(x-1))))];
                        x_p1 = inputBuffer[c + sc*(t + st*(z + sz*(y + sy*(x+1))))];
                        y_m1 = inputBuffer[c + sc*(t + st*(z + sz*((y-1) + sy*x)))];
                        y_p1 = inputBuffer[c + sc*(t + st*(z + sz*((y+1) + sy*x)))];

                        outputBuffer[c + sc*(t + st*(z + sz*(y + sy*x)))] = float(sqrt( pow(x_m1 - x_p1,2.0) + pow(y_m1 - y_p1, 2.0) ));
                    }
                }
            }
        }

    }
    m_output = new SImageFloat(outputBuffer, unsigned(sx), unsigned(sy), unsigned(sz), unsigned(st), unsigned(sc));
}

void SGradientFilter::runXYZ(){
    // image info
    int sx = int(m_input->getSizeX());
    int sy = int(m_input->getSizeY());
    int sz = int(m_input->getSizeZ());
    int st = int(m_input->getSizeT());
    int sc = int(m_input->getSizeC());

    float* inputBuffer = dynamic_cast<SImageFloat*>(m_input)->getBuffer();
    float* outputBuffer = new float[m_input->getBufferSize()];
    float x_m1, x_p1, y_m1, y_p1, z_m1, z_p1;
    for (int c = 0 ; c < sc ; c++){

        for (int x = 1 ; x < sx-1 ; x++){
            for (int y = 1 ; y < sy-1 ; y++){
                for (int z = 1 ; z < sz-1 ; z++){
                    for (int t = 0 ; t < st ; t++){
                        x_m1 = inputBuffer[c + sc*(t + st*(z + sz*(y + sy*(x-1))))];
                        x_p1 = inputBuffer[c + sc*(t + st*(z + sz*(y + sy*(x+1))))];
                        y_m1 = inputBuffer[c + sc*(t + st*(z + sz*((y-1) + sy*x)))];
                        y_p1 = inputBuffer[c + sc*(t + st*(z + sz*((y+1) + sy*x)))];
                        z_m1 = inputBuffer[c + sc*(t + st*(z-1 + sz*(y + sy*x)))];
                        z_p1 = inputBuffer[c + sc*(t + st*(z+1 + sz*(y + sy*x)))];

                        outputBuffer[c + sc*(t + st*(z + sz*(y + sy*x)))] = float(sqrt( pow(x_m1 - x_p1,2.0) + pow(y_m1 - y_p1, 2.0) + pow(z_m1 - z_p1, 2.0)));
                    }
                }
            }
        }

    }
    m_output = new SImageFloat(outputBuffer, unsigned(sx), unsigned(sy), unsigned(sz), unsigned(st), unsigned(sc));
}

void SGradientFilter::runXYT(){
    // image info
    int sx = int(m_input->getSizeX());
    int sy = int(m_input->getSizeY());
    int sz = int(m_input->getSizeZ());
    int st = int(m_input->getSizeT());
    int sc = int(m_input->getSizeC());

    float* inputBuffer = dynamic_cast<SImageFloat*>(m_input)->getBuffer();
    float* outputBuffer = new float[m_input->getBufferSize()];
    float x_m1, x_p1, y_m1, y_p1, t_m1, t_p1;
    for (int c = 0 ; c < sc ; c++){

        for (int x = 1 ; x < sx-1 ; x++){
            for (int y = 1 ; y < sy-1 ; y++){
                for (int z = 0 ; z < sz ; z++){
                    for (int t = 1 ; t < st-1 ; t++){
                        x_m1 = inputBuffer[c + sc*(t + st*(z + sz*(y + sy*(x-1))))];
                        x_p1 = inputBuffer[c + sc*(t + st*(z + sz*(y + sy*(x+1))))];
                        y_m1 = inputBuffer[c + sc*(t + st*(z + sz*((y-1) + sy*x)))];
                        y_p1 = inputBuffer[c + sc*(t + st*(z + sz*((y+1) + sy*x)))];
                        t_m1 = inputBuffer[c + sc*(t-1 + st*(z + sz*(y + sy*x)))];
                        t_p1 = inputBuffer[c + sc*(t+1 + st*(z + sz*(y + sy*x)))];

                        outputBuffer[c + sc*(t + st*(z + sz*(y + sy*x)))] = float(sqrt( pow(x_m1 - x_p1,2.0) + pow(y_m1 - y_p1, 2.0) + pow(t_m1 - t_p1, 2.0)));
                    }
                }
            }
        }

    }
    m_output = new SImageFloat(outputBuffer, unsigned(sx), unsigned(sy), unsigned(sz), unsigned(st), unsigned(sc));
}

void SGradientFilter::runXYZT(){
    // image info
    int sx = int(m_input->getSizeX());
    int sy = int(m_input->getSizeY());
    int sz = int(m_input->getSizeZ());
    int st = int(m_input->getSizeT());
    int sc = int(m_input->getSizeC());

    float* inputBuffer = dynamic_cast<SImageFloat*>(m_input)->getBuffer();
    float* outputBuffer = new float[m_input->getBufferSize()];
    float x_m1, x_p1, y_m1, y_p1, z_m1, z_p1, t_m1, t_p1;
    for (int c = 0 ; c < sc ; c++){

        for (int x = 1 ; x < sx-1 ; x++){
            for (int y = 1 ; y < sy-1 ; y++){
                for (int z = 1 ; z < sz-1 ; z++){
                    for (int t = 1 ; t < st-1 ; t++){
                        x_m1 = inputBuffer[c + sc*(t + st*(z + sz*(y + sy*(x-1))))];
                        x_p1 = inputBuffer[c + sc*(t + st*(z + sz*(y + sy*(x+1))))];
                        y_m1 = inputBuffer[c + sc*(t + st*(z + sz*((y-1) + sy*x)))];
                        y_p1 = inputBuffer[c + sc*(t + st*(z + sz*((y+1) + sy*x)))];
                        z_m1 = inputBuffer[c + sc*(t + st*(z-1 + sz*(y + sy*x)))];
                        z_p1 = inputBuffer[c + sc*(t + st*(z+1 + sz*(y + sy*x)))];
                        t_m1 = inputBuffer[c + sc*(t-1 + st*(z + sz*(y + sy*x)))];
                        t_p1 = inputBuffer[c + sc*(t+1 + st*(z + sz*(y + sy*x)))];

                        outputBuffer[c + sc*(t + st*(z + sz*(y + sy*x)))] = float(sqrt( pow(x_m1 - x_p1,2.0) + pow(y_m1 - y_p1, 2.0) + pow(z_m1 - z_p1, 2.0) + pow(t_m1 - t_p1, 2.0)));
                    }
                }
            }
        }

    }
    m_output = new SImageFloat(outputBuffer, unsigned(sx), unsigned(sy), unsigned(sz), unsigned(st), unsigned(sc));
}

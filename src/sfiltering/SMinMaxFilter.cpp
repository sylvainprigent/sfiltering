/// \file SMinMaxFilter.cpp
/// \brief SMinMaxFilter class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2019

#include "SMinMaxFilter.h"
#include "score/SException.h"
#include "score/SMath.h"

#ifdef SL_USE_OPENMP
#include "omp.h"
#endif

SMinMaxFilter::SMinMaxFilter() : SImageFilter(){
    m_processName = "SMinMaxFilter";
    m_processPrecision = 32;
    m_processZ = true;
    m_processT = true;
    m_processC = true;

    m_direction = "max";
}

SMinMaxFilter::~SMinMaxFilter(){

}

void SMinMaxFilter::setDirection(std::string value){
    m_direction = value;
}

void SMinMaxFilter::setRadius(unsigned int rx, unsigned int ry, unsigned int rz, unsigned int rt){
    m_rx = int(rx);
    m_ry = int(ry);
    m_rz = int(rz);
    m_rt = int(rt);
}

void SMinMaxFilter::run(){

    // image info
    int sx = int(m_input->getSizeX());
    int sy = int(m_input->getSizeY());
    int sz = int(m_input->getSizeZ());
    int st = int(m_input->getSizeT());
    int sc = int(m_input->getSizeC());

    float* inputBuffer = dynamic_cast<SImageFloat*>(m_input)->getBuffer();
    float* outputBuffer = new float[m_input->getBufferSize()];
    float value, v;


    if (m_direction == "min"){
        float min = SMath::FMAX;

        for (int c = 0 ; c < sc ; c++){
#pragma omp parallel for
            for (int x = m_rx ; x < sx-m_rx ; x++){
                for (int y = m_ry ; y < sy-m_ry ; y++){
                    for (int z = m_rz ; z < sz-m_rz ; z++){
                        for (int t = m_rt ; t < st-m_rt ; t++){

                            value = min;
                            for (int fx = -m_rx ; fx <= m_rx ; fx++){
                                for (int fy = -m_ry ; fy <= m_ry ; fy++){
                                    for (int fz = -m_rz ; fz <= m_rz ; fz++){
                                        for (int ft = -m_rt ; ft <= m_rt ; ft++){
                                            v = inputBuffer[c + sc*((t-ft) + st*((z-fz) + sz*((y-fy) + sy*(x-fx))))];
                                            if (v < value){
                                                value = v;
                                            }
                                        }
                                    }
                                }
                            }
                            outputBuffer[c + sc*(t + st*(z + sz*(y + sy*x)))] = value;
                        }
                    }
                }
            }

        }
    }
    else if (m_direction == "max"){
        float max = SMath::FMIN;

        for (int c = 0 ; c < sc ; c++){
#pragma omp parallel for
            for (int x = m_rx ; x < sx-m_rx ; x++){
                for (int y = m_ry ; y < sy-m_ry ; y++){
                    for (int z = m_rz ; z < sz-m_rz ; z++){
                        for (int t = m_rt ; t < st-m_rt ; t++){

                            value = max;
                            for (int fx = -m_rx ; fx <= m_rx ; fx++){
                                for (int fy = -m_ry ; fy <= m_ry ; fy++){
                                    for (int fz = -m_rz ; fz <= m_rz ; fz++){
                                        for (int ft = -m_rt ; ft <= m_rt ; ft++){
                                            v = inputBuffer[c + sc*((t-ft) + st*((z-fz) + sz*((y-fy) + sy*(x-fx))))];
                                            if (v > value){
                                                value = v;
                                            }
                                        }
                                    }
                                }
                            }
                            outputBuffer[c + sc*(t + st*(z + sz*(y + sy*x)))] = value;
                        }
                    }
                }
            }

        }
    }
    else{
        throw SException("SMinMaxFilter direction must be 'min' or 'max'");
    }

    m_output = new SImageFloat(outputBuffer, unsigned(sx), unsigned(sy), unsigned(sz), unsigned(st), unsigned(sc));
}

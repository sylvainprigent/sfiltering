/// \file SMeanFilter.cpp
/// \brief SMeanFilter class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2019

#include "SMeanFilter.h"
#include "score/SException.h"

#ifdef SL_USE_OPENMP
#include "omp.h"
#endif

SMeanFilter::SMeanFilter() : SImageFilter(){
    m_processName = "SMeanFilter";
    m_processPrecision = 32;
    m_processZ = true;
    m_processT = true;
    m_processC = true;
}

SMeanFilter::~SMeanFilter(){

}

void SMeanFilter::setRadius(unsigned int rx, unsigned int ry, unsigned int rz, unsigned int rt){
    m_rx = int(rx);
    m_ry = int(ry);
    m_rz = int(rz);
    m_rt = int(rt);
}

void SMeanFilter::run(){

    // image info
    int sx = int(m_input->getSizeX());
    int sy = int(m_input->getSizeY());
    int sz = int(m_input->getSizeZ());
    int st = int(m_input->getSizeT());
    int sc = int(m_input->getSizeC());

    float* inputBuffer = dynamic_cast<SImageFloat*>(m_input)->getBuffer();
    float* outputBuffer = new float[m_input->getBufferSize()];
    float filterSize = (2*m_rx+1)*(2*m_ry+1)*(2*m_rz+1)*(2*m_rt+1);
    float val;

#pragma omp parallel for
    for (int i = 0 ; i < sx*sy*sz*st*sc ; i++){
        outputBuffer[i] = 0;
    }

    for (int c = 0 ; c < sc ; c++){
#pragma omp parallel for
        for (int x = m_rx ; x < sx-m_rx ; x++){
            for (int y = m_ry ; y < sy-m_ry ; y++){
                for (int z = m_rz ; z < sz-m_rz ; z++){
                    for (int t = m_rt ; t < st-m_rt ; t++){
                        val = 0.0;
                        for (int fx = -m_rx ; fx <= m_rx ; fx++){
                            for (int fy = -m_ry ; fy <= m_ry ; fy++){
                                for (int fz = -m_rz ; fz <= m_rz ; fz++){
                                    for (int ft = -m_rt ; ft <= m_rt ; ft++){
                                        val += inputBuffer[c + sc*((t-ft) + st*((z-fz) + sz*((y-fy) + sy*(x-fx))))];
                                    }
                                }
                            }
                        }
                        outputBuffer[c + sc*(t + st*(z + sz*(y + sy*x)))] = val/filterSize;
                    }
                }
            }
        }

    }
    m_output = new SImageFloat(outputBuffer, unsigned(sx), unsigned(sy), unsigned(sz), unsigned(st), unsigned(sc));
}

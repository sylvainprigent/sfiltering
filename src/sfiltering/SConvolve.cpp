/// \file SConvolve.cpp
/// \brief SConvolve class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2020

#include "SConvolve.h"
#include "score/SException.h"

#ifdef SL_USE_OPENMP
#include "omp.h"
#endif

SConvolve::SConvolve() : SImageFilter(){
    m_processName = "SConvolve";
    m_processPrecision = 32;
    m_processZ = true;
    m_processT = true;
    m_processC = true;
}

SConvolve::~SConvolve(){

}

void SConvolve::setKernel(SImage* kernel){
    m_kernel = dynamic_cast<SImageFloat*>(kernel)->getBuffer();
    m_ksx = kernel->getSizeX();
    m_ksy = kernel->getSizeY();
    m_ksz = kernel->getSizeZ();
    m_kst = kernel->getSizeT();

    this->checkKernelSize();
}

void SConvolve::setKernel(float* buffer, unsigned int sx, unsigned int sy, unsigned int sz, unsigned int st){
    m_kernel = buffer;
    m_ksx = int(sx);
    m_ksy = int(sy);
    m_ksz = int(sz);
    m_kst = int(st);

    this->checkKernelSize();
}

void SConvolve::checkKernelSize(){
    if (  !(m_ksx & 1) || !(m_ksy & 1) || !(m_ksz & 1 || !(m_kst & 1)) ) {
        throw SException(std::string("The kernel must be odd").c_str());
    }
}

void SConvolve::run(){

    // image info
    int sx = int(m_input->getSizeX());
    int sy = int(m_input->getSizeY());
    int sz = int(m_input->getSizeZ());
    int st = int(m_input->getSizeT());
    int sc = int(m_input->getSizeC());

    float* inputBuffer = dynamic_cast<SImageFloat*>(m_input)->getBuffer();
    float* outputBuffer = new float[m_input->getBufferSize()];

    int halfX = m_ksx/2;
    int halfY = m_ksy/2;
    int halfZ = 0;
    if (m_ksz > 1 ){
        halfZ = m_ksz/2;
    }
    int halfT = 0;
    if (m_kst > 1 ){
        halfT = m_kst/2;
    }

    float val;
    for (int c = 0 ; c < sc ; c++){

#pragma omp parallel for
        for (int x = halfX ; x < sx-halfX ; x++){
            for (int y = halfY ; y < sy-halfY ; y++){
                for (int z = halfZ ; z < sz-halfZ ; z++){
                    for (int t = halfT ; t < st-halfT ; t++){

                        val = 0.0;
                        for (int fx = -halfX ; fx <= halfX ; fx++){
                            for (int fy = -halfY ; fy <= halfY ; fy++){
                                for (int fz = -halfZ ; fz <= halfZ ; fz++){
                                    for (int ft = -halfT ; ft <= halfT ; ft++){
                                        val += inputBuffer[c + sc*(t+ft + st*(z+fz + sz*((y+fy)) + sy*(x+fx)))] * m_kernel[t+halfT + m_kst*(z+halfZ + m_ksz*((y+halfY)) + m_ksy*(x+halfX))];
                                    }
                                }
                            }
                        }
                        outputBuffer[c + sc*(t + st*(z + sz*(y + sy*x)))] = val;

                    }
                }
            }
        }
    }
    m_output = new SImageFloat(outputBuffer, unsigned(sx), unsigned(sy), unsigned(sz), unsigned(st), unsigned(sc));
}

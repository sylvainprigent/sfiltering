/// \file SGaussianFilter.cpp
/// \brief SGaussianFilter class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2020

#include "SGaussianFilter.h"
#include "score/SException.h"
#include "score/SMath.h"
#include "math.h"

#ifdef SL_USE_OPENMP
#include "omp.h"
#endif

SGaussianFilter::SGaussianFilter() : SImageFilter(){
    m_processName = "SGaussianFilter";
    m_processPrecision = 32;
    m_processZ = true;
    m_processT = true;
    m_processC = true;

    m_sigma = 1;
}

SGaussianFilter::~SGaussianFilter(){

}

void SGaussianFilter::setSigma(float sigma){
    m_sigma = sigma;

    if ( sigma < 0 ){
        throw SException("SGaussianFilter: sigma must be positive");
    }
}

void SGaussianFilter::run(){

    // compute the kernel

    float sigma2 = m_sigma*m_sigma;
    int halfSizeGF = int(0.5+sqrt( double(2*double(sigma2)*log( double(300) ) )  ) );
    int sizeGF = 2*halfSizeGF+1;
    float norm = float( sqrt( double(1/(2*SMath::PI*sigma2) ) ) );


    float *kernel = new float[sizeGF*sizeGF];
    for (int i = - halfSizeGF; i <= halfSizeGF ; i++ ){
        for (int j = - halfSizeGF; j <= halfSizeGF ; j++ ){

            kernel[sizeGF*(i+halfSizeGF)+(j+halfSizeGF)] = norm*exp( - i*i/(2*sigma2) - j*j/(2*sigma2)  );
        }
    }

    // image info
    int sx = int(m_input->getSizeX());
    int sy = int(m_input->getSizeY());
    int sz = int(m_input->getSizeZ());
    int st = int(m_input->getSizeT());
    int sc = int(m_input->getSizeC());

    float* inputBuffer = dynamic_cast<SImageFloat*>(m_input)->getBuffer();
    float* outputBuffer = new float[m_input->getBufferSize()];
    float val;
    for (int c = 0 ; c < sc ; c++){
        for (int t = 0 ; t < st ; t++){
            for (int z = 0 ; z < sz ; z++){

#pragma omp parallel for
                for (int x = halfSizeGF ; x <= sx-halfSizeGF ; x++){
                    for (int y = halfSizeGF ; y <= sy-halfSizeGF ; y++){

                        val = 0;
                        for (int fx = -halfSizeGF ; fx < halfSizeGF ; fx++ ){
                            for (int fy = -halfSizeGF ; fy < halfSizeGF ; fy++ ){
                                val += inputBuffer[c + sc*(t + st*(z + sz*((y+fy) + sy*(x+fx))))]*kernel[sizeGF*(fx+halfSizeGF)+(fy+halfSizeGF)];
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

/// \file SGaussian3dFilter.cpp
/// \brief SGaussian3dFilter class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2020

#include "SGaussian3dFilter.h"
#include "score/SException.h"
#include "math.h"

#ifdef SL_USE_OPENMP
#include "omp.h"
#endif

SGaussian3dFilter::SGaussian3dFilter() : SImageFilter(){
    m_processName = "SGaussian3dFilter";
    m_processPrecision = 32;
    m_processZ = true;
    m_processT = true;
    m_processC = true;

    m_sigmaX = 1;
    m_sigmaY = 1;
    m_sigmaZ = 1;
}

SGaussian3dFilter::~SGaussian3dFilter(){

}

void SGaussian3dFilter::setSigmaX(float sigmaX){
    m_sigmaX = sigmaX;

    if ( sigmaX < 0 ){
        throw SException("SGaussian3dFilter: sigmaX must be positive");
    }
}

void SGaussian3dFilter::setSigmaY(float sigmaY){
    m_sigmaY = sigmaY;

    if ( sigmaY < 0 ){
        throw SException("SGaussian3dFilter: sigmaY must be positive");
    }
}

void SGaussian3dFilter::setSigmaZ(float sigmaZ){
    m_sigmaZ = sigmaZ;

    if ( sigmaZ < 0 ){
        throw SException("SGaussian3dFilter: sigmaZ must be positive");
    }
}

void SGaussian3dFilter::run(){

    // compute the kernel

    float sigmaX2 = m_sigmaX*m_sigmaX;
    float sigmaY2 = m_sigmaY*m_sigmaY;
    float sigmaZ2 = m_sigmaZ*m_sigmaZ;
    int halfX = int(0.5+sqrt( double(2*double(sigmaX2)*log( double(300) ) )  ) );
    int halfY = int(0.5+sqrt( double(2*double(sigmaY2)*log( double(300) ) )  ) );
    int halfZ = int(0.5+sqrt( double(2*double(sigmaZ2)*log( double(300) ) )  ) );
    int sizeX = 2*halfX+1;
    int sizeY = 2*halfY+1;
    int sizeZ = 2*halfZ+1;


    float *kernel = new float[sizeX*sizeY*sizeZ];
    float norm = 0;
    float kv;
    for (int i = - halfX; i <= halfX ; i++ ){
        for (int j = - halfY; j <= halfY ; j++ ){
            for (int k = - halfZ; k <= halfZ ; k++ ){

                kv = exp( - i*i/(2*sigmaX2) - j*j/(2*sigmaY2) - k*k/(2*sigmaZ2)  );
                kernel[k* sizeZ*(sizeY*i*j)] = kv;
                norm += kv;
            }
        }
    }
    for (int i = 0 ; i < sizeX*sizeY*sizeZ ; i++){
        kernel[i] /= norm;
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

#pragma omp parallel for
                for (int x = halfX ; x <= sx-halfX ; x++){
                    for (int y = halfY ; y <= sy-halfY ; y++){
                        for (int z = halfZ ; z < sz-halfZ ; z++){

                        val = 0;
                        for (int fx = -halfX ; fx < halfX ; fx++ ){
                            for (int fy = -halfY ; fy < halfY ; fy++ ){
                                for (int fz = -halfZ ; fz < halfZ ; fz++ ){
                                    val += inputBuffer[c + sc*(t + st*(z+fz + sz*((y+fy) + sy*(x+fx))))]*kernel[fz+halfZ + sizeZ*(sizeY*(fx+halfX)+(fy+halfY))];

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

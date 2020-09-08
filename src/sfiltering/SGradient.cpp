/// \file SGradient.cpp
/// \brief SGradient class
/// \author Sylvain Prigent
/// \version 0.1
/// \date 2018

#include "math.h"

#include "SGradient.h"
#include "simage/SImageFloat.h"

SGradient::SGradient() : SImageProcess(){
    m_processName = "SGradient";
    m_processZ = true;
    m_processT = true;
    m_processC = true;
    m_processPrecision = 32;

    m_normL1 = -1;
    m_normL2 = -1;
}

SGradient::~SGradient(){

}

void SGradient::run(){

    if (m_input->getSizeZ() == 1){
        this->calculate2DGradient();
    }
    else{
        this->calculate3DGradient();
    }

}

void SGradient::calculate2DGradient(){
    float * buffer = dynamic_cast<SImageFloat*>(m_input)->getBuffer();
    unsigned int sc = m_input->getSizeC();
    unsigned int st = m_input->getSizeT();
    unsigned int sz =1;
    unsigned int sy = m_input->getSizeY();
    unsigned int sx = m_input->getSizeX();
    unsigned int z = 0;

    float *bufferGx = new float[m_input->getBufferSize()];
    float *bufferGy = new float[m_input->getBufferSize()];
    for (unsigned int c = 0 ; c < sc ; c++){
        for (unsigned int t = 0 ; t < st ; t++){
            // gradient x, y
            for (unsigned int x = 1 ; x < sx-1 ; x++){
                for (unsigned int y = 1 ; y < sy-1 ; y++){
                    //buffer[ c + sc*(t + st*(z + sz*(y + sy*x)))];
                    bufferGx[c + sc*(t + st*(z + sz*(y + sy*x)))] = buffer[ c + sc*(t + st*(z + sz*(y + sy*(x+1))))] - buffer[ c + sc*(t + st*(z + sz*(y + sy*(x-1))))];
                    bufferGy[c + sc*(t + st*(z + sz*(y + sy*x)))] = buffer[ c + sc*(t + st*(z + sz*(y+1 + sy*x)))] - buffer[ c + sc*(t + st*(z + sz*(y-1 + sy*x)))];
                }
            }

            // set borders to 0.0
            for (unsigned int y = 0 ; y <  sy ; y++){
                bufferGx[c + sc*(t + st*(z + sz*(y + sy*0)))] = 0.0;
                bufferGx[c + sc*(t + st*(z + sz*(y + sy*(sx-1))))] = 0.0;
                bufferGy[c + sc*(t + st*(z + sz*(y + sy*0)))] = 0.0;
                bufferGy[c + sc*(t + st*(z + sz*(y + sy*(sx-1))))] = 0.0;
            }
            for (unsigned int x = 0 ; x <  sx ; x++){
                bufferGx[c + sc*(t + st*(z + sz*(0 + sy*x)))] = 0.0;
                bufferGx[c + sc*(t + st*(z + sz*(sy-1 + sy*x)))] = 0.0;
                bufferGy[c + sc*(t + st*(z + sz*(0 + sy*x)))] = 0.0;
                bufferGy[c + sc*(t + st*(z + sz*(sy-1 + sy*x)))] = 0.0;
            }
        }
    }
    m_gradients.clear();
    m_gradients.push_back(new SImageFloat(bufferGx, sx, sy, sz, st, sc));
    m_gradients.push_back(new SImageFloat(bufferGy, sx, sy, sz, st, sc));
}

void SGradient::calculate3DGradient(){
    float * buffer = dynamic_cast<SImageFloat*>(m_input)->getBuffer();
    unsigned int sc = m_input->getSizeC();
    unsigned int st = m_input->getSizeT();
    unsigned int sz =1;
    unsigned int sy = m_input->getSizeY();
    unsigned int sx = m_input->getSizeX();

    float *bufferGx = new float[m_input->getBufferSize()];
    float *bufferGy = new float[m_input->getBufferSize()];
    float *bufferGz = new float[m_input->getBufferSize()];
    for (unsigned int c = 0 ; c < sc ; c++){
        for (unsigned int t = 0 ; t < st ; t++){
            // gradient x, y, z
            for (unsigned int z = 1 ; z < sz-1 ; z++){
                for (unsigned int x = 1 ; x < sx-1 ; x++){
                    for (unsigned int y = 1 ; y < sy-1 ; y++){
                        bufferGx[c + sc*(t + st*(z + sz*(y + sy*x)))] = buffer[ c + sc*(t + st*(z + sz*(y + sy*(x+1))))] - buffer[ c + sc*(t + st*(z + sz*(y + sy*(x-1))))];
                        bufferGy[c + sc*(t + st*(z + sz*(y + sy*x)))] = buffer[ c + sc*(t + st*(z + sz*(y+1 + sy*x)))] - buffer[ c + sc*(t + st*(z + sz*(y-1 + sy*x)))];
                        bufferGz[c + sc*(t + st*(z + sz*(y + sy*x)))] = buffer[ c + sc*(t + st*(z+1 + sz*(y + sy*x)))] - buffer[ c + sc*(t + st*(z-1 + sz*(y + sy*x)))];
                    }
                }
            }
            // set borders to 0.0
            for (unsigned int z = 0 ; z < sz ; z++){
                for (unsigned int y = 0 ; y <  sy ; y++){
                    bufferGx[c + sc*(t + st*(z + sz*(y + sy*0)))] = 0.0;
                    bufferGx[c + sc*(t + st*(z + sz*(y + sy*(sx-1))))] = 0.0;
                    bufferGy[c + sc*(t + st*(z + sz*(y + sy*0)))] = 0.0;
                    bufferGy[c + sc*(t + st*(z + sz*(y + sy*(sx-1))))] = 0.0;
                    bufferGz[c + sc*(t + st*(z + sz*(y + sy*0)))] = 0.0;
                    bufferGz[c + sc*(t + st*(z + sz*(y + sy*(sx-1))))] = 0.0;
                }
                for (unsigned int x = 0 ; x <  sx ; x++){
                    bufferGx[c + sc*(t + st*(z + sz*(0 + sy*x)))] = 0.0;
                    bufferGx[c + sc*(t + st*(z + sz*(sy-1 + sy*x)))] = 0.0;
                    bufferGy[c + sc*(t + st*(z + sz*(0 + sy*x)))] = 0.0;
                    bufferGy[c + sc*(t + st*(z + sz*(sy-1 + sy*x)))] = 0.0;
                    bufferGz[c + sc*(t + st*(z + sz*(0 + sy*x)))] = 0.0;
                    bufferGz[c + sc*(t + st*(z + sz*(sy-1 + sy*x)))] = 0.0;
                }
            }

        }
    }
    m_gradients.clear();
    m_gradients.push_back(new SImageFloat(bufferGx, sx, sy, sz, st, sc));
    m_gradients.push_back(new SImageFloat(bufferGy, sx, sy, sz, st, sc));
    m_gradients.push_back(new SImageFloat(bufferGz, sx, sy, sz, st, sc));
}

std::vector<SImage*> SGradient::getOutput(){
    return m_gradients;
}

SImage* SGradient::getL2(){

    unsigned long bs = m_input->getBufferSize();
    float *magBuffer = new float[bs];
    float val;
    m_normL2 = 0.0;

    if (m_input->getSizeZ() == 1){
        float* bufferGx = dynamic_cast<SImageFloat*>(m_gradients[0])->getBuffer();
        float* bufferGy = dynamic_cast<SImageFloat*>(m_gradients[1])->getBuffer();
        for (unsigned long i = 0 ; i < bs ; i++){
            val = sqrt(bufferGx[i]*bufferGx[i] + bufferGy[i]*bufferGy[i]);
            magBuffer[i] = val;
            m_normL2 +=val;
        }
    }
    else{
        float* bufferGx = dynamic_cast<SImageFloat*>(m_gradients[0])->getBuffer();
        float* bufferGy = dynamic_cast<SImageFloat*>(m_gradients[1])->getBuffer();
        float* bufferGz = dynamic_cast<SImageFloat*>(m_gradients[1])->getBuffer();
        for (unsigned long i = 0 ; i < bs ; i++){
            val = sqrt(bufferGx[i]*bufferGx[i] + bufferGy[i]*bufferGy[i] + bufferGz[i]*bufferGz[i] );
            magBuffer[i] = val;
            m_normL2 +=val;
        }
    }
    return new SImageFloat(magBuffer, m_input->getSizeX(),  m_input->getSizeY(), m_input->getSizeZ(), m_input->getSizeT(), m_input->getSizeC() );
}

SImage* SGradient::getL1(){

    unsigned long bs = m_input->getBufferSize();
    float *magBuffer = new float[bs];
    float val;
    m_normL1 = 0.0;

    if (m_input->getSizeZ() == 1){
        float* bufferGx = dynamic_cast<SImageFloat*>(m_gradients[0])->getBuffer();
        float* bufferGy = dynamic_cast<SImageFloat*>(m_gradients[1])->getBuffer();
        for (unsigned long i = 0 ; i < bs ; i++){
            val = fabs(bufferGx[i]) + fabs(bufferGy[i]);
            magBuffer[i] = val;
            m_normL1 +=val;
        }
    }
    else{
        float* bufferGx = dynamic_cast<SImageFloat*>(m_gradients[0])->getBuffer();
        float* bufferGy = dynamic_cast<SImageFloat*>(m_gradients[1])->getBuffer();
        float* bufferGz = dynamic_cast<SImageFloat*>(m_gradients[2])->getBuffer();
        for (unsigned long i = 0 ; i < bs ; i++){
            val = fabs(bufferGx[i]) + fabs(bufferGy[i]) + fabs(bufferGz[i]);
            magBuffer[i] = val;
            m_normL1 +=val;
        }
    }
    return new SImageFloat(magBuffer, m_input->getSizeX(),  m_input->getSizeY(), m_input->getSizeZ(), m_input->getSizeT(), m_input->getSizeC() );
}

float SGradient::getNormL1(){
    if (m_normL1 < 0){
        this->getL1();
    }
    return m_normL1;
}
float SGradient::getNormL2(){
    if (m_normL2 < 0){
        this->getL2();
    }
    return m_normL2;
}

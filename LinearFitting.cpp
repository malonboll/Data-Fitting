#include "LinearFitting.h"

LinearFitting::LinearFitting(sCoordinates* dataSet, const int numOfData) :
pData(dataSet),
sizeOfData(numOfData)
{};

eReturnStatus LinearFitting::calcCoefficient(double& A, double& B)
{
    int Sxx = 0;
    int Sx = 0;
    int Sn = 0;
    int Sxg = 0;
    int Sg = 0;
    int det = 0;

    for(int i = 0; i < sizeOfData; i++)
    {
        Sxx += pData[i].x * pData[i].x;
        Sx += pData[i].x;
        Sn += 1;
        Sxg += pData[i].x * pData[i].y;
        Sg += pData[i].y;
    }
    
    det = (Sxx * Sn) - (Sx * Sx);

    if(det == 0) return eReturnStatus::DIVIED_ZERO;

    A = ((Sn * Sxg) + (-Sx * Sg)) / det;
    B = ((-Sx * Sxg) + (Sxx * Sg)) / det;

    return eReturnStatus::OK;
}
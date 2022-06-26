#pragma once

enum eReturnStatus
{
    OK,
    DIVIED_ZERO
};

class LinearFitting
{
    public:
    struct sCoordinates
    {
        int x;
        int y;
    };

    LinearFitting(sCoordinates* dataSet, const int numOfData);
    eReturnStatus calcCoefficient(double& A, double& B);

    private:
    sCoordinates* pData;
    int sizeOfData;
};
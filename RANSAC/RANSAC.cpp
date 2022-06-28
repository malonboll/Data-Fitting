#include "RANSAC.h"
#include <random>
#include <ctime>
RANSAC::RANSAC(const int _n, const double _t) :
n(_n),
t(_t),
maxInlierCounter(0),
Result_Coeff_A(0.0),
Result_Coeff_B(0.0)
{}

void RANSAC::initRANSAC()
{
    this->maxInlierCounter = 0;
    this->Result_Coeff_A = 0.0;
    this->Result_Coeff_B = 0.0;
}

void RANSAC::fitting(std::vector<int>& input)
{
    initRANSAC();

    for(int i = 0; i < n; i++)
    {
        // select random index
        std::vector<int> indexVector;
        selectRandomIndex(indexVector, 2, 0, input.size() - 1);

        // linear fitting을 진행하여 계수 A, B를 구한다
        if(indexVector[0] - indexVector[1] == 0)
        {
            --i;
            continue;
        }
        int x0 = indexVector[0];
        int y0 = input[x0];
        int x1 = indexVector[1];
        int y1 = input[x1];
        double Cur_Coeff_A = (y1 - y0) / (x1 - x0);
        double Cur_Coeff_B = y0 - (Cur_Coeff_A * x0); 

        // inliar count
        int curInliar = countInliar(input, Cur_Coeff_A, Cur_Coeff_B);

        if(curInliar > maxInlierCounter)
        {
            maxInlierCounter = curInliar;
            Result_Coeff_A = Cur_Coeff_A;
            Result_Coeff_B = Cur_Coeff_B;
            //printf("%d, %lf, %lf\r\n", maxInlierCounter, Result_Coeff_A, Result_Coeff_B);
        }
    }
}

void RANSAC::selectRandomIndex(std::vector<int>& indexVec, const int n, const int minVal, const int maxVal)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(minVal, maxVal);
    for(int i = 0; i < n; i++)
    {
        int randNum = dist(mt);
        indexVec.push_back(randNum);
    }
}

int RANSAC::countInliar(std::vector<int>& input, const double coeff_A, const double coeff_B)
{
    int cnt = 0;
    for(int i = 0; i < input.size(); i++)
    {
        if(abs((coeff_A * i) + coeff_B - input[i]) < t) cnt++;
    }

    return cnt;
}
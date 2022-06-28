#include <vector>

class RANSAC
{
    public:
    RANSAC(const int _n, const double _t);
    void fitting(std::vector<int>& input);

    private:
    int n;  // Number of ransac iterations
    double t;  // inlier, outlier threshold 
    int maxInlierCounter;
    double Result_Coeff_A;
    double Result_Coeff_B;

    void initRANSAC();
    void selectRandomIndex(std::vector<int>& indexVec, const int n, const int minVal, const int maxVal);
    int countInliar(std::vector<int>& input, const double coeff_A, const double coeff_B);
};
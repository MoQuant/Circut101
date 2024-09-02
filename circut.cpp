#include <iostream>
#include <vector>
#include <math.h>

void PRINTX(std::vector<std::vector<double>> u){
    for(auto & t : u){
        for(auto & i : t){
            std::cout << i << "\t";
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<double>> MMULT(std::vector<std::vector<double>> x, std::vector<std::vector<double>> y){
    std::vector<std::vector<double>> result;
    std::vector<double> temp;
    double total = 0;
    for(int i = 0; i < x.size(); ++i){
        temp.clear();
        for(int j = 0; j < y[0].size(); ++j){
            total = 0;
            for(int k = 0; k < x[0].size(); ++k){
                total += x[i][k]*y[k][j];
            }
            temp.push_back(total);
        }
        result.push_back(temp);
    }
    return result;
}

std::vector<std::vector<double>> TRANSPOSE(std::vector<std::vector<double>> u){
    std::vector<std::vector<double>> v;
    std::vector<double> temp;
    for(int i = 0; i < u[0].size(); ++i){
        temp.clear();
        for(int j = 0; j < u.size(); ++j){
            temp.push_back(u[j][i]);
        }
        v.push_back(temp);
    }
    return v;
}

std::vector<std::vector<double>> INVERSE(std::vector<std::vector<double>> x){
    int n = x.size();
    std::vector<std::vector<double>> I;
    std::vector<double> iI;
    for(int i = 0; i < n; ++i){
        iI.clear();
        for(int j = 0; j < n; ++j){
            if(i == j){
                iI.push_back(1.0);
            } else {
                iI.push_back(0.0);
            }
        }
        I.push_back(iI);
    }

    for(int i = 1; i < n; ++i){
        for(int j = 0; j < i; ++j){
            double A = x[i][j];
            double B = x[j][j];
            for(int k = 0; k < n; ++k){
                x[i][k] -= (A/B)*x[j][k];
                I[i][k] -= (A/B)*I[j][k];
            }
        }
    }

    for(int i = 1; i < n; ++i){
        for(int j = 0; j < i; ++j){
            double A = x[j][i];
            double B = x[i][i];
            for(int k = 0; k < n; ++k){
                x[j][k] -= (A/B)*x[i][k];
                I[j][k] -= (A/B)*I[i][k];
            }
        }
    }

    

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            I[i][j] = I[i][j] / x[i][i];
        }
    }

    return I;
}

std::vector<std::vector<double>> SolveForCurrent(std::vector<std::vector<double>> A, std::vector<std::vector<double>> B){
    std::vector<std::vector<double>> Current;
    double lambda = 0.000001;

    std::vector<std::vector<double>> AT, ATA, IATA, ATB;
    AT = TRANSPOSE(A);
    ATA = MMULT(AT, A);
    int n = ATA.size();

    for(int i = 0; i < n; ++i){
        ATA[i][i] += lambda;
    }

    IATA = INVERSE(ATA);

    ATB = MMULT(AT, B);

    Current = MMULT(IATA, ATB);

    return Current;
}

void Circuit1()
{
    double E = 2.0;

    double R1 = 10;
    double R2 = 20;
    double R3 = 15;
    double R4 = 30;
    double R5 = 5;
    double R6 = 25;

    std::vector<std::vector<double>> R = {
        {R1, R2, 0, 0, R5, 0},
        {0, R2, -R3, R4, 0, 0},
        {0, 0, 0, R4, -R5, R6}
    };

    std::vector<std::vector<double>> B = {{E},{0},{0}};
    
    std::vector<std::vector<double>> Current = SolveForCurrent(R, B);

    std::vector<std::vector<double>> Check = MMULT(R, Current);

    PRINTX(Check);

}

void Circuit2()
{
    double V = 10.0;
    double R1 = 1.0;
    double R2 = 25.0;
    double R3 = 50.0;
    double R4 = 1.0;
    double R5 = 30.0;
    double R6 = 55.0;
    double R7 = 25.0;
    double R8 = 50.0;
    double R9 = 1.0;
    double R10 = 30.0;
    double R11 = 55.0;

    std::vector<std::vector<double>> A, B, Current;

    A = {
        {R1+R2+R3, -R2, -R3, 0, 0, 0},
        {-R2, R2+R4+R5, -R4, -R5, 0, 0},
        {-R3, -R4, R3+R4+R6, -R6, 0, 0},
        {0, -R5, -R6, R5+R6+R7+R8, -R7, -R8},
        {0, 0, 0, -R7, R7+R9+R10, -R9},
        {0, 0, 0, -R8, -R9, R8+R9+R11}
    };

    B = {
        {10},
        {0},
        {0},
        {0},
        {0},
        {0}
    };

    Current = SolveForCurrent(A, B);



    PRINTX(MMULT(A, Current));

}

int main(){
    Circuit2();
}

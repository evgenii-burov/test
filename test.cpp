#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>

class Matrix
{
    std::vector<std::vector<double>> matrix;
    //n-размер, k-полуширина
    int n, k;
public:
    Matrix(std::string file_name)
    {
        std::ifstream in_stream(file_name);
        if (!in_stream)
        {
            std::cout << "Couldn't open input file";
            exit(0);
        }
        int n0, k0;
        in_stream >> n0 >> k0;
        n = n0;
        k = k0;
        matrix.resize(n);
        for (int i = 0; i < n;i++)
        {
            matrix[i].resize(2 * k + 1);
            for (int j = 0; j < 2*k+1;j++)
            {
                in_stream >> matrix[i][j];
            }
        }
    }

    void printDenseFormat()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                double elem = abs(i - j) > k ? 0 : (matrix[i][k + j - i]);
                //(matrix[i][k + 1 + i - j])
                std::cout << elem << "\t";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    void printBandedFormat()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < 2*k+1; j++)
            {
                std::cout << matrix[i][j] << "\t";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    void decompose()
    {
        for (int i = 0; i < n;i++)
        {
            for (int j = 0; j < 2 * k + 1;j++)
            {
                if()
                double sum_over_l = 0;
                if (j<k) //l_ij
                {
                    for (int l = 0; l < j - k + i;l++)
                    {
                        if (l - k + i < 0 || l - k + i > 2 * k)
                            continue;
                        sum_over_l += matrix[i][l - k + i] * matrix[l][l - k + i] * matrix[l][j];
                    }
                    matrix[i][j] = (matrix[i][j] - sum_over_l) / matrix[j-k+i][j];
                }
                if (j==k) //d_ii
                {
                    for (int l = 0; l < i;l++)
                    {
                        if (l - k + i < 0 || l - k + i > 2 * k)
                            continue;
                        sum_over_l += matrix[i][l - k + i] * matrix[l][l - k + i] * matrix[l][j];
                    }
                    matrix[i][j] = matrix[i][j] - sum_over_l;
                }
                if (j > k) //u_ij
                {
                    for (int l = 0; l < j - k + i;l++)
                    {
                        if (l - k + i < 0 || l - k + i > 2 * k)
                            continue;
                        sum_over_l += matrix[i][l - k + i] * matrix[l][l - k + i] * matrix[l][j];
                    }
                    matrix[i][i - k + i] = (matrix[i][j] - sum_over_l) / matrix[i][k];
                }
            }
        }
    }
};

int main()
{
    std::setprecision(2);
    Matrix m = Matrix("matrix.txt");
    m.printDenseFormat();
    m.printBandedFormat();
    m.decompose();
    m.printDenseFormat();
    m.printBandedFormat();
}


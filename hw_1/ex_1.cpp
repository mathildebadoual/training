// Exercice 1 (How to make matrices disappear):

#include <iostream>
#include <vector>
#include <list>

using namespace std;
typedef vector<vector<double>> matrix;

void PrintMatrix(const matrix mat) {
    const auto rows = mat.size();
    const auto cols = mat[0].size();
    for (auto i = 0; i < rows; ++i) {
        for (auto j = 0; j < cols; ++j) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

matrix MatrixMult(const matrix x, const matrix y) {
    const auto rows_x = x.size();
    const auto cols_x = x[0].size();
    const auto rows_y = y.size();
    const auto cols_y = y[0].size();
    matrix product(rows_x, vector<double>(cols_y));
    for (auto row = 0; row < rows_x; ++row) {
        for (int col = 0; col < cols_y; ++col) {
            for (int k = 0; k < cols_x; ++k) {
                product[row][col] += x[row][k] * y[k][col];
            }
        }
    }
    return product;
}

bool TestNullMatrix(const matrix m)
{
    const auto rows_m = m.size();
    const auto cols_m = m[0].size();
    for (int row = 0; row < rows_m; ++row)
        for (int col = 0; col < cols_m; ++col){
            if (m[row][col] != 0){
                return false;
            }
        }
    return true;
}

bool Try2MatrixMult(const vector<matrix> to_try)
{
    for(auto m_1 : to_try)
    {
        for(auto m_2 : to_try)
        {
            matrix product = MatrixMult(m_1, m_2);
            if(TestNullMatrix(product)==true)
            {
                cout << "matrice is null with: " << endl;
                PrintMatrix(m_1);
                PrintMatrix(m_2);
                return true;
            }
        }
    }
    return false;
}

bool Try3MatrixMult(const vector<matrix> to_try)
{
    for(auto m_1 : to_try)
    {
        for(auto m_2 : to_try)
        {
            matrix product_int = MatrixMult(m_1, m_2);
            for(auto m_3 : to_try)
            {
                matrix product = MatrixMult(product_int, m_3);
                if(TestNullMatrix(product)==true)
                {
                    cout << "matrice is null with: " << endl;
                    PrintMatrix(m_1);
                    PrintMatrix(m_2);
                    PrintMatrix(m_3);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Try4MatrixMult(const vector<matrix> to_try)
{
    for(auto m_1 : to_try)
    {
        for(auto m_2 : to_try)
        {
            matrix product_int_1 = MatrixMult(m_1, m_2);
            for(auto m_3 : to_try)
            {
                matrix product_int_2 = MatrixMult(product_int_1, m_3);
                for(auto m_4 : to_try)
                {
                    matrix product = MatrixMult(product_int_2, m_4);
                    if(TestNullMatrix(product)==true)
                    {
                        cout << "matrice is null with: " << endl;
                        PrintMatrix(m_1);
                        PrintMatrix(m_2);
                        PrintMatrix(m_3);
                        PrintMatrix(m_4);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

int main(int argc, const char* argv[]) {
    auto a = matrix({{2, -2}, {2, 2}});
    auto b = matrix({{0, 0}, {0, 1}});
    vector<matrix> to_try(8);
    to_try = {a, b};
    bool is_null = false;
    is_null = Try2MatrixMult(to_try);
    is_null = Try3MatrixMult(to_try);
    is_null = Try4MatrixMult(to_try);
    return 0;
}


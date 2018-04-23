// Exercice 2 (How to make bigger matrices disappear):

#include <iostream>
#include <vector>
#include <list>
#include <stdio.h>
#include <stdlib.h>


using namespace std;
typedef vector<vector<double>> matrix;

void printMatrix(const matrix mat) {
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
bool testNullMatrix(const matrix m)
{
    bool check = true;
    const auto rows_m = m.size();
    const auto cols_m = m[0].size();
    for (int row = 0; row < rows_m; ++row)
        for (int col = 0; col < cols_m; ++col){
            if (m[row][col] != 0 ){
                check = false;
                break;
            }
        }
    return check;
}

matrix matrixMult(const matrix x, const matrix y) {
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

bool testMultNull(const matrix m_a, const matrix m_b) {
    if(testNullMatrix(matrixMult(m_a, m_b))){
        return true;
    }
    return false;
}

bool testEqual(const matrix m_1, const matrix m_2){
    const auto rows_m_1 = m_1.size();
    const auto cols_m_1 = m_1[0].size();
    if (rows_m_1 != m_2.size()){
        return false;
    }
    if (cols_m_1 != m_2[0].size()){
        return false;
    }
    for (int row = 0; row < rows_m_1; ++row)
        for (int col = 0; col < cols_m_1; ++col){
            if (m_1[row][col] != m_2[row][col]){
                return false;
            }
        }
    return true;
}

struct node {
    matrix m;
    struct node* left;
    struct node* right;
};

typedef vector<struct node*> vector_nodes;

static int searchNull(struct node* node, vector_nodes nodes_tested) {
    if (node == NULL) {
        nodes_tested.pop_back();
        struct node* previous_node = nodes_tested.back();
        nodes_tested.pop_back();
        searchNull(previous_node->right, nodes_tested);
    }
    else {
        if(testNullMatrix(node->m)) return(true);
        else {
            nodes_tested.push_back(node);
            return searchNull(node->left, nodes_tested);
        }
    }
}

struct node* newNode(matrix m) {
    struct node* node = new(struct node);
    node->m = m;
    node->left = NULL;
    node->right = NULL;
    return(node);
}

void build(struct node* node, const matrix m_a, const matrix m_b, int num_max) {
    if (num_max <= 3){
        if (node->left == NULL & node->) {
            node->left = newNode(matrixMult(node->m, m_a));
            node->right = newNode(matrixMult(node->m, m_b));
            build(node->left, m_a, m_b, ++num_max);
            build(node->right, m_a, m_b, ++num_max);
        }
    }
}

void printTree(struct node* node) {
    if (node == NULL) return;
    printTree(node->left);
    printMatrix(node->m);
    printTree(node->right);
}

int main()
{
    const auto m_a = matrix({{2, -2}, {2, 2}});
    const auto m_b = matrix({{0, 0}, {0, 1}});
    const auto m_i = matrix({{1, 0}, {0, 1}});
    struct node* root;
    int num_max = 0
    build(root, m_a, m_b, num_max);
    printTree(root);
    return 0;
}



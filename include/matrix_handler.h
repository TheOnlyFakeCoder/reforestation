#include <vector>
#include <iostream>

using namespace std;

class MatrixHandler {
    public:
        void getCof(const vector<vector<double>>& mat, vector<vector<double>>& cof, 
                                                int p, int q, int n) {
            int i = 0, j = 0;
            for (int row = 0; row < n; row++) {
                for (int col = 0; col < n; col++) {
                    if (row != p && col != q) {
                        cof[i][j++] = mat[row][col];
                        if (j == n - 1) {
                            j = 0;
                            i++;
                        }
                    }
                }
            }
        }

        // Recursive function for finding determinant 
        // of matrix mat of dimension n
        double getDet(const vector<vector<double>>& mat, int n) {
            if (n == 1) return mat[0][0];
            
            double det = 0.0;
        
            // To store cofactors
            vector<vector<double>> cof(mat.size(), vector<double>(mat.size()));
        
            int sign = 1;
            for (int f = 0; f < n; f++) {
                getCof(mat, cof, 0, f, n);
                det += sign * mat[0][f] * getDet(cof, n - 1);
                sign = -sign;
            }
            return det;
        }

        // Function to get adjoint of mat in adj
        void adjoint(const vector<vector<double>>& mat, vector<vector<double>>& adj) {
            int n = mat.size();
            if (n == 1) {
                adj[0][0] = 1;
                return;
            }
            
            int sign = 1;
            vector<vector<double>> cof(n, vector<double>(n));
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    getCof(mat, cof, i, j, n);
                    sign = ((i + j) % 2 == 0) ? 1 : -1;
                    adj[j][i] = sign * getDet(cof, n - 1);
                }
            }
        }

        vector<vector<double>> getInverse(vector<vector<double>>& matrix) {
            double determinant = getDet(matrix, matrix.size());
            int n = matrix.size();
            vector<vector<double>> adj(n, vector<double>(n));
            adjoint(matrix, adj);
            for(size_t i = 0; i < matrix.size(); i++) {
                for(size_t j = 0; j < matrix.size(); j++) {
                    matrix[i][j] = matrix[i][j]/determinant;
                }
            }
            return matrix;
        }

        // Function to calculate and store inverse, returns 
        // false if matrix is singular
        bool inverse(vector<vector<double>>& mat, vector<vector<float>>& inv) {
            int n = mat.size();
            int det = getDet(mat, n);
            if (det == 0) {
                cout << "Singular matrix, can't find its inverse";
                return false;
            }

            vector<vector<double>> adj(n, vector<double>(n));
            adjoint(mat, adj);

            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    inv[i][j] = adj[i][j] / float(det);

            return true;
        }

        vector<vector<double>> transpose(const vector<vector<double>>& matrix) {
            vector<vector<double>> transposed;
            for(size_t i = 0; i < matrix.size();i++) {

                vector<double> newRows;
                for(size_t j = 0; j < matrix.size(); j++) {
                    double value = matrix[j][i];
                    newRows.push_back(value);
                }

                transposed.push_back(newRows);
            }

            return transposed;
        }

        vector<double> solveLinear(const vector<vector<double>>& inverseMatrix, const vector<double>& b) {
            vector<double> solution(inverseMatrix.size(), 0.0);
            for(size_t i = 0; i < inverseMatrix.size(); i++) {
                solution[i] = 0;
                for(size_t j = 0; j < inverseMatrix.size(); j++) {
                    solution[i] += b[j]*inverseMatrix[i][j];
                }
            }
            return solution;
        }

        template <typename T>
        void printMatrixElements(const vector<vector<T>> matrix) {
            for (const auto& row : matrix) {
                cout << "[ ";
                for (double val : row) {
                    cout << val << " ";
                }
                cout << "]\n";
            }
        }

        void printVectorElements(const vector<double> vec) {
            cout << "[ ";
            for (const auto& val: vec) {
                cout << val << " ";
            } 
            cout << "]" << endl;
        }
};
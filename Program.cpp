#include <iostream>
#include <math.h>

using namespace std;

double deter(int n, double mat[10][10])
{
    int d = 0;
    double submat[10][10];

    if (n == 2) return ((mat[0][0] * mat[1][1]) - (mat[1][0] * mat[0][1]));

    if(n == 1) return mat[0][0];

    else
    {
        for (int c = 0; c < n; c++)
        {
            int x = 0;

            for (int i = 1; i < n; i++)
            {
                int y = 0;

                for (int o = 0; o < n; o++)
                {
                    if (o == c) continue;

                    submat[x][y] = mat[i][o];

                    y++;
                }

                x++;
            }
            
            d = d + (pow(-1, c) * mat[0][c] * deter(n - 1, submat));
        }
    }
    return d;
}

double inverseXY(int n, double mat[10][10], int ix, int ox)
{
    double matN[10][10], det;

    int startX, startY;

    startX = startY = 0;
    det = deter(n,mat);

    for(int i = 0; i < n; i++)
    {
        startY = 0;

        if(i == ix)
        {
            continue;
        }
        else
        {
            for(int o = 0; o < n; o++)
            {
                if(o == ox)
                {
                    continue;
                }
                else
                {
                    matN[startX][startY] = mat[o][i];
                }
                startY++;
            }
        }
        startX++;
    }

    return pow(-1, ix+ox)*deter(n-1,matN)/det;
}

double inverse2(int n, double mat[10][10], int i, int o)
{
    double resMat[10][10], Det;

    Det = deter(n, mat);

    if (i == o)
    {
        resMat[i][o] = mat[1-i][1-o];
    }
    else
    {
        resMat[i][o] = -mat[1-i][1-o];
    }


    return resMat[i][o] / Det;
}

int main()
{
    int x_A, x_B, x_R, y_A, y_B, y_R, oprNum;
    double MatrixA[10][10], MatrixB[10][10], invMatB[10][10],ResultMat[10][10];

    bool progExit = false;

    cout << "Please enter dimensions of Matrix A:\n";
    cin >> y_A >> x_A;

    cout << "Please enter dimensions of Matrix B:\n";
    cin >> y_B >> x_B;

    x_A = abs(x_A);
    x_B = abs(x_B);

    y_A = abs(y_A);
    y_B = abs(y_B);

    cout << "Please enter values of Matrix A:\n";
    for (int i = 0; i < y_A; i++)
    {
        for (int o = 0; o < x_A; o++)
        {
            cin >> MatrixA[o][i];
        }
    }

    cout << "Please enter values of Matrix B:\n";
    for (int i = 0; i < y_B; i++)
    {
        for (int o = 0; o < x_B; o++)
        {
            cin >> MatrixB[o][i];
        }
    }

    while (!progExit)
    {
        cout << "Please choose operation type(1: A+B, 2: A-B, 3: AxB, 4: A*inverse(B), 5: |A|, 6: |B|, 7: quit):\n";
        cin >> oprNum;

        if(oprNum == 7)
        {
            cout << "Thank you!\n";
            progExit = true;
        }

        else if(oprNum == 1)
        {
            if ((x_A == x_B) && (y_A == y_B))
            {
                x_R = x_A;
                y_R = y_A;

                for (int i = 0; i < y_R; i++)
                {
                    for (int o = 0; o < x_R; o++)
                    {
                        ResultMat[o][i] = MatrixA[o][i] + MatrixB[o][i];

                        cout << ResultMat[o][i] << " ";
                        if (o == (x_R - 1))
                        {
                            cout << "\n";
                        }
                    }
                }
            }
            else
            {
                cout << "The operation you chose is invalid for the given matrices.\n";
            }
        }
        else if(oprNum == 2)
        {
            if ((x_A == x_B) && (y_A == y_B))
            {
                x_R = x_A;
                y_R = y_A;

                for (int i = 0; i < y_R; i++)
                {
                    for (int o = 0; o < x_R; o++)
                    {
                        ResultMat[o][i] = MatrixA[o][i] - MatrixB[o][i];

                        cout << ResultMat[o][i] << " ";
                        if (o == (x_R - 1))
                        {
                            cout << "\n";
                        }
                    }
                }
            }
            else
            {
                cout << "The operation you chose is invalid for the given matrices.\n";
            }
        }
        else if(oprNum == 3)
        {
            if (x_A == y_B)
            {
                x_R = x_B;
                y_R = y_A;

                for (int i = 0; i < y_R; i++)
                {
                    for (int o = 0; o < x_R; o++)
                    {
                        ResultMat[o][i] = 0;
                    }
                }

                for (int i = 0; i < y_R; i++)
                {
                    for (int o = 0; o < x_R; o++)
                    {
                        for (int m = 0; m < x_A; m++)
                        {
                            ResultMat[o][i] += MatrixA[m][i] * MatrixB[o][m];
                        }
                    }
                }

                for (int i = 0; i < y_R; i++)
                {
                    for (int o = 0; o < x_R; o++)
                    {
                        cout << ResultMat[o][i] << " ";
                
                        if (o == (x_R - 1))
                        {
                            cout << "\n";
                        }
                    }
                }
            }

            else
            {
                cout << "The operation you chose is invalid for the given matrices.\n";
            }
        }
        else if(oprNum == 4)
        {
            if((x_B == y_B) && (x_A == y_B) && (deter(x_B,MatrixB) != 0))
            {
                if(x_B == 2)
                {
                    for(int i = 0; i < x_B; i++)
                    {
                        for(int o = 0; o < x_B; o++)
                        {
                            invMatB[i][o] = inverse2(x_B, MatrixB, o, i);
                        }
                    }
                }
                else
                {
                    for(int i = 0; i < x_B; i++)
                    {
                        for(int o = 0; o < x_B; o++)
                        {
                            invMatB[i][o] = inverseXY(x_B,MatrixB,i,o);
                        }
                    }
                }

                for (int i = 0; i < y_A; i++)
                {
                    for (int o = 0; o < x_B; o++)
                    {
                        ResultMat[o][i] = 0;
                    }
                }

                for (int i = 0; i < y_A; i++)
                {
                    for (int o = 0; o < x_B; o++)
                    {
                        for (int m = 0; m < x_A; m++)
                        {
                            ResultMat[o][i] += MatrixA[m][i] * invMatB[o][m];
                        }
                    }
                }

                for (int i = 0; i < y_A; i++)
                {
                    for (int o = 0; o < x_B; o++)
                    {
                        if(round(ResultMat[o][i]) == 0)
                        {
                            cout << 0 << " ";

                            if (o == (x_B - 1))
                            {
                                cout << "\n";
                            }
                        }
                        else
                        {
                            cout << round(ResultMat[o][i]) << " ";

                            if (o == (x_B - 1))
                            {
                                cout << "\n";
                            }
                        }
                    }
                }
            }
            else
            {
                cout << "The operation you chose is invalid for the given matrices.\n";
            }
        }
        else if(oprNum == 5)
        {
            if (y_A == x_A)
            {
                cout << deter(y_A, MatrixA) << endl;
            }

            else
            {
                cout << "The operation you chose is invalid for the given matrices.\n";
            }

        }
        else if(oprNum == 6)
        {
            if (y_B == x_B)
            {
                cout << deter(y_B, MatrixB) << endl;
            }

            else
            {
                cout << "The operation you chose is invalid for the given matrices.\n";
            }
        }
    }
}
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <string>
#include <unordered_map>
#include <limits>
#include <cmath>
#include <functional>


using namespace std;

// Define the dimensions of the cube
const int faceSize = 3;
const int expandedSize = 12;

// Function to expand the cube based on its faces
vector<vector<char>> expandCube(vector<vector<char>>& back, vector<vector<char>>& up, vector<vector<char>>& front, vector<vector<char>>& down, vector<vector<char>>& right, vector<vector<char>>& left) {
    vector<vector<char>> expanded(expandedSize, vector<char>(faceSize * 4, ' '));

    // Place the back face
    for (int i = 0; i < faceSize; ++i)
        for (int j = 0; j < faceSize; ++j)
            expanded[i][faceSize + j] = back[i][j];

    // Place the up face
    for (int i = 0; i < faceSize; ++i)
        for (int j = 0; j < faceSize; ++j)
            expanded[faceSize + i][faceSize + j] = up[i][j];

    // Place the front face
    for (int i = 0; i < faceSize; ++i)
        for (int j = 0; j < faceSize; ++j)
            expanded[2 * faceSize + i][faceSize + j] = front[i][j];

    // Place the down face
    for (int i = 0; i < faceSize; ++i)
        for (int j = 0; j < faceSize; ++j)
            expanded[3 * faceSize + i][faceSize + j] = down[i][j];

    // Place the right face
    for (int i = 0; i < faceSize; ++i)
        for (int j = 0; j < faceSize; ++j)
            expanded[faceSize + i][2 * faceSize + j] = right[i][j];

    // Place the left face
    for (int i = 0; i < faceSize; ++i)
        for (int j = 0; j < faceSize; ++j)
            expanded[faceSize + i][j] = left[i][j];

    return expanded;
}


void rotateLeftClockwise(vector<vector<char>>& expanded) {
    // 旋转左面本身
        for (int i = 0; i < faceSize / 2; ++i) {
            for (int j = i; j < faceSize - i - 1; ++j) {
                // 保存左面的当前值
                char temp = expanded[faceSize + i][j];

                // 进行四次交换，完成90度旋转
                expanded[faceSize + i][j] = expanded[faceSize + (faceSize - 1 - j)][i];
                expanded[faceSize + (faceSize - 1 - j)][i] = expanded[faceSize + (faceSize - 1 - i)][faceSize - 1 - j];
                expanded[faceSize + (faceSize - 1 - i)][faceSize - 1 - j] = expanded[faceSize + j][faceSize - 1 - i];
                expanded[faceSize + j][faceSize - 1 - i] = temp;
            }
        }

    // Perform the rotation on the adjacent columns directly
    for (int i = 0; i < faceSize; ++i) {
        // Save the top column value temporarily
        char temp = expanded[faceSize + i][faceSize];

        // Move the back column to the top column
        expanded[faceSize + i][faceSize] = expanded[i][faceSize];

        // Move the bottom column to the back column
        expanded[i][faceSize] = expanded[3 * faceSize + i][faceSize];

        // Move the front column to the bottom column
        expanded[3 * faceSize + i][faceSize] = expanded[2 * faceSize + i][faceSize];

        // Move the saved top column value to the front column
        expanded[2 * faceSize + i][faceSize] = temp;
    }
}


void rotateLeftCounterclockwise(vector<vector<char>>& expanded) {
    // 逆时针旋转左面本身
        for (int i = 0; i < faceSize / 2; ++i) {
            for (int j = i; j < faceSize - i - 1; ++j) {
                // 保存左面的当前值
                char temp = expanded[faceSize + i][j];

                // 进行四次交换，完成90度逆时针旋转
                expanded[faceSize + i][j] = expanded[faceSize + j][faceSize - 1 - i];
                expanded[faceSize + j][faceSize - 1 - i] = expanded[faceSize + (faceSize - 1 - i)][faceSize - 1 - j];
                expanded[faceSize + (faceSize - 1 - i)][faceSize - 1 - j] = expanded[faceSize + (faceSize - 1 - j)][i];
                expanded[faceSize + (faceSize - 1 - j)][i] = temp;
            }
        }

    // Perform the rotation on the adjacent columns directly
    for (int i = 0; i < faceSize; ++i) {
        // Save the top column value temporarily
        char temp = expanded[faceSize + i][faceSize];

        // Move the front column to the top column
        expanded[faceSize + i][faceSize] = expanded[2 * faceSize + i][faceSize];

        // Move the bottom column to the front column
        expanded[2 * faceSize + i][faceSize] = expanded[3 * faceSize + i][faceSize];

        // Move the back column to the bottom column
        expanded[3 * faceSize + i][faceSize] = expanded[i][faceSize];

        // Move the saved top column value to the back column
        expanded[i][faceSize] = temp;
    }
}

void rotateMiddleLayerClockwise(vector<vector<char>>& expanded) {
    for (int i = 0; i < faceSize; ++i) {
        // 保存上层的当前列值
        char temp = expanded[faceSize + i][faceSize + 1];

        // 上层的列值被替换为后面的列值
        expanded[faceSize + i][faceSize + 1] = expanded[i][faceSize + 1];

        // 后面的列值被替换为下层的列值
        expanded[i][faceSize + 1] = expanded[3 * faceSize + i][faceSize + 1];

        // 下层的列值被替换为前面的列值
        expanded[3 * faceSize + i][faceSize + 1] = expanded[2 * faceSize + i][faceSize + 1];

        // 前面的列值被替换为上层保存的列值
        expanded[2 * faceSize + i][faceSize + 1] = temp;
    }
}

void rotateMiddleLayerCounterClockwise(vector<vector<char>>& expanded) {
    for (int i = 0; i < faceSize; ++i) {
        // 保存上层的当前列值
        char temp = expanded[i][faceSize + 1];

        // 上层的列值被替换为前面的列值
        expanded[i][faceSize + 1] = expanded[faceSize + i][faceSize + 1];

        // 前面的列值被替换为下层的列值
        expanded[faceSize + i][faceSize + 1] = expanded[2 * faceSize + i][faceSize + 1];

        // 下层的列值被替换为后面的列值
        expanded[2 * faceSize + i][faceSize + 1] = expanded[3 * faceSize + i][faceSize + 1];

        // 后面的列值被替换为上层保存的列值
        expanded[3 * faceSize + i][faceSize + 1] = temp;
    }
}

void rotateRightClockwise(vector<vector<char>>& expanded) {
    // 逆时针旋转右面本身
       for (int i = 0; i < faceSize / 2; ++i) {
           for (int j = i; j < faceSize - i - 1; ++j) {
               // 保存右面的当前值
               char temp = expanded[faceSize + i][2 * faceSize + j];

               // 进行四次交换，完成90度逆时针旋转
               expanded[faceSize + i][2 * faceSize + j] = expanded[faceSize + j][3 * faceSize - 1 - i];
               expanded[faceSize + j][3 * faceSize - 1 - i] = expanded[faceSize + (faceSize - 1 - i)][3 * faceSize - 1 - j];
               expanded[faceSize + (faceSize - 1 - i)][3 * faceSize - 1 - j] = expanded[faceSize + (faceSize - 1 - j)][2 * faceSize + i];
               expanded[faceSize + (faceSize - 1 - j)][2 * faceSize + i] = temp;
           }
       }

    // 直接在矩阵中进行值交换来移动第三列
    for (int i = 0; i < faceSize; ++i) {
        // 保存顶部列的当前值
        char temp = expanded[faceSize + i][2 * faceSize - 1];

        // 顶部列的值被替换为后面的列值
        expanded[faceSize + i][2 * faceSize - 1] = expanded[i][2 * faceSize - 1];

        // 后面的列值被替换为底部的列值
        expanded[i][2 * faceSize - 1] = expanded[3 * faceSize + i][2 * faceSize - 1];

        // 底部的列值被替换为前面的列值
        expanded[3 * faceSize + i][2 * faceSize - 1] = expanded[2 * faceSize + i][2 * faceSize - 1];

        // 前面的列值被替换为顶部保存的列值
        expanded[2 * faceSize + i][2 * faceSize - 1] = temp;
    }
}

void rotateRightCounterclockwise(vector<vector<char>>& expanded) {
    // 顺时针旋转右面本身
        for (int i = 0; i < faceSize / 2; ++i) {
            for (int j = i; j < faceSize - i - 1; ++j) {
                // 保存右面的当前值
                char temp = expanded[faceSize + i][2 * faceSize + j];

                // 进行四次交换，完成90度顺时针旋转
                expanded[faceSize + i][2 * faceSize + j] = expanded[faceSize + (faceSize - 1 - j)][2 * faceSize + i];
                expanded[faceSize + (faceSize - 1 - j)][2 * faceSize + i] = expanded[faceSize + (faceSize - 1 - i)][2 * faceSize + (faceSize - 1 - j)];
                expanded[faceSize + (faceSize - 1 - i)][2 * faceSize + (faceSize - 1 - j)] = expanded[faceSize + j][2 * faceSize + (faceSize - 1 - i)];
                expanded[faceSize + j][2 * faceSize + (faceSize - 1 - i)] = temp;
            }
        }

    // 直接在矩阵中进行值交换来移动第三列
    for (int i = 0; i < faceSize; ++i) {
        // 保存后面的当前列值
        char temp = expanded[i][2 * faceSize - 1];

        // 后面的列值被替换为顶部的列值
        expanded[i][2 * faceSize - 1] = expanded[faceSize + i][2 * faceSize - 1];

        // 顶部的列值被替换为前面的列值
        expanded[faceSize + i][2 * faceSize - 1] = expanded[2 * faceSize + i][2 * faceSize - 1];

        // 前面的列值被替换为底部的列值
        expanded[2 * faceSize + i][2 * faceSize - 1] = expanded[3 * faceSize + i][2 * faceSize - 1];

        // 底部的列值被替换为保存的列值
        expanded[3 * faceSize + i][2 * faceSize - 1] = temp;
    }
}

void rotateBottomClockwise(vector<vector<char>>& expanded) {

    // 逆时针旋转底面本身
        for (int i = 0; i < faceSize / 2; ++i) {
            for (int j = i; j < faceSize - i - 1; ++j) {
                // 保存底面的当前值
                char temp = expanded[3 * faceSize + i][faceSize + j];

                // 进行四次交换，完成90度逆时针旋转
                expanded[3 * faceSize + i][faceSize + j] = expanded[3 * faceSize + j][faceSize + (faceSize - 1 - i)];
                expanded[3 * faceSize + j][faceSize + (faceSize - 1 - i)] = expanded[3 * faceSize + (faceSize - 1 - i)][faceSize + (faceSize - 1 - j)];
                expanded[3 * faceSize + (faceSize - 1 - i)][faceSize + (faceSize - 1 - j)] = expanded[3 * faceSize + (faceSize - 1 - j)][faceSize + i];
                expanded[3 * faceSize + (faceSize - 1 - j)][faceSize + i] = temp;
            }
        }

    // 直接在矩阵中进行值交换来移动第三列
    for (int i = 0; i < faceSize; ++i) {
        // 保存后面的当前列值
        char temp = expanded[0][3+i];

        // 后面的列值被替换为左面的列值
        expanded[0][3+i] = expanded[5-i][0];

        // 左面的列值被替换为前面的列值
        expanded[5-i][0] = expanded[8][5-i];

        // 前面的列值被替换为右面的列值
        expanded[8][5-i] = expanded[3+i][8];

        // 右面的列值被替换为保存的列值
        expanded[3+i][8] = temp;
    }
}

// Function to simulate the 3- (bottom face counterclockwise 90-degree) rotation
void rotateBottomCounterclockwise(vector<vector<char>>& expanded) {
    // 顺时针旋转底面本身
        for (int i = 0; i < faceSize / 2; ++i) {
            for (int j = i; j < faceSize - i - 1; ++j) {
                // 保存底面的当前值
                char temp = expanded[3 * faceSize + i][faceSize + j];

                // 进行四次交换，完成90度顺时针旋转
                expanded[3 * faceSize + i][faceSize + j] = expanded[3 * faceSize + (faceSize - 1 - j)][faceSize + i];
                expanded[3 * faceSize + (faceSize - 1 - j)][faceSize + i] = expanded[3 * faceSize + (faceSize - 1 - i)][faceSize + (faceSize - 1 - j)];
                expanded[3 * faceSize + (faceSize - 1 - i)][faceSize + (faceSize - 1 - j)] = expanded[3 * faceSize + j][faceSize + (faceSize - 1 - i)];
                expanded[3 * faceSize + j][faceSize + (faceSize - 1 - i)] = temp;
            }
        }

    // 直接在矩阵中进行值交换来移动第三列
    for (int i = 0; i < faceSize; ++i) {
        // 保存后面的当前列值
        char temp = expanded[0][3 + i];

        // 后面的列值被替换为右面的列值
        expanded[0][3 + i] = expanded[3 + i][8];

        // 右面的列值被替换为前面的列值
        expanded[3 + i][8] = expanded[8][5 - i];

        // 前面的列值被替换为左面的列值
        expanded[8][5 - i] = expanded[5 - i][0];

        // 左面的列值被替换为保存的列值
        expanded[5 - i][0] = temp;
    }
}
// Function to simulate the 4+ rotation
void rotateEquatorialLayerClockwise(vector<vector<char>>& expanded) {
    // 直接在矩阵中进行值交换来移动中层
       for (int i = 0; i < faceSize; ++i) {
           char tempRight = expanded[1][3+i];

           expanded[1][3+i] = expanded[5-i][1];
           expanded[5-i][1] = expanded[7][5-i];
           expanded[7][5-i] = expanded[3+i][7];
           expanded[3+i][7] = tempRight;
       }
}

// Function to simulate the 4- rotation
void rotateEquatorialLayerCounterclockwise(vector<vector<char>>& expanded) {
    // 直接在矩阵中进行值交换来移动中层
        for (int i = 0; i < faceSize; ++i) {
            char tempLeft = expanded[7][faceSize + i];

            expanded[7][faceSize + i] = expanded[faceSize + i][1];
            expanded[faceSize + i][1] = expanded[1][faceSize + (faceSize - 1 - i)];
            expanded[1][faceSize + (faceSize - 1 - i)] = expanded[5 - i][7];
            expanded[5 - i][7] = tempLeft;
        }
}
// Function to simulate the 5+ rotation
void rotateTopFaceClockwise(vector<vector<char>>& expanded) {
    for (int i = 0; i < faceSize / 2; ++i) {
            for (int j = i; j < faceSize - i - 1; ++j) {
                char temp = expanded[faceSize + i][faceSize + j];

                expanded[faceSize + i][faceSize + j] = expanded[faceSize + (faceSize - 1 - j)][faceSize + i];
                expanded[faceSize + (faceSize - 1 - j)][faceSize + i] = expanded[faceSize + (faceSize - 1 - i)][faceSize + (faceSize - 1 - j)];
                expanded[faceSize + (faceSize - 1 - i)][faceSize + (faceSize - 1 - j)] = expanded[faceSize + j][faceSize + (faceSize - 1 - i)];
                expanded[faceSize + j][faceSize + (faceSize - 1 - i)] = temp;
            }
        }

    // 直接在矩阵中进行值交换来移动最上一行（顺时针旋转）
    for (int i = 0; i < faceSize; ++i) {
        char tempBack = expanded[2][3 + i];              // 保存后面的当前值

        expanded[2][3 + i] = expanded[5-i][2];  // 前面的最上一行到右面的最上一行
        expanded[5-i][2] = expanded[6][5-i];  // 右面的最上一行到前面的最上一行
        expanded[6][5-i] = expanded[3 + i][6];          // 后面的最上一行到左面的最上一行
        expanded[3 + i][6] = tempBack;                    // 左面的最上一行到后面的最上一行
    }
}
// Function to simulate the 5- rotation
void rotateTopFaceCounterClockwise(vector<vector<char>>& expanded) {
    for (int i = 0; i < faceSize / 2; ++i) {
        for (int j = i; j < faceSize - i - 1; ++j) {
            char temp = expanded[faceSize + i][faceSize + j];

            expanded[faceSize + i][faceSize + j] = expanded[faceSize + j][faceSize + (faceSize - 1 - i)];
            expanded[faceSize + j][faceSize + (faceSize - 1 - i)] = expanded[faceSize + (faceSize - 1 - i)][faceSize + (faceSize - 1 - j)];
            expanded[faceSize + (faceSize - 1 - i)][faceSize + (faceSize - 1 - j)] = expanded[faceSize + (faceSize - 1 - j)][faceSize + i];
            expanded[faceSize + (faceSize - 1 - j)][faceSize + i] = temp;
        }
    }
        // 直接在矩阵中进行值交换来移动最上一行（逆时针旋转）
        for (int i = 0; i < faceSize; ++i) {
            char tempFront = expanded[6][faceSize + i];       // 保存前面的当前值

            expanded[6][faceSize + i] = expanded[3+ i][2];   // 右面的最上一行到前面的最上一行
            expanded[3+i][2] = expanded[2][5- i];          // 后面的最上一行到右面的最上一行
            expanded[2][5-i] = expanded[5- i][6];          // 左面的最上一行到后面的最上一行
            expanded[5-i][6] = tempFront;                   // 前面的最上一行到左面的最上一行
        }
}
// Function to simulate the 6+ rotation
void rotateFrontFaceClockwise(vector<vector<char>>& expanded) {
    for (int i = 0; i < faceSize / 2; ++i) {
        for (int j = i; j < faceSize - i - 1; ++j) {
            char temp = expanded[2 * faceSize + i][faceSize + j];

            expanded[2 * faceSize + i][faceSize + j] = expanded[2 * faceSize + (faceSize - 1 - j)][faceSize + i];
            expanded[2 * faceSize + (faceSize - 1 - j)][faceSize + i] = expanded[2 * faceSize + (faceSize - 1 - i)][faceSize + (faceSize - 1 - j)];
            expanded[2 * faceSize + (faceSize - 1 - i)][faceSize + (faceSize - 1 - j)] = expanded[2 * faceSize + j][faceSize + (faceSize - 1 - i)];
            expanded[2 * faceSize + j][faceSize + (faceSize - 1 - i)] = temp;
        }
    }

    for (int i = 0; i < faceSize  ; ++i) {
        char temp = expanded[faceSize + faceSize - 1][faceSize + i];
        expanded[faceSize + faceSize - 1][faceSize + i] = expanded[5][i];
        expanded[5][i] = expanded[9][5-i];
        expanded[9][5 - i] = expanded[5][6 + i];
        expanded[5][6 + i] = temp;
    }
}

// Function to simulate the 6- rotation
void rotateFrontFaceCounterClockwise(vector<vector<char>>& expanded) {
    for (int i = 0; i < faceSize / 2; ++i) {
            for (int j = i; j < faceSize - i - 1; ++j) {
                char temp = expanded[2 * faceSize + i][faceSize + j];

                expanded[2 * faceSize + i][faceSize + j] = expanded[2 * faceSize + j][faceSize + (faceSize - 1 - i)];
                expanded[2 * faceSize + j][faceSize + (faceSize - 1 - i)] = expanded[2 * faceSize + (faceSize - 1 - i)][faceSize + (faceSize - 1 - j)];
                expanded[2 * faceSize + (faceSize - 1 - i)][faceSize + (faceSize - 1 - j)] = expanded[2 * faceSize + (faceSize - 1 - j)][faceSize + i];
                expanded[2 * faceSize + (faceSize - 1 - j)][faceSize + i] = temp;
            }
        }

    for (int i = 0; i < faceSize; ++i) {
        char temp = expanded[5][6 + i];
        expanded[5][6 + i] = expanded[9][5 - i];
        expanded[9][5 - i] = expanded[5][i];
        expanded[5][i] = expanded[faceSize + faceSize - 1][faceSize + i];
        expanded[faceSize + faceSize - 1][faceSize + i] = temp;
    }
}

// Function to simulate the 7+ rotation
void rotateStandingLayerClockwise(vector<vector<char>>& expanded) {
    for (int i = 0; i < faceSize; ++i) {
        char tempUp = expanded[4][3+i];      // 保存上面中层的当前状态
        expanded[4][3+i] = expanded[4][i];   // 左面中层到上面中层
        expanded[4][i] = expanded[10][3+(faceSize-1)-i];  // 下面中层到左面中层
        expanded[10][3+(faceSize-1)-i] = expanded[4][6+i];   // 右面中层到下面中层
        expanded[4][6+i] = tempUp;           // 上面中层到右面中层
    }
}

// Function to simulate the 7- rotation
void rotateStandingLayerCounterClockwise(vector<vector<char>>& expanded) {
    for (int i = 0; i < faceSize; ++i) {
        char tempUp = expanded[4][6+i];      // 保存上面中层的当前状态
        expanded[4][6+i] = expanded[10][3+(faceSize-1)-i];   // 右面中层到上面中层
        expanded[10][3+(faceSize-1)-i] = expanded[4][i];  // 下面中层到右面中层
        expanded[4][i] = expanded[4][3+i];   // 左面中层到下面中层
        expanded[4][3+i] = tempUp;           // 上面中层到左面中层
    }
}
// Function to simulate the 8+ rotation
void rotateBackFaceClockwise(vector<vector<char>>& expanded) {

    int n = faceSize;
    for (int layer = 0; layer < n / 2; ++layer) {
        int first = layer;
        int last = n - 1 - layer;
        for (int i = first; i < last; ++i) {
            int offset = i - first;
            // 保存顶部左边的值
            char top = expanded[first][faceSize + i];

            // 左边移动到顶部（逆时针方向）
            expanded[first][faceSize + i] = expanded[i][faceSize + last];

            // 底部移动到左边（逆时针方向）
            expanded[i][faceSize + last] = expanded[last][faceSize + last - offset];

            // 右边移动到底部（逆时针方向）
            expanded[last][faceSize + last - offset] = expanded[last - offset][faceSize + first];

            // 保存顶部左边的值移动到右边（逆时针方向）
            expanded[last - offset][faceSize + first] = top;
        }
    }


    for (int i = 0; i < faceSize; ++i) {
            char tempUp = expanded[3][3+i];      // 保存上面中层的当前状态
            expanded[3][3+i] = expanded[3][i];   // 右面中层到上面中层
            expanded[3][i] = expanded[11][5-i];  // 下面中层到右面中层
            expanded[11][5-i] = expanded[3][6+i];   // 左面中层到下面中层
            expanded[3][6+i] = tempUp;           // 上面中层到左面中层
        }

}
// Function to simulate the 8- rotation
void rotateBackFaceCounterclockwise(vector<vector<char>>& expanded) {
    int n = faceSize;
    for (int layer = 0; layer < n / 2; ++layer) {
        int first = layer;
        int last = n - 1 - layer;
        for (int i = first; i < last; ++i) {
            int offset = i - first;
            // 保存顶部左边的值
            char top = expanded[first][faceSize + i];

            // 左边移动到顶部
            expanded[first][faceSize + i] = expanded[last - offset][faceSize + first];

            // 底部移动到左边
            expanded[last - offset][faceSize + first] = expanded[last][faceSize + last - offset];

            // 右边移动到底部
            expanded[last][faceSize + last - offset] = expanded[i][faceSize + last];

            // 保存顶部左边的值移动到右边
            expanded[i][faceSize + last] = top;
        }
    }

    for (int i = 0; i < faceSize; ++i) {
        char tempUp = expanded[3][3 + i];       // 保存上面中层的当前状态
        expanded[3][3 + i] = expanded[3][6 + i]; // 左面中层到上面中层
        expanded[3][6 + i] = expanded[11][5 - i]; // 下面中层到左面中层
        expanded[11][5 - i] = expanded[3][i];    // 右面中层到下面中层
        expanded[3][i] = tempUp;                 // 上面中层到右面中层
    }
}

void printExpandedCube(const vector<vector<char>>& expanded) {
    for (const auto& row : expanded) {
        for (char cell : row) {
            cout << cell << ' ';
        }
        cout << endl;
    }
}
// Rotation map for function pointers
unordered_map<string, function<void(vector<vector<char>>&)>> rotations = {
    {"0+", rotateLeftClockwise},
    {"0-", rotateLeftCounterclockwise},
    {"1+", rotateMiddleLayerClockwise},
    {"1-", rotateMiddleLayerCounterClockwise},
    {"2+", rotateRightClockwise},
    {"2-", rotateRightCounterclockwise},
    {"3+", rotateBottomClockwise},
    {"3-", rotateBottomCounterclockwise},
    {"4+", rotateEquatorialLayerClockwise},
    {"4-", rotateEquatorialLayerCounterclockwise},
    {"5+", rotateTopFaceClockwise},
    {"5-", rotateTopFaceCounterClockwise},
    {"6+", rotateFrontFaceClockwise},
    {"6-", rotateFrontFaceCounterClockwise},
    {"7+", rotateStandingLayerClockwise},
    {"7-", rotateStandingLayerCounterClockwise},
    {"8+", rotateBackFaceClockwise},
    {"8-", rotateBackFaceCounterclockwise},
};
int heuristic(const vector<vector<char>>& state) {
    int h = 0;
    // 遍历每个面及其各自的坐标
    for (int f = 0; f < 6; ++f) {
        char center;
        int startRow, startCol;

        // 确定每个面的中心和起点
        switch (f) {
            case 0: center = state[0][4]; startRow = 0; startCol = 3; break;  // 后面
            case 1: center = state[3][4]; startRow = 3; startCol = 3; break;  // 上面
            case 2: center = state[6][4]; startRow = 6; startCol = 3; break;  // 前面
            case 3: center = state[9][4]; startRow = 9; startCol = 3; break;  // 下面
            case 4: center = state[3][7]; startRow = 3; startCol = 6; break;  // 右面
            case 5: center = state[3][1]; startRow = 3; startCol = 0; break;  // 左面
        }

        // 检查当前面上的每个单元格
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (state[startRow + i][startCol + j] != center) {
                    ++h;
                }
            }
        }
    }
    return h;
}

bool isSolved(const vector<vector<char>>& expanded) {
    return heuristic(expanded) == 0;
}

// 定义节点结构
struct Node {
    vector<vector<char>> state;
    string moves;
    int cost;
    bool operator<(const Node& other) const {
        return cost > other.cost;
    }
};

string solveCubeAStar(vector<vector<char>>& initial) {
    priority_queue<Node> pq;
    unordered_set<string> visited;

    auto hashState = [](const vector<vector<char>>& state) {
        string hash;
        for (const auto& row : state) {
            for (char c : row) {
                hash += c;
            }
        }
        return hash;
    };

    pq.push({initial, "", heuristic(initial)});

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (isSolved(current.state)) {
            return current.moves;
        }

        string currentHash = hashState(current.state);
        if (visited.find(currentHash) != visited.end()) {
            continue;
        }
        visited.insert(currentHash);

        for (const auto& rotation : rotations) {
            vector<vector<char>> nextState = current.state;
            rotation.second(nextState);

            string nextHash = hashState(nextState);
            if (visited.find(nextHash) == visited.end()) {
                string nextMoves = current.moves + (current.moves.empty() ? "" : " ") + rotation.first;
                int newCost = nextMoves.size() / 2 + 1 + heuristic(nextState);
                pq.push({nextState, nextMoves, newCost});
            }
        }
    }

    return "No solution found";
}


void readCubeFace(vector<vector<char>>& face) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cin >> face[i][j];
        }
    }
}

int main() {
    vector<vector<char>> back(3, vector<char>(3));
    vector<vector<char>> up(3, vector<char>(3));
    vector<vector<char>> front(3, vector<char>(3));
    vector<vector<char>> down(3, vector<char>(3));
    vector<vector<char>> right(3, vector<char>(3));
    vector<vector<char>> left(3, vector<char>(3));

    string faceName;

    cin >> faceName;
    readCubeFace(back);

    cin >> faceName;
    readCubeFace(up);

    cin >> faceName;
    readCubeFace(front);

    cin >> faceName;
    readCubeFace(down);

    cin >> faceName;
    readCubeFace(right);

    cin >> faceName;
    readCubeFace(left);

    // Expand the cube
    vector<vector<char>> expanded = expandCube(back, up, front, down, right, left);



    //Solve the cube
    string solution =solveCubeAStar(expanded);

    //Print the solution
    if (solution != "No solution found") {
        cout <<solution<< endl;
    } else {
        cout << "No solution found." << endl;
    }




    return 0;
}

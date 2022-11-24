#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <string>
#include <math.h>


void print_puzzle(std::vector<std::vector<int>> &matrix, int dim)
{
    int width = std::to_string(dim*dim).length() + 1;

    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
            std::cout << std::setw(width) << matrix[i][j];
        std::cout << "\n";
    }
    std::cout << "\n";
}


int fill_row(std::vector<std::vector<int>> &matrix, int r, int &n, int d, int dim)
{
    int s, e, j;

    s = d == 1 ? 0 : dim - 1;
    e = d == 1 ? dim : 0 - 1;

    // Skip trailling non-zeros
    for (int i = s; i != e && matrix[r][i] != 0; i += d)
        s += d;

    // Fill empty space
    j = 0;
    for (int i = s; i != e && matrix[r][i] == 0; i += d)
    {
        matrix[r][i] = n++;
        j = i;
    }
    return j;
}


int fill_col(std::vector<std::vector<int>> &matrix, int c, int &n, int d, int dim)
{
    int s, e, j;

    s = d == 1 ? 0 : dim - 1;
    e = d == 1 ? dim : 0 - 1;

    // Skip trailling non-zeros
    for (int i = s; i != e && matrix[i][c] != 0; i += d)
        s += d;

    // Fill empty space
    j = 0;
    for (int i = s; i != e && matrix[i][c] == 0; i += d)
    {
        matrix[i][c] = n++;
        j = i;
    }
    return j;
}


std::vector<std::vector<int>> make_goal(int dim)
{
    std::vector<std::vector<int>> matrix;
    int n, dir, last_c, last_r;

    for (int i = 0; i < dim; i++)
    {
        std::vector<int> row;
        for (int j = 0; j < dim; j++)
            row.push_back(0);
        matrix.push_back(row);
    }
    
    n = 1;
    dir = 1;
    last_r = 0;
    last_c = 0;
    while (n < dim * dim - 1)
    {
        last_c = fill_row(matrix, last_r, n, dir, dim);
        last_r = fill_col(matrix, last_c, n, dir, dim);
        dir *= -1;
    }
    return matrix;
}


std::vector<int> flatten(std::vector<std::vector<int>> const &matrix)
{
    std::vector<int> array;

    for (auto const &m: matrix)
        array.insert(array.end(), m.begin(), m.end());
    return array;
}


int inversions(std::vector<int> &matrix, std::vector<int> &goal, int dim)
{
    int total;
    int j, tmp;

    total = 0;
    while (!std::equal(matrix.begin(), matrix.end(), goal.begin()))
    {
        for (int i = 0; i < dim * dim; i++)
        {
            if (matrix[i] != goal[i])
            {
                j = std::find(matrix.begin(), matrix.end(), goal[i]) - matrix.begin();                
                total++;
                tmp = matrix[i];
                matrix[i] = matrix[j];
                matrix[j] = tmp;
            }
        }
    }
    return total;
}


std::vector<int> find(std::vector<std::vector<int>> &matrix, int target, int dim)
{
    std::vector<int> vec;

    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            if (matrix[i][j] == target)
            {
                vec.push_back(i);
                vec.push_back(j);
                return vec;
            }
        }
    }
    vec.push_back(-1);
    vec.push_back(-1);
    return vec;
}


int manhattan(std::vector<std::vector<int>> &matrix, std::vector<std::vector<int>> &goal, int target, int dim)
{
    std::vector<int> mv, gv;

    mv = find(matrix, target, dim);
    gv = find(goal, target, dim);
    return std::abs(gv[0] - mv[0]) + std::abs(gv[1] - mv[1]);
}


int is_solvable(std::vector<std::vector<int>> &start, std::vector<std::vector<int>> &goal, int dim)
{
    int inv, h;
    std::vector<int> flatten_s = flatten(start);
    std::vector<int> flatten_e = flatten(goal);

    inv = inversions(flatten_s, flatten_e, dim);
    h = manhattan(start, goal, 0, dim);
    std::cout << inv << " " << h << std::endl;
    if (inv % 2 == h % 2)
        return 1;
    return 0;
}


int main(int argc, char **argv)
{
    int dim = 4;
    std::vector<std::vector<int>> goal = make_goal(dim);
    std::vector<std::vector<int>> start = {
        std::vector<int> {4, 7, 15, 1},
        std::vector<int> {3, 13, 10, 11},
        std::vector<int> {5, 12, 9, 14},
        std::vector<int> {2, 6, 0, 8}
    };
    // std::vector<std::vector<int>> start = {
    //     std::vector<int> {1, 4, 0},
    //     std::vector<int> {5, 8, 6},
    //     std::vector<int> {2, 7, 3}
    // };

    print_puzzle(start, dim);
    print_puzzle(goal, dim);

    if (is_solvable(start, goal, dim))
        std::cout << "Solvable" << std::endl;
    else
        std::cout << "Not solvable" << std::endl;
    
    return (0);
}
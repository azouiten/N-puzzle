

#include "parser.hpp"

void print_puzzle(t_matrix &matrix, int dim)
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


int fillRow(t_matrix &matrix, int r, int &n, int d, int dim)
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


int fillCol(t_matrix &matrix, int c, int &n, int d, int dim)
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


t_matrix makeGoal(int dim)
{
    t_matrix matrix;
    int n = 1, dir = 1, last_c = 0, last_r = 0;

    for (int i = 0; i < dim; i++)
    {
        std::vector<int> row;
        for (int j = 0; j < dim; j++)
            row.push_back(0);
        matrix.push_back(row);
    }
    while (n < dim * dim - 1)
    {
        last_c = fillRow(matrix, last_r, n, dir, dim);
        last_r = fillCol(matrix, last_c, n, dir, dim);
        dir *= -1;
    }
    return matrix;
}

std::vector<int> flatten(t_matrix &matrix)
{
    std::vector<int> array;

    for (t_matrix::iterator it = matrix.begin(); it != matrix.end(); it++)
    {
        array.insert(array.end(), (*it).begin(), (*it).end());
    }
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


std::vector<int> find(t_matrix &matrix, int target, int dim)
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


int manhattan(t_matrix &matrix, t_matrix &goal, int target, int dim)
{
    std::vector<int> mv, gv;

    mv = find(matrix, target, dim);
    gv = find(goal, target, dim);
    return std::abs(gv[0] - mv[0]) + std::abs(gv[1] - mv[1]);
}


int isSolvable(t_matrix &start, t_matrix &goal, int dim)
{
    int inv, h;
    std::vector<int> flatten_s = flatten(start);
    std::vector<int> flatten_e = flatten(goal);
    inv = inversions(flatten_s, flatten_e, dim);
    h = manhattan(start, goal, 0, dim);
    std::cout << "issolvable\n";
    if (inv % 2 == h % 2)
        return 1;
    return 0;
}
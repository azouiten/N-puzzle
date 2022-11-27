#ifndef _PARSER_
#define _PARSER_

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <iomanip>
#include <math.h>
#include <algorithm>
#include <string>

typedef std::vector<std::vector<int>> t_matrix;
typedef std::vector<int> t_array;


class   Parser
{
private:
    std::string _fileName;
    size_t      _puzzleSize;
    t_array    _array;

    void    loadData(std::ifstream &puzzleFile);
    void    trimComment(std::string &line);
    void    grabSize(std::string line);
    void    grabPuzzle(std::string line);
public:
    Parser(std::string fileName);
    ~Parser(void);

    class InvalidPuzzleException : public std::exception
    {
        public:
            virtual const char * what(void) const throw();
    };

    class InvalidFileException : public std::exception
    {
        public:
            virtual const char * what(void) const throw();
    };

    t_matrix    getMatrix(void);
    t_array     &getArray(void);
    size_t  getDim(void);

};

int isSolvable(t_matrix &start, t_matrix &goal, int dim);
t_matrix makeGoal(int dim);
void print_puzzle(t_matrix &matrix, int dim);
t_matrix makeGoalAsArray(int dim);

std::vector<int> flatten(t_matrix const &matrix);

template <typename T>
void print_vector(std::vector<T> V, std::string headline)
{
    typename std::vector<T>::iterator iter = V.begin();
    typename std::vector<T>::iterator end = V.end();

    std::cout << headline << std::endl;
    while (iter != end)
    {
        std::cout << std::setw(3) << std::setfill(' ') << *iter << std::endl;
        iter++;
    }
}
#endif
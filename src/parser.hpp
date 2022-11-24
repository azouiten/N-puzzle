#ifndef _PARSER_
#define _PARSER_

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <iomanip>

class   Parser
{
private:
    std::string _fileName;
    std::string _content;
    size_t      _puzzleSize;
    std::vector<int>    _array;
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

    void loadData(std::ifstream &puzzleFile);
    void    trimComment(std::string &line);
    void    grabSize(std::string line);
    void    grabPuzzle(std::string line);
};

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
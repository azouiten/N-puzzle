#include "parser.hpp"

Parser::Parser(std::string fileName) : _fileName(fileName), _puzzleSize(0)
{
    std::ifstream   puzzleFile;
    size_t          index = 0;
    char            *value_c, *line_c;
    int             number;

    puzzleFile.open(_fileName, std::ios::in);
    if (!puzzleFile.good())
        throw InvalidFileException();
    this->loadData(puzzleFile);
    puzzleFile.close();
    // print_vector(_array, "data\n");
    // std::cout << "size : " << _puzzleSize << std::endl;
}

Parser::~Parser(void)
{

}

const char * Parser::InvalidPuzzleException::what() const throw()
{
    return ("Invalid Puzzle!");
}

const char * Parser::InvalidFileException::what() const throw()
{
    return ("Invalid File!");
}

void    Parser::trimComment(std::string &line)
{
    size_t index = 0, start = 0, end = 0;
    int found = 0;
    size_t pos = line.rfind('#');
    if (pos == 0)
        line.clear();
    if (pos != std::string::npos)
        line = line.substr(0, pos);
}

void    Parser::grabSize(std::string line)
{
    size_t index = 0, lenght = line.size();
    size_t found = 0, count = 0;
    while (index < lenght)
    {
        if (line[index] != ' ' && !isdigit(line[index]))
            throw InvalidPuzzleException();
        if (!found && line[index] != ' ')
        {
            count++;
            found = 1;
        }
        else if (found && line[index] == ' ')
        {
            found = 0;
        }
        index++;
    }
    if (count > 1)
        throw InvalidPuzzleException();
    _puzzleSize = std::stoi(line);
    if (!_puzzleSize)
        throw InvalidPuzzleException();
}

void    Parser::grabPuzzle(std::string line)
{
    size_t index = 0, lenght = line.size();
    size_t found = 0, count = 0;
    int number = 0;
    while (index < lenght)
    {
        if (line[index] != ' ' && !isdigit(line[index]))
            throw InvalidPuzzleException();
        if (!found && line[index] != ' ')
        {
            count ++;
            found = 1;
            number = std::stoi(line.c_str() + index);
            _array.push_back(number);
        }
        else if (found && line[index] == ' ')
        {
            found = 0;
        }
        index++;
    }
    if (count != _puzzleSize)
        throw InvalidPuzzleException();
}

void Parser::loadData(std::ifstream &puzzleFile)
{
    std::string line;
    std::vector<std::string> puzzle;
    while (!puzzleFile.eof())
    {
        getline(puzzleFile, line);
        this->trimComment(line);
        if (!_puzzleSize && !line.empty())
            this->grabSize(line);
        else if (!line.empty())
            this->grabPuzzle(line);
    }
    if (!_puzzleSize)
        throw InvalidPuzzleException();
    if (_array.size() / _puzzleSize != _puzzleSize)
        throw InvalidPuzzleException();
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return (1);
    try
    {
        Parser parser(argv[1]);
    }
    catch (std::exception &e)
    {
        std::cout << "Error:" << e.what() << std::endl;
    }
}
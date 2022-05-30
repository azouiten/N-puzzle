#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <vector>

typedef std::vector<std::string >   t_content;
typedef std::vector<uint>           t_state;


std::string trim(std::string str)
{
    size_t i, j;

    i = 0;
    while (i < str.size() && str[i] == ' ' && ++i);
    j = str.size() - 1;
    while (j != i && str[j] == ' ' && j--);
    return (str.substr(i, j - i + 1));
}


bool is_number(std::string str)
{
    std::string::iterator   it;

    it = str.begin();
    while (it != str.end() && std::isdigit(*it)) ++it;
    return (!str.empty() && it == str.end());
}


std::vector<std::string > split(std::string str, int del)
{
    std::string::iterator       it;
    std::string                 token;
    std::vector<std::string >   tokens;

    it = str.begin();
    while (it != str.end())
    {
        if (*it != del)
        {
            while (it != str.end() && *it != del)
            {
                token = token + *it;
                it++;
            }
            tokens.push_back(token);
            token.clear();
            continue ;
        }
        it++;
    }
    return (tokens);
}


std::vector<std::string> read(std::string filename)
{
    std::ifstream   ifs;
    t_content       content;
    std::string     line;
    int pos;

    ifs.open(filename, std::ios::in);
    if (ifs.is_open())
    {
        while (getline(ifs, line))
        {
            line = trim(line);
            if (line.size() && line[0] != '#')
            {
                if ((pos = line.find('#')) != std::string::npos)
                    line = std::string(line, 0, pos);
                content.push_back(line);
            }
        }
    }
    return (content);
}


int parse_content(t_content content, u_short &dim, t_state &state)
{
    t_content::iterator         it;
    std::string                 line;
    std::vector<std::string >   tokens;
    std::vector<u_int >         row;
    u_int                       total, dummy, count;

    if (content.size() == 0)
        return (-1);

    it = content.begin();
    try
    {
        std::cout << *it << "|" << std::endl;
        if (!is_number(*it))
        {
            std::cout << *it << std::endl;
            throw std::invalid_argument("retard");
        }
        dim = std::stoi(*it);
    }
    catch (std::invalid_argument)
    {
        return (-1);
    }

    total = 0;
    dummy = 0;
    count = 0;
    it++;
    while (it != content.end())
    {
        tokens = split(*it, ' ');
        if (tokens.size() != dim)
            return (-1);
        for (int i = 0; i < tokens.size(); i++)
        {
            try
            {
                if (!is_number(tokens[i]))
                    return (-1);
                total += std::stoi(tokens[i]);
                dummy += count++;
                state.push_back(std::stoi(tokens[i]));
                // row.push_back(std::stoi(tokens[i]));
            }
            catch(const std::exception& e)
            {
                return (-1);
            }
        }
        // state.push_back(row);
        // row.clear();
        it++;
    }
    if (total != dummy)
        return (-1);
    return (0);
}


t_state parse(std::string filename)
{
    t_state state;
    u_short dim;

    if (parse_content(read(filename), dim, state) == -1)
    {
        std::cout << "Invalid input file" << std::endl;
        state.clear();
    }
    return (state);
}


void usage()
{
    std::cout << "Usage:" << std::endl;
    std::cout << "./npuzzle filename [heuristic]" << std::endl;
    std::cout << "  filename:   Filename containing the dimension of the puzzle and the puzzle." << std::endl;
    std::cout << "  heuristic:  Heuristic function to be used." << std::endl;
    std::cout << "              manhattan is choosen by default." << std::endl;
    std::cout << "              1. manhattan" << std::endl;
    std::cout << "              2. euclidian" << std::endl;
    std::cout << "              3. misplaced tiles" << std::endl;
}


int main(int argc, char **argv)
{
    t_state st;

    st = parse(argv[1]);
    for (t_state::iterator it = st.begin(); it != st.end(); it++)
    {
        std::cout << *it << " ";
    }
    return (0);
}
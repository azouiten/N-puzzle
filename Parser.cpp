#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <vector>

typedef std::vector<std::string >       t_content;
typedef std::vector<std::vector<u_int> >  t_state;

std::string trim(std::string str)
{
    int i;

    i = 0;
    while (i < str.size() && str[i] == ' ' && ++i);
    return (str.substr(i, str.size() - i));
}

bool is_number(std::string str)
{
    std::string::iterator   it;

    it = str.begin();
    while (it != str.end() && std::isdigit(*it)) ++it;
    return (!str.empty() && it == str.end());
}

std::vector<std::string> read(std::string file_name)
{
    std::ifstream   ifs;
    t_content       content;
    std::string     line;

    ifs.open(file_name, std::ios::in);
    if (ifs.is_open())
    {
        while (getline(ifs, line))
        {
            line = trim(line);
            if (line.size() && line[0] != '#')
                content.push_back(trim(line));
        }
    }
    return (content);
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

int parse_content(t_content content, u_short &dim, t_state &state)
{
    t_content::iterator         it;
    std::string                 line;
    std::vector<std::string >   tokens;
    std::vector<u_int >         row;

    // If content is empty, return error flag (-1)
    if (content.size() == 0)
        return (-1);

    // Parse the dimension line
    it = content.begin();
    try
    {
        if (!is_number(*it))
            throw std::invalid_argument("retard");
        dim = std::stoi(*it);
    }
    catch (std::invalid_argument)
    {
        return (-1);
    }

    // Parse puzzle lines
    it++;
    while (it != content.end())
    {
        tokens = split(*it, ' ');
        for (int i = 0; i < tokens.size(); i++)
        {
            try
            {
                if (!is_number(tokens[i]))
                    return (-1);
                row.push_back(stoi(row))
            }
            catch(const std::exception& e)
            {
               return (-1);
            }
        }
        row.clear();
        it++;
    }

    return (0);
}

int main(int argc, char **argv)
{
    u_short dim;
    t_state state;

    if (parse_content(read(argv[1]), dim, state) == -1)
        std::cout << "Invalid input file" << std::endl;
    else
        std::cout << "Cool" << std::endl;
    return (0);
}
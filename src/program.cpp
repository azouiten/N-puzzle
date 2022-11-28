
#include "parser.hpp"
#include "solver.hpp"

struct InvalidArgException : public std::exception {
   const char * what () const throw () {
      return "Invalid arguments!";
   }
};

static void grabArgs(int lenght ,char **args, e_heuristic *heu,\
bool *greedy, bool *uniform)
{
    int index = 1;
    lenght--;
    while (index < lenght)
    {
        if (!strcmp(args[index], manhattanFlag))
            *heu = manhattan;
        else if (!strcmp(args[index], euclideanFlag))
            *heu = euclidean;
        else if (!strcmp(args[index], MisplacedTilesFlag))
            *heu = misplacedTiles;
        else if (!strcmp(args[index], GreedySearchFlag))
        {
            *uniform = true;
            *greedy = false;
        }
        else if (!strcmp(args[index], UniformSearchFlag))
        {
            *uniform = false;
            *greedy = true;
        }
        index ++;
    }
}

int main(int argc, char **argv)
{
    e_heuristic heu = manhattan;
    bool        uniform = true;
    bool        greedy = true;
    try
    {
        if (argc < 2)
            throw InvalidArgException();
        if (argc > 2)
            grabArgs(argc, argv, &heu, &greedy, &uniform);
        Parser parser(argv[argc - 1]);
        size_t  dim = parser.getDim();
        t_matrix matrix = parser.getMatrix();
        t_matrix goal = makeGoal(dim);

        if (isSolvable(matrix, goal, dim))
            std::cout << "solvable\n";
        else
            std::cout << "unsolvable\n";
        Solver s(dim, parser.getArray(),flatten(goal));
        s.run(heu, uniform, greedy);
    }
    catch (std::exception &e)
    {
        std::cout << "Error:" << e.what() << std::endl;
    }
}

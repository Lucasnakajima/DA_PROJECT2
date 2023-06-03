#ifndef AIRTRANSPORT_MENU_H
#define AIRTRANSPORT_MENU_H
#include "Graph.h"
#include "load_graphs.h"
#include <stdlib.h>
///Classe para o Menu.
///
///Um menu apenas apresenta as opcoes.
class Menu {
private:
    /// @brief Object used to load the graphs as needed
    load_graphs l;

public:
     /**
     * @brief Constructs a Menu object.
     */
    Menu();

    /**
     * @brief Runs the menu.
     */
    void run();


    /**
     * @brief Tests whether the input is valid.
     * @param choice The user's choice.
     * @param values A vector containing the values associated with the user's choice.
     * @return True if the input is valid, false otherwise.
     */
    bool inputTest(char choice, std::vector<int> values);

    /**
     * @brief Pauses the program and waits for user input.
     */
    void pause();

    /**
     * @brief Displays the algorithm menu for a given graph and performs the chosen action.
     * @param g The graph to operate on
     * @param flag Flag indicating whether backtracking is applicable for the graph
     */
    void algomenu(Graph g, bool flag);

    /**
     * @brief Prints a path represented by a vector of integers.
     * @param v The vector representing the path
     */
    void printPath(vector<int> v);
};


#endif //AIRTRANSPORT_MENU_H
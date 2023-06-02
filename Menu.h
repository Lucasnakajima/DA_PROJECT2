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


    void pause();

    void algomenu(Graph g, bool flag);

    void printPath(vector<int> v);
};


#endif //AIRTRANSPORT_MENU_H
//
// Created by Utilizador on 5/12/2023.
//

#include "load_graphs.h"


void load_graphs::load() {
    std::ifstream file("data.csv");
    std::string line;
    std::getline(file, line);

    int maxOrigem = 0;
    int maxDestino = 0;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string origem, destino, distancia, labelOrigem, labelDestino;

        std::getline(iss, origem, ',');
        std::getline(iss, destino, ',');
        std::getline(iss, distancia, ',');
        std::getline(iss, labelOrigem, ',');
        std::getline(iss, labelDestino, ',');

        int origemNum = std::stoi(origem);
        int destinoNum = std::stoi(destino);

        maxOrigem = std::max(maxOrigem, origemNum);
        maxDestino = std::max(maxDestino, destinoNum);
    }

    int maximum = std::max(maxOrigem, maxDestino);

    std::cout << "Highest number between 'origem' and 'destino': " << maximum << std::endl;

    file.close();
    return;
}
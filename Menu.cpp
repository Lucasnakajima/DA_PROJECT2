 #include <unistd.h>
#include "Menu.h"
#include <locale>
#include <algorithm>
#include <string>
#include <climits>

 using namespace std;
Menu::Menu() {
    run();
}

void Menu::run() {
    while(true){
        Graph graph_toy(false);
        Graph graph_medium(true);
        Graph graph_real(true);
        cout << string(50,'\n');
        cout << "||==================================================================================================================||\n"
                "||  ████████╗███████╗██████╗      █████╗ ██╗      ██████╗  ██████╗ ██████╗ ██╗████████╗██╗  ██╗███╗   ███╗███████╗  ||\n"
                "||  ╚══██╔══╝██╔════╝██╔══██╗    ██╔══██╗██║     ██╔════╝ ██╔═══██╗██╔══██╗██║╚══██╔══╝██║  ██║████╗ ████║██╔════╝  ||\n"
                "||     ██║   ███████╗██████╔╝    ███████║██║     ██║  ███╗██║   ██║██████╔╝██║   ██║   ███████║██╔████╔██║███████╗  ||\n"
                "||     ██║   ╚════██║██╔═══╝     ██╔══██║██║     ██║   ██║██║   ██║██╔══██╗██║   ██║   ██╔══██║██║╚██╔╝██║╚════██║  ||\n"
                "||     ██║   ███████║██║         ██║  ██║███████╗╚██████╔╝╚██████╔╝██║  ██║██║   ██║   ██║  ██║██║ ╚═╝ ██║███████║  ||\n"
                "||     ╚═╝   ╚══════╝╚═╝         ╚═╝  ╚═╝╚══════╝ ╚═════╝  ╚═════╝ ╚═╝  ╚═╝╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝  ||\n"
                "||==================================================================================================================||\n"
                "||                     TOY GRAPHS                      |                     REAL WORLD GRAPHS                      ||\n"
                "||==================================================================================================================||\n"
                "||                                                     |                                                            ||\n"
                "||  Shipping                                      [11] |  Graph 1                                              [21] ||\n"
                "||  Stadiums                                      [12] |  Graph 2                                              [22] ||\n"
                "||  Tourism                                       [13] |  Graph 3                                              [23] ||\n"
                "||==================================================================================================================||\n"
                "||                                       EXTRA FULLY-CONNECTED MEDIUM GRAPHS                                        ||\n"
                "||==================================================================================================================||\n"
                "||                                     Edges_25                              [31]                                   ||\n"
                "||                                     Edges_50                              [32]                                   ||\n"
                "||                                     Edges_75                              [33]                                   ||\n"
                "||                                     Edges_100                             [34]                                   ||\n"
                "||                                     Edges_200                             [35]                                   ||\n"
                "||                                     Edges_300                             [36]                                   ||\n"
                "||                                     Edges_400                             [37]                                   ||\n"
                "||                                     Edges_500                             [38]                                   ||\n"
                "||                                     Edges_600                             [39]                                   ||\n"
                "||                                     Edges_700                             [40]                                   ||\n"
                "||                                     Edges_800                             [41]                                   ||\n"
                "||                                     Edges_900                             [42]                                   ||\n"
                "||==================================================================================================================||\n"
                "||                                                   EXIT [0]                                                       ||\n"
                "||==================================================================================================================||\n"
                "Choose an option: ";
        int choice;
        vector<int> values = {0,11,12,13,21,22,23,31,32,33,34,35,36,37,38,39,40,41,42};
        cin >> choice;
        if(!inputTest(choice,values)) continue;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch(choice){
            case 11:
                graph_toy = l.load_toy("shipping.csv");
                break;
            case 12:
                graph_toy = l.load_toy("stadiums.csv");
                break;
            case 13:
                graph_toy = l.load_toy("tourism.csv");
                break;
            case 21:
                graph_real = l.load_real("graph1");
                break;
            case 22:
                graph_real = l.load_real("graph2");
                break;
            case 23:
                graph_real = l.load_real("graph3");
                break;
            case 31:
                graph_medium = l.load_medium(25);
                break;
            case 32:
                graph_medium = l.load_medium(50);
                break;
            case 33:
                graph_medium = l.load_medium(75);
                break;
            case 34:
                graph_medium = l.load_medium(100);
                break;
            case 35:
                graph_medium = l.load_medium(200);
                break;
            case 36:
                graph_medium = l.load_medium(300);
                break;
            case 37:
                graph_medium = l.load_medium(400);
                break;
            case 38:
                graph_medium = l.load_medium(500);
                break;
            case 39:
                graph_medium = l.load_medium(600);
                break;
            case 40:
                graph_medium = l.load_medium(700);
                break;
            case 41:
                graph_medium = l.load_medium(800);
                break;
            case 42:
                graph_medium = l.load_medium(900);
                break;
            case 0:
                cout << string(15,'\n');
                cout << "██████╗ ██╗   ██╗███████╗██╗\n"
                        "██╔══██╗╚██╗ ██╔╝██╔════╝██║\n"
                        "██████╔╝ ╚████╔╝ █████╗  ██║\n"
                        "██╔══██╗  ╚██╔╝  ██╔══╝  ╚═╝\n"
                        "██████╔╝   ██║   ███████╗██╗\n"
                        "╚═════╝    ╚═╝   ╚══════╝╚═╝";
                cout << string(15,'\n');
                exit(0);
            default:
                cout << "Invalid Input !";
                pause();
        }
        if(10<choice and choice<14) algomenu(graph_toy, "toy");
        else if (31<=choice and choice<=42) algomenu(graph_medium, "medium");
        else algomenu(graph_real, "real");
    }
}

void Menu::algomenu(Graph g, string flag){
    int choice;
    while(true) {
        cout << "||=====================================================||\n"
                "|| Choose the action you want to perform:              ||\n"
                "|| Backtracking (Toy graphs only)                  [1] ||\n"
                "|| 2-approximation algorithm                       [2] ||\n"
                "|| Heuristic algorithm                             [3] ||\n"
                "|| Ratio between algorithms (not for real graphs)  [4] ||\n"
                "|| Go back                                         [0] ||\n"
                "||=====================================================||\n"
                "Choose an option: ";
        cin >> choice;
        vector<int> values = {0, 1, 2, 3, 4};
        vector<int> a;
        vector<int> b;
        double w;
        auto start = std::chrono::high_resolution_clock::now();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        long long dura;
        double c;
        if (!inputTest(choice, values)) continue;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch(choice){
            case 0:
                return;
            case 1:
                if(flag == "toy"){
                    start = std::chrono::high_resolution_clock::now();
                    a = g.Backtracking();
                    end = std::chrono::high_resolution_clock::now();
                    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                    dura = duration.count();
                    w = g.pathWeight(a);
                    cout << "This is the best path for the graph using the backtracking algorithm:\n";
                    printPath(a);
                    cout << "\nThe total duration is: " << dura << " ms\n";
                    cout << "The total distance is: " << w << "\n";
                    pause();
                }
                else{
                    cout << "As this is not a toy graph, backtracking cannot be performed in a timely manner!";
                    pause();
                };
                break;
            case 2:
                start = std::chrono::high_resolution_clock::now();
                a = g.TSPApproximation();
                end = std::chrono::high_resolution_clock::now();
                duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                dura = duration.count();
                w = g.pathWeight(a);
                cout << "This is the 2-approximation path for the graph:\n";
                printPath(a);
                cout << "\nThe total duration is: " << dura << " ms\n";
                cout << "The total distance is: " << w << "\n";
                pause();
                break;
            case 3:
                if(flag == "real"){
                    cout << "Unfortunately the heuristic algorithm only works for fully connected graphs...";
                    break;
                }
                start = std::chrono::high_resolution_clock::now();
                a = g.DivideConquerClusteredNN();
                end = std::chrono::high_resolution_clock::now();
                duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                dura = duration.count();
                w = g.pathWeight(a);
                cout << "This is the Nearest Neighbor path for the graph:\n";
                printPath(a);
                cout << "\nThe total duration is: " << dura << " ms\n";
                cout << "The total distance is: " << w << "\n";
                pause();
                break;
            case 4:
                if(flag == "real"){
                    cout << "Unfortunately the heuristic algorithm only works for fully connected graphs and Backtracking can´t be performed in a timely manner in the real graphs.";
                    break;
                }
                cout << "Choose the action you want to perform:\n"
                        "*Backtracking vs 2-approximation   [1]\n"
                        "*2-approximation vs heuristic      [2]\n"
                        "Choose an option:";
                cin >> choice;
                if (!inputTest(choice, {1,2})) break;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if(choice == 1){
                    if(flag == "medium"){
                        cout << "As this is not a toy graph, backtracking cannot be performed in a timely manner!\n";
                        break;
                    }
                    a = g.Backtracking();
                    b = g.DivideConquerClusteredNN();
                }
                else{
                    a = g.TSPApproximation();
                    b = g.DivideConquerClusteredNN();
                }

                c = g.ratioBetweentwopaths(a,b);
                cout << "The ratio between the 2 algorithms is: " << c << "\n";
                pause();
                break;
            default:
                break;
        }
    }
}

void Menu::printPath(vector<int> v){
    cout << 0 << " ";
    for(int i=1; i<v.size(); i++){
        cout << "-> " << v[i] << " ";
    }
    cout << "-> " << 0 ;
}

bool Menu:: inputTest(char choice ,vector<int> values) {
    if (cin.fail() || cin.peek() != '\n') {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Invalid input! Try again!" << endl;
        sleep(1);
        return false;
    }
    if (!binary_search(values.begin(),values.end(),choice)) {
        cout << "Invalid choice! Try again!" << endl;
        sleep(1);
        return false;
    }
    return true;
}

void Menu::pause() {
    cout << "\n";
    cout << "Press any key to continue...";
    cin.get();
}
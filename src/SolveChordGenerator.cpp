//
// Created by Damien Sprockeels on 05/07/2024.
//

#include "../headers/SolveChordGenerator.hpp"

vector<ChordGenerator*> solve_chord_progression_problem(int size, Tonality* tonality){
    auto cg = new ChordGenerator(size, tonality);

    BAB<ChordGenerator> engine(cg);
    delete cg;

    vector<ChordGenerator*> sols;

    int n_sols = 1;
    while(ChordGenerator* sol = engine.next()) {
        if (n_sols == 10) break;
        sols.push_back(sol);
        std::cout << "Solution n°" << to_string(n_sols) << ":\n" << sol->pretty() << std::endl;
        delete sol;
        n_sols++;
    }
    std::cout << "Number of solutions: " << n_sols << std::endl;
    return sols;
}
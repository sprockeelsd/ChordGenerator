//
// Created by Damien Sprockeels on 02/07/2024.
//

#include "../headers/ChordGeneratorUtilities.hpp"
#include "../headers/ChordGenerator.hpp"
#include "../headers/SolveChordGenerator.hpp"
#include "../Diatony/c++/headers/aux/MidiFileGeneration.hpp"

int main(int argc, char **argv) {
    string four_voice = argv[1]; /// true if we want to generate the 4voice chords, false if we just want chords and state
    int size = 10;
    Tonality* Cmajor = new MajorTonality(C);

    auto sol = solve_chord_progression_problem_best(size, Cmajor);

    auto chords = IntVarArray_to_int_vector(sol->getChords());
    for (int i = 0; i < chords.size(); i++)
        switch (chords[i]){ //todo handle bII somehow as well as aug6
            case FIVE_OF_TWO:               chords[i] = SIXTH_DEGREE;       break;
            case FIVE_OF_THREE:             chords[i] = SEVENTH_DEGREE;     break;
            case FIVE_OF_FOUR:              chords[i] = FIRST_DEGREE;       break;
            case FIVE_OF_FIVE:              chords[i] = SECOND_DEGREE;      break;
            case FIVE_OF_SIX:               chords[i] = THIRD_DEGREE;       break;
            case FIFTH_DEGREE_APPOGIATURA:  chords[i] = FIRST_DEGREE;       break;
            default:                                                        break;
        }
    std::cout << int_vector_to_string(chords) << std::endl;

    auto states = IntVarArray_to_int_vector(sol->getStates());
    std::cout << int_vector_to_string(states) << std::endl;

    auto qualities = IntVarArray_to_int_vector(sol->getQualities());
    std::cout << int_vector_to_string(qualities) << std::endl;

    if(four_voice == "true"){
        auto diatony_sol = solve_diatony_problem_optimal(size, Cmajor, chords, qualities, states);

        writeSolToMIDIFile(size, "output", diatony_sol);

        std::cout << "MIDI file created." << std::endl;
        std::cout << "\n\n-----------------------------------------------------------------------------------------------------" <<
                  "\n\n \t\t\t\t\tSummary:\n\n" <<  "-----------------------------------------------------------------------------------------------------\n\n" <<
                  sol->pretty() << std::endl << "Solution:\n" << diatony_sol->to_string() << std::endl;
    }
    return 0;
}

#include "../include/solve.hpp"

int find_target_height(int up, int down, int target) {

    if (up == 0 || target == 0) {
        std::cerr << "Error: zero input data" << std::endl; 
        std::exit(1);
    }

    else if (up < 0 || down < 0 || target < 0) {
        std::cerr << "Error: negative input data" << std::endl; 
        std::exit(1);
    }

    else if (up >= target) {
        return 1;
    }

    else if (down >= up && up < target) {
        std::cerr << "Error: impossible to solve input data" << std::endl; 
        std::exit(1);
    }
    else {
        int size = up - down;
        int new_target = target - up;
        int counter = 1 + (new_target + size - 1)/size;
        return counter;
    }
    return 0;
}
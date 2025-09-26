#include "../include/solve.hpp"

int main() {
    int UpSPeed, DownSpeed, desiredHeigth;
    
    std::cout<<"Enter UpSPeed, DownSpeed, desiredHeigth"<<std::endl;
    std::cin >> UpSPeed >> DownSpeed >> desiredHeigth;
    if (std::cin.fail()) {
        std::cerr << "Error: wrong input type (expected integers)" << std::endl;
        std::exit(1); 
    }
    
    std::cout<<find_target_height(UpSPeed, DownSpeed, desiredHeigth)<<std::endl;

    return 0;
}
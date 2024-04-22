//
// Created by 19003 on 2024/4/1.
//

#include <iostream>
#include <memory>
#include<vector>
#include"src/solution4_12.cpp"

#include"src/solution4_6.cpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    using namespace heattransfer;
    Solution4_12 solution_12;
    auto* solution_6 = new Solution_4_6();
    //std::cout << solution_12.GetTime();
    solution_6->PrintAnswer(solution_6->GetFinalAnswer());

    return 0;
}

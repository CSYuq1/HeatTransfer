//
// Created by 19003 on 2024/4/1.
//

#include <iostream>
#include"src/solution4_12.cpp"
#include"src/solution4_6.cpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    using namespace heattransfer;
    auto solution=new Solution4_12();
    std::cout<<solution->GetTime();
    //auto solution =new Solution_4_6;
    //solution->PrintAnswer(solution->GetFinalAnswer());
    return 0;
}

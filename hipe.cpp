#include <iostream>
#include <array>
#include <vector>
#include <chrono>
#include <list>
#include <unordered_map>


int main(){
    auto roll = [](){return rand() % 6 + 1;};
    
    std::vector<int> cont;
    cont.push_back(roll());
    const int* pAddressOfOriginalBegin = &(*cont.begin());

    std::chrono::duration<double> durTime(0);

    while(getc(stdin))
    {
        const int* pAddressBegin = &(*cont.begin());

        std::cout << "Contain " << cont.size() << " elements, took " <<
        std::chrono::duration_cast<std::chrono::microseconds>(durTime).count() << "us\n"; 
        

        for(const int &iter : cont){
            const int *pAddressOfX = &iter;
            int OffsetFromCurrent = pAddressOfX - pAddressBegin;
            int OffsetFromBegin = pAddressOfX - pAddressOfOriginalBegin;
            std::cout << "OffsetFromCurrent - " << OffsetFromCurrent << "  OffsetFromBegin - " << OffsetFromBegin << "\n";

        }

        auto tp1 = std::chrono::high_resolution_clock::now();
        cont.push_back(roll());
        auto tp2 = std::chrono::high_resolution_clock::now();
        durTime = (tp1 - tp2);

    }
}
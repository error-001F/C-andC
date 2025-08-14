#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>
#include <memory>
#include <algorithm>
#include <thread>
#include <string>

class Stats {
    public:
    virtual ~Stats(){};
    virtual void update(double val) = 0;
    virtual double eval() const = 0;
}; 
int a; 

std::unique_ptr<Stats> create_stat_from_name(const std::string_view& name);


int main(int argc, char * argv[]){  

    std::vector<std::unique_ptr<Stats>> stat_ptrs;// вектор из обьектов класса Stats
    for(int i=1; i<argc; ++i){
            stat_ptrs.emplace_back(create_stat_from_name(argv[i])); /*create_stat_from_name нужен для того, чтобы входные данные
унаследовали виртуальный класс Stats и имели тип string_view*/   
    }

    bool anyinput = false;
    double val;
    while(std::cin >> val){
        std::for_each(stat_ptrs.begin(), stat_ptrs.end(), [val](auto& stat_ptr){
            stat_ptr -> update(val);
        });
        anyinput = true;
    }

    //handle invalid input data
    if (!std::cin.eof() && !std::cin.good()){
        std::cerr << "Invalid input data\n";
        return 1;
    }
    if(anyinput){
        std::for_each(stat_ptrs.begin(), stat_ptrs.end(), [](auto& stat_ptr){
            std::cout << std::setw(8) << stat_ptr -> eval();
        });
    }
}
class MeanStats : public Stats{
    public:
    void update(double val) override{
        sum_ += val;
        ++count_;
    }
    double eval() const override{
        return sum_/count_;
    }
    private:
    double sum_ = 0.0;
    size_t count_ = 0;
};
class MinStats : public Stats {
    public:
    void update(double val) override{
        min_ = std::min(min_, val);
    }
    double eval() const override{
        return min_;
    }
    private:
    double min_ = std::numeric_limits<int>::max();
};
class MaxStats : public Stats {
    public:
    void update(double val) override{
        max_ = std::max(max_, val);
    }
    double eval() const override{
        return max_;
    }
    private:
    double max_ = std::numeric_limits<int>::min();
};
std::unique_ptr<Stats> create_stat_from_name(const std::string_view& name){
    // using namespace std::literals;
    if (name == "mean"){
        return std::make_unique<MeanStats>();
    }
    else if(name == "min"){
        return std::make_unique<MinStats>();
    }
    else if (name == "max"){
         return std::make_unique<MaxStats>();
    }
    throw std::invalid_argument("unknown");
}

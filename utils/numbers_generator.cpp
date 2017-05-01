#include <algorithm>
#include <iostream>
#include <fstream>
#include <random>
#include <vector>

int main(int argc, char**argv)
{
    const std::string help_text = R"(
Required arguments: K N filename, where:
 - K : integer, upper bound of generated numbers interval [0, k). For K <= 0, unique numbers from [0, N) will be generated.
 - N : integer, total count of generated numbers.
 - filename : string, name of file to output numbers.)";
    if (argc != 4) {
        std::cout << help_text.c_str() << std::endl;
        return 1;
    }

    const int K = atoi(argv[1]);
    const int N = atoi(argv[2]);
    std::vector<int> numbers(N);
    if (K > 0) {
        for (int& number : numbers)
            number = rand() % K;
    } else {
        for (int i = 0; i < N; ++i)
            numbers[i] = i;
        std::random_shuffle(numbers.begin(), numbers.end());
    }

    std::ofstream output_stream(argv[3], std::ofstream::out);
    output_stream << N << std::endl;
    for (int number : numbers)
        output_stream << number << " ";
    output_stream << std::endl;
    output_stream.close();

    return 0;
}

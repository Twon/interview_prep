#include <catch2/catch.hpp>
#include <sites/codility/prefix_sums/num_zero_sub_arrays.hpp>
#include <random>
#include <iterator>
#include <algorithm>

using namespace std;

namespace {

inline std::vector<int> generate_random_vector(const size_t num, int min, int max)
{
    std::vector<int> results(num);
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(min,max);
    std::generate(results.begin(), results.end(), [&dist, &rng](){ return dist(rng); });
    return results;
};
/*
inline std::vector<int> generate_random_extremes_vector(const size_t num, int min, int max)
{
    std::vector<int> results(num);
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0,1 );
    int extremes[2] = { min, max };
    std::generate(results.begin(), results.end(), [&dist, &rng, &extremes](){ return extremes[dist(rng)]; });
    return results;
};*/

}

TEST_CASE("Example test for num_zero_sub_arrays", "[num_zero_sub_arrays.example]")
{
    vector inputs = {2, -2, 3, 0, 4, -7};

    auto expected = num_zero_sub_arrays_bruteforce(inputs);
    auto actual = num_zero_sub_arrays(inputs);

    REQUIRE(expected == 4);
    REQUIRE(expected == actual);
}

TEST_CASE("Simple 1 test for num_zero_sub_arrays", "[num_zero_sub_arrays.simple1]")
{
    vector inputs = {6, 3, -1, -3, 4, -2, 2, 4, 6, -12, -7};

    auto expected = num_zero_sub_arrays_bruteforce(inputs);
    auto actual = num_zero_sub_arrays(inputs);

    REQUIRE(expected == 5);
    REQUIRE(expected == actual);
}


TEST_CASE("Small random for num_zero_sub_arrays: random, N = ~100", "[num_zero_sub_arrays.small_random]")
{
    vector inputs = generate_random_vector(100, -10000, 10000);

    auto expected = num_zero_sub_arrays_bruteforce(inputs);
    auto actual = num_zero_sub_arrays(inputs);

    REQUIRE(expected == actual);
}

TEST_CASE("Medium random for num_zero_sub_arrays: random, N = ~700", "[num_zero_sub_arrays.medium_random]")
{
    vector inputs = generate_random_vector(700, -10000, 10000);

    auto expected = num_zero_sub_arrays_bruteforce(inputs);
    auto actual = num_zero_sub_arrays(inputs);

    REQUIRE(expected == actual);
}

/*
TEST_CASE("Large ones for num_zero_sub_arrays: numbers from -1 to 1, N = ~100,000", "[num_zero_sub_arrays.large_ones]")
{
    vector inputs = generate_random_vector(100000, -1, 1);

    auto expected = num_zero_sub_arrays_bruteforce(inputs);
    auto actual = num_zero_sub_arrays(inputs);

    REQUIRE(expected == actual);
}

TEST_CASE("Large random for num_zero_sub_arrays: numbers from -10,000 to 10,000, N = ~100,000", "[num_zero_sub_arrays.large_random]")
{
    vector inputs = generate_random_vector(100000, -10000, 10000);

    auto expected = num_zero_sub_arrays_bruteforce(inputs);
    auto actual = num_zero_sub_arrays(inputs);

    REQUIRE(expected == actual);
}

TEST_CASE("Extreme values for num_zero_sub_arrays: all maximal values, N = ~100,000", "[num_zero_sub_arrays.extreme_values]")
{
    vector inputs = generate_random_extremes_vector(100000, -10000, 10000);

    auto expected = num_zero_sub_arrays_bruteforce(inputs);
    auto actual = num_zero_sub_arrays(inputs);

    REQUIRE(expected == actual);
}*/
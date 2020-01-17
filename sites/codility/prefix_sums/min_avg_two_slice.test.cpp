#include <catch2/catch.hpp>
#include <sites/codility/prefix_sums/min_avg_two_slice.hpp>
#include <random>
#include <iterator>
#include <algorithm>

using namespace std;

inline std::vector<int> generate_random_vector(const size_t num, int min, int max)
{
    std::vector<int> results(num);
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(min,max);
    std::generate(results.begin(), results.end(), [&dist, &rng](){ return dist(rng); });
    return results;
};

inline std::vector<int> generate_random_extremes_vector(const size_t num, int min, int max)
{
    std::vector<int> results(num);
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0,1 );
    int extremes[2] = { min, max };
    std::generate(results.begin(), results.end(), [&dist, &rng, &extremes](){ return extremes[dist(rng)]; });
    return results;
};

TEST_CASE("Example test for min_avg_two_slice", "[min_avg_two_slice.example]")
{
    vector inputs = {4, 2, 2, 5, 1, 5, 8};

    auto expected = min_avg_two_slice_bruteforce(inputs);
    auto actual = min_avg_two_slice(inputs);

    REQUIRE(expected == 1);
    REQUIRE(expected == actual);
}

TEST_CASE("Simple 1 test for min_avg_two_slice", "[min_avg_two_slice.simple1]")
{
    vector inputs = {-3, -5, -8, -4, -10};

    auto expected = min_avg_two_slice_bruteforce(inputs);
    auto actual = min_avg_two_slice(inputs);

    REQUIRE(expected == 2);
    REQUIRE(expected == actual);
}

TEST_CASE("Small random for min_avg_two_slice: random, N = ~100", "[min_avg_two_slice.small_random]")
{
    vector inputs = generate_random_vector(100, -10000, 10000);

    auto expected = min_avg_two_slice_reference(inputs);
    auto actual = min_avg_two_slice(inputs);

    REQUIRE(expected == actual);
}

TEST_CASE("Medium random for min_avg_two_slice: random, N = ~700", "[min_avg_two_slice.medium_random]")
{
    vector inputs = generate_random_vector(700, -10000, 10000);

    auto expected = min_avg_two_slice_reference(inputs);
    auto actual = min_avg_two_slice(inputs);

    REQUIRE(expected == actual);
}

TEST_CASE("Large ones for min_avg_two_slice: numbers from -1 to 1, N = ~100,000", "[min_avg_two_slice.large_ones]")
{
    vector inputs = generate_random_vector(100000, -1, 1);

    auto expected = min_avg_two_slice_reference(inputs);
    auto actual = min_avg_two_slice(inputs);

    REQUIRE(expected == actual);
}

TEST_CASE("Large random for min_avg_two_slice: numbers from -10,000 to 10,000, N = ~100,000", "[min_avg_two_slice.large_random]")
{
    vector inputs = generate_random_vector(100000, -10000, 10000);

    auto expected = min_avg_two_slice_reference(inputs);
    auto actual = min_avg_two_slice(inputs);

    REQUIRE(expected == actual);
}

TEST_CASE("Extreme values for min_avg_two_slice: all maximal values, N = ~100,000", "[min_avg_two_slice.extreme_values]")
{
    vector inputs = generate_random_extremes_vector(100000, -10000, 10000);

    auto expected = min_avg_two_slice_reference(inputs);
    auto actual = min_avg_two_slice(inputs);

    REQUIRE(expected == actual);
}
//
// Created by Antony Peacock on 16/01/2020.
//

#include "min_avg_two_slice.hpp"


// you can use includes, for example:
// #include <algorithm>
#include <vector>
#include <numeric>
#include <limits>
#include <iterator>

using namespace std;

int min_avg_two_slice(std::vector<int> &A) {

    vector<int> partial(A.size()+1);
    partial[0]=0;
    partial_sum(A.begin(), A.end(), partial.begin()+1);

    int min_slice_start = numeric_limits<int>::max();
    int current_slice_start = 0;
    auto min_average = ((A[0] + A[1]) / 2.0);

    for (int i = 2; i < static_cast<int>(A.size()); ++i)
    {
        auto average_of_previous = ((partial[i+1] - partial[current_slice_start]) / i - current_slice_start + 1 );
        auto average_of_two = ((A[i-1] + A[i]) / 2.0);

        auto current_average = average_of_previous;
        if (average_of_two < current_average)
        {
            current_average = average_of_two;
            current_slice_start = i-1;
        }

        if (current_average < min_average)
        {
            min_average = current_average;
            min_slice_start = current_slice_start;
        }
    }

    return min_slice_start;
}
#include "min_avg_two_slice.hpp"


// you can use includes, for example:
// #include <algorithm>
#include <numeric>
#include <limits>
#include <iterator>

using namespace std;

/*! This brute force is horribly slow, don't try to use this without having something to occupy your self in the mean
    time.

    O(n^3)

 */
int min_avg_two_slice_bruteforce(vector<int> &A)
{
    // write your code in C++14 (g++ 6.2.0)
    double min = numeric_limits<double>::max();
    int min_slice_start = numeric_limits<int>::max();

    for (int i = 0; i < static_cast<int>(A.size())-1; ++i)
    {
        for (int j = i+1; j < static_cast<int>(A.size()); ++j)
        {
            const double slice = accumulate(A.begin()+i, A.begin()+j+1, 0.0) / (j-i+1);
            if (slice < min)
            {
                //cout << slice << " < " << min << " && " << i << " < " << min_slice_start << endl;
                min = slice;
                min_slice_start = i;
            }
            else if (slice == min && i < min_slice_start)
            {
                min_slice_start = i;
            }
        }
    }
    //cout << min << endl;
    return min_slice_start;
}

/*! This solution is from here: https://www.martinkysel.com/codility-minavgtwoslice-solution/. Personally I didn't think
    I'd be able to solve the problem like this in an interview, I certainly wouldn't write a mathematical proof to
    verify what I had done.  See the below solution for a much more intuative solution.  However this is useful as
    a reference for comparing results, which is not as slow as the bruteforce.

def solution(A):
    min_idx = 0
    min_value = 10001

    for idx in xrange(0, len(A)-1):
        if (A[idx] + A[idx+1])/2.0 < min_value:
            min_idx = idx
            min_value = (A[idx] + A[idx+1])/2.0
        if idx < len(A)-2 and (A[idx] + A[idx+1] + A[idx+2])/3.0 < min_value:
            min_idx = idx
            min_value = (A[idx] + A[idx+1] + A[idx+2])/3.0

    return min_idx
*/
int min_avg_two_slice_reference(std::vector<int> &A)
{
    auto min_idx = 0;
    auto min_value = 10001.0;

    for (int idx = 0; idx < static_cast<int>(A.size()-1); ++idx)
    {
        if ((A[idx] + A[idx + 1])/2.0 < min_value)
        {
            min_idx = idx;
            min_value = static_cast<double>(A[idx] + A[idx + 1]) / 2.0;
        }
        if (idx < static_cast<int>(A.size()-2) && (A[idx] + A[idx + 1] + A[idx + 2]) / 3.0 < min_value)
        {
            min_idx = idx;
            min_value = static_cast<double>(A[idx] + A[idx + 1] + A[idx + 2]) / 3.0;
        }
    }

    return min_idx;
}

/*! This algorithm uses a modified version of Kadane's algorithm for the Maximum Sub Array problem as described here:
    https://stackoverflow.com/a/52616898/4764531

    A few helpful links:
    - https://en.wikipedia.org/wiki/Maximum_subarray_problem#Kadane's_algorithm
    - https://medium.com/@rsinghal757/kadanes-algorithm-dynamic-programming-how-and-why-does-it-work-3fd8849ed73d

    O(n)
 */
int min_avg_two_slice(std::vector<int> &A)
{
    vector<int> partial(A.size()+1);
    partial[0]=0;
    partial_sum(A.begin(), A.end(), partial.begin()+1);

    int min_slice_start = 0;
    int current_slice_start = 0;
    auto min_average = ((A[0] + A[1]) / 2.0);

    for (int i = 2; i < static_cast<int>(A.size()); ++i)
    {
        auto average_of_previous = ((partial[i+1] - partial[current_slice_start]) /
                                    static_cast<double>(i - current_slice_start + 1 ));
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
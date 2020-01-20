#include "num_zero_sub_arrays.hpp"
#include <numeric>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <string>

using namespace std;

/*! This brute force is horribly slow, don't try to use this without having something to occupy your self in the mean
    time.

    O(n^3)

 */
int num_zero_sub_arrays_bruteforce(vector<int> &A)
{
    // write your code in C++14 (g++ 6.2.0)
    int count = 0;
    for (int i = 0; i < static_cast<int>(A.size()); ++i)
    {
        for (int j = i; j < static_cast<int>(A.size()); ++j)
        {
            const double sub_total = accumulate(A.begin()+i, A.begin()+j+1, 0.0) / (j-i+1);
            if (sub_total == 0)
            {
                //cout << slice << " < " << min << " && " << i << " < " << min_slice_start << endl;
                count++;
            }
        }
    }
    //cout << min << endl;
    return count;
}

//int num_zero_sub_arrays_reference(std::vector<int> &A);


int print_num_zero_sub_arrays(vector<int> &A)
{
    using subarray = pair<int, int>;

    // We store a map for each unique partial sum of the possible indices with this partial sum.
    unordered_map<int, vector<int>> sum_indices;
    vector<subarray> zero_subarrays;

    auto sum = 0;
    for (int i = 0; i < static_cast<int>(A.size()); ++i)
    {
        sum+=A[i];

        // Any sum of is a sub array of from the start to i
        if (sum == 0)
        {
            zero_subarrays.push_back(make_pair(0, i));
        }

        const auto prev_sums = sum_indices.find(sum);
        if (prev_sums != sum_indices.end())
        {
            const auto& prev_sums_idx = prev_sums->second;
            for_each(
                    prev_sums_idx.begin(),
                    prev_sums_idx.end(),
                    [&zero_subarrays, &i](auto idx)
                    {
                        zero_subarrays.push_back(make_pair(idx+1, i));
                    }
            );
        }

        sum_indices[sum].push_back(i);
    }

    cout << "Sub arrays for [";
    copy(A.begin(), A.end(), ostream_iterator<int>(cout, ", "));
    cout << "] are:" << endl;
    for_each(
            zero_subarrays.begin(),
            zero_subarrays.end(),
            [](const auto& i)
            {
                cout << i.first << ", " << i.second << endl;
            }
    );

    return zero_subarrays.size();
//    return count;
}

/*!
    O(n)
 */
int num_zero_sub_arrays(vector<int> &A)
{
/*    int count = 0;

    // We store a map for each unique partial sum of the possible indices with this partial sum.
    unordered_map<int, int> sum_indices = { {0, 1}};
    vector<int> partial(A.size()+1 );
    partial_sum(
        A.begin(),
        A.end(),
        next(partial.begin()),
        [&count, &sum_indices](auto lhs, auto rhs)
        {
            lhs += rhs;
            auto& sum = sum_indices[lhs];
            count += sum;
            sum++;
            return lhs;
        }
    );
    return count;*/


    int count = 0;
    auto sum = 0;
    // Start with an implicit sum of zero before we start calculating the partial sum.
    unordered_map<int, int> sum_indices = { {0, 1}};
    for (int i = 0; i < static_cast<int>(A.size()); ++i)
    {
        sum+=A[i];

        // Any sum of is a sub array of from the start to i
        /*if (sum == 0)
        {
            count++;
            //zero_subarrays.push_back(make_pair(0, i));
        }*/

        const auto prev_sums = sum_indices.find(sum);
        if (prev_sums != sum_indices.end())
        {
            count += prev_sums->second;
        }

        sum_indices[sum] += 1;
    }

    //print_num_zero_sub_arrays(A);
    return count;
}
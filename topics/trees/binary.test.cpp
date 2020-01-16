#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <topics/trees/binary.hpp>
#include <iterator>

using namespace std;

const auto unordered_create_binary_tree()
{
    vector input = {1,2,3,4,5,6,7,8,9,10};
    reverse(input.begin(), input.end());
    return sorted_array_to_bst(input,0, static_cast<int>(input.size())-1);
}

TEST_CASE("Example test", "[example]")
{
    GIVEN("A binary search tree created from a list of 1 - 10")
    {
        vector inputs = {1,2,3,4,5,6,7,8,9,10};
        binary_node* tree = create_binary_search_tree(inputs);
        //print_tree(tree, cout);


        WHEN("First prove detecting an invalid binary tree works")
        {
            auto unordered_binary_tree = unordered_create_binary_tree();
            REQUIRE(!is_binary_search_tree(unordered_binary_tree));

            THEN("Once falsified then demonstrate it works on a binary search tree")
            {
                REQUIRE(is_binary_search_tree(tree));
            }
        }
        WHEN("Performing a breadth first search")
        {
            const auto levels = breadth_first_iterative(tree);
            THEN("Expect a tree or four levels with the following entries")
            {
                REQUIRE(levels.size() == 4);
                REQUIRE(levels[0] == vector{5});
                REQUIRE(levels[1] == vector{2, 8});
                REQUIRE(levels[2] == vector{1, 3, 6, 9});
                REQUIRE(levels[3] == vector{4, 7, 10});
            }
        }
        WHEN("Performing using recusive iterations")
        {
            THEN("Confirm the expected output order of elements")
            {
                REQUIRE(preorder_recursive(tree) == vector{5, 2, 1, 3, 4, 8, 6, 7, 9, 10});
                REQUIRE(inorder_recursive(tree) == vector{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
                REQUIRE(postorder_recursive(tree) == vector{1, 4, 3, 2, 7, 6, 10, 9, 8, 5});
            }
        }

        destroy_binary_tree(tree);
        REQUIRE(tree == nullptr);
    }








}

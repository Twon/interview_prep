
#pragma once

#include <vector>
#include <algorithm>
#include <cassert>
#include <functional>
#include <string_view>
#include <numeric>

struct binary_node
{
    int data = 0;
    binary_node* left = nullptr;
    binary_node* right = nullptr;
};

binary_node* create_binary_search_tree(std::vector<int> input);
void destroy_binary_tree(binary_node*& tree);
bool is_binary_search_tree(binary_node* tree, int min = std::numeric_limits<int>::min(), int max = std::numeric_limits<int>::max());
binary_node* sorted_array_to_bst(const std::vector<int>& input, int start, int end);
std::vector<int> preorder_recursive(binary_node* node);
std::vector<int> inorder_recursive(binary_node* node);
std::vector<int> postorder_recursive(binary_node* node);
std::vector<std::vector<int>> breadth_first_iterative(binary_node* node);
void print_tree(binary_node* node, std::ostream& stream, const std::string_view& seperator = " ");
#include <topics/trees/binary.hpp>
#include <deque>
#include <ostream>

using namespace std;

binary_node* create_binary_search_tree(std::vector<int> input)
{
    if (input.empty())
        return nullptr;

    std::sort(input.begin(), input.end());
    return sorted_array_to_bst(input,0, static_cast<int>(input.size())-1);
}

void destroy_binary_tree(binary_node*& tree)
{
    if (!tree)
        return;

    destroy_binary_tree(tree->left);
    destroy_binary_tree(tree->right);
    delete tree;
    tree = nullptr;
}

binary_node* sorted_array_to_bst(const std::vector<int>& input, int start, int end)
{
    if (start > end)
        return nullptr;

    const auto mid = (start + end) / 2;
    auto node = new binary_node{};
    node->data = input[mid];
    node->left = sorted_array_to_bst(input, start, mid - 1);
    node->right = sorted_array_to_bst(input,mid+1, end);
    return node;
}

std::vector<int> preorder_recursive(binary_node* node)
{
    if (!node)
        return vector<int>{};

    vector<int> results{node->data};
    std::vector<int> left = preorder_recursive(node->left);
    std::vector<int> right = preorder_recursive(node->right);
    results.insert(results.end(), left.begin(), left.end());
    results.insert(results.end(), right.begin(), right.end());
    return results;
}

std::vector<int> inorder_recursive(binary_node* node)
{
    if (!node)
        return vector<int>{};

    vector<int> results;
    std::vector<int> left = inorder_recursive(node->left);
    std::vector<int> right = inorder_recursive(node->right);
    results.insert(results.end(), left.begin(), left.end());
    results.push_back(node->data);
    results.insert(results.end(), right.begin(), right.end());
    return results;
}

std::vector<int> postorder_recursive(binary_node* node)
{
    if (!node)
        return vector<int>{};

    vector<int> results;
    std::vector<int> left = postorder_recursive(node->left);
    std::vector<int> right = postorder_recursive(node->right);
    results.insert(results.end(), left.begin(), left.end());
    results.insert(results.end(), right.begin(), right.end());
    results.push_back(node->data);
    return results;
}

std::vector<std::vector<int>> breadth_first_iterative(binary_node* node)
{
    vector<vector<int>> results;
    if (!node)
        return results;

    deque<binary_node*> next_level = {node};
    while(!next_level.empty())
    {
        deque<binary_node*> current;
        current.swap(next_level);

        vector<int> level_values;
        while(!current.empty())
        {
            auto node = current.front();
            current.pop_front();

            level_values.push_back(node->data);
            if (node->left)
                next_level.push_back(node->left);
            if (node->right)
                next_level.push_back(node->right);
        }
        results.emplace_back(std::move(level_values));
    }

    return results;
}


void print_tree(binary_node* node, ostream& stream, const string_view& seperator)
{
    deque<binary_node*> next_level = {node};
    while(!next_level.empty())
    {
        deque<binary_node*> current;
        current.swap(next_level);

        vector<int> level_values;
        while(!current.empty())
        {
            auto node = current.front();
            current.pop_front();

            if (node)
            {
                stream << node->data << seperator;
                next_level.push_back(node->left);
                next_level.push_back(node->right);
            }
            else
            {
                stream << "null" << seperator;
            }
        }
        stream << endl;
    }
}
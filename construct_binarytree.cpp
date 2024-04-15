#include <exception>
#include <iostream>
#include <cstring>
using namespace std;

struct BinaryTreeNode {
    int value;
    BinaryTreeNode* left;
    BinaryTreeNode* right;
    BinaryTreeNode(int v)
        : value(v)
        , left(nullptr)
        , right(nullptr)
    {
    }
};

BinaryTreeNode* ConstructCore(int* startPreorder, int* endPreorder, int* startInorder, int* endInorder)
{
    auto root = new BinaryTreeNode(*startPreorder);
    if (startPreorder == endPreorder) {
        if (*startPreorder == *startInorder && startInorder == endInorder)
            return root;
        else
            throw std::runtime_error("Invalid input.");
    }

    int leftLength = 0;
    int rightLength = 0;
    int *pos = nullptr;
    for (pos = startInorder; pos <= endInorder; ++pos) {
        if (*pos == root->value) {
            leftLength = pos - startInorder;
            rightLength = endInorder - pos;
            break;
        }
    }
    if (leftLength > 0) {
        root->left = ConstructCore(startPreorder+1, startPreorder+leftLength, startInorder, pos - 1);
    }
    if (rightLength > 0) {
        root->right = ConstructCore(startPreorder+leftLength + 1, endPreorder, pos + 1, endInorder);
    }
    return root;
}
BinaryTreeNode* Construct(int* preOrder, int* inOrder, int length)
{
    if (preOrder == nullptr || inOrder == nullptr || length <= 0)
        return nullptr;
    return ConstructCore(preOrder, preOrder + length - 1, inOrder, inOrder + length - 1);
}
int main()
{
    int preOrder[] = { 1, 2, 4, 7, 3, 5, 6, 8 };
    int inOrder[] = { 4, 7, 2, 1, 5, 3, 8, 6 };
    Construct(preOrder, inOrder, sizeof(preOrder)/sizeof(int));
}
#ifndef AVL_IMPL_H
#define AVL_IMPL_H

#include <algorithm>
#include <cstdlib>
#include <vector>

#include "avl.h"

// AVLNode

template <typename T>
AVLNode<T>::AVLNode(T value)
    : data(value), left(nullptr), right(nullptr), height(0) {}

// AVLTree

template <typename T>
AVLTree<T>::AVLTree() : root(nullptr) {}

template <typename T>
int AVLTree<T>::height(AVLNode<T> *node)
{
    // COMPLETE HERE
}

template <typename T>
int AVLTree<T>::getBalance(AVLNode<T> *node)
{
    // COMPLETE HERE
}

template <typename T>
AVLNode<T> *AVLTree<T>::rightRotate(AVLNode<T> *y)
{
    // COMPLETE HERE
}

// Rotación izquierda
template <typename T>
AVLNode<T> *AVLTree<T>::leftRotate(AVLNode<T> *x)
{
    // COMPLETE HERE
}

template <typename T>
AVLNode<T> *AVLTree<T>::minValueNode(AVLNode<T> *node)
{
    // COMPLETE HERE
}

// Inserción
template <typename T>
AVLNode<T> *AVLTree<T>::insert(AVLNode<T> *node, T key)
{
    // COMPLETE HERE
}

// Eliminar un nodo
template <typename T>
AVLNode<T> *AVLTree<T>::remove(AVLNode<T> *root, T key)
{
    // COMPLETE HERE
}

// Búsqueda
template <typename T>
bool AVLTree<T>::search(AVLNode<T> *node, T key)
{
    // COMPLETE HERE
}

// Recorrido preorder
template <typename T>
void AVLTree<T>::preorder(AVLNode<T> *root, std::vector<T> &ret)
{
    // COMPLETE HERE
}

// Recorrido inorder
template <typename T>
void AVLTree<T>::inorder(AVLNode<T> *root, std::vector<T> &ret)
{
    // COMPLETE HERE
}

// Recorrido postorder
template <typename T>
void AVLTree<T>::postorder(AVLNode<T> *root, std::vector<T> &ret)
{
    // COMPLETE HERE
}

/// Public functions

template <typename T>
void AVLTree<T>::insert(T key)
{
    // COMPLETE HERE
    AVLNode<T> nexter = root;
    while (nexter != nullptr)
    {
        if (nexter->data == key)
            return;
        if (nexter->data > key)
        {
            if (nexter->left != nullptr)
            {
                nexter = nexter->left;
            }
            else
            {
                AVLNode<T> newNode = new AVLNode<T>(key);
                nexter->neft = newNode;
            }
        }
        else
        {
            if (nexter->right != nullptr)
            {
                nexter = nexter->right;
            }
            else
            {
                AVLNode<T> newNode = new AVLNode<T>(key);
                nexter->right = newNode; // 1 2 3 4 5
            }
        }
    }
}

template <typename T>
void AVLTree<T>::remove(T key)
{
    // COMPLETE HERE
}

template <typename T>
bool AVLTree<T>::search(T key)
{
    // COMPLETE HERE
    AVLNode<T> nexter = root;
    while (nexter != nullptr)
    {
        if (nexter->data == key)
            return true;
        if (nexter->data > key)
            nexter = nexter->left;
        else
            nexter = nexter->right;
    }
    return false;
}

template <typename T>
std::vector<T> AVLTree<T>::preorderTraversal()
{
    // COMPLETE HERE
    std::vector<T> preorderVector;
    auto preorder = [&preorderVector](auto &self, AVLNode<T> *&root) -> void
    {
        if (root == nullptr)
            return;
        preorderVector.push_back(root->data);
        self(self, root->left);
        self(self, root->right);
    };
    preorder(preorder, root);
    return preorderVector;
}

template <typename T>
std::vector<T> AVLTree<T>::inorderTraversal()
{
    // COMPLETE HERE
    std::vector<T> inorderVector;
    auto inorder = [&inorderVector](auto &self, AVLNode<T> *&root) -> void
    {
        if (root == nullptr)
            return;
        self(self, root->left);
        inorderVector.push_back(root->data);
        self(self, root->right);
    };
    inorder(inorder, root);
    return inorderVector;
}

template <typename T>
std::vector<T> AVLTree<T>::postorderTraversal()
{
    // COMPLETE HERE
    std::vector<T> postorderVector;
    auto postorder = [&postorderVector](auto &self, AVLNode<T> *&root) -> void
    {
        if (root == nullptr)
            return;
        self(self, root->left);
        self(self, root->right);
        postorderVector.push_back(root->data);
    };
    postorder(postorder, root);
    return postorderVector;
}

template <typename T>
int AVLTree<T>::height()
{
    // COMPLETE HERE
    return root->height;
}

template <typename T>
bool AVLTree<T>::isBalanced()
{
    // COMPLETE HERE
    if (root == nullptr)
        return true;
    int left{}, right{};
    if (root->left != nullptr)
        left = root->left->height;
    if (root->right != nullptr)
        left = root->right->height;
    return std::abs(left - right) < 2;
}

#endif

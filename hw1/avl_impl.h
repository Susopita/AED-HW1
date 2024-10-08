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
    return node == nullptr ? 0 : node->height;
}

template <typename T>
int AVLTree<T>::getBalance(AVLNode<T> *node)
{
    // COMPLETE HERE
    return node == nullptr ? 0 : height(node->left) - height(node->right);
}

template <typename T>
AVLNode<T> *AVLTree<T>::rightRotate(AVLNode<T> *y)
{
    // COMPLETE HERE
    AVLNode<T> *x = y->left;
    AVLNode<T> *T2 = x->right;

    // Rotación
    x->right = y;
    y->left = T2;

    // Actualizar alturas
    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    // Retornar nueva raíz
    return x;
}

// Rotación izquierda
template <typename T>
AVLNode<T> *AVLTree<T>::leftRotate(AVLNode<T> *x)
{
    // COMPLETE HERE
    AVLNode<T> *y = x->right;
    AVLNode<T> *T2 = y->left;

    // Rotación
    y->left = x;
    x->right = T2;

    // Actualizar alturas
    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    // Retornar nueva raíz
    return y;
}

template <typename T>
AVLNode<T> *AVLTree<T>::minValueNode(AVLNode<T> *node)
{
    // COMPLETE HERE
    AVLNode<T> *current = node;

    // El nodo más a la izquierda es el menor
    while (current->left != nullptr)
    {
        current = current->left;
    }
    return current;
}

// Inserción
template <typename T>
AVLNode<T> *AVLTree<T>::insert(AVLNode<T> *node, T key)
{
    // COMPLETE HERE
    // 1. Inserción normal de BST
    if (!node)
    {
        return new AVLNode<T>(key); // Crear un nuevo nodo
    }

    if (key < node->data)
    {
        node->left = insert(node->left, key);
    }
    else if (key > node->data)
    {
        node->right = insert(node->right, key);
    }
    else
    {
        // No permitimos claves duplicadas
        return node;
    }

    // 2. Actualizar la altura de este nodo ancestro
    node->height = 1 + std::max(height(node->left), height(node->right));

    // 3. Obtener el factor de balance de este nodo para ver si está desbalanceado
    int balance = getBalance(node);

    // 4. Si el nodo está desbalanceado, hay 4 casos:
    // Agregamos verificación de que node->left y node->right no sean nullptr antes de acceder a sus datos.

    // Caso 1: Desbalance a la izquierda-izquierda (Left-Left)
    if (balance > 1 && node->left && key < node->left->data)
    {
        return rightRotate(node);
    }

    // Caso 2: Desbalance a la derecha-derecha (Right-Right)
    if (balance < -1 && node->right && key > node->right->data)
    {
        return leftRotate(node);
    }

    // Caso 3: Desbalance a la izquierda-derecha (Left-Right)
    if (balance > 1 && node->left && key > node->left->data)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Caso 4: Desbalance a la derecha-izquierda (Right-Left)
    if (balance < -1 && node->right && key < node->right->data)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Retornar el puntero del nodo (sin cambios si no se desbalanceó)
    return node;
}

// Eliminar un nodo
template <typename T>
AVLNode<T> *AVLTree<T>::remove(AVLNode<T> *root, T key)
{
    // COMPLETE HERE
    // 1. Realizar la eliminación estándar de BST
    if (root == nullptr)
    {
        return root; // Árbol vacío
    }

    // Buscar el nodo a eliminar
    if (key < root->data)
    {
        root->left = remove(root->left, key);
    }
    else if (key > root->data)
    {
        root->right = remove(root->right, key);
    }
    else
    {
        // Nodo encontrado

        // Caso 1: Nodo con un solo hijo o sin hijos
        if (root->left == nullptr || root->right == nullptr)
        {
            AVLNode<T> *temp = root->left ? root->left : root->right;

            // Caso de no tener hijos
            if (temp == nullptr)
            {
                temp = root;
                root = nullptr;
            }
            else
            {
                // Caso de tener un solo hijo
                *root = *temp; // Copiar los datos del hijo en el nodo actual
            }
            delete temp; // Eliminar el nodo temporal
        }
        // Caso 2: Nodo con dos hijos
        else
        {
            // Obtener el sucesor (el nodo con el valor mínimo en el subárbol derecho)
            AVLNode<T> *temp = minValueNode(root->right);

            // Copiar los datos del sucesor en el nodo actual
            root->data = temp->data;

            // Eliminar el sucesor
            root->right = remove(root->right, temp->data);
        }
    }

    // Si el árbol tenía solo un nodo, regresa
    if (root == nullptr)
    {
        return root;
    }

    // 2. Actualizar la altura del nodo actual
    root->height = 1 + std::max(height(root->left), height(root->right));

    // 3. Obtener el factor de balance del nodo actual
    int balance = getBalance(root);

    // 4. Balancear el árbol si es necesario
    // Caso 1: Left Left
    if (balance > 1 && getBalance(root->left) >= 0)
    {
        return rightRotate(root);
    }

    // Caso 2: Left Right
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Caso 3: Right Right
    if (balance < -1 && getBalance(root->right) <= 0)
    {
        return leftRotate(root);
    }

    // Caso 4: Right Left
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    // 5. Retornar el nodo
    return root;
}

// Búsqueda
template <typename T>
bool AVLTree<T>::search(AVLNode<T> *node, T key)
{
    // COMPLETE HERE
    if (node->data == key)
        return true;
    if (node->data > key)
        return search(node->left, key);
    if (node->data < key)
        return search(node->right, key);
    return false;
}

// Recorrido preorder
template <typename T>
void AVLTree<T>::preorder(AVLNode<T> *root, std::vector<T> &ret)
{
    // COMPLETE HERE
    if (root == nullptr)
        return;
    ret.push_back(root->data);
    preorder(root->left, ret);
    preorder(root->right, ret);
}

// Recorrido inorder
template <typename T>
void AVLTree<T>::inorder(AVLNode<T> *root, std::vector<T> &ret)
{
    // COMPLETE HERE
    if (root == nullptr)
        return;
    inorder(root->left, ret);
    ret.push_back(root->data);
    inorder(root->right, ret);
}

// Recorrido postorder
template <typename T>
void AVLTree<T>::postorder(AVLNode<T> *root, std::vector<T> &ret)
{
    // COMPLETE HERE
    if (root == nullptr)
        return;
    postorder(root->left, ret);
    postorder(root->right, ret);
    ret.push_back(root->data);
}

/// Public functions

template <typename T>
void AVLTree<T>::insert(T key)
{
    // COMPLETE HERE
    root = insert(root, key);
    return;
}

template <typename T>
void AVLTree<T>::remove(T key)
{
    // COMPLETE HERE
    root = remove(root, key);
    return;
}

template <typename T>
bool AVLTree<T>::search(T key)
{
    // COMPLETE HERE
    return search(root, key);
}

template <typename T>
std::vector<T> AVLTree<T>::preorderTraversal()
{
    // COMPLETE HERE
    std::vector<T> ret;
    preorder(root, ret);
    return ret;
}

template <typename T>
std::vector<T> AVLTree<T>::inorderTraversal()
{
    // COMPLETE HERE
    std::vector<T> ret;
    inorder(root, ret);
    return ret;
}

template <typename T>
std::vector<T> AVLTree<T>::postorderTraversal()
{
    // COMPLETE HERE
    std::vector<T> ret;
    postorder(root, ret);
    return ret;
}

template <typename T>
int AVLTree<T>::height()
{
    // COMPLETE HERE
    return height(root);
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

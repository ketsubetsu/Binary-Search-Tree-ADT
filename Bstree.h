/**
 * The specification for an extensible parametric binary search tree.
 * @author ketsubetsu
 * <pre>
 * File: Bstree.h
 * </pre>
 */

#include <string>
#include <iostream>
#include <stdexcept>
#include <iostream>
#include <algorithm>

#ifndef BSTREE_H
#define BSTREE_H

using namespace std;

/**
 * for report exceptions for the BSTree class
 */
class BstreeException
{
private:
   /**
    * a description of why the exception occurred
    */
   string message;
public:
   /**
    * creates an instance of this class
    * @param msg the reason for the exception
    */
   BstreeException(const string& msg)
   {
      message = msg;
   }
   /**
    * Gives the reason for the exception
    * @return the reason for the exception
    */
   string what() const
   {
      return message;
   }
};

/**
 * A parametric extensible binary search tree class
 * @param <T> the binary search tree data type
 */
template <typename T>
class Bstree
{
private:
   /**
    * forward declaration of a function pointer of type (const T&) -> void
    */
   typedef void (*FuncType)(const T& item);
  /**
   * Constructs an empty binary search tree;
   */
   /**
    * forward declaration of the Node class
    */
   template <typename U> class Node;
   /**
    * the number of nodes in this tree
    */
   long order;
   /**
    * A pointer to the root node of this tree
    */
   Node<T>* root;
   /**
    * An auxiliary recursive function for the destructor.
    * @param subtreRoot a pointer to the root of a subtree of this tree
    */
   void recDestroy(Node<T>* subtreeRoot);
   /**
    * Give a pointer to the parent node of the specified Node
    * @param node the node whose parent node is to be found
    * @return the pointer to the parent node of the specified Node
    */
   Node<T>* findParent(Node<T>* node);
   /**
    * Traverses this tree in inorder
    * @param node a node of this tree
    * @param apply a pointer to a function of type (const T&) -> void
    * that is applied to the data field in the specified node
    */
   void inorderTraverse (Node<T>* node, FuncType apply) const;
   /**
    * Removes the specified node from the tree
    * @param node a pointer to the node to be removed
    * @return true if the node is removed; otherwise false
    */
   bool remove(Node<T>* node);
   /**
    * searches for the specified item in this tree
    * @param item the search key
    * @return a pointer to the node containing the item if it is found;
    * otherwise, nullptr
    */
   Node<T>* search(const T& item) const;

   /****** BEGIN: AUGMENTED PRIVATE FUNCTIONS ******/

   /**
    * Traverses this tree in preorder
    * @param node a node of this tree
    * @param apply a pointer to a function of type (const T&) -> void
    * that is applied to the data field in the specified node
    */
   void preorderTraverse (Node<T>* node, FuncType apply) const;

   /**
    * Traverses this tree in postorder
    * @param node a node of this tree
    * @param apply a pointer to a function of type (const T&) -> void
    * that is applied to the data field in the specified node
    */
   void postorderTraverse (Node<T>* node, FuncType apply) const;

   /**
    * Recursively computes the height of the subtree rooted at the specified Node
    * @param node the root of a subtree
    * @return the height of the subtree rooted at the specified Node
    */
   long height(const Node<T>* node) const;
   /**
    * Recursively counts the number of leaf nodes in the subtree rooted at the
    * specified Node
    * @param node the root of a subtree
    * @return the number of leaf nodes in subtree rooted at the specified Node
    */
   long countLeaves(const Node<T>* node) const;
   /**
    * Recursively counts the number of half nodes in the subtree rooted at the
    * specified Node
    * @param node the root of a subtree
    * @return the number of half nodes in subtree rooted at the specified Node
    */
   long countHalves(const Node<T>* node) const;
   /**
    * Recursively removes the leaf nodes in the subtree rooted at the specified node
    * @param node the root of a subtree
    */
   void trim(Node<T>* node);

   /**
    * Gives the height if the subtree rooted at the specified node is balanced;
    * otherwise, -2
    * @param node the root of a subtree
    * @return -2 if the subtree rooted at the specified node is
    * not balanced; otherwise the height of the subtree root at the specified node
    */
    long balHeight(const Node<T>* node) const;

   /****** END: AUGMENTED PRIVATE FUNCTIONS ******/
public:
  /**
   * Constructs an empty binary search tree;
   */
   Bstree();

  /**
   * Returns the binary search tree memory to the system
   */
   virtual ~Bstree();

  /**
   * Determines whether the binary search tree is empty.
   * @return true if the tree is empty; otherwise, false
   */
   bool empty() const;

  /**
   * Inserts an item into the tree.
   * @param item the value to be inserted.
   */
   void insert(T item);

  /**
   * Determines whether an item is in the tree.
   * @param item item with a specified search key.
   * @return true on success; false on failure.
   */
   bool inTree(T item) const;

  /**
   * Deletes an item from the tree.
   * @param item item with a specified search key.
   * @return true on success; false on failure.
   */
   bool remove(const T& item);

  /**
   * Returns the item in the tree with the specified
   * key. If the item does not exists, an exception occurs.
   * @param key the key to the item to be retrieved.
   * @return it with the specified key.
   * @throws BstreeException if the item with the specified key is not
   * in the tree
   */
   const T& retrieve(const T& key) const;

  /**
   * Traverses a binary tree in inorder and applies the function visit
   * once for each node.
   * @param apply a pointer to a function of type (const T&) -> void
   */
   void inorderTraverse(FuncType apply) const;

  /**
   * Gives the number of node in this tree
   * @return the size of the tree; the number of nodes in this tree.
   */
   long size() const;

   /****** BEGIN: AUGMENTED PUBLIC FUNCTIONS ******/

  /**
   * Traverses a binary tree in preorder and applies the function visit
   * once for each node.
   * @param apply a pointer to a function of type (const T&) -> void
   */
   void preorderTraverse(FuncType apply) const;

  /**
   * Traverses a binary tree in postorder and applies the function visit
   * once for each node.
   * @param apply a pointer to a function of type (const T&) -> void
   */
   void postorderTraverse(FuncType apply) const;

   /**
    * Gives the height of this tree
    * @return the height of this tree
    */
   long height() const;
   /**
    * Gives the item in the left-most node of this tree.
    * @return the item in the left-most node of this tree
    * @throw BstreeException when this tree is empty
    */
   const T& min() const;
   /**
    * Gives the item in the right-most node of this tree.
    * @return the item in the right-most node of this tree
    * @throw BstreeException when this tree is empty
    */
   const T& max() const;
   /**
    * Counts the number of leaf nodes in this tree
    * @return the number of leaf nodes in this tree
    */
   long countLeaves() const;
   /**
    * Counts the number of half nodes in this tree
    * @return the number of half nodes this tree
    */
   long countHalves() const;
   /**
    * Removes the leaf nodes in this tree
    */
   void trim();

   /**
    * Determines whether this tree is balanced
    * @return true if this tree is balanced; otherwise, false
    */
   bool isBalanced() const;

   /****** END: AUGMENTED PUBLIC FUNCTIONS ******/
};

/**
 * nested Node class definition
 * @param <T> the data type of the item in this node
 * @param <U> the data type of the binary search tree
 */
template <typename U>
template <typename T>
class Bstree<U>::Node
{
private:
   /**
    * the data item in this Node
    */
   T data;
   /**
    * a pointer to the left child of this Node
    */
   Node<T>* left;
   /**
    * a pointer to the right child of this Node
    */
   Node<T>* right;
   /**
    * Granting friendship - access to private members of this class to the
    * Bstee<U> class
    */
   friend class Bstree<U>;
public:
  /**
   * Constructs a node with a given data value.
   * @param item the data to store in this node
   */
   Node(T item);

};
#endif //BSTREE_H

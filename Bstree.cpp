/**
 * Implementation file for function of the Bstree<T> class
 * @author ketsubetsu
 * @see Bstree.h
 * <pre>
 * File: Bstree.cpp
 * </pre>
 */

using namespace std;

#include "Bstree.h"

/* Nested Node class definitions */
template <typename U>
template <typename T>
Bstree<U>::Node<T>::Node(T item)
{
   data = item;
   left = nullptr;
   right = nullptr;
}

/* Outer Bstree class definitions */
template <typename T>
Bstree<T>::Bstree()
{
   root = nullptr;
   order = 0;
}

template <typename T>
Bstree<T>::~Bstree()
{
   recDestroy(root);
}

template <typename T>
bool Bstree<T>::empty() const
{
   return root == nullptr;
}

template<typename T>
void Bstree<T>::insert(T item)
{
   Node<T>* tmp;
   Node<T>* newnode = new Node<T>(item);

   /* If it is the first node in the tree */
   if (!root)
   {
      root = newnode;
      order++;
      return;
   }
   /*find where it should go */
   tmp = root;
   while (true)
   {
      if (tmp->data == item)
      { /* Key already exists. */
         tmp->data = item;
         delete newnode; /* dont need it */
         return;
      }
      else if (tmp->data > item)
      {
         if (!(tmp->left))
         {/* If the key is less than tmp */
            tmp->left = newnode;
            order++;
            return;
         }
         else
         {/* continue searching for insertion pt. */
            tmp = tmp->left;
         }
      }
      else
      {
         if (!(tmp->right))
         {/* If the key is greater than tmp */
            tmp->right = newnode;
            order++;
            return;
         }
         else
         {/* continue searching for insertion point*/
            tmp = tmp->right;
         }
      }
   }
}

template<typename T>
bool Bstree<T>::inTree(T item) const
{
   Node<T>* tmp;
   if (!root)
      return false;
   /*find where it is */
   tmp = root;
   while (true)
   {
      if (tmp->data == item)
         return true;
      else if (tmp->data > item)
      {
         if (!(tmp->left))
            return false;
         else
         {/* continue searching */
            tmp = tmp->left;
         }
      }
      else
      {
         if (!(tmp->right))
            return false;
         else
            /* continue searching for insertion pt. */
            tmp = tmp->right;
      }
   }
}

template<typename T>
bool Bstree<T>::remove(const T& item)
{
   Node<T>* nodeptr = search(item);
   if (nodeptr)
   {
      remove(nodeptr);
      order--;
      return true;
   }
   return false;
}

template<typename T>
const T& Bstree<T>::retrieve(const T& key) const
{
   Node<T>* nodeptr;
   if (!root)
      throw BstreeException("Exception:tree empty on retrieve().");
   nodeptr = search(key);
   if (!nodeptr)
      throw BstreeException("Exception: non-existent key on retrieve().");
   return nodeptr->data;
}

template<typename T>
void Bstree<T>::inorderTraverse(FuncType apply) const
{
   inorderTraverse(root,apply);
}

template<typename T>
long Bstree<T>::size() const
{
   return order;
}

template<typename T>
void Bstree<T>::recDestroy(Node<T>* root)
{
   if (root)
   {
      if (root->left) recDestroy(root->left);
      if (root->right) recDestroy(root->right);
      delete root;
   }
}

template<typename T>
Bstree<T>::Node<T>* Bstree<T>::findParent(Node<T>* node)
{
   Node<T>* tmp = root;
   if (tmp == node)
      return nullptr;
   while(true)
   {
      //assert(tmp->data != node->data);
      if (!tmp)
         return nullptr;
      if (tmp->data > node->data)
      {
         //assert(tmp->left);
         if (tmp->left == node)
            return tmp;
         else
            tmp = tmp->left;
      }
      else
      {
         //assert(tmp->right);
         if (tmp->right == node)
            return tmp;
         else
            tmp = tmp->right;
      }
   }
}

template<typename T>
void Bstree<T>::inorderTraverse(Node<T>* node, FuncType apply) const
{
   if (node)
   {
      inorderTraverse(node->left,apply);
      apply(node->data);
      inorderTraverse(node->right,apply);
   }
}

template<typename T>
Bstree<T>::Node<T>* Bstree<T>::search(const T& item) const
{
   Node<T>* tmp = root;
   while(tmp)
   {
      if (tmp->data == item)
         return tmp;
      else if (tmp->data > item)
         tmp = tmp->left;
      else
         tmp = tmp->right;
   }
   return tmp;
}


template<typename T>
bool Bstree<T>::remove(Node<T>* node)
{
   T data;
   Node<T> *replacement;
   Node<T>* parent = findParent(node);
   if (!parent)
      return false;
   if (node->left && node->right)
   {
      replacement = node->right;
      while (replacement->left)
         replacement = replacement->left;
      data = replacement->data;
      remove(replacement);
      node->data = data;
   }
   else
   {
      if (!(node->left) && !(node->right))
         replacement = nullptr;
      else if (node->left == nullptr)
         replacement = node->right;
      else
         replacement = node->left;
      if (!parent)
         root = replacement;
      else if (parent->left == node)
         parent->left = replacement;
      else
         parent->right = replacement;
      delete node;
   }
   return true;
}

/****** IMPLEMENT AUGMENTED PRIVATE Bstree FUNCTIONS BELOW ******/

// Private auxiliary function for preorderTraverse
template <typename T>
void Bstree<T>::preorderTraverse(Node<T>* node, FuncType apply) const
{
  if (node)
  {
    apply(node->data);
    preorderTraverse(node->left, apply);
    preorderTraverse(node->right, apply);
  }
}

// Private auxiliary function for postorderTraverse
template <typename T>
void Bstree<T>::postorderTraverse(Node<T>* node, FuncType apply) const
{
  if (node)
  {
    postorderTraverse(node->left, apply);
    postorderTraverse(node->right, apply);
    apply(node->data);
  }
}

// Private auxiliary function for height
template <typename T>
long Bstree<T>::height(const Node<T>* node) const
{
  if (node == nullptr)
  {
    return -1;
  }
  return std::max(height(node->left), height(node->right)) + 1;
}

// Private auxiliary function for countLeaves
template <typename T>
long Bstree<T>::countLeaves(const Node<T>* node) const
{
  if (node->left)
  {
	  if (node->right)
		  return countLeaves(node->left)+countLeaves(node->right);
	  else
		  return countLeaves(node->left);
  }
  else if (node->right)
	  return countLeaves(node->right);
  else
	  return 1;
}

// Private auxiliary function for countHalves
template <typename T>
long Bstree<T>::countHalves(const Node<T>* node) const
{
  if (node->left)
  {
    if (node->right)
    	return countHalves(node->left)+countHalves(node->right);
    else
    	return 1+countHalves(node->left);
  }
  else if (node->right)
	  return 1+countHalves(node->right);
  else
	  return 0;
}

// Private auxiliary function for trim
template <typename T>
void Bstree<T>::trim(Node<T>* node)
{
	if (node->left)
	{
	    if (node->right)
	    {
	        trim(node->left);
	        trim(node->right);
	    }
	    else
	    {
	        trim(node->left);
	    }
	}
	else
	{
	    if (node->right)
	        trim(node->right);
	    else
	    {
	        remove(node->data);
	    }
	}
}

// Private auxiliary function for balHeight
template<typename T>
long Bstree<T>::balHeight(const Node<T>* node) const
{
    if(!node)
        return -1;
    long lh = balHeight(node -> left);
    long rh = balHeight(node -> right);
    long df = abs(lh - rh);
    if (df > 1 || lh == -2 || rh == -2)
        return -2;
    return std::max(lh, rh) + 1;
}

/****** IMPLEMENT AUGMENTED PUBLIC Bstree FUNCTIONS BELOW ******/

// Public function for max
template <typename T>
const T& Bstree<T>::max() const
{
  if (!root)
  {
    throw BstreeException("Tree is empty");
  }
  Node<T>* ptr=root;
  while(ptr->right)
  {
	  ptr=ptr->right;
  }
  return ptr->data;
}

// Public function for min
template <typename T>
const T& Bstree<T>::min() const
{
  if (!root)
  {
    throw BstreeException("Tree is empty");
  }
  Node<T>* ptr=root;
  while(ptr->left)
  {
  	  ptr=ptr->left;
  }
    return ptr->data;
}

//Public function for trim
template <typename T>
void Bstree<T>::trim()
{
	if (root)
		trim(root);
}

// Public function for preorderTraverse
template <typename T>
void Bstree<T>::preorderTraverse(FuncType apply) const
{
  preorderTraverse(root, apply);
}

// Public function for postorderTraverse
template <typename T>
void Bstree<T>::postorderTraverse(FuncType apply) const
{
  postorderTraverse(root, apply);
}

// Public function for height
template <typename T>
long Bstree<T>::height() const
{
	if(root == nullptr)
		return -1;
	else
		return height(root);
}

// Public function for countLeaves
template <typename T>
long Bstree<T>::countLeaves() const
{
	if(!root)
		return 0;
	else
		return countLeaves(root);
}

// Public function for countHalves
template <typename T>
long Bstree<T>::countHalves() const
{
	if (!root)
		return 0;
	return countHalves(root);
}

// Public function for isBalanced
template <typename T>
bool Bstree<T>::isBalanced() const
{
	if (balHeight(root)==-2)
		return false;
	else
		return true;
}

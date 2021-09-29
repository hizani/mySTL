#ifndef SET_H
#define SET_H

#include "bst.h"

namespace mySTL
{
	// Empty struct to represent a lack of value in sets.
	struct empty {};

    template <typename T>
	class multiset : public mySTL::bst<T, empty>
    {
		typedef typename mySTL::bst<T, empty>::node_ node_;
	    typedef typename mySTL::bst<T, empty>::color_ color_;

    public:

		// Insert new node with passed key.
		void insert(const T& key)
		{
			if (this->root_ == this->LEAF) {
				this->root_ = new node_();
				this->root_->key = key;
				this->root_->color = color_::BLACK;
				this->root_->left_node = this->LEAF;
				this->root_->right_node = this->LEAF;
				return;
			}

			node_* parent = this->LEAF;
			node_** node = &this->root_;
			while (true) {
				if ((*node) == this->LEAF) {
					*node = new node_();
					(*node)->key = key;
					(*node)->parent = parent;
					(*node)->left_node = this->LEAF;
					(*node)->right_node = this->LEAF;
					this->fix_insert(*node);
					return;
				}

				if (key <= (*node)->key) {
					parent = *node;
					node = &((*node)->left_node);
					continue;
				}
				parent = *node;
				node = &((*node)->right_node);
			}
		}

	};

    template <typename T>
	class set : public mySTL::bst<T, empty>
	{
		typedef typename mySTL::bst<T, empty>::node_ node_;
	    typedef typename mySTL::bst<T, empty>::color_ color_;

    public:
		// Insert new node with passed key.
		void insert(const T& key)
		{
			if (this->root_ == this->LEAF) {
				this->root_ = new node_();
				this->root_->key = key;
				this->root_->color = color_::BLACK;
				this->root_->left_node = this->LEAF;
				this->root_->right_node = this->LEAF;
				return;
			}

			node_* parent = this->LEAF;
			node_** node = &this->root_;
			while (true) {
				if ((*node) == this->LEAF) {
					*node = new node_();
					(*node)->key = key;
					(*node)->parent = parent;
					(*node)->left_node = this->LEAF;
					(*node)->right_node = this->LEAF;
					this->fix_insert(*node);
					return;
				}

				if (key == (*node)->key) {
					return;
				}

				if (key < (*node)->key) {
					parent = *node;
					node = &((*node)->left_node);
					continue;
				}
				parent = *node;
				node = &((*node)->right_node);
			}
		}

	};
}

#endif
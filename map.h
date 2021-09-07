#ifndef MAP_H
#define MAP_H

#include "bst.h"
namespace mySTL
{
    template <typename K, typename V>
    class multimap : public mySTL::bst<K, V>
    {
    	typedef typename mySTL::bst<K, V>::node_ node_;
	    typedef typename mySTL::bst<K, V>::color_ color_;

    public:

		virtual void insert(const K& key, const V& value)
		{
			if (this->root_ == this->LEAF) {
				this->root_ = new node_();
				this->root_->key = key;
				this->root_->value = value;
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
					(*node)->value = value;
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

		V& operator[](const K& key)
		{
			return this->find(key)->value;
		}



	};

	template <typename K, typename V>
    class map : public mySTL::multimap<K, V>
    {		
    	typedef typename mySTL::bst<K, V>::node_ node_;
	    typedef typename mySTL::bst<K, V>::color_ color_;


		public:
		void insert(const K& key, const V& value) override
		{
			if (this->root_ == this->LEAF) {
				this->root_ = new node_();
				this->root_->key = key;
				this->root_->value = value;
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
					(*node)->value = value;
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
} // namespace mySTL
#endif

#ifndef SET_H
#define SET_H

namespace mySTL
{
    template <typename T>
	class multiset
    {
        public:
		multiset() {};

        ~multiset()
		{
			delete root_;
		}

        virtual void insert(T& key)
		{
			if (!root_) {
				root_ = new node_();
				root_->key = key;
				return;
			}

			node_* parent = nullptr;
			node_** node = &root_;
			while (true) {
				if (!(*node)) {
					*node = new node_();
					(*node)->key = key;
					(*node)->parent = parent;
					return;
				}

				if (key <= (*node)->key) {
					parent = *node;
					node = &((*node)->left_node);
					continue;
				}
				parent = *node;
				node = &((*node)->right_node);
				continue;
			}
		}

		virtual void insert(T&& key)
		{
			if (!root_) {
				root_ = new node_();
				root_->key = key;
				return;
			}

			node_* parent = nullptr;
			node_** node = &root_;
			while (true) {
				if (!(*node)) {
					*node = new node_();
					(*node)->key = key;
					(*node)->parent = parent;
					return;
				}

				if (key <= (*node)->key) {
					parent = *node;
					node = &((*node)->left_node);
					continue;
				}
				parent = *node;
				node = &((*node)->right_node);
				continue;
			}
		}

        		T* find(const T& key)
		{
			node_* node = root_;
			while (true) {
				if (!node) {
					return nullptr;
				}

				if (node->key == key) {
					return &(node->key);
				}

				if (key <= node->key) {
					node = node->left_node;
					continue;
				}

				node = node->right_node;
				continue;
			}
		}

		T* find(const T&& key)
		{
			node_* node = root_;
			while (true) {
				if (!node) {
					return nullptr;
				}

				if (node->key == key) {
					return &(node->key);
				}

				if (key <= node->key) {
					node = node->left_node;
					continue;
				}

				node = node->right_node;
				continue;
			}
		}
        
        bool contains(const T& key)
		{
			if (find(key) != nullptr)
				return true;
			return false;
		}

        void clear()
		{
			delete root_;
			root_ = nullptr;
		}

        protected:
        struct node_
		{
			T key;

			node_* left_node;
			node_* right_node;
			node_* parent;

            ~node_()
			{
				if (left_node)
					delete left_node;
				if (right_node)
					delete right_node;
			}
		};


		node_* root_ = nullptr;
    };

    template <typename T>
	class set : public multiset<T>
	{
        public:
		virtual void insert(T& key) override
		{
			if (!multiset<T>::root_) {
				multiset<T>::root_ = new typename multiset<T>::node_();
				multiset<T>::root_->key = key;
				return;
			}

			typename multiset<T>::node_* parent = nullptr;
			typename multiset<T>::node_** node = &(multiset<T>::root_);
			while (true) {
				if (!(*node)) {
					*node = new typename multiset<T>::node_();
					(*node)->key = key;
					(*node)->parent = parent;
					return;
				}

				if (key <= (*node)->key) {
					return;
				}

				if (key < (*node)->key) {
					parent = *node;
					node = &((*node)->left_node);
					continue;
				}
				parent = *node;
				node = &((*node)->right_node);
				continue;
			}
		}

		virtual void insert(T&& key) override
		{
			if (!multiset<T>::root_) {
				multiset<T>::root_ = new typename multiset<T>::node_();
				multiset<T>::root_->key = key;
				return;
			}

			typename multiset<T>::node_* parent = nullptr;
			typename multiset<T>::node_** node = &(multiset<T>::root_);
			while (true) {
				if (!(*node)) {
					*node = new typename multiset<T>::node_();
					(*node)->key = key;
					(*node)->parent = parent;
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
				continue;
			}
		}            
	};
}

#endif
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
			delete this->root_;
		}

		virtual void insert(T& key)
		{
			if (!this->root_) {
				this->root_ = new node_();
				this->root_->key = key;
				this->root_->color = BLACK;
				return;
			}

			node_* parent = nullptr;
			node_** node = &this->root_;
			while (true) {
				if (!(*node)) {
					*node = new node_();
					(*node)->key = key;
					(*node)->parent = parent;
					fix_insert(*node);
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

		virtual void insert(T&& key)
		{
			if (!this->root_) {
				this->root_ = new node_();
				this->root_->key = key;
				this->root_->color = BLACK;
				return;
			}

			node_* parent = nullptr;
			node_** node = &this->root_;
			while (true) {
				if (!(*node)) {
					*node = new node_();
					(*node)->key = key;
					(*node)->parent = parent;
					fix_insert(*node);
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

		T* find(const T& key)
		{
			node_* node = this->root_;
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
			}
		}

		T* find(const T&& key)
		{
			node_* node = this->root_;
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
			}
		}

		bool contains(const T& key)
		{
			if (find(key) != nullptr)
				return true;
			return false;
		}

		void remove(const T& key)
		{
			node_* node = this->root_;
			while (true) {
				if (!node) {
					return;
				}

				if (node->key == key) {
					remove_node(node);
					return;
				}

				if (key <= node->key) {
					node = node->left_node;
					continue;
				}

				node = node->right_node;
			}
		}

		void remove(const T&& key)
		{
			node_* node = this->root_;
			while (true) {
				if (!node) {
					return;
				}

				if (node->key == key) {
					remove_node(node);
					return;
				}

				if (key <= node->key) {
					node = node->left_node;
					continue;
				}

				node = node->right_node;
			}
		}

		void clear()
		{
			delete this->root_;
			this->root_ = nullptr;
		}
        protected:

		enum color_
		{
			BLACK,
			RED
		};

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

			color_ color = RED;
		};

		node_* root_ = nullptr;

		bool is_red(node_* node)
		{
			if (node != nullptr && node->color == RED)
				return true;
			return false;
		}

		void replace_node(node_* node1, node_* node2) {
			if (node1->parent == nullptr)
			{
				root_ = node2;
			}
			else if (node1 == node1->parent->left_node)
			{
				node1->parent->left_node = node2;
			}
			else
			{
				node1->parent->right_node = node2;
			}
			node2->parent = node1->parent;
		}

		void remove_node(node_* node)
		{
			node_* fix_node;
			node_* minimum_node = node;
			color_ node_color = minimum_node->color;
			if (node->left_node == nullptr) {
				fix_node = node->right_node;
				replace_node(node, node->right_node);
			}
			else if (node->right_node == nullptr) {
				fix_node = node->left_node;
				replace_node(node, node->left_node);
			}
			else {
				minimum_node = node->right_node;
				while (minimum_node->left_node != nullptr) {
					minimum_node = minimum_node->left_node;
				}
				node_color = minimum_node->color;
				fix_node = minimum_node->right_node;
				if (minimum_node->parent == node) {
					fix_node->parent = minimum_node;
				}
				else {
					replace_node(minimum_node, minimum_node->right_node);
					minimum_node->right_node = node->right_node;
					minimum_node->right_node->parent = minimum_node;
				}
				replace_node(node, minimum_node);
				minimum_node->left_node = node->left_node;
				minimum_node->left_node->parent = minimum_node;
				minimum_node->color = node->color;
			}
			node->left_node = nullptr;
			node->right_node = nullptr;
			delete node;
			if (node_color == BLACK)
				fix_remove(fix_node);
		}

		node_* get_grandparent(node_* node)
		{
			return node->parent->parent;
		}

		node_* get_uncle(node_* node)
		{
			node_* grandparent = get_grandparent(node);
			if (grandparent->left_node == node->parent)
				return grandparent->right_node;
			return grandparent->left_node;
		}

		node_* get_sibling(node_* node)
		{
			if (node->parent->left_node == node)
				return node->parent->right_node;
			return node->parent->left_node;
		}

		void flip_color(node_* node)
		{
			if (!node)
				return;
			if (is_red(node))
			{
				node->color = BLACK;
				return;
			}
			node->color = RED;
		}

		bool is_root(node_* node)
		{
			if (node == root_) {
				return true;
			}
			return false;
		}

		void rotate_left(node_* node)
		{
			node_* node_to_rotate = node->right_node;
			node->right_node = node_to_rotate->left_node;
			if (node_to_rotate->left_node != nullptr) {
				node_to_rotate->left_node->parent = node;
			}
			node_to_rotate->parent = node->parent;
			if (node->parent == nullptr) {
				this->root_ = node_to_rotate;
			}
			else if (node == node->parent->left_node) {
				node->parent->left_node = node_to_rotate;
			}
			else {
				node->parent->right_node = node_to_rotate;
			}

			node_to_rotate->left_node = node;
			node->parent = node_to_rotate;
		}

		void rotate_right(node_* node)
		{
			node_* node_to_rotate = node->left_node;
			node->left_node = node_to_rotate->right_node;
			if (node_to_rotate->right_node != nullptr) {
				node_to_rotate->right_node->parent = node;
			}
			node_to_rotate->parent = node->parent;
			if (node->parent == nullptr) {
				this->root_ = node_to_rotate;
			}
			else if (node == node->parent->right_node) {
				node->parent->right_node = node_to_rotate;
			}
			else {
				node->parent->left_node = node_to_rotate;
			}

			node_to_rotate->right_node = node;
			node->parent = node_to_rotate;
		}

		void fix_insert(node_* node)
		{
			node_* uncle;
			node_* grandparent;
			while (is_red(node->parent)) {
				uncle = get_uncle(node);
				grandparent = get_grandparent(node);

				if (is_red(uncle)) {
					flip_color(uncle);
					flip_color(node->parent);
					flip_color(grandparent);
					node = grandparent;

					if (is_root(node)) break;
					continue;
				}

				// Parent is right child of grandparent

				if (node->parent == grandparent->right_node) {
					if (node == node->parent->left_node) {
						node = node->parent;
						//grandparent = get_grandparent(node);
						rotate_right(node);
					}

					flip_color(node->parent);
					flip_color(grandparent);
					rotate_left(grandparent);

					if (is_root(node)) break;
					continue;
				}

				// Parent is left child of grandparent

				if (node == node->parent->right_node) {
					node = node->parent;
					//grandparent = get_grandparent(node);
					rotate_left(node);
				}

				flip_color(node->parent);
				flip_color(grandparent);
				rotate_right(grandparent);

				if (is_root(node)) break;
				continue;
			}
			root_->color = BLACK;
		}

		void fix_remove(node_* node)
		{
			while (node != root_ && !is_red(node))
			{
				node_* sibling = get_sibling(node);
				if (node == node->parent->left_node) {
					if (is_red(sibling))
					{
						flip_color(sibling);
						flip_color(node->parent);
						rotate_left(node->parent);
						sibling = get_sibling(node);
					}

					if (!is_red(sibling->left_node) && !is_red(sibling->right_node)) {
						flip_color(sibling);
						node = node->parent;
						continue;
					}
					if (!is_red(sibling->right_node)) {
						flip_color(sibling);
						flip_color(sibling->left_node);
						rotate_right(sibling);
						sibling = get_sibling(node);
					}

					sibling->color = node->parent->color;
					node->parent->color = BLACK;
					sibling->right_node->color = BLACK;
					rotate_left(node->parent);
					node = root_;
					continue;
				}

				if (is_red(sibling))
				{
					flip_color(sibling);
					flip_color(node->parent);
					rotate_right(node->parent);
					sibling = get_sibling(node);
				}

				if (!is_red(sibling->left_node) && !is_red(sibling->right_node)) {
					flip_color(sibling);
					node = node->parent;
					continue;
				}
				if (!is_red(sibling->left_node)) {
					flip_color(sibling);
					flip_color(sibling->right_node);
					rotate_left(sibling);
					sibling = get_sibling(node);
				}

				sibling->color = node->parent->color;
				node->parent->color = BLACK;
				sibling->left_node->color = BLACK;
				rotate_right(node->parent);
				node = root_;
			}
			node->color = BLACK;
		}
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
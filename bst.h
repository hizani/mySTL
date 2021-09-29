#ifndef BST_H
#define BST_H

namespace mySTL 
{
    template<typename K, typename V>
    class bst
    {
    public:
		// Return true if contains key.
		bool contains(const K& key)
		{
			if (find(key) != nullptr)
				return true;
			return false;
		}

		// Remove node by key value.
		void remove(const K& key)
		{
			node_* node = this->root_;
			while (true) {
				if (node == LEAF) {
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

		// Clear the bst.
		void clear()
		{
			delete this->root_;
			this->root_ = LEAF;
		}

    protected:
        bst() 
		{
			LEAF = new node_;
			LEAF->color = BLACK;
			LEAF->left_node = nullptr;
			LEAF->right_node = nullptr;
			LEAF->parent = nullptr;
			root_ = LEAF;

		}

        ~bst()
		{
			delete this->root_;
		}

		// Colors of nodes for red-black 
		// bst implementation.
        enum color_
		{
			BLACK,
			RED
		};

		// Node of bst.
        struct node_
		{
			K key;
            V value;

			node_* left_node; 	// Left child.
			node_* right_node;	// Right child.
			node_* parent;		// Parent of a node.

			color_ color = RED;	// color of a node

			~node_()
			{
				if (left_node->left_node != nullptr && left_node->right_node != nullptr)
					delete left_node;
				if (right_node->left_node != nullptr && right_node->right_node != nullptr)
					delete right_node;
			}

		};
        
        
		node_* root_;	// First node of a bst.
		node_* LEAF; 	// Leaf of a bst.

		// Return pointer to bst node with passed key. 
		node_* find(const K& key)
		{
			node_* node = this->root_;
			while (true) {
				if (node == LEAF) {
					return nullptr;
				}

				if (node->key == key) {
					return &(*node);
				}

				if (key <= node->key) {
					node = node->left_node;
					continue;
				}

				node = node->right_node;
			}
		}

		// Return true if passed node is red.
		bool is_red(node_* node)
		{
			if (node->color == RED)
				return true;
			return false;
		}

		// Replace node1 with node2.
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

		// Remove passed node and find
		// fix_node on which balancing will be carried out.
		void remove_node(node_* node)
		{
			node_* fix_node;							// Node to be balanced.
			node_* minimum_node = node; 				// Minimum node (not leaf) of the removing node subtree.
			color_ node_color = minimum_node->color;	// Minimum node color.
			if (node->left_node == LEAF) {
				fix_node = node->right_node;
				replace_node(node, node->right_node);
			}
			else if (node->right_node == LEAF) {
				fix_node = node->left_node;
				replace_node(node, node->left_node);
			}
			else {
				minimum_node = node->right_node;
				while (minimum_node->left_node != LEAF) {
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
			node->left_node = LEAF;
			node->right_node = LEAF;
			delete node;
			if (node_color == BLACK)
				fix_remove(fix_node);
		}
		
		// Return pointer to a grandparent of passed node.
		node_* get_grandparent(node_* node)
		{
			return node->parent->parent;
		}

		// Return pointer to a uncle of passed node.
		node_* get_uncle(node_* node)
		{
			node_* grandparent = get_grandparent(node);
			if (grandparent->left_node == node->parent)
				return grandparent->right_node;
			return grandparent->left_node;
		}

		// Return pointer to a sibling of passed node.
		node_* get_sibling(node_* node)
		{
			if (node->parent->left_node == node)
				return node->parent->right_node;
			return node->parent->left_node;
		}

		// Change color of passed node to opposite.
		void flip_color(node_* node)
		{
			if (is_red(node))
			{
				node->color = BLACK;
				return;
			}
			node->color = RED;
		}

		// Return true if passed node is root of a bst.
		bool is_root(node_* node)
		{
			if (node == root_) {
				return true;
			}
			return false;
		}

		// Rotate passed node to the left.
		//
		// Passed node moves to the node->right_node's place and
		// node->left_node moves to the passed node's place.
		void rotate_left(node_* node)
		{
			node_* node_to_rotate = node->right_node;
			node->right_node = node_to_rotate->left_node;
			if (node_to_rotate->left_node != LEAF) {
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

		// Rotate passed node to the right.
		//
		// Passed node moves to the node->left_node's place and
		// node->right_node moves to the passed node's place.
		void rotate_right(node_* node)
		{
			node_* node_to_rotate = node->left_node;
			node->left_node = node_to_rotate->right_node;
			if (node_to_rotate->right_node != LEAF) {
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

		// Make tree to be balanced after insert.
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

				if (node->parent == grandparent->right_node) {
					if (node == node->parent->left_node) {
						node = node->parent;
						rotate_right(node);
					}

					flip_color(node->parent);
					flip_color(grandparent);
					rotate_left(grandparent);

					if (is_root(node)) break;
					continue;
				}

				if (node == node->parent->right_node) {
					node = node->parent;
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

		// Make tree to be balanced after remove.
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

}

#endif
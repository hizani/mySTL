#ifndef SET_H
#define SET_H

namespace mySTL
{
    template <typename T>
	class multiset
    {
        public:
		multiset() {};

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

        protected:
        struct node_
		{
			T key;

			node_* left_node;
			node_* right_node;
			node_* parent;
		};


		node_* root_ = nullptr;
    };
}

#endif
#ifndef LIST_H
#define LIST_H

namespace mySTL
{
    template<typename T>
    class list
    {
    public:
        // Insert new element at the end of the list.
        void push_back(const T& value)
        {
            node_* new_node = new node_(value, back_, nullptr);
            if(back_ != nullptr)
                back_->next = new_node;
            back_ = new_node;
            if(front_ == nullptr)
                front_ = new_node;
            length_++;
        }
        // Insert new element at the begining of the list.
        void push_front(const T& value)
        {
            node_* new_node = new node_(value, nullptr, front_);
            if(front_ != nullptr)
                front_->previous = new_node;
            front_ = new_node;
            if(back_ == nullptr)
                back_ = new_node;
            length_++;
        }

        // Insert new element by passed index.
        void insert(const T& value, const unsigned int index)
        {
            if(length_ <= index)
                return;

            if(index == 0) {
                push_front(value);
                return;
            }

            node_* new_node = new node_(value);

            
            node_* node = traverse_to_idx(index);

            // Insert new_node. 
            new_node->previous = node->previous;
            new_node->next = node;

            // Change poiner of new_node->next.
            node->previous = new_node;

            // Change poiner of new_node->previous.
            new_node->previous->next = new_node;

            length_++;
        }

        // Remove last element from the list.
        void pop_back()
        {
            if(length_ <= 0)
                return;

            back_ = back_->previous;

            back_->next->previous = nullptr;
            delete back_->next;

            back_->next = nullptr;

            length_--;
        }

        // Remove firts element of the list
        void pop_front()
        {
            if(length_ <= 0)
                return;

            front_ = front_->next;

            front_->previous->next = nullptr;
            delete front_->previous;

            front_->previous = nullptr;
         
            length_--;
        }

        // Remove an element by passed index. 
        void remove(const unsigned int index)
        {
            if(length_ <= index)
                return;

            if(index == 0) {
                pop_front();
                return;
            }

            if(index == length_ - 1) {
                pop_back();
                return;
            }

            node_* node = traverse_to_idx(index);

            node->previous->next = node->next;
            node->next->previous = node->previous;

            node->previous = nullptr;
            node->next = nullptr;
            delete node;

            length_--;
        }

        // Return reference to the element by passed index.
        T& operator[](const unsigned int index)
        {
            node_* node = traverse_to_idx(index);

            return node->value;
        }

        ~list()
        {
            if(front_ != nullptr)
                delete front_;
        }

    private:

        // Node of the list.
        struct node_
        {
            T value;            // Value of the node.
            node_* previous;    // Pointer to previous node.
            node_* next;        // Pointer to next node.

            // Create node with passed value
            // and next and parevious pointerts of nullptr.
            node_(const T& value)
            {
                this->value = value;
                this->previous = nullptr;
                this->next = nullptr;
            }

            // Create node with passed
            // value, previous and next.
            node_(const T& value, node_* previous, node_* next)
            {
                this->value = value;
                this->previous = previous;
                this->next = next;
            }

            ~node_()
            {
                if(previous != nullptr)
                    delete previous;
                if(previous != nullptr)
                    delete next;
            }
        };


        // Traverse the list from front or back to index element.
        node_* traverse_to_idx(unsigned int index)
        {
            node_* node = nullptr;

            switch (index < (length_ / 2))
            {
            // Traverse the list from front to back.
            case true:
                node = front_;
                for (int ii = 0; ii != index; ii++)
                {
                    node = node->next;
                }
                break;

            // Traverse the list from back to front.
            case false:
                node = back_;
                for (int ii = (length_ - 1); ii != index; ii--)
                {
                    node = node->previous;
                }
                break;
            }

            return node;
        }

        node_* front_ = nullptr;    // First element of the list.
        node_* back_ = nullptr;     // Last element of the list.

        unsigned int length_ = 0;   // Length of the list.
    };

}

#endif
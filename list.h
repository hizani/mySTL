#ifndef LIST_H
#define LIST_H

namespace mySTL
{
    template<typename T>
    class list
    {
    public:
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

        void insert(const T& value, const unsigned int index)
        {
            if(length_ <= index)
                return;

            if(index == 0) {
                push_front(value);
                return;
            }

            node_* new_node = new node_(value);

            
            node_* node = nullptr;

            switch (index < (length_ / 2))
            {
            case true:
                node = front_;
                for (int ii = 0; ii != index; ii++)
                {
                    node = node->next;
                }
                break;

            case false:
                node = back_;
                for (int ii = (length_ - 1); ii != index; ii--)
                {
                    node = node->previous;
                }
                break;
            }

            new_node->previous = node->previous;
            new_node->next = node;

            node->previous = new_node;

            new_node->previous->next = new_node;

            length_++;
        }

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

            node_* node = nullptr;

            switch (index < (length_ / 2))
            {
            case true:
                node = front_;
                for (int ii = 0; ii != index; ii++)
                {
                    node = node->next;
                }
                break;

            case false:
                node = back_;
                for (int ii = (length_ - 1); ii != index; ii--)
                {
                    node = node->previous;
                }
                break;
            }

            node->previous->next = node->next;
            node->next->previous = node->previous;

            node->previous = nullptr;
            node->next = nullptr;
            delete node;

            length_--;
        }

        T& operator[](const unsigned int index)
        {
            node_* node = nullptr;

            switch (index < (length_ / 2))
            {
            case true:
                node = front_;
                for (int ii = 0; ii != index; ii++)
                {
                    node = node->next;
                }
                break;

            case false:
                node = back_;
                for (int ii = (length_ - 1); ii != index; ii--)
                {
                    node = node->previous;
                }
                break;
            }

            return node->value;
        }

    private:

        struct node_
        {
            T value;
            node_* previous;
            node_* next;

            node_(const T& value)
            {
                this->value = value;
                this->previous = nullptr;
                this->next = nullptr;
            }

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

        node_* front_ = nullptr;
        node_* back_ = nullptr;

        unsigned int length_ = 0;
    };

}

#endif
#ifndef VECTOR_H
#define VECTOR_H

namespace mySTL
{
    template <typename T>
    class vector
    {
    public:
        vector()
        {
            capacity(10);
        }

        vector(const unsigned int cap)
        {
            capacity(cap);
        }

        void insert(const T& value)
        {
            if(capacity_ < end_ + 1)
                capacity(capacity_ * 2);
            array_[end_ + 1] = value;
            end_++;
        }

        void remove(const unsigned int index)
        {
            if(index == end_) {
                end_--;
                return;
            }

            /* TODO: Make first element delition without reallocation
            
            if(index == 0) {
                delete array_[1] //clean first element
                array_ = &array_[1];
                end_--;
                capacity_--;
                return;
            } */

            T* temp = new T[capacity_];
            int jj = -1;
            for(int ii = 0; ii <= end_; ii++) {
                jj++;
                if(ii == index)
                {
                    jj--;
                    continue;
                }
                temp[jj] = array_[ii];
            }
            end_--;
            if(array_ != nullptr)
                delete array_;
            array_ = temp;

           
        }

        /* TODO: implement at() method */

        T& operator[](const unsigned int index)
        {
            return array_[index];
        }

        void capacity(const unsigned int number)
        {
            if(number == capacity_)
                return;

            if(end_ > capacity_)
                end_ = capacity_;

            capacity_ = number;
            T* temp = new T[number];
            for(int ii = 0; ii <= end_; ii++) {
                temp[ii] = array_[ii];
            }
            if(array_ != nullptr)
                delete array_;
            array_ = temp;
        }

    private:
        unsigned int capacity_ = -1;
        int end_ = -1;
        T* array_ = nullptr;    

    };
}

#endif
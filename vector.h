#ifndef VECTOR_H
#define VECTOR_H

namespace mySTL
{
    template <typename T>
    class vector
    {
    public:

        // Create vector with capacity of 10
        vector()
        {
            capacity(10);
        }

        // Create vector with capacity of cap
        vector(const unsigned int cap)
        {
            capacity(cap);
        }

        ~vector()
        {
            delete[] array_;
        }

        // Insert new element to the vector.
        void insert(const T& value)
        {
            // Reallocate array if the vector 
            // is run out of capacity.
            if (capacity_ < length_ + 1)
                capacity(capacity_ * 2);
            array_[length_ + 1] = value;
            length_++;
        }

        // Remove element from vector.
        void remove(const unsigned int index)
        {
            // Shift the end point of the vector
            // if it is last element to be removed.
            if (index == length_)
            {
                length_--;
                return;
            }

            T* temp = new T[capacity_];
            int jj = -1;

            // Save elements to the new array.
            for (int ii = 0; ii <= length_; ii++)
            {
                jj++;
                // Skip removing element.
                if (ii == index)
                {
                    jj--;
                    continue;
                }
                temp[jj] = array_[ii];
            }
            length_--;
            if (array_ != nullptr)
                delete[] array_;
            array_ = temp;
        }

        // Return reference to the element by passed index.
        T& operator[](const unsigned int index)
        {
            return array_[index];
        }

        // Change vector's capacity.
        void capacity(const int number)
        {   
            // Do nothing if new capacity is lower 
            // than current length of the vector.
            if ((length_ + number) <= capacity_)
                return;

            capacity_ += number;
            T* temp = new T[number];
            for (int ii = 0; ii <= length_; ii++)
            {
                temp[ii] = array_[ii];
            }
            if (array_ != nullptr)
                delete[] array_;
            array_ = temp;
        }

    private:
        int capacity_ = -1;     // Capacity of the vector.
        int length_ = -1;       // Length of the vector.
        T* array_ = nullptr;    // Array with elements of the vector.
    };
}

#endif
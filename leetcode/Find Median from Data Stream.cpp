/*
Median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle value.

For example,
[2,3,4], the median is 3

[2,3], the median is (2 + 3) / 2 = 2.5

Design a data structure that supports the following two operations:

void addNum(int num) - Add a integer number from the data stream to the data structure.
double findMedian() - Return the median of all elements so far.
*/

class MedianFinder {
    using MultiSetItr = multiset<int>::iterator;
public:
    /** initialize your data structure here. */
    MedianFinder()
        :data(), 
        median(0),
        low(nullptr),
        high(nullptr)
    {}
    
    void addNum(int num) 
    {
        data.insert(num);
        if(data.size() == 1)
        {
            low = data.begin();
            high = data.begin();
        }
        else if(!(data.size() % 2))
        {
            if(num < median)
                --low;
            else 
                ++high;          
        }
        else
        {
            if(num < *low)
                --high;
            else if(num >= *high)
                ++low;
            else
            {
                --high;
                ++low;
            }
        }
        median = (double(*low) + double(*high)) / 2;
    }
    
    double findMedian() 
    {
        return median;
    }
private:
    multiset<int> data;
    double median;
    MultiSetItr low;
    MultiSetItr high;
};

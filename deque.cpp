/**
 * @file deque.cpp
 * Implementation of the Deque class.
 *
 */

template <class T>
Deque<T>::Deque(){ 
    n1 = 0; 
    n2 = 0; // think about it -1 (take adding one element case)
}

/**
 * Adds the parameter object to the right of the Deque.
 *
 * @param newItem object to be added to the Deque.
 */
template <class T>
void Deque<T>::pushR(T newItem)
{     
    //queue (enqueue funciton) - built in   
    data.push_back(newItem);
    n2++;
}

/**
 * Removes the object at the left of the Deque, and returns it to the
 * caller.
 *
 * See .h file for implementation notes. 
 *
 * @return The item that used to be at the left of the Deque.
 */
template <class T>
T Deque<T>::popL()
{
    /**
     * @todo Your code here! 
     */
    T out = data.at(n1); // tests nice way to check methods 
    //data.erase(data.begin() + n1); // no need to do it (n1 increments and resize takes care of it) + O(n)
    n1++;
    if (n2 - n1 <= n1){ //** how did he make dequeue tests?
        vector<T> newVector;
        //int index = 0;
        //n2--;
        for(int pos = n1; pos < n2; pos++){ //not <= n2 ()
            newVector.push_back(data.at(pos));
            //index++;
        }
        data = newVector;
        //newVector.clear();
        n2 = n2 - n1;
        n1 = 0;
    }
    return out; // creating a copy out data not deleting it (not a pointer)
}

/**
 * Removes the object at the right of the Deque, and returns it to the
 * caller.
 *
 * @return The item that used to be at the right of the Deque.
 */
template <class T>
T Deque<T>::popR()
{
    T out = data.at(n2-1);
    //data.erase(data.begin() + n2); 
    n2--;
    if (n2 - n1 <= n1){
        vector<T> newVector;
        //int index = 0;
        for(int pos = n1; pos < n2; pos++){
            newVector.push_back(data.at(pos));
            //index++;
        }
        data = newVector; //old data goes away 
        //newVector.clear(); // no need to clear newVector
        n2 = n2-n1;
        n1 = 0;
    }
    return out; // creating a copy not deleting it
}

/**
 * Finds the object at the left of the Deque, and returns it to the
 * caller. Unlike popL(), this operation does not alter the deque.
 *
 * @return The item at the front of the deque.
 */
template <class T>
T Deque<T>::peekL()
{

  return data.at(n1);

}

/**
 * Finds the object at the right of the Deque, and returns it to the
 * caller. Unlike popR(), this operation does not alter the deque.
 *
 * @return the value of The item at the right of the deque.
 */
template <class T>
T Deque<T>::peekR()
{
    return data.at(n2-1);
}

/**
 * Determines if the Deque is empty.
 *
 * @return bool which is true if the Deque is empty, false otherwise.
 */
template <class T>
bool Deque<T>::isEmpty() const
{

    return data.empty();

}

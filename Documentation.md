# Documentation
Will migrate this to a webpage for accessibility once bulk of engine is developed

## Function Analysis (Big O Notation) Note
* All functions are represented as the Big O of the content of the function and DOES NOT include the Big O of the functions that it calls.
* Any notation that is not constant, O(1), will have its variable description listed
* Full function descriptions are listed where they are defined in their corrisponding .hpp file
```C++
void foo() {
    std::vector<int> x;
    //...
    // Add stuff to x
    //...
    std::sort(x.begin(), x.end());
}
```
This is seen as O(1) even though std::sort is usually O(N*log(N))
# Self-Organizing-List 
The Self-Organizing List C++ class is a versatile data structure that allows you to efficiently manage a list of elements while providing features for organizing and manipulating the list. This class is designed to be easy to use and integrates self-organizing behavior to improve the efficiency of frequently accessed elements.

# Introduction
A self-organizing list is a data structure that reorganizes its elements based on access frequency. Elements that are frequently accessed are moved closer to the front of the list to reduce access time. This class provides a C++ implementation of a self-organizing list with various operations to manipulate and organize the elements efficiently.

# Features
* Efficient Access: Frequently accessed elements are moved towards the front of the list.
* Standard Container Functions: Provides familiar container functions like push_back, push_front, pop_back, pop_front, etc.
* Sorting: Maintains an ascending and descending order for efficient searches.
* Resizable: The list can be resized to accommodate more or fewer elements.
* Reversing: Easily reverse the order of elements in the list.
* Splicing: Merge two self-organizing lists together.
* Customizable: Template-based, allowing storage of any data type.

# How to Compile
1) g++ self_organizing_list.cpp main.cpp -o program
2) execute the Program: ./program

# Usage
* Creating a Self-Organizing List
    To create a self-organizing list, declare an instance of the SelfOrganizingList class with your desired data type:
    SelfOrganizingList<int> myList;

* push_back(const T& val)
    Adds an element to the end of the list.
    myList.push_back(42);

* push_front(const T& val)
    Adds an element to the front of the list.
    myList.push_front(24);

* insert(std::size_t pos, const T& val)
      Inserts an element at the specified position in the list.
    myList.insert(1, 7); // Inserts 7 at position 1

* pop_back()
    Removes the last element from the list.
    myList.pop_back();

* pop_front()
    Removes the first element from the list.
    myList.pop_front();

* erase(std::size_t pos)
    Removes the element at the specified position in the list.
    myList.erase(1); // Removes the element at position 1

* resize(std::size_t count)
    Changes the size of the list to the specified count. If the new size is larger, default-initialized elements are added; if smaller, elements are removed.
    myList.resize(10); // Resize to 10 elements

* reverse()
    Reverses the order of elements in the list.
    myList.reverse();

* splice(std::size_t pos, SelfOrganizingList<T>& list)
    Merges the elements from another SelfOrganizingList into the current list, starting at the specified position.
    SelfOrganizingList<int> otherList;
    // Fill otherList with elements
    myList.splice(2, otherList); // Merge otherList into myList starting at position 2

* clear()
    Removes all elements from the list, leaving it empty.

* size()
    Returns the number of elements in the list.

* print()
    Prints the elements of the list in their current order.

* print_ascending_order()
    Prints the elements of the list in ascending order.

* print_descending_order()
    Prints the elements of the list in descending order.

* print_from_tail()
    Prints the elements of the list starting from the end (tail) in their current order.

* put_in_sorted_order(Node* node)
    this function refers pointer m_asc of the inserted node to the next greater node, and pointer m_desc to the next lesser node

* advance_node(Node* node)
  this function provide a self-organizing nature of this list.Elements that are accessed are moved closer to the front of the list to reduce access time.

# Comparison Operators
The following operators allow you to compare SelfOrganizingList objects:

* ==  Checks if two lists are equal.
* !=  Checks if two lists are not equal.
* >  Checks if one list is greater than the other.
* >=  Checks if one list is greater than or equal to the other.
* <  Checks if one list is less than the other.
* <=  Checks if one list is less than or equal to the other.

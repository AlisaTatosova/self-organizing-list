#ifndef SELF_ORGANIZING_LIST_H
#define SELF_ORGANIZING_LIST_H
#include <iostream>

template <typename T>
class SelfOrganizingList {
private:
    struct Node {
        Node(); // // deafult constructor
        explicit Node(const T& value); // parameterized constructor

        T m_value;
        Node* m_next; //ptr to next node
        Node* m_prev; // ptr to previous node
        Node* m_asc; // ptr to the next greater node
        Node* m_desc; // ptr to the next smaller node
    };

    Node* m_head; // head of list
    Node* m_tail; // tail of list
    Node* m_asc_head; // node with min element
    Node* m_desc_head; // node with max element
    std::size_t m_size;

public:
    SelfOrganizingList();  // deafult constructor
    SelfOrganizingList(const SelfOrganizingList& other); // copy constructor
    SelfOrganizingList(SelfOrganizingList&& other) noexcept; // move constructor
    SelfOrganizingList(std::size_t size); // parameterized constructor
    SelfOrganizingList(std::initializer_list<T> list); //constructor with initializer list
    ~SelfOrganizingList(); // destructor

public:
    SelfOrganizingList& operator=(const SelfOrganizingList& other); // copy assingment operator
    SelfOrganizingList& operator=(SelfOrganizingList&& other) noexcept; // move assignment operator
    void assign(std::initializer_list<T> list); // assigns elements of initializer list to list

    // element access
    T& front(); // access the first element
    const T& front() const;
    T& back(); // access the last element
    const T& back() const;

public:
    const T get_at(const std::size_t pos); // get value of node at some position
    std::size_t size() const; // return the number of elements
    bool empty();  // checks emptiness

public:
    //modifiers
    void push_back(const T& val); // adds element at the end
    void push_front(const T& val); // adds element at front
    void insert(const std::size_t pos, const T& val); // inserts some value at some position
    void insert(const std::size_t pos, const std::size_t count, const T& val); // inserts some count of some value starting from some position 
    void insert(const std::size_t pos, const std::initializer_list<T>& values); // inserts initializer list values starting from some positin
    void pop_back(); // deletes last element
    void pop_front(); // deletes front element
    void erase(const std::size_t pos); // erases element from some position
    void erase(const std::size_t start_pos, const std::size_t end_pos); // erases elements of some interval
    void emplace_front(const std::size_t count); // changes size of list adding new nodes at front(with values 0)
    void resize(const std::size_t count); // changes size of list adding new nodes at the end(with values 0)
    void swap(SelfOrganizingList<T>& other); // swap lists
    void clear(); // clears the contents

public:
    void merge(SelfOrganizingList<T>& other); // merges 2lists
    void splice(std::size_t pos, SelfOrganizingList<T>& list); // moves elements from another list in current list starting from some position
    void remove(const T& val); // removes elements with some value
    void reverse(); // reverses the list
    void unique(); // removes neighbour dublicate elements
    void sort(); // sorts the list
    
public:
    void print_from_head(); // print starting from head
    void print_ascending_order(); // print in ascending order
    void print_descending_order(); // print in descending order
    void print_from_tail(); // print starting from tail

public:
    bool operator==(const SelfOrganizingList& other) const;
    bool operator!=(const SelfOrganizingList& other) const;
    bool operator>(const SelfOrganizingList& other) const;
    bool operator>=(const SelfOrganizingList& other) const;
    bool operator<(const SelfOrganizingList& other) const;
    bool operator<=(const SelfOrganizingList& other) const;

private:
    void put_back(Node* node); // putting node at back of sorted order
    void put_front(Node* node); // putting node at front of sorted order
    void put_in_sorted_order(Node* node); // refers pointer m_asc of the node to the next greater node, and pointer m_desc to the next lesser node
    void remove_from_sorted_order(Node* node); // removes node from sorted order
    Node* get_node_at_pos(const std::size_t pos); // getting node at some position
    void advance_node(Node* node); //provides a self-organizing nature of this list.Elements that are accessed are moved closer to the front of the list to reduce access time.
};

#endif
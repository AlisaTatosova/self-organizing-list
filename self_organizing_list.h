#ifndef SELF_ORGANIZING_LIST_H
#define SELF_ORGANIZING_LIST_H
#include <iostream>

template <typename T>
class SelfOrganizingList {
private:
    struct Node {
        Node();
        explicit Node(const T& value);

        T m_value;
        Node* m_next;
        Node* m_prev;
        Node* m_asc;
        Node* m_desc;
    };

    Node* m_head;
    Node* m_tail;
    Node* m_asc_head;
    Node* m_desc_head;
    std::size_t m_size;

public:
    SelfOrganizingList(); 
    SelfOrganizingList(const SelfOrganizingList& other);
    SelfOrganizingList(SelfOrganizingList&& other) noexcept;
    SelfOrganizingList(const T* arr, std::size_t size);
    SelfOrganizingList(std::initializer_list<T> list);
    ~SelfOrganizingList();

public:
    SelfOrganizingList& operator=(const SelfOrganizingList& other);
    SelfOrganizingList& operator=(SelfOrganizingList&& other);
    void assign(std::initializer_list<T> list);
    T& front(); //access the first element
    const T& front() const;
    T& back(); //access the last element
    const T& back() const;
    void push_back(const T& val);
    void push_front(const T& val);
    void insert(const std::size_t pos, const T& val);
    void insert(const std::size_t pos, const std::size_t count, const T& val);
    void insert(const std::size_t pos, const std::initializer_list<T>& values);
    void pop_back();
    void pop_front();
    void erase(const std::size_t pos);
    void erase(const std::size_t start_pos, const std::size_t end_pos);
    void resize(const std::size_t count);
    void reverse();
    void splice(std::size_t pos, SelfOrganizingList<T>& list); //moves elements from another list
    void swap(SelfOrganizingList<T>& other);
    void unique();
    const T get_at(const std::size_t pos);
    void clear();
    std::size_t size() const;
    bool empty();
    void print();
    void print_ascending_order();
    void print_descending_order();
    void print_from_tail();

public:
    bool operator==(const SelfOrganizingList& other) const;
    bool operator!=(const SelfOrganizingList& other) const;
    bool operator>(const SelfOrganizingList& other) const;
    bool operator>=(const SelfOrganizingList& other) const;
    bool operator<(const SelfOrganizingList& other) const;
    bool operator<=(const SelfOrganizingList& other) const;

private:
    void put_back(Node* node);
    void put_front(Node* node);
    void put_in_sorted_order(Node* node); // refers pointer m_asc of the inserted node to the next greater node, and pointer m_desc to the next lesser node
    void remove_from_sorted_order(Node* node);
    Node* get_node_at_pos(const std::size_t pos);
    void advance_node(Node* node); //provides a self-organizing nature of this list.Elements that are accessed are moved closer to the front of the list to reduce access time.
};

#endif
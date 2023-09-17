#include "self_organizing_list.h"

// deafult constructor
template <typename T>
SelfOrganizingList<T>::Node::Node() 
    : m_next{nullptr}
    , m_prev{nullptr}
    , m_asc{nullptr}
    , m_desc{nullptr} {}

// parametrized constructor
template <typename T>
SelfOrganizingList<T>::Node::Node(const T& value)
    : m_value{value}
    , m_next{nullptr}
    , m_prev{nullptr}
    , m_asc{nullptr}
    , m_desc{nullptr} {}

// deafult constructor
template <typename T>
SelfOrganizingList<T>::SelfOrganizingList() 
    : m_head{nullptr}
    , m_tail{nullptr}
    , m_asc_head{nullptr}
    , m_desc_head{nullptr}
    , m_size{0} {}

// copy constructor
template <typename T>
SelfOrganizingList<T>::SelfOrganizingList(const SelfOrganizingList<T>& other) 
    : m_head{nullptr}
    , m_tail{nullptr}
    , m_asc_head{nullptr}
    , m_desc_head{nullptr}
    , m_size{0} {

    Node* curr = other.m_head;
    while (curr) {
        push_back(curr -> m_value);
        curr = curr -> m_next;
    }
}

// move constructor
template <typename T>
SelfOrganizingList<T>::SelfOrganizingList(SelfOrganizingList<T>&& other) noexcept
    : m_head{other.m_head}
    , m_tail{other.m_tail}
    , m_asc_head{other.m_asc_head}
    , m_desc_head{other.m_desc_head}
    , m_size{0} {
    other.m_head = nullptr;
    other.m_tail = nullptr;
    other.m_asc_head = nullptr;
    other.m_desc_head = nullptr;
    other.m_size = 0;
}

// parameterized constructor
template <typename T>
SelfOrganizingList<T>::SelfOrganizingList(std::size_t size) 
    : m_head(nullptr)
    , m_tail(nullptr)
    , m_asc_head{nullptr}
    , m_desc_head{nullptr} {
    for (std::size_t i = 0; i < size; ++i) {
        push_back(0);
    }
}

// constructor with initializer list
template <typename T>
SelfOrganizingList<T>::SelfOrganizingList(std::initializer_list<T> list)
    : m_head(nullptr)
    , m_tail(nullptr)
    , m_asc_head{nullptr}
    , m_desc_head{nullptr} {
    for (const auto& el : list) {
        push_back(el);
    }
}

// destructor
template <typename T>
SelfOrganizingList<T>::~SelfOrganizingList() {
    clear();
}

// copy assingment operator
template <typename T>
SelfOrganizingList<T>& SelfOrganizingList<T>::operator=(const SelfOrganizingList<T>& other) {
    // checking for self assignment
    if (this == &other) {
        return *this;
    }
    clear(); // clearing list in which we assign
    Node* curr = other.m_head;
    while (curr) { 
        push_back(curr -> m_value);
        curr = curr -> m_next;
    }
    return *this;
}

 // move assignment operator
template <typename T>
SelfOrganizingList<T>& SelfOrganizingList<T>::operator=(SelfOrganizingList<T>&& other) noexcept {
    // checking for self assignment
    if (this == &other) {
        return *this;
    }
    clear(); // clearing list in which we assign
    m_size = other.m_size;
    m_head = other.m_head;
    m_asc_head = other.m_asc_head;
    m_desc_head = other.m_desc_head;
    m_tail = other.m_tail;
    other.m_head = nullptr;
    other.m_asc_head = nullptr;
    other.m_desc_head = nullptr;
    other.m_tail = nullptr;
    other.m_size = 0;
    return *this;
}

// assigns elements of initializer list to list
template <typename T>
void SelfOrganizingList<T>::assign(std::initializer_list<T> list) {
    clear(); // clear list
    insert(0, list); // insert initializer list values to list
}

//access the first element
template <typename T>
T& SelfOrganizingList<T>::front() {
    Node* curr = get_node_at_pos(0); // getting node at position 0
    return curr -> m_value;
}

template <typename T>
const T& SelfOrganizingList<T>::front() const {
    Node* curr = get_node_at_pos(0);
    return curr -> m_value;
}

//access the last element
template <typename T>
T& SelfOrganizingList<T>::back() {
    Node* curr = get_node_at_pos(m_size - 1); // getting node at last position
    return curr -> m_value;
}

template <typename T>
const T& SelfOrganizingList<T>::back() const {
    Node* curr = get_node_at_pos(m_size - 1);
    return curr -> m_value;
}

// get value of node at some position
template <typename T>   
const T SelfOrganizingList<T>::get_at(const std::size_t pos) {
    Node* curr = get_node_at_pos(pos); // geting node of some position
    advance_node(curr); // after getting node, call advance_node(Node*) function to swap that node with the node in his left: moving closer node that has been accessed to reduce access time next time getting that node.
    return curr -> m_value;
}

// return the number of elements
template <typename T>
std::size_t SelfOrganizingList<T>::size() const {
    return m_size;
}

// checks emptiness
template <typename T>   
bool SelfOrganizingList<T>::empty() {
    return m_size == 0;
}

// adds element at the end
template <typename T>
void SelfOrganizingList<T>::push_back(const T& val) {
    Node* new_node = new Node(val);
    if (!m_tail) { // if there is no element 
        m_head = new_node;
        m_tail = new_node;
    } else { 
        Node* tmp = m_tail;
        tmp -> m_next = new_node;
        new_node -> m_prev = tmp;
        m_tail = new_node;
    }
    ++m_size;
    put_in_sorted_order(new_node); // refers pointer m_asc of the inserted node to the next greater node, and pointer m_desc to the next lesser node
}

// adds element at front
template <typename T>
void SelfOrganizingList<T>::push_front(const T& val) {
    Node* new_node = new Node(val);
    if (!m_head) { // if there is no element
        m_head = new_node;
        m_tail = new_node;
    } else {
        Node* tmp = m_head;
        new_node -> m_next = tmp;
        tmp -> m_prev = new_node;
        m_head = new_node;
    }
    ++m_size;
    put_in_sorted_order(new_node); // refers pointer m_asc of the inserted node to the next greater node, and pointer m_desc to the next lesser node
}

// deletes last element
template <typename T>
void SelfOrganizingList<T>::pop_back() {
    if (!m_head) {
        throw std::runtime_error("There is no element in list.");
    } 
    Node* tmp = nullptr;
    if (m_head == m_tail) { // if there is single element
        tmp = m_head;
        m_head = nullptr;
        m_tail = nullptr;
    } else {
        tmp = m_tail;
        Node* node = m_head;
        while (node -> m_next != m_tail) {
            node = node -> m_next;
        }
        m_tail = node;
        m_tail -> m_next = nullptr;
    }
    --m_size;
    remove_from_sorted_order(tmp);  // removing node from sorted order
    delete tmp;
}

// deletes front element
template <typename T>
void SelfOrganizingList<T>::pop_front() {
    if (!m_head) {
        throw std::runtime_error("There is no element in list.");
    } 
        
    Node* tmp = nullptr;
    if (m_head == m_tail) { // if there is single element
        tmp = m_head;
        m_head = nullptr;
        m_tail = nullptr;
    } else {
        tmp = m_head;
        Node* node = m_head -> m_next;
        m_head = node;
    }
    --m_size;
    remove_from_sorted_order(tmp);  // removing node from sorted order
    delete tmp;
}

// inserts some value at some position
template <typename T>
void SelfOrganizingList<T>::insert(const std::size_t pos, const T& val) {
    if (pos < 0 || pos > m_size) { // checking if position is invalid
        throw std::out_of_range("Invalid postion");
    } else if (pos == 0) { // checking if position is front
        push_front(val);
    } else if (pos == m_size) { // cheking if insert must be at the end of list
        push_back(val);
    } else { 
        Node* to_insert = new Node(val);
        Node* node = get_node_at_pos(pos);
        node -> m_prev -> m_next = to_insert;
        to_insert -> m_prev = node -> m_prev;
        to_insert -> m_next = node;
        node -> m_prev = to_insert; 
        ++m_size;
        put_in_sorted_order(to_insert); // putting node in sorted order
    }
}

// inserts some count of some value starting from some position 
template <typename T>
void SelfOrganizingList<T>::insert(const std::size_t pos, const std::size_t count, const T& val) {
    if (pos < 0 || pos > m_size) { // checking if position is invalid
        throw std::out_of_range("Invalid postion");
    } else if (pos == 0) { // checking if position is front
        for (int i = 0; i < count; ++i) {
            push_front(val);
        }
    } else if (pos == m_size) { // cheking if insert must be at the end of list
        for (int i = 0; i < count; ++i) {
            push_back(val);
        }
    } else {
        for (int i = 0; i < count; ++i) {
            Node* to_insert = new Node(val);
            Node* node = get_node_at_pos(pos);
            node -> m_prev -> m_next =  to_insert;
            to_insert -> m_prev = node -> m_prev;
            to_insert -> m_next = node;
            node -> m_prev = to_insert; 
            ++m_size;
            put_in_sorted_order(to_insert); // putting node in sorted order
        }
    }
}

// inserts initializer list values starting from some positin
template <typename T>
void SelfOrganizingList<T>::insert(const std::size_t pos, const std::initializer_list<T>& values) {
    int index = pos;
    for (const auto& val : values) {
        insert(index, val);
        ++index;
    }
}

// erases element from some position
template <typename T>
void SelfOrganizingList<T>::erase(const std::size_t pos) {
    if (pos < 0 || pos >= m_size) { // checking if position is invalid
        throw std::out_of_range("Invalid postion");
    } else if (pos == 0) { // checking if position is front
        pop_front();
    } else if (pos == m_size - 1) { // checking if it is last position
        pop_back();
    } else {
        Node* to_delete = get_node_at_pos(pos);
        to_delete -> m_next -> m_prev = to_delete -> m_prev;
        to_delete -> m_prev -> m_next = to_delete -> m_next;
        --m_size;
        remove_from_sorted_order(to_delete); // removing node from sorted order
        delete to_delete;
    }
}

// erases elements of some interval
template <typename T>
void SelfOrganizingList<T>::erase(const std::size_t start_pos, const std::size_t end_pos) {
    if (start_pos < 0 || start_pos >= m_size || end_pos < 0 || end_pos >= m_size) { // checking if position is invalid
        throw std::out_of_range("Invalid postion");
    } else if (start_pos == 0) { // checking if start position is front
        for (int i = 0; i < end_pos; ++i) {
            pop_front();
        }
    } else if (start_pos == m_size - 1) { // checking if start position is last position
        pop_back();
    } else {
        int index = start_pos;
        for (int i = start_pos; i <= end_pos; ++i) {
            erase(index); 
        }
    }
}

// changes size of list adding new nodes at front(with values 0)
template <typename T>
void SelfOrganizingList<T>::emplace_front(const std::size_t count) {
    if (count == m_size) { // if count = size there is nothing done
        return;
    } else if (count > m_size) { // if count > size inserting at front count - size nodes(with value 0) 
        insert(0, count - m_size, 0);
    } else { // if count < size erasing size - count nodes from front
        erase(0, m_size - count);
    }
}

// changes size of list adding new nodes at the end(with values 0)
template <typename T>
void SelfOrganizingList<T>::resize(const std::size_t count) {
    if (count == m_size) { // if count = size there is nothing done
        return;
    } else if (count > m_size) { // if count > size inserting at the end count - size nodes(with value 0) 
        for (int i = 0; i < m_size - count; ++i) {
            push_back(0);
        }
    } else { // if count < size erasing from end
        while (m_size > count) {
            erase(m_size - 1);
        }
    }
}

// swap lists
template <typename T>
void SelfOrganizingList<T>::swap(SelfOrganizingList<T>& other) {
    std::swap(m_head, other.m_head);
    std::swap(m_tail, other.m_tail);
    std::swap(m_asc_head, other.m_asc_head);
    std::swap(m_desc_head, other.m_desc_head);
    std::swap(m_size, other.m_size); 
}

// merges 2lists
template <typename T>
void SelfOrganizingList<T>::merge(SelfOrganizingList<T>& other) {
    if (!other.m_head) { // if other list is empty
        return;
    }

    //if the list in which we want to merge is empty
    if (!m_head) {
        *this = other;
        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_asc_head = nullptr;
        other.m_desc_head = nullptr;
        other.m_size = 0;
        return;
    }

    Node* curr = other.m_head;
    while (other.m_head) {
        curr = other.m_head;
        other.m_head = other.m_head -> m_next;
        curr -> m_next = nullptr;
        curr -> m_prev = nullptr;
        curr -> m_asc = nullptr;
        curr -> m_desc = nullptr;
        m_tail -> m_next = curr;
        curr -> m_prev = m_tail;
        m_tail = curr;
        put_in_sorted_order(m_tail);
    }
    // assinging nullptr to all pointers of other
    other.m_head = nullptr;
    other.m_asc_head = nullptr;
    other.m_desc_head = nullptr;
    other.m_tail = nullptr;
    other.m_size = 0;
    return;
}

// moves elements from another list in current list starting from some position
template <typename T>
void SelfOrganizingList<T>::splice(std::size_t pos, SelfOrganizingList<T>& list) {
    if (pos < 0 || list.empty()) {  // if position invalid or list from which we splice is empty
        return;
    }
    // inserting list to the current list starting from some position
    Node* head = list.m_head;
    for (int i = 0; i < list.size(); ++i) {
        insert(pos + i, head -> m_value);
        head = head -> m_next;
    }
    list.clear();
}

// removes elements with some value
template <typename T>
void SelfOrganizingList<T>::remove(const T& val) {
    Node* curr = m_head;
    std::size_t pos = 0;
    while (curr) {
        if (curr -> m_value == val) {
            // saving a reference to the next node before erasing the current node
            Node* next = curr -> m_next;
            erase(pos);
            curr = next; 
        } else {
            curr = curr -> m_next;
            ++pos;
        }
    }
}

// reverses the list
template <typename T>
void SelfOrganizingList<T>::reverse() {
    Node* curr = nullptr;
    Node* tmp = nullptr;
    Node* new_tail = m_head;

    while (new_tail) {
        curr = new_tail;
        tmp = curr -> m_next;
        curr -> m_next = curr -> m_prev; // reverse the next pointer
        curr -> m_prev = tmp; // reverse the prev pointer
        new_tail = tmp;
    }
    m_tail = m_head; // the old head becomes the new tail
    m_head = curr; // the current node becomes the new head
}

// removes neighbour dublicate elements
template <typename T>
void SelfOrganizingList<T>::unique() {
    Node* curr = m_head;
    std::size_t pos = 0;
    while (curr && curr -> m_next) {
        ++pos;
        if (curr -> m_value == curr -> m_next -> m_value) { // if neighbour element are dublicates
            erase(pos);
            --pos;
        } else {
            curr = curr -> m_next;
        }
    }
}

// sorts the list
template <typename T>
void SelfOrganizingList<T>::sort() {
    m_head = m_asc_head;
    m_tail = m_desc_head;
    Node* curr = m_head;
    while (curr) { 
        curr -> m_next = curr -> m_asc;
        curr -> m_prev = curr -> m_desc;
        curr = curr -> m_next;
    }
}

// removes all nodes
template <typename T>
void SelfOrganizingList<T>::clear() {
    while (m_head) {
        Node* curr = m_head -> m_next;
        delete m_head;
        m_head = curr;
    }
    // assinging nullptr to all pointers
    m_head = nullptr;
    m_tail = nullptr;
    m_asc_head = nullptr;
    m_desc_head = nullptr;
    m_size = 0;
}

// print starting from head
template <typename T>
void SelfOrganizingList<T>::print_from_head() {
    Node* curr = m_head;
    while (curr) {
        std::cout << curr -> m_value << " ";
        curr = curr -> m_next;
    }
    std::cout << std::endl;
}

// print starting from tail
template <typename T>
void SelfOrganizingList<T>::print_from_tail() {
    Node* curr = m_tail;
    while (curr) {
        std::cout << curr -> m_value << " ";
        curr = curr -> m_prev;
    }
    std::cout << std::endl;
}

// print in ascending order
template <typename T>    
void SelfOrganizingList<T>::print_ascending_order() {
    Node* curr = m_asc_head;
    while (curr) {
        std::cout << curr -> m_value << " ";
        curr = curr -> m_asc;
    }
    std::cout << std::endl;
}

// print in descending order
template <typename T>
void SelfOrganizingList<T>::print_descending_order() {
    Node* curr = m_desc_head;
    while (curr) {
        std::cout << curr -> m_value << " ";
        curr = curr -> m_desc;
    }
    std::cout << std::endl;
}

template <typename T>
bool SelfOrganizingList<T>::operator==(const SelfOrganizingList<T>& other) const {
    // initialize pointers to the heads of both lists
    Node* curr1 = m_head;
    Node* curr2 = other.m_head;

    // traverse both lists 
    while (curr1 && curr2) {
        // compare the values of the current nodes
        if (curr1 -> m_value != curr2 -> m_value) {
            return false; // if values are not equal, lists are not equal
        }
        // move to the next nodes in both lists
        curr1 = curr1->m_next;
        curr2 = curr2->m_next;
    }

    // check if both lists have been traversed completely
    // if both are nullptr, the lists are equal; otherwise, they're not
    return curr1 == nullptr && curr2 == nullptr;
}

template <typename T>
bool SelfOrganizingList<T>::operator>(const SelfOrganizingList<T>& other) const {
    // initialize pointers to the heads of both lists
    Node* curr1 = m_head;
    Node* curr2 = other.m_head;

    // traverse both lists 
    while (curr1 && curr2) {
        if (curr1 -> m_value >= curr2 -> m_value) {
            // if the current value in the current list is greater or equal,
            // move to the next nodes in both lists
            curr1 = curr1 -> m_next;
            curr2 = curr2 -> m_next;
        } else if (curr1 -> m_value < curr2 -> m_value) {
            return false; // if the current value in the current list is less, the current list is not greater
        }
    }

    // if we reach here, it means one list is a prefix of the other.
    if (curr1) {
        return true; // the current list is greater because it still has elements
    } else if (curr2) {
        return false; // the other list is greater because it still has elements
    } else {
        // lists are equal
        return false;
    }
}

template <typename T>
bool SelfOrganizingList<T>::operator>=(const SelfOrganizingList<T>& other) const {
    return (*this > other) || (*this == other);
}

template <typename T>
bool SelfOrganizingList<T>::operator<(const SelfOrganizingList<T>& other) const {
    return !(*this >= other);
}

template <typename T>
bool SelfOrganizingList<T>::operator<=(const SelfOrganizingList<T>& other) const {
    return !(*this > other);
}

// putting back of sorted order
template <typename T>
void SelfOrganizingList<T>::put_back(Node* node) {
    Node* curr = m_asc_head;
    if (!m_asc_head) { 
        m_asc_head = node;
        node -> m_asc = nullptr;
        m_desc_head = node;
        node -> m_desc = nullptr;
    } else {
        // moving to the end of ascending order
        while (curr -> m_asc) {
            curr = curr -> m_asc;
        }
        curr -> m_asc = node;
        m_desc_head = node;
        node -> m_desc = curr;
        node -> m_asc = nullptr;
    }
}

// putting at front of sorted order
template <typename T>
void SelfOrganizingList<T>::put_front(Node* node) {
    Node* curr = m_asc_head;
    if (!m_asc_head) {
        m_asc_head = node;
        node -> m_asc = nullptr;
        m_desc_head = node;
        node -> m_desc = nullptr;
    } else {
        node -> m_asc = curr;
        curr -> m_desc = node;
        m_asc_head = node;
    }
}
 
// puting node in sorted order
template <typename T>
void SelfOrganizingList<T>::put_in_sorted_order(Node* node) {
    Node* curr = m_head;
    Node* asc = m_asc_head;
    Node* desc = m_desc_head; 
    // finding place where must be putted 
    while (asc && asc -> m_value < node -> m_value) {
        asc = asc -> m_asc;
    }

    if (!asc) {  // if we reached end of ascending order put at the end
        put_back(node);
    } else if (asc == m_asc_head) { // if must be putted at front
        put_front(node);
    } else {
        node -> m_asc = asc;
        node -> m_desc = asc -> m_desc;
        asc -> m_desc = node;
        node -> m_desc-> m_asc = node;
    }
}

// removing node from sorted order
template <typename T>
void SelfOrganizingList<T>::remove_from_sorted_order(Node* node) {
    if (node == m_asc_head) { // check if the node is the head of the ascending order 
        m_asc_head = m_asc_head -> m_asc; // update the ascending head to the next node
        m_asc_head -> m_asc -> m_desc = nullptr;
        return;
    } 
    // if the node is not the ascending head, update links
    if (node -> m_asc) {
        node -> m_asc -> m_desc = node -> m_desc; // update the descending link of the previous node
    } 
    if (node -> m_desc){
        node -> m_desc -> m_asc = node -> m_asc; // update the ascending link of the next node
    }
}

// getting node at of some position
template <typename T>
typename SelfOrganizingList<T>::Node* SelfOrganizingList<T>::get_node_at_pos(const std::size_t pos) {
    if (pos < 0 || pos >= m_size) { // if position is invalid
        throw std::invalid_argument("Invalid position");
    }

    Node* curr = nullptr;
    if (pos < m_size / 2) { // if position is lesser than size / 2 start searching from head
        curr = m_head;
        std::size_t count{};
        while (curr && pos != count) {
            ++count;
            curr = curr -> m_next;
        }
    } else { // if position is greater than size / 2 start searching from tail
        curr = m_tail;
        std::size_t count = m_size - 1;
        while (curr && pos != count) {
            --count;
            curr = curr -> m_prev;
        }
    }
    return curr;
}

// provides a self-organizing nature of this list
// elements that are accessed are moved closer to the front of the list to reduce access time.
template <typename T>
void SelfOrganizingList<T>::advance_node(Node* node) {
    if (!node || node == m_head) {  // if node is front element
        return;
    }
    Node* lhs = node -> m_prev; // lhs is previous node of given nodee
    if (lhs -> m_prev && node -> m_next) { // if lhs 'previous' and given node's 'next' exists
        lhs -> m_prev -> m_next = node;
        node -> m_prev = lhs -> m_prev;
        lhs -> m_next = node -> m_next;
        node -> m_next -> m_prev = lhs;
        node -> m_next = lhs;
        lhs -> m_prev  = node;
    } else if (!lhs -> m_prev) { // if lhs 'previous' doesn't exist
        node -> m_prev = lhs -> m_prev;
        lhs -> m_prev = node;
        lhs -> m_next = node -> m_next;
        node -> m_next -> m_prev = lhs;
        node -> m_next = lhs;
        m_head = node;
    } else { // if given node's 'next' doesn't exist
        lhs -> m_prev -> m_next = node;
        node -> m_prev = lhs -> m_prev;
        lhs -> m_prev = node;
        lhs -> m_next = node -> m_next; 
        node -> m_next = lhs;
        m_tail = lhs;
    }
}




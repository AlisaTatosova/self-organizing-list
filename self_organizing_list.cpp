#include "self_organizing_list.h"

template <typename T>
SelfOrganizingList<T>::Node::Node() 
    : m_next{nullptr}
    , m_prev{nullptr}
    , m_asc{nullptr}
    , m_desc{nullptr} {}

template <typename T>
SelfOrganizingList<T>::Node::Node(const T& value)
    : m_value{value}
    , m_next{nullptr}
    , m_prev{nullptr}
    , m_asc{nullptr}
    , m_desc{nullptr} {}

template <typename T>
SelfOrganizingList<T>::SelfOrganizingList() 
    : m_head{nullptr}
    , m_tail{nullptr}
    , m_asc_head{nullptr}
    , m_desc_head{nullptr}
    , m_size{0} {}

template <typename T>
SelfOrganizingList<T>::SelfOrganizingList(const SelfOrganizingList<T>& other) 
    : m_head{nullptr}
    , m_tail{nullptr}
    , m_asc_head{nullptr}
    , m_desc_head{nullptr}
    , m_size{0} {

    Node* curr = other.m_head;
    while(curr) {
        push_back(curr -> m_value);
        curr = curr -> m_next;
    }
}

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

template <typename T>
SelfOrganizingList<T>::SelfOrganizingList(const T* arr, std::size_t size) 
    : m_head(nullptr)
    , m_tail(nullptr)
    , m_asc_head{nullptr}
    , m_desc_head{nullptr} {
    for (std::size_t i = 0; i < size; ++i) {
        push_back(arr[i]);
    }
}

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

template <typename T>
SelfOrganizingList<T>::~SelfOrganizingList() {
    clear();
}

template <typename T>
SelfOrganizingList<T>& SelfOrganizingList<T>::operator=(const SelfOrganizingList<T>& other) {
    if (this == &other) {
        return *this;
    }
    clear();
    Node* curr = other.m_head;
    while (curr) {
        push_back(curr -> m_value);
        curr = curr -> m_next;
    }
    return *this;
}

template <typename T>
SelfOrganizingList<T>& SelfOrganizingList<T>::operator=(SelfOrganizingList<T>&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    clear();
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

template <typename T>
void SelfOrganizingList<T>::assign(std::initializer_list<T> list) {
    clear();
    insert(0, list);
}

template <typename T>
T& SelfOrganizingList<T>::front() {
    Node* curr = get_node_at_pos(0);
    return curr -> m_value;
}

template <typename T>
const T& SelfOrganizingList<T>::front() const {
    Node* curr = get_node_at_pos(0);
    return curr -> m_value;
}

template <typename T>
T& SelfOrganizingList<T>::back() {
    Node* curr = get_node_at_pos(m_size - 1);
    return curr -> m_value;
}

template <typename T>
const T& SelfOrganizingList<T>::back() const {
    Node* curr = get_node_at_pos(m_size - 1);
    return curr -> m_value;
}

template <typename T>
void SelfOrganizingList<T>::push_back(const T& val) {
    Node* new_node = new Node(val);
    if (!m_tail) {
        m_head = new_node;
        m_tail = new_node;
    } else {
        Node* tmp = m_tail;
        tmp -> m_next = new_node;
        new_node -> m_prev = tmp;
        m_tail = new_node;
    }
    ++m_size;
    put_in_sorted_order(new_node);
}

template <typename T>
void SelfOrganizingList<T>::push_front(const T& val) {
    Node* new_node = new Node(val);
    if (!m_head) {
        m_head = new_node;
        m_tail = new_node;
    } else {
        Node* tmp = m_head;
        new_node -> m_next = tmp;
        tmp -> m_prev = new_node;
        m_head = new_node;
    }
    ++m_size;
    put_in_sorted_order(new_node);
}

template <typename T>
void SelfOrganizingList<T>::pop_back() {
    if (!m_head) {
        throw std::runtime_error("There is no element in list.");
    } 
    Node* tmp = nullptr;
    if (m_head == m_tail) {
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
    remove_from_sorted_order(tmp);
    delete tmp;
}

template <typename T>
void SelfOrganizingList<T>::pop_front() {
    if (!m_head) {
        throw std::runtime_error("There is no element in list.");
    } 
        
    Node* tmp = nullptr;
    if (m_head == m_tail) {
        tmp = m_head;
        m_head = nullptr;
        m_tail = nullptr;
    } else {
        tmp = m_head;
        Node* node = m_head -> m_next;
        m_head = node;
    }
    --m_size;
    remove_from_sorted_order(tmp);
    delete tmp;
}

template <typename T>
void SelfOrganizingList<T>::erase(const std::size_t pos) {
    if (pos < 0 || pos >= m_size) {
        throw std::out_of_range("Invalid postion");
    } else if (pos == 0) {
        pop_front();
    } else if (pos == m_size - 1) {
        pop_back();
    } else {
        Node* to_delete = get_node_at_pos(pos);
        to_delete -> m_next -> m_prev = to_delete -> m_prev;
        to_delete -> m_prev -> m_next = to_delete -> m_next;
        --m_size;
        remove_from_sorted_order(to_delete);
        delete to_delete;
    }
}

template <typename T>
void SelfOrganizingList<T>::erase(const std::size_t start_pos, const std::size_t end_pos) {
    if (start_pos < 0 || start_pos >= m_size || end_pos < 0 || end_pos >= m_size) {
        throw std::out_of_range("Invalid postion");
    } else if (start_pos == 0) {
        for (int i = 0; i < end_pos; ++i) {
            pop_front();
        }
    } else if (start_pos == m_size - 1) {
        pop_back();
    } else {
        int index = start_pos;
        for (int i = start_pos; i <= end_pos; ++i) {
            erase(index); 
        }
    }
}

template <typename T>
void SelfOrganizingList<T>::insert(const std::size_t pos, const T& val) {
    if (pos < 0 || pos > m_size) {
        throw std::out_of_range("Invalid postion");
    } else if (pos == 0) {
        push_front(val);
    } else if (pos == m_size) {
        push_back(val);
    } else {
        Node* to_insert = new Node(val);
        Node* node = get_node_at_pos(pos);
        node -> m_prev -> m_next = to_insert;
        to_insert -> m_prev = node -> m_prev;
        to_insert -> m_next = node;
        node -> m_prev = to_insert; 
        ++m_size;
        put_in_sorted_order(to_insert);
    }
}

template <typename T>
void SelfOrganizingList<T>::insert(const std::size_t pos, const std::size_t count, const T& val) {
    if (pos < 0 || pos > m_size) {
        throw std::out_of_range("Invalid postion");
    } else if (pos == 0) {
        for (int i = 0; i < count; ++i) {
            push_front(val);
        }
    } else if (pos == m_size) {
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
            put_in_sorted_order(to_insert);
        }
    }
}

template <typename T>
void SelfOrganizingList<T>::insert(const std::size_t pos, const std::initializer_list<T>& values) {
    int index = pos;
    for (const auto& val : values) {
        insert(index, val);
        ++index;
    }
}

template <typename T>
void SelfOrganizingList<T>::resize(const std::size_t count) {
    if (count == m_size) {
        return;
    } else if (count > m_size) {
        for (int i = 0; i < m_size - count; ++i) {
            push_back(0);
        }
    } else {
        while (m_size > count) {
            erase(m_size - 1);
        }
    }
}

template <typename T>
void SelfOrganizingList<T>::reverse() {
    Node* curr = nullptr;
    Node* tmp = nullptr;
    Node* new_tail = m_head;

    while (new_tail) {
        curr = new_tail;
        tmp = curr -> m_next;
        curr -> m_next = curr -> m_prev;
        curr -> m_prev = tmp;
        new_tail = tmp;
    }
    m_tail = m_head;
    m_head = curr;
}

template <typename T>
void SelfOrganizingList<T>::splice(std::size_t pos, SelfOrganizingList<T>& list) {
    if (pos < 0 || list.empty()) {
        return;
    }
    Node* head = list.m_head;
    for (int i = 0; i < list.size(); ++i) {
        insert(pos + i, head -> m_value);
        head = head -> m_next;
    }
    list.clear();
}

template <typename T>
void SelfOrganizingList<T>::swap(SelfOrganizingList<T>& other) {
    std::swap(m_head, other.m_head);
    std::swap(m_tail, other.m_tail);
    std::swap(m_asc_head, other.m_asc_head);
    std::swap(m_desc_head, other.m_desc_head);
}

template <typename T>
void SelfOrganizingList<T>::unique() {
    Node* curr = m_head;
    std::size_t pos = 0;
    while (curr && curr -> m_next) {
        ++pos;
        if (curr -> m_value == curr -> m_next -> m_value) {
            erase(pos);
            --pos;
        } else {
            curr = curr -> m_next;
        }
    }
}

template <typename T>
bool SelfOrganizingList<T>::operator==(const SelfOrganizingList<T>& other) const {
    Node* curr1 = m_head;
    Node* curr2 = other.m_head;

    while (curr1 && curr2) {
        if (curr1 -> m_value != curr2 -> m_value) {
            return false;
        }
        curr1 = curr1 -> m_next;
        curr2 = curr2 -> m_next;
    }
    return curr1 == nullptr && curr2 == nullptr;
}

template <typename T>
bool SelfOrganizingList<T>::operator!=(const SelfOrganizingList<T>& other) const {
    return !(*this == other);
}

template <typename T>
bool SelfOrganizingList<T>::operator>(const SelfOrganizingList<T>& other) const {
    Node* curr1 = m_head;
    Node* curr2 = other.m_head;

    while (curr1 && curr2) {
        if (curr1 -> m_value >= curr2 -> m_value) {
            curr1 = curr1->m_next;
            curr2 = curr2->m_next;
        } else if (curr1->m_value < curr2->m_value) {
            return false;
        }
    }

    // If we reach here, it means one list is a prefix of the other.
    if (curr1) {
        return true;
    } else if (curr2) {
        return false;
    } else {
        // Lists are equal
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

template <typename T>   
const T SelfOrganizingList<T>::get_at(const std::size_t pos) {
    Node* curr = get_node_at_pos(pos);
    advance_node(curr);
    return curr -> m_value;
}

template <typename T>
void SelfOrganizingList<T>::clear() {
    while (m_head) {
        Node* curr = m_head -> m_next;
        delete m_head;
        m_head = curr;
    }
    m_head = nullptr;
    m_tail = nullptr;
    m_asc_head = nullptr;
    m_desc_head = nullptr;
    m_size = 0;
}

template <typename T>
std::size_t SelfOrganizingList<T>::size() const {
    return m_size;
}

template <typename T>   
bool SelfOrganizingList<T>::empty() {
    return m_size == 0;
}

template <typename T>
void SelfOrganizingList<T>::print() {
    Node* curr = m_head;
    while (curr) {
        std::cout << curr -> m_value << " ";
        curr = curr -> m_next;
    }
    std::cout << std::endl;
}

template <typename T>    
void SelfOrganizingList<T>::print_ascending_order() {
    Node* curr = m_asc_head;
    while (curr) {
        std::cout << curr -> m_value << " ";
        curr = curr -> m_asc;
    }
    std::cout << std::endl;
}

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
void SelfOrganizingList<T>::print_from_tail() {
    Node* curr = m_tail;
    while (curr) {
        std::cout << curr -> m_value << " ";
        curr = curr -> m_prev;
    }
    std::cout << std::endl;
}

template <typename T>
void SelfOrganizingList<T>::put_back(Node* node) {
    Node* curr = m_asc_head;
    if (!m_asc_head) {
        m_asc_head = node;
        node -> m_asc = nullptr;
        m_desc_head = node;
        node -> m_desc = nullptr;
    } else {
        while (curr -> m_asc) {
            curr = curr -> m_asc;
        }
        curr -> m_asc = node;
        m_desc_head = node;
        node -> m_desc = curr;
        node -> m_asc = nullptr;
    }
}

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
 
template <typename T>
void SelfOrganizingList<T>::put_in_sorted_order(Node* node) {
    Node* curr = m_head;
    Node* asc = m_asc_head;
    Node* desc = m_desc_head; 
    while (asc && asc -> m_value < node -> m_value) {
        asc = asc -> m_asc;
    }

    if (!asc) {
        put_back(node);
    } else if (asc == m_asc_head) {
        put_front(node);
    } else {
        node -> m_asc = asc;
        node -> m_desc = asc -> m_desc;
        asc -> m_desc = node;
        node -> m_desc-> m_asc = node;
    }
}

template <typename T>
void SelfOrganizingList<T>::remove_from_sorted_order(Node* node) {
    if (node == m_asc_head) {
        m_asc_head = m_asc_head -> m_asc;
        m_asc_head -> m_asc -> m_desc = nullptr;
        return;
    } 
    if (node -> m_asc) {
        node -> m_asc -> m_desc = node -> m_desc;
    } 
    if (node -> m_desc){
        node -> m_desc -> m_asc = node -> m_asc;
    }
}

template <typename T>
typename SelfOrganizingList<T>::Node* SelfOrganizingList<T>::get_node_at_pos(const std::size_t pos) {
    if (pos < 0 || pos >= m_size) {
        throw std::invalid_argument("Invalid position");
    }

    Node* curr = nullptr;
    if (pos < m_size / 2) {
        curr = m_head;
        std::size_t count{};
        while (curr && pos != count) {
            ++count;
            curr = curr -> m_next;
        }
    } else {
        curr = m_tail;
        std::size_t count = m_size - 1;
        while (curr && pos != count) {
            --count;
            curr = curr -> m_prev;
        }
    }
    return curr;
}

template <typename T>
void SelfOrganizingList<T>::advance_node(Node* node) {
    if (!node || node == m_head) {
        return;
    }
    Node* lhs = node -> m_prev;
    if (lhs -> m_prev && node -> m_next) {
        lhs -> m_prev -> m_next = node;
        node -> m_prev = lhs -> m_prev;
        lhs -> m_next = node -> m_next;
        node -> m_next -> m_prev = lhs;
        node -> m_next = lhs;
        lhs -> m_prev  = node;
    } else if (!lhs -> m_prev) {
        node -> m_prev = lhs -> m_prev;
        lhs -> m_prev = node;
        lhs -> m_next = node -> m_next;
        node -> m_next -> m_prev = lhs;
        node -> m_next = lhs;
        m_head = node;
    } else {
        lhs -> m_prev -> m_next = node;
        node -> m_prev = lhs -> m_prev;
        lhs -> m_prev = node;
        lhs -> m_next = node -> m_next; 
        node -> m_next = lhs;
        m_tail = lhs;
    }
}




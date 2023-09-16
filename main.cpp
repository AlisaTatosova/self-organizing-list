#include "self_organizing_list.h"
#include "self_organizing_list.cpp"
#include <iostream>

int main() {
    SelfOrganizingList<int> list1;
    list1.insert(0, 45);
    list1.push_back(5);
    list1.push_back(89);
    list1.push_back(3);
    list1.push_back(4);
    
    list1.pop_back();
    list1.push_back(111);
    list1.insert(3, 77);
    list1.pop_front();

    std::cout << "List before geting some position: ";
    list1.print_from_head();

    const int a = list1.get_at(2);

    std::cout << "List after geting position: ";
    list1.print_from_head();
    
    std::cout << "Sorted list in ascending: ";
    list1.print_ascending_order();

    std::cout << "Sorted list in descending: ";
    list1.print_descending_order();

    SelfOrganizingList<int> list2;
    list2.push_back(500);
    list2.push_back(8900);
    list2.push_back(3000);

    std::cout << "List2: ";
    list2.print_from_head();

    list2 = list1;
    
    list2.insert(2, 5, 99);
    list2.insert(1, {4, 6, 30, 5});
    list2.erase(1);

    std::cout << "List2 after some inserts and erases: ";
    list2.print_from_head();    
    
    SelfOrganizingList<int> list3;

    list3.push_back(1);
    list3.push_back(45);
    list3.push_back(3);
    list3.push_back(4);

    std::cout << "List3: ";
    list3.print_from_head();
   
    std::cout << "List3 after reverse: ";
    list3.reverse();
    list3.print_from_head();

   
    list3.splice(2, list2);

    std::cout << "List3 after splicing with list2: ";
    list3.print_from_head();

    return 0;
}
#include <iostream>
#include <string>
#include <fstream>

struct bank_deposit {
    std::string title;
    float sum;
    std::string currency;
    unsigned int interest_rate;
};

struct object {
    bank_deposit data;
    object *next;
    object *prev;
};

struct list {
    object *first;
    object *last;
};

int main(int argc, char *argv[]) {
    std::string file_name = argv[1];
    std::ifstream file;
    file.open(file_name);

    list list1;
    list1.first = nullptr;
    list1.last = nullptr;

    list1.first = new object;
    list1.first->next = list1.first;
    list1.first->prev = list1.first;

    file >> list1.first->data.title;
    file >> list1.first->data.sum;
    file >> list1.first->data.currency;
    file >> list1.first->data.interest_rate;

    list1.last = new object;
    list1.first->next = list1.last;
    list1.first->prev = list1.last;
    list1.last->next = list1.first;
    list1.last->prev = list1.first;

    file >> list1.last->data.title;
    file >> list1.last->data.sum;
    file >> list1.last->data.currency;
    file >> list1.last->data.interest_rate;


    while (true) {
        std::string title;
        file >> title;
        if (title == "")
            break;
        object *new_object = new object;
        list1.last->next = new_object;
        list1.first->prev = new_object;
        new_object->next = list1.first;
        new_object->prev = list1.last;
        list1.last = new_object;

        list1.last->data.title = title;
        file >> list1.last->data.sum;
        file >> list1.last->data.currency;
        file >> list1.last->data.interest_rate;
    }
    file.close();


    object *iter;
    bool is_sorted = false;
    while (!is_sorted) {
        iter = list1.first;
        is_sorted = true;
        while (iter != list1.last) {
            if (iter->data.sum > iter->next->data.sum) {
                object *tmp = iter->next;
                iter->prev->next = iter->next;
                iter->next->prev = iter->prev;
                iter->next->next->prev = iter;
                iter->next = iter->next->next;
                tmp->next = iter;
                iter->prev = tmp;
                is_sorted = false;
                if (iter == list1.first){
                    list1.first = tmp;
                } else if (tmp == list1.last){
                    list1.last = iter;
                }
            }
            iter = iter->next;
        };

    }
    iter = list1.first;
    do {
        std::cout << iter->data.title << ' '
                  << iter->data.sum << ' '
                  << iter->data.currency << ' '
                  << iter->data.interest_rate << std::endl;
        iter = iter->next;
    } while (iter != list1.first);

    iter = list1.first->next;
    while (iter != list1.first) {
        iter = iter->next;
        delete iter->prev;
    }
    delete list1.first;

    list1.first = nullptr;
    list1.last = nullptr;


    return 0;
}

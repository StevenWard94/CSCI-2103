/**
 * Steven Ward
 * CSCI-2103
 * string_list.cpp
 */

#include <iostream>
#include <limits>
#include <string>
#include <sstream>

#include <stddef.h>

template<typename D> class List;
template<typename D> std::ostream& operator<< (std::ostream& , List<D> const& );


template<class E>
class List {
    typedef E value_t;

  public:
    static const size_t NPOS = -1;

    inline size_t size( ) const { return size_; }
    inline bool isEmpty( ) const { return !head_; }

    List& add(value_t data, size_t pos = NPOS);
    List& remove(size_t pos = 0);

    size_t find(value_t data) const;
    value_t operator[](size_t index);

    List( ) = default;
    inline List(value_t const& data_head) : head_{new Node(data_head)}, size_(1) { }

    inline ~List( ) { del(head_); }

  private:
    struct Node {
        value_t data{ };
        Node* next{ nullptr };

        Node( ) = default;
        Node(value_t data, Node* next = nullptr)
                : data(data), next(next) { }
    };

    Node* head_{ nullptr };
    size_t size_ = 0;

    inline void del(Node* chain) {
        if (chain->next != nullptr) {
            del(chain->next);
        }
        delete chain;
    }

    friend std::ostream& operator<< <E>(std::ostream& os, List<E> const& ls);
};
// end of List<E> class definition.


template<class E>
std::ostream& operator<< (std::ostream& os, List<E> const& ls) {
    os << "[ ";
    typename List<E>::Node const* output_it = ls.head_;
    while (output_it != nullptr) {
        os << output_it->data << " ";
        output_it = output_it->next;
    }
    os << " ]";
    return os;
}

template<>
std::ostream& operator<< (std::ostream& os, List<std::string> const& strls) {
    typename List<std::string>::Node const* output_it = strls.head_;
    while (output_it != nullptr) {
        os << output_it->data;
        output_it = output_it->next;
        if (output_it != nullptr) {
            std::cout << " ";
        }
    }
    return os;
}


template<class E>
List<E>& List<E>::add(value_t data, size_t pos/* = NPOS*/) {
    if (!isEmpty() && pos > 0) {
        Node* leading_it  = this->head_;
        Node* trailing_it = new Node();

        // if pos >= size, loop will stop at the end of the list and append
        for (size_t i = 0; i < pos && i < size(); i++) {
            trailing_it = leading_it;
            leading_it  = leading_it->next;
        }
        trailing_it->next = new Node(data, leading_it);
    }
    else {
        this->head_ = new Node(data, this->head_);
    }
    size_++;
    return *this;
}


template<class E>
List<E>& List<E>::remove(size_t pos/* = 0*/) {
    if ( !isEmpty() ) {
        Node* leading_it  = this->head_;
        Node* trailing_it = nullptr;

        for (size_t i = 0; i < pos && i < size(); i++) {
            trailing_it = leading_it;
            leading_it  = leading_it->next;
        }

        if (trailing_it == nullptr) {
            this->head_ = leading_it->next;
        }
        else {
            trailing_it->next = leading_it->next;
        }
        delete leading_it;
        size_--;
    }

    return *this;
}


template<class E>
size_t List<E>::find(value_t data) const {
    if ( !isEmpty() ) {
        Node const* const_it = this->head_;
        size_t index = 0;

        while (const_it != nullptr) {
            if (const_it->data == data) return index;
            const_it = const_it->next;
            index++;
        }
    }
    return List::NPOS;
}


template<class E>
typename List<E>::value_t List<E>::operator[](size_t index) {
    // Note: operator performs no bounds-checking
    Node* it = this->head_;
    for (size_t j = 0; j < index; j++) {
        it = it->next;  // Note: this will throw on invalid index
    }
    return std::forward<value_t>(it->data);
}


int main(int argc, char** argv) {
    std::ios_base::sync_with_stdio(false);
    List<std::string> strList;

    std::cout << "Hello! Let's make a word list!" << std::endl << std::string(30, '*');
    std::cout << std::endl
            << "Please enter a sentence or a space-delimited list of words and hit enter when you are done:"
            << std::endl << std::string(95, '-') << std::endl;

    std::string str_buf;
    std::getline(std::cin, str_buf);
    std::istringstream iss(str_buf);
    std::string word;
    while (iss >> word) {
        strList.add(word);
    }

    std::cout << std::endl << std::endl;
    std::cout << "OK! Now give me another word, just one this time: ";
    std::getline(std::cin, str_buf);
    std::cout << "Cool, now give me a number: (between 1 and " << strList.size() << ") ";
    size_t num;
    std::cin >> num;

    std::cout << std::endl << "Here's your sentence with " << str_buf << " as the "
            << num << (num == 1 ? "st" : num == 2 ? "nd" : num == 3 ? "rd" : "th")
            << " word:" << std::endl << strList.add(str_buf, num - 1)
            << std::endl << std::endl;

    std::cout << "Now we will try searching through your sentence!" << std::endl
            << "Just give me a word and I will give you its position in the sentence!"
            << std::endl;

    if (std::cin.rdbuf()->in_avail()) {
        std::cin.ignore(std::cin.rdbuf()->in_avail());
    }
    std::getline(std::cin, str_buf);

    size_t index = strList.find(str_buf);
    while (index == List<std::string>::NPOS) {
        std::cout << std::endl << "C'mon now! That word isn't in your sentence!"
                << std::endl << "Give me another one: ";
        std::getline(std::cin, str_buf);
        index = strList.find(str_buf);
    }
    std::cout << std::endl << str_buf << " is the " << index + 1
            << (index == 0 ? "st" : index == 1 ? "nd" : index == 2 ? "rd" : "th")
            << " word in the new sentence!" << std::endl;
    std::cout << std::endl << "That reminds me, I think the sentence would be better without that word..."
            << std::endl << std::endl << "I'm just going to remove it for you:" << std::endl
            << strList.remove(index);
    std::cout << std::endl << std::endl << "Well, I think that is all we have time for..."
            << std::endl << "Goodbye for now!";
    std::cin.ignore();

    return 0;
}

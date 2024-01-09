#pragma once
#include <cstddef>
#include <string>
#include <utility>
#include <iostream>

template <typename Type>
class SingleLinkedList {

    struct Node {
        Node() = default;
        Node(const Type& val, Node* next)
            : value(val)
            , next_node(next) {
        }
        Type value;
        Node* next_node = nullptr;
    };
 
    template <typename ValueType>
    class BasicIterator {
       
        friend class SingleLinkedList;
        explicit BasicIterator(Node* node):node_(node) {}

    public:  
      
        using iterator_category = std::forward_iterator_tag;
        using value_type = Type;
        using difference_type = std::ptrdiff_t;
        using pointer = ValueType*;
        using reference = ValueType&;

        BasicIterator() = default;      

        BasicIterator(const BasicIterator<Type>& other) noexcept: node_(other.node_) {}


        BasicIterator& operator=(const BasicIterator& rhs) = default;

        [[nodiscard]] bool operator==(const BasicIterator<const Type>& rhs) const noexcept {
            return  node_==rhs.node_;
        }

        [[nodiscard]] bool operator!=(const BasicIterator<const Type>& rhs) const noexcept {
           return  node_!=rhs.node_;
        }
        
        [[nodiscard]] bool operator==(const BasicIterator<Type>& rhs) const noexcept {
            return  node_==rhs.node_;
        }
       
        [[nodiscard]] bool operator!=(const BasicIterator<Type>& rhs) const noexcept {
            return  node_!=rhs.node_;
        }
       
        BasicIterator& operator++() noexcept {
            node_=node_->next_node;
            return *this;           
        }

        BasicIterator operator++(int) noexcept {
           auto old_value(*this);
           ++(*this);
           return old_value;
        }

        [[nodiscard]] reference operator*() const noexcept {           
            return (*node_).value;
        }
        
        [[nodiscard]] pointer operator->() const noexcept {
            return &(node_->value);
        }

    private:
        Node* node_ = nullptr;       
    };
    
public:
    using value_type = Type;
    using reference = value_type&;
    using const_reference = const value_type&;
    using Iterator = BasicIterator<Type>;
    using ConstIterator = BasicIterator<const Type>;
   
    SingleLinkedList () = default;
    
    SingleLinkedList(std::initializer_list<Type> values) ;
    
    SingleLinkedList(const SingleLinkedList& other) ;

    SingleLinkedList& operator=(const SingleLinkedList& rhs); 
    
    [[nodiscard]] Iterator begin() noexcept {       
        return Iterator(head_.next_node);
    }

    [[nodiscard]] Iterator end() noexcept {       
        return Iterator();
    }

    [[nodiscard]] ConstIterator begin() const noexcept {
        return ConstIterator(head_.next_node);
    }

    [[nodiscard]] ConstIterator end() const noexcept {
        return ConstIterator();
    }

    [[nodiscard]] ConstIterator cbegin() const noexcept {
       return ConstIterator(head_.next_node);
    }

    [[nodiscard]] ConstIterator cend() const noexcept {       
       return ConstIterator();
    }
    
    [[nodiscard]] Iterator before_begin() noexcept {
        
        return Iterator(&head_);
    }
      
    [[nodiscard]] ConstIterator before_begin() const noexcept {        
        return ConstIterator(const_cast< Node* >(&head_));
    }
    
    [[nodiscard]] ConstIterator cbefore_begin() const noexcept {
         return ConstIterator(const_cast< Node* >(&head_));
       }
   
    Iterator InsertAfter(ConstIterator pos, const Type& value) {
               auto point= new Node(value,pos.node_->next_node);
               ++size_;
               pos.node_->next_node=point;
               return Iterator(point); 
    }
        
    

    Iterator EraseAfter(ConstIterator pos) noexcept {
        
        auto point=((pos.node_->next_node)->next_node);
        delete (pos.node_->next_node);
        (pos.node_->next_node)=point;
        return Iterator(point);
        
    }
    void swap(SingleLinkedList& other) noexcept;
    
    void PopFront() noexcept; 
    
    void PushFront(const Type& value) ;
    
    void Clear();
    
    // Возвращает количество элементов в списке
    [[nodiscard]] size_t GetSize() const noexcept;

    // Сообщает, пустой ли список
    [[nodiscard]] bool IsEmpty() const noexcept; 

    ~SingleLinkedList (){
        Clear();
    } 
private:
    Node head_;
    size_t size_=0;
    
};


template <typename Type>
SingleLinkedList<Type>::SingleLinkedList(std::initializer_list<Type> values) {      
      SingleLinkedList tmp;
      auto point_to_point=&(tmp.head_.next_node);
      auto point=tmp.head_.next_node;
      
      for(auto iter_tmp=values.begin();iter_tmp!=values.end();++iter_tmp){
          point=new Node(*iter_tmp,nullptr);
          *point_to_point=point;         
          ++tmp.size_;
          point_to_point=&((*point_to_point)->next_node);
      }      
      (*this).swap(tmp);
    }

template <typename Type>
SingleLinkedList<Type>::SingleLinkedList(const SingleLinkedList<Type>& other) {
    
          SingleLinkedList tmp;
          auto point_to_point=&(tmp.head_.next_node);
          auto point=tmp.head_.next_node;
          for(auto iter_tmp=other.begin();iter_tmp!=other.end();++iter_tmp){
               point=new Node(*iter_tmp,nullptr);
               *point_to_point=point;         
               ++tmp.size_;
               point_to_point=&((*point_to_point)->next_node);
              } 
          (*this).swap(tmp);
        
    }
    
template <typename Type>
SingleLinkedList<Type>& SingleLinkedList<Type>::operator=(const SingleLinkedList& rhs) {
        if(this!=&rhs){        
            auto tmp(rhs);
            (*this).swap(tmp);       
        }
        return *this;
    }
    
template <typename Type>
void  SingleLinkedList<Type>::swap(SingleLinkedList& other) noexcept {
        Node* tmp;
        size_t l_size=0;
        tmp=other.head_.next_node;
        l_size=other.size_;        
        other.head_.next_node=head_.next_node;
        other.size_=size_;
        head_.next_node=tmp;
        size_=l_size; 
    }
    
template <typename Type>
void SingleLinkedList<Type>::PopFront() noexcept {
     if (size_!=0){
             auto p=head_.next_node->next_node;
             delete head_.next_node;
             head_.next_node=p;
             --size_;
         }
        
    }
    
template <typename Type>
bool SingleLinkedList<Type>::IsEmpty() const noexcept {       
       return (size_)?false:true;
    }

template <typename Type>
size_t SingleLinkedList<Type>::GetSize() const noexcept {        
        return size_;
    }

template <typename Type>
void SingleLinkedList<Type>::Clear(){
        while (head_.next_node!=nullptr) {
            Node*ptr=head_.next_node->next_node;
            delete head_.next_node;
            head_.next_node=ptr;
            --size_;
        }
    }
template <typename Type>
void SingleLinkedList<Type>::PushFront(const Type& value) {
        head_.next_node = new Node(value, head_.next_node);
        ++size_;
    }

template <typename Type>
void swap(SingleLinkedList<Type>& lhs, SingleLinkedList<Type>& rhs) noexcept {
    lhs.swap(rhs);
}

template <typename Type>
bool operator==(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    return std::equal(lhs.begin(),lhs.end(),rhs.begin());
}

template <typename Type>
bool operator!=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    // Заглушка. Реализуйте сравнение самостоятельно
    return !(lhs==rhs);
}

template <typename Type>
bool operator<(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    return std::lexicographical_compare(lhs.begin(),lhs.end(),rhs.begin(),rhs.end());
}

template <typename Type>
bool operator<=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    return !std::lexicographical_compare(rhs.begin(),rhs.end(),lhs.begin(),lhs.end());
}

template <typename Type>
bool operator>(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    return std::lexicographical_compare(rhs.begin(),rhs.end(),lhs.begin(),lhs.end());
}

template <typename Type>
bool operator>=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    return !std::lexicographical_compare(lhs.begin(),lhs.end(),rhs.begin(),rhs.end());
}

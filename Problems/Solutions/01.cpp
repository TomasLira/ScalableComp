
//-----------------------------------------------
// Thread-Safe Queue with Fine-Grained Locking
//-----------------------------------------------
// Key Features:
// - Separate mutexes for head and tail to minimize contention.
// - Automatic memory management.
// - Use of dummy node makes head_ and tail_ work on diff nodes when queue is not empty

#include <iostream>
#include <thread>
#include <mutex>

template <typename T>
class ThreadSafeQueue
{
private:
    struct node
    {
        std::shared_ptr<T> data;
        std::unique_ptr<node> next;
    };
std::mutex head_mutex;
// Created dummy *node to allow the proper use of threads
std::unique_ptr<node> head;

std::mutex tail_mutex;
node* tail;

// Guarantees that only one threds access tail
node* get_tail()
{
    std::lock_guard<std::mutex> tail_lock(tail_mutex);
    return tail;
}

std::unique_ptr<node> pop_head()
{
    std::lock_guard<std::mutex> head_lock(head_mutex);
    // head.get() gets' acess to node. If condition is true queue is empty
    if(head.get() == get_tail())
    {
        return nullptr;
    }

    std::unique_ptr<node> old_head(std::move(head));
    head = std::move(old_head->next);
    return old_head;
}

public:
    //ThreadSafeQueue(): head(new node),tail(head.get()){}
    ThreadSafeQueue()
    {
        std::unique_ptr<node> dummy(std::make_unique<node>());  // Create dummy node
        tail = dummy.get();  // tail points to the dummy node
        head = std::move(dummy);  // head takes ownership of the dummy node
    }
    ThreadSafeQueue(const ThreadSafeQueue& other)=delete;
    ThreadSafeQueue& operator=(const ThreadSafeQueue& other)=delete;

    std::shared_ptr<T> try_pop()
    {
        std::unique_ptr<node> old_head=pop_head();
        // versão simplificada: old_head?old_head->data:std::shared_ptr<T>();
        if (old_head) {
            return old_head->data;  // returns if node has been removed
        } else {
            return std::shared_ptr<T>();  // returns null pointer
        }
    }
    void push(T new_value)
    {
        std::shared_ptr<T> new_data(
            std::make_shared<T>(std::move(new_value)));
        
        // init a empty *node pointer p
        std::unique_ptr<node> p(new node);
        node* const new_tail = p.get()

        std::lock_guard<std::mutex> tail_lock(tail_mutex);
        tail->data = new_data;
        tail->next = std::move(p);
        tail = new_tail;
    }

};

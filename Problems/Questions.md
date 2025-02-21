# **Scalable Computing: 20 Problems on Data Structures, Algorithms, and Multithreading in C++**

## **1. Concurrent Queues**
### **Problem Statement**
Implement a **thread-safe Queue** that allows concurrent insertions and deletions using `std::mutex`.

### **Prerequisites & Knowledge**
- Basics of **Queues** operations
- Understanding **mutex locks** for thread safety
- Avoiding **deadlocks** during concurrent modification

---

## **2. Thread-Safe Stack Implementation**
### **Problem Statement**
Create a **thread-safe stack** using `std::mutex`. Implement `push`, `pop`, and `top` operations with proper synchronization.

### **Prerequisites & Knowledge**
- Stack operations (LIFO)
- Thread synchronization using `std::mutex`
- Exception safety in concurrent environments

---

## **3. Multi-threaded Binary Search Tree (BST)**
### **Problem Statement**
Implement a **concurrent binary search tree** that supports insertions and searches from multiple threads simultaneously.

### **Prerequisites & Knowledge**
- Basics of **BST** operations
- Protecting critical sections with **mutexes**
- Handling concurrent read-write scenarios

---

## **4. Parallel Breadth-First Search (BFS)**
### **Problem Statement**
Implement a **parallel BFS algorithm** for traversing a graph using `std::thread`.

### **Prerequisites & Knowledge**
- Understanding graph traversal algorithms
- Synchronizing shared data across threads
- Avoiding **race conditions** during node visitation

---

## **5. Multi-threaded Priority Queue**
### **Problem Statement**
Implement a **thread-safe priority queue** using `std::priority_queue` and `std::mutex`.

### **Prerequisites & Knowledge**
- Priority queue fundamentals
- Lock management for concurrent access
- Efficient insertion and deletion operations

---

## **6. Parallel Quick Sort Algorithm**
### **Problem Statement**
Write a **parallel quicksort algorithm** that spawns new threads for sorting partitions concurrently.

### **Prerequisites & Knowledge**
- Quick sort divide-and-conquer technique
- Dynamic thread management using `std::thread`
- Avoiding excessive thread creation

---

## **7. Concurrent Hash Map**
### **Problem Statement**
Create a **thread-safe hash map** where insertions, deletions, and searches can happen concurrently using fine-grained locks.

### **Prerequisites & Knowledge**
- Basics of **hash maps** and collision handling
- **Fine-grained locking** techniques for better performance
- Avoiding data races

---

## **8. Multi-threaded Fibonacci Calculation**
### **Problem Statement**
Compute the **n-th Fibonacci number** using multiple threads to optimize recursive calls.

### **Prerequisites & Knowledge**
- Recursive algorithm optimization
- Memoization techniques with thread safety
- Avoiding redundant thread creation

---

## **9. Parallel DFS (Depth-First Search)**
### **Problem Statement**
Implement a **parallel depth-first search** for graphs, using threads for each branch of exploration.

### **Prerequisites & Knowledge**
- DFS traversal fundamentals
- Managing recursive calls across threads
- Avoiding deadlocks and race conditions

---

## **10. Multi-threaded Sorting of Linked List**
### **Problem Statement**
Implement a **parallel merge sort** specifically designed for a **linked list**.

### **Prerequisites & Knowledge**
- Merge sort algorithm for linked lists
- Efficient splitting of linked lists for parallel processing
- Synchronizing list merging with mutexes

---

## **11. Producer-Consumer Problem Using Bounded Buffer**
### **Problem Statement**
Solve the **producer-consumer problem** with a fixed-size circular buffer using `std::mutex` and `std::condition_variable`.

### **Prerequisites & Knowledge**
- Circular buffer data structure
- Synchronizing access between multiple producers and consumers
- Preventing **deadlocks** and ensuring fair resource access

---

## **12. Deadlock-Free Resource Allocation**
### **Problem Statement**
Write a simulation of resource allocation where threads avoid **deadlock** using a priority-based system.

### **Prerequisites & Knowledge**
- Understanding **deadlocks** and their causes
- Priority-based scheduling
- Lock acquisition ordering

---

## **13. Concurrent Doubly Linked List**
### **Problem Statement**
Implement a **thread-safe doubly linked list** with concurrent insertions and deletions.

### **Prerequisites & Knowledge**
- Basics of **doubly linked lists**
- Using `std::mutex` for safe concurrent operations
- Avoiding deadlocks while traversing and modifying the list

---

## **14. Parallel Matrix Transposition**
### **Problem Statement**
Perform **matrix transposition** using multiple threads for large matrices.

### **Prerequisites & Knowledge**
- Matrix operations and their memory layouts
- Dividing work evenly across threads
- Handling data dependencies in parallel operations

---

## **15. Multi-threaded Graph Coloring**
### **Problem Statement**
Implement a **graph coloring algorithm** that assigns colors to nodes concurrently, minimizing color conflicts.

### **Prerequisites & Knowledge**
- Basics of **graph coloring** algorithms
- Handling node dependencies across threads
- Synchronizing access to shared color assignments

---

## **16. Parallel Prefix Sum (Scan)**
### **Problem Statement**
Implement a **parallel prefix sum** operation on a large array using multiple threads.

### **Prerequisites & Knowledge**
- Prefix sum algorithm and applications
- Breaking down the problem for parallel execution
- Efficient combination of partial results

---

## **17. Multi-threaded Memory Pool Allocator**
### **Problem Statement**
Design a **thread-safe memory pool allocator** to manage dynamic memory allocations efficiently across threads.

### **Prerequisites & Knowledge**
- Basics of custom memory allocation
- Synchronizing memory requests
- Preventing memory leaks in a multi-threaded environment

---

## **18. Asynchronous Logging System**
### **Problem Statement**
Create an **asynchronous logging system** where multiple threads log messages to a shared file without blocking.

### **Prerequisites & Knowledge**
- Using `std::async` for asynchronous task execution
- Thread-safe file I/O operations
- Efficient queue management for log entries

---

## **19. Parallel Dijkstra’s Shortest Path Algorithm**
### **Problem Statement**
Implement a **parallel version of Dijkstra’s algorithm** for computing shortest paths in a graph.

### **Prerequisites & Knowledge**
- Understanding of **Dijkstra’s algorithm**
- Managing shared data structures across threads
- Efficient thread communication and synchronization

---

## **20. Thread-Safe Skip List**
### **Problem Statement**
Create a **concurrent skip list** that supports efficient search, insertion, and deletion in logarithmic time.

### **Prerequisites & Knowledge**
- Skip list fundamentals
- Handling concurrent modifications
- Efficient lock management for performance optimization

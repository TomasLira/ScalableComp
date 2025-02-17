# Scalable Computing: 10 Introductory and Educational Problems in C++

## **1. Multi-threaded Summation**
### **Problem Statement**
Write a C++ program that computes the sum of numbers from **1 to 1,000,000** using multiple threads. Divide the work equally among **4 threads**.

### **Prerequisites & Knowledge**
- Basics of **multithreading** in C++ (`std::thread`)
- **Mutex** and race conditions
- Thread synchronization using `std::mutex`

---

## **2. Parallel Matrix Multiplication**
### **Problem Statement**
Implement a **parallel matrix multiplication** program using `std::thread`. The program should take two **NxN matrices** and compute their product in a multi-threaded fashion.

### **Prerequisites & Knowledge**
- Understanding of **matrix multiplication**
- Multi-threading with `std::thread`
- Using `std::vector` for dynamic memory handling

---

## **3. OpenMP Parallel Loop Optimization**
### **Problem Statement**
Use **OpenMP** to parallelize a for-loop that sums an array of **10,000,000** elements.

### **Prerequisites & Knowledge**
- Basics of **OpenMP** (`#pragma omp parallel for`)
- Understanding of **loop parallelization**
- Using `reduction(+:sum)` to handle summation safely

---

## **4. Multi-threaded Web Server**
### **Problem Statement**
Implement a **basic web server** in C++ that can handle multiple connections concurrently using **threads**.

### **Prerequisites & Knowledge**
- Understanding of **sockets in C++**
- Using `std::thread` to handle multiple connections
- Understanding **HTTP request-response model**

---

## **5. Distributed Summation with MPI**
### **Problem Statement**
Use **MPI (Message Passing Interface)** to distribute the sum of **1 to 100,000** across multiple processes.

### **Prerequisites & Knowledge**
- Basics of **MPI (`MPI_Init`, `MPI_Comm_rank`, `MPI_Comm_size`)**
- Message passing and **inter-process communication (IPC)**
- Using `MPI_Reduce` to gather results

---

## **6. Load Balancing with Thread Pool**
### **Problem Statement**
Implement a **thread pool** that efficiently processes a queue of computational tasks.

### **Prerequisites & Knowledge**
- Understanding **thread pooling** and its advantages
- Using `std::condition_variable` and `std::mutex` for thread synchronization
- Implementing a **task queue** using `std::queue`

---

## **7. Parallel Sorting with Merge Sort**
### **Problem Statement**
Implement a **parallel merge sort** using `std::thread` to speed up sorting of a large array.

### **Prerequisites & Knowledge**
- Understanding **merge sort algorithm**
- Implementing **divide-and-conquer parallelization**
- Efficient thread spawning and management

---

## **8. Shared Memory Parallel Processing**
### **Problem Statement**
Use **shared memory parallel processing** to sum a large dataset across multiple threads using `std::atomic` to avoid race conditions.

### **Prerequisites & Knowledge**
- Understanding **shared memory model**
- Using **atomic operations** (`std::atomic`) for thread safety
- Using `std::mutex` vs `std::atomic` for performance optimization

---

## **9. Asynchronous Task Execution**
### **Problem Statement**
Write a C++ program that performs **asynchronous tasks** using `std::async`. The program should fetch multiple files concurrently and process them independently.

### **Prerequisites & Knowledge**
- Understanding **asynchronous programming** in C++
- Using `std::async` for launching background tasks
- Handling **future objects (`std::future`)**

---

## **10. Scalable Message Queue System**
### **Problem Statement**
Implement a simple **producer-consumer** model where multiple producer threads generate messages and multiple consumer threads process them using a **thread-safe queue**.

### **Prerequisites & Knowledge**
- Understanding of **message queue systems**
- Implementing **thread synchronization** using `std::mutex` and `std::condition_variable`
- Using `std::queue` for buffered messaging
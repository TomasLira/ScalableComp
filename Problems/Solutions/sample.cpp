#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <mutex>
#include <shared_mutex>
#include <cassert>
#include <chrono>
#include <barrier>
#include <random>
#include <future>

using namespace std;

// Estrutura do nó
template <typename T>
struct Node
{
    T data;
    Node *next = nullptr;
};

// Lista encadeada concorrente com técnicas refinadas de sincronização
template <typename T>
class LinkedList
{
public:
    // shared_mutex permite múltiplos leitores simultâneos e acesso exclusivo para escrita
    mutable std::shared_mutex mtx_;
    int length_;
    Node<T> *head_;
    Node<T> *tail_;

    // Construtor e Destructor
    explicit LinkedList();
    ~LinkedList();

    // Funções utilitárias com leitura compartilhada
    bool is_empty() const;
    int length() const;
    bool check_consistency() const; // Verifica se o length_ bate com a contagem real de nós

    // Operações da lista (escrita com acesso exclusivo)
    void prepend_node(T data);
    void append_node(T data);
    void delete_nodes_by_value(T data);
    void delete_node_by_index(int index);
    void print_list() const;
};

template <typename T>
LinkedList<T>::LinkedList() : head_(nullptr), tail_(nullptr), length_(0) {}

template <typename T>
LinkedList<T>::~LinkedList()
{
    // Adquire lock exclusivo para limpeza
    std::unique_lock<std::shared_mutex> lock(mtx_);
    auto current_node = head_;
    while (current_node)
    {
        auto next_node = current_node->next;
        delete current_node;
        current_node = next_node;
    }
    cout << "List deleted!" << endl;
}

template <typename T>
bool LinkedList<T>::is_empty() const
{
    std::shared_lock<std::shared_mutex> lock(mtx_);
    return head_ == nullptr;
}

template <typename T>
int LinkedList<T>::length() const
{
    std::shared_lock<std::shared_mutex> lock(mtx_);
    return length_;
}

template <typename T>
bool LinkedList<T>::check_consistency() const
{
    std::shared_lock<std::shared_mutex> lock(mtx_);
    int count = 0;
    for (Node<T> *cur = head_; cur != nullptr; cur = cur->next)
        count++;
    return count == length_;
}

template <typename T>
void LinkedList<T>::prepend_node(T data)
{
    std::unique_lock<std::shared_mutex> lock(mtx_);
    auto new_node = new Node<T>{data, head_};
    if (head_ == nullptr)
    { // Lista vazia
        tail_ = new_node;
    }
    head_ = new_node;
    length_++;
}

template <typename T>
void LinkedList<T>::append_node(T data)
{
    std::unique_lock<std::shared_mutex> lock(mtx_);
    auto new_node = new Node<T>{data, nullptr};
    if (head_ == nullptr)
    { // Lista vazia
        head_ = tail_ = new_node;
    }
    else
    {
        tail_->next = new_node;
        tail_ = new_node;
    }
    length_++;
}

template <typename T>
void LinkedList<T>::delete_nodes_by_value(T data)
{
    std::unique_lock<std::shared_mutex> lock(mtx_);
    if (head_ == nullptr)
        return;

    // Remove os nós do início que contenham o valor
    while (head_ && head_->data == data)
    {
        auto del_node = head_;
        head_ = head_->next;
        delete del_node;
        length_--;
    }

    if (!head_)
    {
        tail_ = nullptr;
        return;
    }

    // Remove do restante da lista
    auto current_node = head_;
    while (current_node->next)
    {
        if (current_node->next->data == data)
        {
            auto del_node = current_node->next;
            current_node->next = current_node->next->next;
            if (del_node == tail_)
                tail_ = current_node;
            delete del_node;
            length_--;
        }
        else
        {
            current_node = current_node->next;
        }
    }
}

template <typename T>
void LinkedList<T>::delete_node_by_index(int idx)
{
    std::unique_lock<std::shared_mutex> lock(mtx_);
    if (head_ == nullptr || idx < 0 || idx >= length_)
        return;

    if (idx == 0)
    {
        auto del_node = head_;
        head_ = head_->next;
        delete del_node;
        length_--;
        return;
    }

    auto current_node = head_;
    for (int i = 0; i < idx - 1 && current_node; i++)
    {
        current_node = current_node->next;
    }
    if (current_node && current_node->next)
    {
        auto del_node = current_node->next;
        current_node->next = del_node->next;
        if (del_node == tail_)
            tail_ = current_node;
        delete del_node;
        length_--;
    }
}

template <typename T>
void LinkedList<T>::print_list() const
{
    std::shared_lock<std::shared_mutex> lock(mtx_);
    auto current = head_;
    while (current)
    {
        cout << current->data << " -> ";
        current = current->next;
    }
    cout << "nullptr" << endl;
}

// -----------------------------------------------------------------------------
// Testes utilizando técnicas avançadas de concorrência e paralelismo
// -----------------------------------------------------------------------------

// Teste 1: Vários threads realizando append simultaneamente
// Função que adiciona elementos à lista de maneira concorrente
void append_elements(LinkedList<int> &list, int thread_id, int num_appends)
{
    int start_value = thread_id * num_appends;

    for (int j = 0; j < num_appends; ++j)
    {
        list.append_node(start_value + j);
    }
}

// Teste de inserção concorrente usando múltiplas threads
void test_concurrent_append()
{
    // Inicializa a lista encadeada
    LinkedList<int> list;

    // Configura o número de threads e a quantidade de inserções por thread
    const int num_threads = 10;
    const int num_appends_per_thread = 1000;
    std::vector<std::thread> threads;

    // Cria as threads e inicia as inserções simultâneas
    for (int thread_id = 0; thread_id < num_threads; ++thread_id)
    {
        threads.emplace_back(
            append_elements,       // Função a ser executada
            std::ref(list),        // Passa a lista por referência (para modificar o mesmo objeto)
            thread_id,             // ID único de cada thread
            num_appends_per_thread // Número de inserções por thread
        );
    }

    // Aguarda todas as threads finalizarem
    for (auto &t : threads)
    {
        t.join();
    }

    // Verificação: o tamanho da lista deve ser o esperado
    const int expected_length = num_threads * num_appends_per_thread;
    assert(list.length() == expected_length);
    assert(list.check_consistency());

    std::cout << "Teste de append concorrente passou. Tamanho final: "
              << list.length() << std::endl;
}

// Teste 2: Vários threads realizando prepend simultaneamente
void test_concurrent_prepend()
{
    LinkedList<int> list;
    const int num_threads = 10;
    const int num_prepends_per_thread = 500;
    vector<thread> threads;

    for (int i = 0; i < num_threads; i++)
    {
        threads.emplace_back([&list, i, num_prepends_per_thread]()
                             {
            for (int j = 0; j < num_prepends_per_thread; j++) {
                list.prepend_node(i);
            } });
    }

    for (auto &t : threads)
        t.join();

    assert(list.length() == num_threads * num_prepends_per_thread);
    assert(list.check_consistency());
    cout << "Teste de prepend concorrente passou. Tamanho final: " << list.length() << endl;
}

// Teste 3: Combinação de append e deleção concorrente
void test_concurrent_append_and_delete()
{
    LinkedList<int> list;
    const int num_threads = 10;
    const int num_appends_per_thread = 100;
    vector<thread> threads;

    // Threads adicionando nós com valores de 0 a 9
    for (int i = 0; i < num_threads; i++)
    {
        threads.emplace_back([&list, i, num_appends_per_thread]()
                             {
            for (int j = 0; j < num_appends_per_thread; j++) {
                list.append_node(i);
            } });
    }

    for (auto &t : threads)
        t.join();

    // Threads removendo nós com valor específico
    vector<thread> delete_threads;
    for (int i = 0; i < num_threads; i++)
    {
        delete_threads.emplace_back([&list, i]()
                                    { list.delete_nodes_by_value(i); });
    }

    for (auto &t : delete_threads)
        t.join();

    assert(list.is_empty());
    cout << "Teste de append e delete concorrentes passou. A lista está vazia." << endl;
}

// Teste 4: Leitores e escritores concorrentes
void test_concurrent_readers_and_writers()
{
    LinkedList<int> list;
    const int num_writer_threads = 5;
    const int num_reader_threads = 5;
    const int operations_per_writer = 200;
    vector<thread> writers, readers;

    // Threads escritores que realizam operações de append e prepend
    for (int i = 0; i < num_writer_threads; i++)
    {
        writers.emplace_back([&list, i, operations_per_writer]()
                             {
            for (int j = 0; j < operations_per_writer; j++) {
                if (j % 2 == 0)
                    list.append_node(i * operations_per_writer + j);
                else
                    list.prepend_node(i * operations_per_writer + j);
                // Pequena pausa para simular carga
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            } });
    }

    // Threads leitores que verificam o tamanho e a consistência
    for (int i = 0; i < num_reader_threads; i++)
    {
        readers.emplace_back([&list]()
                             {
            for (int j = 0; j < 300; j++) {
                int len = list.length();
                bool empty = list.is_empty();
                // Apenas lemos a lista (sem imprimir para não poluir a saída)
                assert(list.check_consistency());
                (void)len; (void)empty;
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            } });
    }

    for (auto &w : writers)
        w.join();
    for (auto &r : readers)
        r.join();

    assert(list.check_consistency());
    cout << "Teste de leitores e escritores concorrentes passou. Tamanho final: " << list.length() << endl;
}

// Teste 5: Operações randômicas concorrentes usando std::async
void test_random_operations()
{
    LinkedList<int> list;
    const int num_tasks = 10;
    const int operations_per_task = 1000;
    vector<future<void>> futures;
    std::random_device rd;
    std::mt19937 gen(rd());

    for (int t = 0; t < num_tasks; t++)
    {
        futures.push_back(std::async(std::launch::async, [&list, operations_per_task, t]()
                                     {
            std::mt19937 local_gen(t + std::chrono::steady_clock::now().time_since_epoch().count());
            std::uniform_int_distribution<> op_dist(0, 3);
            for (int i = 0; i < operations_per_task; i++) {
                int op = op_dist(local_gen);
                switch(op) {
                    case 0:
                        list.append_node(i + t * operations_per_task);
                        break;
                    case 1:
                        list.prepend_node(i + t * operations_per_task);
                        break;
                    case 2:
                        list.delete_nodes_by_value(i % 50); // valor arbitrário
                        break;
                    case 3: {
                        int len = list.length();
                        if (len > 0) {
                            std::uniform_int_distribution<> idx_dist(0, len - 1);
                            int idx = idx_dist(local_gen);
                            list.delete_node_by_index(idx);
                        }
                        break;
                    }
                }
                // Pequena pausa para variar o intercalamento das operações
                std::this_thread::sleep_for(std::chrono::microseconds(10));
            } }));
    }

    for (auto &fut : futures)
        fut.get();

    assert(list.check_consistency());
    cout << "Teste de operações randômicas concorrentes passou. Tamanho final: " << list.length() << endl;
}

// Teste 6: Sincronização com std::barrier para início simultâneo
void test_barrier_start()
{
    LinkedList<int> list;
    const int num_threads = 10;
    const int operations_per_thread = 100;
    // Cria uma barreira para sincronizar todas as threads
    std::barrier sync_point(num_threads);
    vector<thread> threads;

    for (int i = 0; i < num_threads; i++)
    {
        threads.emplace_back([&list, i, operations_per_thread, &sync_point]()
                             {
            // Aguarda todas as threads estarem prontas
            sync_point.arrive_and_wait();
            for (int j = 0; j < operations_per_thread; j++) {
                list.append_node(i * operations_per_thread + j);
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            } });
    }

    for (auto &t : threads)
        t.join();

    assert(list.length() == num_threads * operations_per_thread);
    cout << "Teste com barrier passou. Tamanho final: " << list.length() << endl;
}

int main()
{
    cout << "Executando testes concorrentes avançados:" << endl;

    test_concurrent_append();
    test_concurrent_prepend();
    test_concurrent_append_and_delete();
    test_concurrent_readers_and_writers();
    test_random_operations();
    test_barrier_start();

    // Exemplo simples de aplicação concorrente: duas threads adicionam nós com intervalos
    LinkedList<int> list;
    auto thread_func = [&list](int start)
    {
        for (int i = 0; i < 10; i++)
        {
            list.append_node(start + i);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    };

    thread t1(thread_func, 100);
    thread t2(thread_func, 200);
    t1.join();
    t2.join();

    cout << "Lista final após execução concorrente:" << endl;
    list.print_list();

    return 0;
}

// -----------------------------------------------------------------------------
// Segunda implementação
// -----------------------------------------------------------------------------

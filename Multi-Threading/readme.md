# 🧵 Producer-Consumer Queue — C++ Multithreading

A hands-on implementation of the classic **Producer-Consumer problem** using C++ threads, mutex synchronization, and a custom-built array-based queue — no STL containers, no shortcuts.

---

## 📌 What Is This?

The Producer-Consumer problem is one of the most fundamental concurrency problems in systems programming. Two threads share a single resource (a queue):

- **Producer** keeps adding items into the queue
- **Consumer** keeps reading and removing items from the queue
- Without coordination, they'd corrupt each other's data

This project solves that using `std::mutex` to ensure only one thread touches the queue at a time.

---

## 📁 Project Structure

```
├── main.cpp       # Entry point — creates and manages both threads
├── queue.cpp      # Queue logic — enqueue, dequeue, peek, isEmpty
└── Queue.h        # Queue class declaration
```

---

## ⚙️ How It Works

### `main.cpp`
- Creates a shared `Queue` object and a `mutex`
- Spawns **Thread T1** → runs `producer()`
- Spawns **Thread T2** → runs `consumer()`
- Calls `t1.join()` and `t2.join()` to wait for both threads before exiting

### `producer()` — Thread T1
Runs a loop from `i = 1` to `5`:
1. Waits to acquire the mutex lock
2. Calls `q.enqueue(i)` to push the value into the queue
3. Prints the produced value
4. Releases the lock

### `consumer()` — Thread T2
Runs a loop from `i = 1` to `5`:
1. Waits to acquire the mutex lock
2. Checks if the queue is empty via `q.isEmpty()`
3. If not empty → reads with `q.peek()`, prints it, then removes with `q.dequeue()`
4. If empty → skips the iteration
5. Releases the lock

### `Queue` (Array-Based)
| Method | Description |
|---|---|
| `enqueue(int val)` | Adds value at the rear |
| `dequeue()` | Removes value from the front (`front++`) |
| `peek()` | Returns front value without removing |
| `isEmpty()` | Returns `true` if `front == -1` or `front > rear` |

> Queue capacity is fixed at **100 elements** (`arr[100]`).

---

## 🔒 Thread Safety

Every read/write to the shared queue is wrapped inside a critical section:

```cpp
m.lock();
// --- critical section ---
q.enqueue(i);
// ------------------------
m.unlock();
```

This ensures **mutual exclusion** — only one thread can access the queue at any given moment, preventing race conditions and data corruption.

---

## 🖥️ Sample Output

```
======================================
   Producer-Consumer MultiThreading
======================================

[MAIN] Launching T1 (Producer) and T2 (Consumer)...

[T1 - Producer] Thread started

[T1 - Producer] Waiting to acquire lock...
[T1 - Producer] Lock acquired >> Running
[T1 - Producer] Produced : 1  |  Queue size in progress...
[T1 - Producer] Lock released

[T2 - Consumer] Waiting to acquire lock...
[T2 - Consumer] Lock acquired >> Running
[T2 - Consumer] Consumed : 1  |  Removing from queue...
[T2 - Consumer] Lock released

...

[MAIN] Both threads completed.
[MAIN] Program exiting cleanly. Exit code: 0
======================================
```

---

## 🚀 How to Compile & Run

### Requirements
- GCC / G++ compiler
- C++11 or later
- POSIX thread support (`-lpthread`)

### Steps

```bash
# Clone or download the project files
# Then compile:
g++ main.cpp queue.cpp -o output -lpthread

# Run:
./output
```

> On Windows with MinGW, use `-lmingw32 -lwinpthread` instead of `-lpthread`

---

## 🧠 Key Concepts

| Concept | Used As |
|---|---|
| `std::thread` | Spawning T1 (producer) and T2 (consumer) |
| `std::mutex` | Protecting the shared queue from concurrent access |
| `mutex.lock()` | Entering the critical section |
| `mutex.unlock()` | Exiting the critical section |
| `thread.join()` | Making main() wait for both threads to finish |
| Critical Section | The block of code accessing the shared queue |
| Race Condition | What happens WITHOUT the mutex (bad) |

---

## ⚠️ Known Limitations

- **Fixed queue size** — array is capped at 100 elements
- **Busy-wait behavior** — consumer loops even when queue is empty instead of waiting
- **No condition variable** — threads don't signal each other; consumer may miss items if it runs before producer
- **No circular buffer** — front pointer only moves forward; old slots aren't reused

---

## 🔭 What's Next / Improvements

- [ ] Replace `mutex.lock()` / `unlock()` with `std::lock_guard` for exception-safe locking
- [ ] Add `std::condition_variable` so consumer waits and producer notifies — eliminates busy-waiting
- [ ] Use a **circular buffer** or `std::queue` for dynamic sizing
- [ ] Add timestamps to thread logs for execution tracing
- [ ] Test with more than 5 items to observe real interleaving behavior

---

## 📚 Concepts to Explore Next

- `std::condition_variable` — producer/consumer signaling
- `std::lock_guard` and `std::unique_lock` — RAII-based locking
- `std::atomic` — lightweight synchronization for simple counters
- **Semaphores** (`std::counting_semaphore` in C++20)
- **Deadlock** — what happens when two threads each wait for each other's lock forever

---

## 👤 Author

**Viraj Jamdhade**

Built as part of learning **Systems Programming & Concurrency in C++**.

---

> *"Concurrency is not parallelism — but a mutex is always a good idea."*

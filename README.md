# 🍕 Food Delivery System

A **C++ console application** that models a food delivery network using **Graph Theory** and **Dijkstra's Algorithm** to find the shortest delivery path from a restaurant to a customer's location, respecting delivery time constraints. Built from scratch using custom data structures.

---

## 📌 Overview

The system reads delivery scenarios from a file, builds a city/location graph, and computes the optimal delivery route for each order. It simulates a real-world food delivery platform where:
- Cities/locations are **graph vertices**
- Roads between them are **edges**
- Each node has a **maximum allowed delivery time**
- Dijkstra's algorithm finds the **shortest valid path**

---

## 🧠 Core Concepts & Data Structures

| Component | Implementation |
|---|---|
| Graph | Adjacency List using custom linked-list nodes |
| Shortest Path | Dijkstra's Algorithm with delivery time constraints |
| Queue | Custom linked-list based Queue with push/pop/peek |
| Orders | `Order` struct — name, delivery location, time limit |
| Restaurants | `Restaurant` struct — name, location, array of orders |
| Input | Read from `test.txt` file (multi test case support) |

---

## 🗂️ Input Format (`test.txt`)

```
<number_of_test_cases>
<N> <num_riders> <num_restaurants>
<from> <to> <weight>   ← repeated for N-1 edges
<restaurant_name> <location> <num_orders>
<order_name> <order_location> <delivery_time>  ← repeated per order
<delivery_time_per_node>  ← repeated for N nodes
```

---

## ⚙️ How It Works

1. Reads number of test cases from `test.txt`
2. For each test case:
   - Builds a graph of `N` nodes with directed edges
   - Loads restaurant details and their orders (name, location, deadline)
   - Reads per-node delivery time limits
   - Runs **Dijkstra's algorithm** from node `0` to node `N-1`
   - Only relaxes edges where the path respects the delivery time constraint
   - Outputs shortest path length, or `"No path exists"` if unreachable

---

## 📏 Algorithm Detail

The modified Dijkstra only updates a neighbor's distance if:
```
dist[u] + 1 <= deliveryTimes[neighbor]
```
This ensures the path is not only the shortest but also **within each stop's delivery window**.

---

## 🛠️ Tech Stack

- **Language:** C++
- **Data Structures:** Custom linked-list, adjacency list graph, queue
- **Algorithm:** Dijkstra's Shortest Path
- **I/O:** File-based input (`fstream`)

---

## 🚀 Getting Started

### Compile

```bash
g++ delieverysystemdsa.cpp -o food_delivery
```

### Prepare Input

Create a `test.txt` file in the same directory following the input format above.

### Run

```bash
./food_delivery
```

---

## 📂 Project Structure

```
Food-Delivery-system-/
├── delieverysystemdsa.cpp   # Full source code
├── test.txt                 # Input file (create before running)
└── README.md
```

---

## 💡 Sample Output

```
Test Case 1:
Riders: 2
Restaurants: 1
Restaurant 1: BurgerHub
Location: 3
Number of Orders: 2
Order 1: Classic_Burger
Location: 7
Delivery Time: 5
...
Shortest Path Length: 4
```

---

## 👤 Author

**Sohaib Shahzad (sohaib0075)**  
[GitHub Profile](https://github.com/sohaib0075)

---

## 📄 License

This project is open source and available under the [MIT License](LICENSE).

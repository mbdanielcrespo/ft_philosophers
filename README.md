# 🍽️ Philosophers

![42 Badge](https://img.shields.io/badge/42-Philosophers-brightgreen)
![Score](https://img.shields.io/badge/Score-100%2F100-success)
![Language](https://img.shields.io/badge/Language-C-blue)
![Concurrency](https://img.shields.io/badge/Concurrency-pthreads-orange)
![Status](https://img.shields.io/badge/Status-Completed-success)

<p align="center">
  <img src="https://raw.githubusercontent.com/byaliego/42-project-badges/main/badges/philosopherse.png" alt="Philosophers Badge" width="150" height="150">
</p>

## 📝 Introduction

**Philosophers** is a 42 School project that tackles the classic Dining Philosophers problem, introducing students to the challenges of concurrent programming, thread synchronization, and the prevention of race conditions and deadlocks.

> "I never thought philosophy would be so deadly."

This project simulates philosophers sitting at a round table, alternating between eating, thinking, and sleeping, while sharing limited resources (forks) and avoiding starvation.

## 🎯 Project Objectives

- Implement a solution to the Dining Philosophers problem
- Learn about threads, mutexes, and concurrent programming
- Prevent deadlocks and race conditions
- Ensure no philosopher starves to death
- Practice resource sharing and synchronization
- Implement accurate timing and state management

## 🧩 Project Structure

```
philo/
├── inc/
│   └── philo.h    # Header with structures and function prototypes
├── src/
│   ├── cleanup.c         # Resource cleanup and error handling
│   ├── dinner.c          # Core philosopher routines
│   ├── forks.c           # Fork management 
│   ├── init.c            # Initialization functions
│   ├── main.c            # Program entry point
│   ├── parse.c           # Command-line argument parsing
│   ├── time.c            # Time-related utilities
│   └── utils.c           # Helper functions
└── Makefile             # Compilation instructions
```

## 🛠️ Implementation Details

### **cleanup.c**
Resource management and error handling:

| Function | Description |
|----------|-------------|
| **cleanup** | Frees allocated resources and destroys mutexes properly |
| **exit_error** | Displays an error message and exits the program gracefully |

### **dinner.c**
Core philosopher routines:

| Function | Description |
|----------|-------------|
| **dinner** | Main routine for each philosopher thread (eat, sleep, think cycle) |
| **eat** | Handles the eating action, updates timestamps, and tracks meals |
| **sleep_and_think** | Manages the sleeping and thinking phases |

### **forks.c**
Fork management and synchronization:

| Function | Description |
|----------|-------------|
| **take_forks** | Implements the logic for acquiring forks with deadlock prevention |
| **drop_forks** | Handles the release of forks after eating |

### **init.c**
Setup and initialization:

| Function | Description |
|----------|-------------|
| **init_mutexes** | Initializes mutexes for forks and other shared resources |
| **init_philosophers** | Sets up philosopher structures with their attributes |
| **init_data** | Initializes the main data structure with simulation parameters |

### **main.c**
Program entry point:

| Function | Description |
|----------|-------------|
| **main** | Parses arguments, initializes data, creates threads, and manages cleanup |

### **parse.c**
Argument validation and parsing:

| Function | Description |
|----------|-------------|
| **parse_args** | Validates and converts command-line arguments to program parameters |
| **ft_atoi** | Converts string to integer with error handling |

### **time.c**
Time-related utilities:

| Function | Description |
|----------|-------------|
| **get_time** | Retrieves current timestamp in milliseconds |
| **precise_sleep** | Implements an accurate sleep function without CPU-intensive busy waiting |

### **utils.c**
Helper functions:

| Function | Description |
|----------|-------------|
| **print_status** | Prints philosopher status with timestamp (eating, sleeping, thinking) |
| **safe_mutex_lock** | Wraps pthread_mutex_lock with error checking |
| **safe_mutex_unlock** | Wraps pthread_mutex_unlock with error checking |

## 🧮 The Problem

The Dining Philosophers problem illustrates challenges in resource allocation:

- N philosophers sit at a round table
- There is one fork between each philosopher (N forks total)
- A philosopher needs two forks to eat (their own and their neighbor's)
- Philosophers alternate between eating, sleeping, and thinking
- If a philosopher doesn't eat for too long, they die of starvation
- The simulation stops when a philosopher dies or when all philosophers have eaten enough

## 🎮 Program Arguments

The program accepts the following arguments:

```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

| Argument | Description |
|----------|-------------|
| **number_of_philosophers** | Number of philosophers and forks |
| **time_to_die** | Time in milliseconds until a philosopher dies if they haven't started eating |
| **time_to_eat** | Time in milliseconds that a philosopher takes to eat |
| **time_to_sleep** | Time in milliseconds that a philosopher spends sleeping |
| **number_of_times_each_philosopher_must_eat** | Optional: simulation stops when all philosophers eat this many times |

## 💡 Key Features

- **Deadlock Prevention**: Philosophers pick up forks in a specific order to prevent deadlocks
- **Race Condition Handling**: All shared resources are protected by mutexes
- **Death Detection**: A separate monitoring system checks if any philosopher is starving
- **Accurate Timing**: Precise time measurement and sleeping implementation
- **Resource Efficiency**: Minimized CPU usage while maintaining accuracy
- **Thread Safety**: Safe communication between threads

## 🧠 Skills Developed

- Concurrent programming with threads
- Synchronization mechanisms (mutexes)
- Deadlock prevention strategies
- Race condition handling
- Resource allocation algorithms
- Efficient time management in multi-threaded environments
- System programming in C

---

<div align="center">
  
  ### 📊 Project Stats
  
  | Metric | Value |
  |--------|-------|
  | Final Score | 100/100 |
  | Files | 8 |
  | Thread Safety | Protected by mutexes |
  | Deadlock Solution | Resource hierarchy |
  
</div>

<p align="center">
  <img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="C">
  <img src="https://img.shields.io/badge/Threads-Concurrency-ff69b4?style=for-the-badge" alt="Threads">
  <img src="https://img.shields.io/badge/42-000000?style=for-the-badge&logo=42&logoColor=white" alt="42">
</p>

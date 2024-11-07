# System Resource Manager

A C++ application that monitors system resource usage (CPU, Memory, Disk, and GPU) and issues warnings when any resource usage exceeds a predefined threshold.

## Features

- Monitors **CPU**, **Memory**, **Disk**, and **GPU** usage.
- Multithreaded approach to monitor resources simultaneously.
- Issues warnings if resource usage exceeds predefined thresholds (e.g., **CPU > 80%**, **Memory > 80%**, **Disk > 90%**, **GPU > 80%**).
- Runs indefinitely and checks system usage every 5 seconds.

## Prerequisites

- A **Linux-based** operating system (e.g., Ubuntu, Fedora).
- A **C++ compiler** (e.g., **g++**).
- **NVIDIA GPU** is assumed for GPU usage. Modify the GPUManager class to support your system if necessary.

## Installation

### Steps to Install

1. **Clone the repository**:
    ```bash
    git clone https://github.com/yourusername/SystemResourceManager.git
    ```

2. **Navigate to the project directory**:
    ```bash
    cd SystemResourceManager
    ```

3. **Compile the C++ code**:
    ```bash
    g++ "System Resource Manager.cpp" -o system_resource_manager -std=c++11 -pthread
    ```

4. **Run the program**:
    ```bash
    ./system_resource_manager
    ```

## Expected Output

When you run the program, it will display the current **CPU**, **Memory**, **Disk**, and **GPU** usage, checking the usage every 5 seconds. If any usage exceeds the predefined threshold, it will print a warning message like:

## Resource Usage Thresholds

- **CPU Usage**: Warning if usage exceeds **80%**.
- **Memory Usage**: Warning if usage exceeds **80%**.
- **Disk Usage**: Warning if usage exceeds **90%**.
- **GPU Usage**: Warning if usage exceeds **80%**.

## Code Overview

1. **CPUManager**: Monitors CPU usage by reading data from `/proc/stat` in Linux.
2. **MemoryManager**: Monitors memory usage using the `sysinfo()` function.
3. **DiskManager**: Monitors disk usage of the root directory (`/`).
4. **GPUManager**: Currently returns a static value (55%) as a placeholder. You can modify it to fetch actual GPU data, possibly using libraries such as [NVIDIA's nvidia-smi](https://developer.nvidia.com/nvidia-system-management-interface) for better integration.
5. **SystemResourceManager**: The main class that manages the monitoring of all resources (CPU, Memory, Disk, and GPU) using multithreading.
6. **Multithreading**: Utilizes C++11 threads to monitor CPU, memory, disk, and GPU usage simultaneously.


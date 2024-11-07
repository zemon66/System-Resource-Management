#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <vector>
#include <unistd.h>
#include <chrono>  
#include <sys/sysinfo.h>
#include <sys/statvfs.h>
#include <sstream>
using namespace std;
class CPUManager {
public:
    double getCPUUsage() {
        ifstream file("/proc/stat");
        string line;
        getline(file, line);

        long user, nice, system, idle, iowait, irq, softirq;
        istringstream ss(line);
        ss.ignore(5);
        ss >> user >> nice >> system >> idle >> iowait >> irq >> softirq;

        long totalIdle = idle + iowait;
        long nonIdle = user + nice + system + irq + softirq;
        long total = totalIdle + nonIdle;

        return 100.0 * (1.0 - (double)totalIdle / total);
    }
};


class MemoryManager {
public:
    double getMemoryUsage() {
        struct sysinfo memInfo;
        sysinfo(&memInfo);
        long long totalMemory = memInfo.totalram * memInfo.mem_unit;
        long long freeMemory = memInfo.freeram * memInfo.mem_unit;

        return ((totalMemory - freeMemory) / (double)totalMemory) * 100;
    }
};


class DiskManager {
public:
    double getDiskUsage(const char* path) {
        struct statvfs diskInfo;
        statvfs(path, &diskInfo);
        long long totalSpace = diskInfo.f_blocks * diskInfo.f_frsize;
        long long freeSpace = diskInfo.f_bavail * diskInfo.f_frsize;

        return ((totalSpace - freeSpace) / (double)totalSpace) * 100;
    }
};



class GPUManager {
public:
    double getGPUUsage() {
        return 55.0; 
    }
};



class SystemResourceManager {
    CPUManager cpu;
    MemoryManager memory;
    DiskManager disk;
    GPUManager gpu;

    mutex mtx;
    double cpuUsage = 0.0;
    double memoryUsage = 0.0;
    double diskUsage = 0.0;
    double gpuUsage = 0.0;

    double cpuThreshold = 80.0;
    double memoryThreshold = 80.0;
    double diskThreshold = 90.0;
    double gpuThreshold = 80.0;

public:
    void monitorCPU() {
        lock_guard<mutex> lock(mtx);
        cpuUsage = cpu.getCPUUsage();
        if (cpuUsage > cpuThreshold) {
            cerr << "Warning: High CPU Usage! (" << cpuUsage << "%)\n";
        }
    }

    void monitorMemory() {
        lock_guard<mutex> lock(mtx);
        memoryUsage = memory.getMemoryUsage();
        if (memoryUsage > memoryThreshold) {
            cerr << "Warning: High Memory Usage! (" << memoryUsage << "%)\n";
        }
    }

    void monitorDisk() {
        lock_guard<mutex> lock(mtx);
        diskUsage = disk.getDiskUsage("/");
        if (diskUsage > diskThreshold) {
            cerr << "Warning: High Disk Usage! (" << diskUsage << "%)\n";
        }
    }

    void monitorGPU() {
        lock_guard<mutex> lock(mtx);
        gpuUsage = gpu.getGPUUsage();
        if (gpuUsage > gpuThreshold) {
            cerr << "Warning: High GPU Usage! (" << gpuUsage << "%)\n";
        }
    }

    void checkThresholds() {
        vector<thread> threads;

        threads.push_back(thread(&SystemResourceManager::monitorCPU, this));
        threads.push_back(thread(&SystemResourceManager::monitorMemory, this));
        threads.push_back(thread(&SystemResourceManager::monitorDisk, this));
        threads.push_back(thread(&SystemResourceManager::monitorGPU, this));

        for (auto& thread : threads) {
            thread.join();
        }

        cout << "Resource usage monitored. CPU: " << cpuUsage 
             << "%, Memory: " << memoryUsage << "%, Disk: " << diskUsage 
             << "%, GPU: " << gpuUsage << "%\n";
    }
};

int main() {
    SystemResourceManager manager;

    chrono::seconds interval(5);

    while (true) {
        manager.checkThresholds();

        this_thread::sleep_for(interval);
    }

    return 0;
}

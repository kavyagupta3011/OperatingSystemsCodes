# OperatingSystemsCodes
This repository contains the C programs and shell scripts developed as part of the **EGC 301P Operating Systems Lab** coursework. The exercises are designed to provide hands-on experience with core OS concepts such as:

- 📁 **File Management** (System calls, file descriptors, locks, etc.)
- 👨‍👩‍👧‍👦 **Process Management** (fork, exec, zombie/orphan processes, scheduling)
- 🔁 **System V IPC** (Pipes, FIFOs, message queues, shared memory, semaphores)
- ⏲️ **Timers, Signals, Resource Limits & Multithreading** (signal handling, resource control, threading)

Each exercise is labeled and corresponds to lab tasks specified in the lab exercises document. These programs explore low-level system operations using POSIX-compliant APIs and demonstrate practical applications of operating system internals.

> All code is written in **C** and is intended for **Linux-based environments**.

### 🔧 How to Compile and Run

Each program can be compiled using `gcc`:
```
gcc program_name.c -o program_name
./program_name
```

All necessary files, FIFOs, shared memory segments, and message queues are created within the programs themselves — no manual setup is required. In Reader-Writer based programs (such as those using FIFO, shared memory, or message queues), **run the Writer first**, as it is responsible for creating the necessary files or resources. The Reader is designed to access those resources **after** they are set up by the Writer. This execution order is intentional and required for correct functioning.

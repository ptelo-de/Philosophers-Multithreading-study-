# Philosophers-Multithreading-study-
Introduction to threads 

Threads: Independent execution units within the same process that share memory.

Running multiple threads in parallel improves efficiency and responsiveness because it allows tasks to be executed concurrently rather than sequentially. 

HOW CAN TWO TASKS RUN AT THE SAME TIME?

A) They can run in separate CPU cores  (best performance)

B) They can run in the same CPU core if this core supports Hyper-threading. Some parts of both threads run at the same time, but the boost is not as big as option A.

C) They can run in the same CPU core with Standard Context Switching, where the tasks do not happen simultaneously but the CPU rapidly switches between them. This approach requires saving registers of the contexts which adds some overhead.

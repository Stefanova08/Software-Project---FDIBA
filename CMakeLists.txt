cmake_minimum_required(VERSION 3.26)
project(rr_scheduler C)

set(CMAKE_C_STANDARD 11)

add_executable(rr_scheduler
        main.c
        scheduler.c
        queue.c)
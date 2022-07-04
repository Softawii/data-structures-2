cmake_minimum_required(VERSION 3.22)
project(ReplacementSelection C)

set(CMAKE_C_STANDARD 23)

add_executable(ReplacementSelection main.c src/replacement_selection.h test/cliente.h src/intercalation.h src/core.h libs/queue/queue.h libs/queue/queue.c libs/pqueue/pqueue.h libs/pqueue/pqueue.c src/utils.h)

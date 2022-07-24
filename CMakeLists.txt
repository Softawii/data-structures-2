cmake_minimum_required(VERSION 3.10)
project(ReplacementSelection C)


install(DIRECTORY DESTINATION ./build)
add_executable(ReplacementSelection main.c include/core/replacement_selection.h include/client/cliente.h include/core/intercalation.h include/core/core.h libs/queue/queue.h libs/queue/queue.c libs/priority_queue/pqueue.h libs/priority_queue/pqueue.c include/utils/utils.h src/client/cliente.c src/utils/utils.c src/core/intercalation.c src/core/replacement_selection.c)

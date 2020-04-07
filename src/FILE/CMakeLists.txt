cmake_minimum_required(VERSION 3.10)
project(FILE C)

set(CMAKE_C_STANDARD 99)
include_directories(/opt/arm/gdbm/include)
link_directories(/opt/arm/gdbm/lib)


add_executable(FILE lowlevel.c std.c main.c opt.c env.c tim.c slog.c limit.c terminal.c termios.c curses.c memory.c lock.c dbm.c program.c signal.c thread.c thread_sem.c thread_mutex.c pipe.c)

target_link_libraries(${PROJECT_NAME} m)
target_link_libraries(${PROJECT_NAME} pthread)
target_link_libraries(${PROJECT_NAME} gdbm)
target_link_libraries(${PROJECT_NAME} gdbm_compat)




project(main_task)

add_subdirectory(user)

add_executable(${PROJECT_NAME} main_task.cpp)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${User_Dir}
)

# target_link_libraries(${PROJECT_NAME}
# PUBLIC
# user
# )

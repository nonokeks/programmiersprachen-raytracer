add_executable(example example.cpp)

target_link_libraries(example ${FRAMEWORK_NAME} ${LIBRARIES})
add_dependencies(example glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS example DESTINATION .)

add_executable(raytracer raytracer.cpp)

target_link_libraries(raytracer ${FRAMEWORK_NAME} ${LIBRARIES})
add_dependencies(raytracer glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS raytracer DESTINATION .)

add_executable(render render.cpp)

target_link_libraries(render ${FRAMEWORK_NAME} ${LIBRARIES})
add_dependencies(render glfw ${FRAMEWORK_NAME} ${COPY_BINARY})

install(TARGETS render DESTINATION .)
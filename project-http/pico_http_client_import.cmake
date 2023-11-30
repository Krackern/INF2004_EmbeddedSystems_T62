add_library(pico_http_client INTERFACE)

target_sources(pico_http_client INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/src/pico_http_client.c
        ${CMAKE_CURRENT_LIST_DIR}/src/socket.c
        ${CMAKE_CURRENT_LIST_DIR}/src/lwip/socket_impl.c)

target_link_libraries(pico_http_client INTERFACE
        pico_cyw43_arch_lwip_threadsafe_background)

target_include_directories(pico_http_client INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_executable(net_serv net_server.cpp)
target_link_libraries(net_serv headers asio::asio)

#Обновление 10.06 - 1:42
install(TARGETS net_serv DESTINATION .)
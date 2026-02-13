#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <time.h>
#include <poll.h>
#include <pthread.h>
#include <vector>
#include <thread>
#include <memory>
#include <atomic>

using namespace std;

struct TimeServer {
    atomic<bool>& running;
    int client = 0;

    TimeServer(atomic<bool>& run) : running(run) {}

    void run() {
        pollfd active;
        memset(&active, 0, sizeof(pollfd));
        active.fd = client;
        active.events = POLLIN;

        while (running) {
            if (poll(&active, 1, 5000) > 0 && (active.revents & POLLIN)) {
                int the_int = 0;
                if (read(active.fd, &the_int, 4) == 0) {
                    printf("Client disconnected\n");
                    break;
                }
            } else {
                time_t the_time;
                time(&the_time);
                the_time = htonl(the_time);
                write(active.fd, &the_time, sizeof(the_time));
            }
        }
        close(active.fd);
    }
};

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Too few arguments -- provide a port number\n");
        return 0;
    }
    addrinfo hints, *result;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    getaddrinfo(NULL, argv[1], &hints, &result);

    int fd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (fd == -1) {
        printf("Socket creation failed\n");
        exit(0);
    }

    if (bind(fd, result->ai_addr, result->ai_addrlen) == -1) {
        printf("Bind error\n");
        exit(0);
    }

    if (listen(fd, 50) == -1) {
        printf("Listen error\n");
        exit(0);
    }

    vector<thread> threads;
    vector<unique_ptr<TimeServer>> servers;
    atomic<bool> running(true);

    while (running) {
        sockaddr address;
        socklen_t size = sizeof(address);
        int client_fd = accept(fd, &address, &size);
        if (client_fd == -1) {
            continue; //handle errors
        }

        char host[NI_MAXHOST], service[NI_MAXSERV];
        if (getnameinfo(&address, size, host, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICSERV | NI_NOFQDN) == 0) {
            printf("Client connected: %s:%s\n", host, service);
        }

        auto srv = make_unique<TimeServer>(running);
        srv->client = client_fd;
        threads.emplace_back(&TimeServer::run, srv.get());
        servers.push_back(move(srv));

        //clean up finished threads
        for (size_t i = 0; i < threads.size(); ) {
            if (!threads[i].joinable()) {
                threads.erase(threads.begin() + i);
            } else {
                i++;
            }
        }
    }

    //signal to stop and join all threads before exiting
    running = false;
    for (auto& th : threads) {
        if (th.joinable()) {
            th.join();
        }
    }

    freeaddrinfo(result);
    close(fd);

    return 0;
}

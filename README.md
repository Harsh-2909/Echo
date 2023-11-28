# Echo
A full fledged light weight web server written in C

This document provides a brief overview of the web server, how to compile and run it, and potential improvements for future versions.

> **Note**: This project is still under development. It is missing a lot of features and is not ready for production use.

## Overview
I made this project to learn more about how web servers work. It is not intended for real-world use.

The web server is a multi-threaded non-blocking web server written in C. It uses the TCP/IP protocol for communication and listens on port 80. The server can handle a maximum of 5 queued connections before it starts dropping new incoming connections.

## Compilation
To compile the server, you need a C compiler such as gcc. Use the following command to compile the server:

```bash
gcc ./src/server.c -o server -lpthread
```
This will create an executable named server.

## Running the Server
To run the server, use the following command:

```bash
./server
```

The server will start and listen for incoming connections on port 80.

## Future Improvements
- Improved Multithreading: The current server is multi-threaded, but it is not very efficient. The server could be improved to use a thread pool to handle incoming connections which will reduce the overhead of creating and destroying threads.

- Logging: The server currently does not have any logging mechanism. Adding logging would help track and debug issues.

- Configuration: The server's settings (like the port number and the maximum number of connections) are currently hardcoded. These could be made configurable through a configuration file or command-line arguments.

- Security: Implementing SSL/TLS to secure the communication between the client and the server.

- HTTP Parsing: The server could be improved to handle HTTP requests and responses, turning it into a fully-fledged HTTP server.
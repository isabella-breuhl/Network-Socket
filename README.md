# Network-Socket
Program that takes a hostname and port as command-line arguments, connects using TCP/IPv4 to the given port on the given hostname, reads data from the remote service until the server closes the connection, and prints the read data to standard out.

# How to use
Compile and build both 'c' and 'go' files

Run 'go' file in conjunction with netcat using **nc -l -p 1025 -c ./service-network** 

Netcat will now listen on port 1025, and it will hand connections it receives to service-network

Connect via a hostname and port (i.e. **./network 127.0.0.1 1025**)

The secret message will print on connection

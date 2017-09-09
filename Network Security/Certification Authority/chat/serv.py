import sys
import socket
import select

HOST = "10.194.42.95"
PORT = 1998
SOCKET_LIST = []
RECV_BUFFER = 4096 
#PORT = 9009

count = 0
def chat_server():
    global cpunt
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server_socket.bind((HOST, PORT))
    server_socket.listen(2)
 
    # add server socket object to the list of readable connections
    SOCKET_LIST.append(server_socket)
 
    print "Chat server started on port " + str(PORT)
 
    while 1:

        # get the list sockets which are ready to be read through select
        # 4th arg, time_out  = 0 : poll and never block
        ready_to_read,ready_to_write,in_error = select.select(SOCKET_LIST,[],[],0)
      
        for sock in ready_to_read:
            # a new connection request recieved
            if sock == server_socket: 
                sockfd, addr = server_socket.accept()
                SOCKET_LIST.append(sockfd)
                print "Client (%s, %s) connected" % addr
                 
                #broadcast(server_socket, sockfd, "[%s:%s] entered our chatting room\n" % addr)
             
            # a message from a client, not a new connection
            else:
                # process data recieved from client, 
                try:
                    # receiving data from the socket.
                    data = sock.recv(RECV_BUFFER)
                    if data[:4] == "CERT":
                        count = count + 1
                        RECV_CERT = "RECV"+count+".cert"
                        with open(RECV_CERT, 'wb') as f:
                            print 'file opened'
                            print('receiving data...')
                            data = data[4:]
                            #print('data=%s', (data))
                            if data[-3:]=='END':
                                data = data[:-3]
                                f.write(data)
                            else:
                                while True:
                                    print('receiving data...')
                                    data = sock.recv(1024)
                                    #print('data=%s', (data))
                                    if data[-3:]=='END':
                                        data = data[:-3]
                                        f.write(data)
                                        break
                                    # write data to a file
                                    f.write(data)
                        f.close()
                        handle_file(server_socket, sock)
                    elif data:
                        # there is something in the socket
                        broadcast(server_socket, sock,data)  
                    else:
                        # remove the socket that's broken    
                        if sock in SOCKET_LIST:
                            SOCKET_LIST.remove(sock)

                        # at this stage, no data means probably the connection has been broken
                        #broadcast(server_socket, sock, "Client (%s, %s) is offline\n" % addr) 

                # exception 
                except:
                    #broadcast(server_socket, sock, "Client (%s, %s) is offline\n" % addr)
                    continue

    server_socket.close()
    
# broadcast chat messages to all connected clients
def handle_file(server_socket, sock, message):
    for socket in SOCKET_LIST:
        # send the message only to peer
        if socket != server_socket and socket != sock :
            try :

                filename = RECV_CERT
                f = open(filename,'rb')
                l = f.read(1024)
                while (l):
                   socket.send(l)
                   #print('Sent ',repr(l))
                   l = f.read(1024)
                f.close()
                socket.send("END")
            except :
                # broken socket connection
                socket.close()
                # broken socket, remove it
                if socket in SOCKET_LIST:
                    SOCKET_LIST.remove(socket)

def broadcast (server_socket, sock, message):
    for socket in SOCKET_LIST:
        # send the message only to peer
        if socket != server_socket and socket != sock :
            try :
                print message
                socket.send(message)
            except :
                # broken socket connection
                socket.close()
                # broken socket, remove it
                if socket in SOCKET_LIST:
                    SOCKET_LIST.remove(socket)
 
if __name__ == "__main__":

    sys.exit(chat_server())         

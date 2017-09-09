
import sys
import socket
import select
from OpenSSL import crypto, SSL
from socket import gethostname
from pprint import pprint
from time import gmtime, mktime
from Crypto.Cipher import PKCS1_OAEP
from Crypto.PublicKey import RSA
import os
import pdb

CSR_FILE = ''
CERT_FILE = ''
KEY_FILE = ''

RECV_CERT = ''
CA_CERT = ''
verify_cmd = ''

def create_self_signed_cert(username):
    global CSR_FILE
    global KEY_FILE
    k1 = crypto.PKey()
    k1.generate_key(crypto.TYPE_RSA, 1024)
    cert1 = crypto.X509Req()
    cert1.get_subject().C = "IN"
    cert1.get_subject().ST = "Delhi"
    cert1.get_subject().L = "Delhi"
    cert1.get_subject().O = "IITD"
    cert1.get_subject().OU = "Comp Sci"
    cert1.get_subject().CN = username
    cert1.set_pubkey(k1)
    cert1.sign(k1, 'sha1')
    CSR_FILE = username+".cert.csr"
    KEY_FILE = username+".key"
    open(CSR_FILE, "wt").write(
        crypto.dump_certificate_request(crypto.FILETYPE_PEM, cert1))
    open(KEY_FILE, "wt").write(
        crypto.dump_privatekey(crypto.FILETYPE_PEM, k1))

 
def chat_client():
    #if(len(sys.argv) < 3) :
        #print 'Usage : python chat_client.py hostname port'
        #sys.exit()
    global CSR_FILE
    global CERT_FILE
    global KEY_FILE

    global RECV_CERT
    global CA_CERT
    global verify_cmd
    host = "127.0.0.1"
    port = 1998
     
    cahost = "127.0.0.1"
    caport = 2020

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    #s.settimeout(2)
    
    sca = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    #sca.settimeout(2)


     
    # connect to remote host
    try :
        username = raw_input("Enter username:")
        create_self_signed_cert(username)

        sca.connect((cahost, caport))
    except :
        print 'Unable to connect'
        sys.exit()
    print 'Connected to CA, receiving CA cert'

    CA_CERT = "CA.cert"

    with open(CA_CERT, 'wb') as f:
        print 'file opened'
        while True:
            print('receiving data...ca cert')
            data = sca.recv(1024)
            #print('data=%s', (data))
            if data[-3:]=='END':
                data = data[:-3]
                f.write(data)
                break
            # write data to a file
            f.write(data)

    f.close()
    print('Successfully get the CA cert file')

    os.system('openssl x509 -inform pem -in CA.cert -pubkey -noout > capublickey.pem')
    #KEY_FILE = "shruti.pem"
    
    capubkey = RSA.importKey(open('capublickey.pem').read())
    cacipher = PKCS1_OAEP.new(capubkey)
    

    filename = CSR_FILE
    f = open(filename,'rb')
    l = f.read(10)
        
    while (l):
        l = cacipher.encrypt(l)
        sca.send(l)
        #print('Sent ',repr(l))
        l = f.read(10)
        #l = cacipher.encrypt(l)
    f.close()
    #sca.send("END")
    sca.send(cacipher.encrypt("END"))
    print('Done sending CSR')

    key = RSA.importKey(open(KEY_FILE).read())
    plain = PKCS1_OAEP.new(key)

    
    CERT_FILE = username+".cert"

    with open(CERT_FILE, 'wb') as f:
        print 'file opened'
        print('receiving data...cert')
        while True:
            #print('receiving data...cert')
            data = sca.recv(128)
            data = plain.decrypt(data)
            #print('data=%s', (data))
            if data[-3:]=='END':
                data = data[:-3]
                f.write(data)
                break
            # write data to a file
            f.write(data)

    f.close()
    print('Successfully get the cert file')
    verify_cmd = "openssl verify -CAfile CA.cert "+CERT_FILE
    print verify_cmd
    os.system(verify_cmd)

    
    try :
        s.connect((host, port))
    except :
        print 'Unable to connect'
        sys.exit()
    
    print 'Connected to remote host. You can start sending messages'
    #sys.stdout.write('[Me] '); sys.stdout.flush()
     
    s.send("CERT") 
    filename = CERT_FILE
    f = open(filename,'rb')
    l = f.read(1024)
    while (l):
       s.send(l)
       #print('Sent ',repr(l))
       l = f.read(1024)
    f.close()
    s.send("END")
    print('Done sending CERT')

    RECV_CERT = "recv.cert"

    with open(RECV_CERT, 'wb') as f:
        print 'file opened'
        while True:
            print('receiving data...other cert')
            data = s.recv(1024)
            #print('data=%s', (data))
            if data[1] == "[":
                data = data.split("] ",1)[1]
            if data[-3:]=='END':
                data = data[:-3]
                f.write(data)
                break
            # write data to a file
            f.write(data)

    f.close()
    print('Successfully get the other cert file')

    os.system('openssl verify -CAfile CA.cert recv.cert')
    os.system('openssl x509 -inform pem -in recv.cert -pubkey -noout > publickey.pem')
    #KEY_FILE = "shruti.pem"
    pubkey = RSA.importKey(open('publickey.pem').read())
    cipher = PKCS1_OAEP.new(pubkey)


    while 1:
        socket_list = [sys.stdin, s]
         
        # Get the list sockets which are readable
        ready_to_read,ready_to_write,in_error = select.select(socket_list , [], [])
         
        for sock in ready_to_read:             
            if sock == s:
                # incoming message from remote server, s
                data = sock.recv(4096)
                if not data :
                    print '\nDisconnected from chat server'
                    sys.exit()
                else :
                    #print data
                    sys.stdout.write("                  Sender:")
                    data = plain.decrypt(data)
                    sys.stdout.write(data)
                    #sys.stdout.write('[Me] '); sys.stdout.flush()     
            
            else :
                # user entered a message
                #sys.stdout.write("Me:");
                msg = sys.stdin.readline()
                msg = cipher.encrypt(msg)
                s.send(msg)
                #sys.stdout.write('[Me] '); sys.stdout.flush() 

    

if __name__ == "__main__":

    sys.exit(chat_client())

import socket                   # Import socket module
import os
from OpenSSL import crypto, SSL
from socket import gethostname
from pprint import pprint
from time import gmtime, mktime
from Crypto.Cipher import PKCS1_OAEP
from Crypto.PublicKey import RSA
import pdb


CA_CERT_CSR = 'CA.cert.csr'
CA_KEY = 'CA.key'

port = 2020                  # Reserve a port for your service.
s = socket.socket()             # Create a socket object
host = "127.0.0.1"     # Get local machine name
s.bind((host, port))            # Bind to the port
s.listen(5)                     # Now wait for client connection.

print 'Server listening....'

def create_self_signed_cert():

    # create a key pair
    k = crypto.PKey()
    k.generate_key(crypto.TYPE_RSA, 1024)

    # create a self-signed cert
    cert = crypto.X509Req()
    cert.get_subject().C = "IN"
    cert.get_subject().ST = "Delhi"
    cert.get_subject().L = "Delhi"
    cert.get_subject().O = "IITD"
    cert.get_subject().OU = "Comp Sci"
    cert.get_subject().CN = "Cert Auth"
    cert.set_pubkey(k)
    cert.sign(k, 'sha1')
    open(CA_CERT_CSR, "wt").write(
        crypto.dump_certificate_request(crypto.FILETYPE_PEM, cert))
    open(CA_KEY, "wt").write(
        crypto.dump_privatekey(crypto.FILETYPE_PEM, k))



create_self_signed_cert()
os.system('openssl x509 -in CA.cert.csr -out CA.cert -req -signkey CA.key -days 365')
key = RSA.importKey(open(CA_KEY).read())
plain = PKCS1_OAEP.new(key)


while True:
    conn, addr = s.accept()     # Establish connection with client.
    print 'Got connection from', addr

    filename='CA.cert'
    f = open(filename,'rb')
    l = f.read(1024)
    while (l):
       conn.send(l)
       #print('Sent ',repr(l))
       l = f.read(1024)
    f.close()
    conn.send("END")
    print('Done sending CA cert')

    with open('client.cert.csr', 'wb') as f:
        print 'file opened'
        print('receiving data...')
        while True:
            data = conn.recv(128)
            data = plain.decrypt(data)
            #print('data=%s', (data))
            if data[-3:]=='END':
                data = data[:-3]
                f.write(data)
                break

        # write data to a file
            f.write(data)

    f.close()
    print('Successfully get the file')
    #s.close()   

    os.system('openssl x509 -req -in client.cert.csr -out client.cert -CA CA.cert -CAkey CA.key -CAcreateserial -days 365')
    os.system('openssl x509 -inform pem -in client.cert -pubkey -noout > client.pem')

    clpubkey = RSA.importKey(open('client.pem').read())
    clcipher = PKCS1_OAEP.new(clpubkey)

    filename='client.cert'
    f = open(filename,'rb')
    l = f.read(10)
    while (l):
        l = clcipher.encrypt(l)
        conn.send(l)
        #print('Sent ',repr(l))
        l = f.read(10)
    f.close()
    #conn.send("END")
    conn.send(clcipher.encrypt("END"))
    print('Done sending client cert')


    #conn.send('Thank you for connecting')
    conn.close()


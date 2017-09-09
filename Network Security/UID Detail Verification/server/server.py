#!/usr/bin/env python
import json
import sys
import rsa

path='C:\\xampp\\htdocs\\nss\\'
# key_path ='C:\\resources\\'

name = str(sys.argv[1])
dob = str(sys.argv[2])
fname = str(sys.argv[3])

msg = {"name":name,"dob":dob,"fname":fname}
msg = json.dumps(msg)

private_key = rsa.key.PrivateKey._load_pkcs1_pem(open('private_key.pem', 'rb').read())
sig = rsa.sign(msg.encode(),private_key,'SHA-256')

sig_enc=",".join([str(int(x)) for x in sig])
data = json.dumps({"msg":msg,"sig":sig_enc})

print(data)
file = open('make.tmp','w')
file.write(data)
file.close()

#sig_2 = [int(x) for x in sig_enc.split(",")]
#print(rsa.verify(msg.encode(),sig,private_key))
#print(sig_enc)
#print(sig)
#print(bytes(data)==sig)

#data = json.dumps({"msg":msg,"sig":str(sig)})

#data2 = (json.loads(data)["sig"])

'''
file = open(path+'make.tmp','w')
file.write(str(data2==sig))
file.write("\n")
file.close()
'''
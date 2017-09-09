# UID Detail Verification

In this project, a central server can be accessed to determine whether some information on an individual is correct or not but without divulging the information itself. 
The encrypted link is set up by SSL Certification. The server hashes its
response with SHA256 and encrypts it with RSA algorithm using its own private
key to create the digital signature of its response.
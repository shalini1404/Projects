import timeit


#Your statements here


s1=[[14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7],[0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8],[4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0],[15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13]]
s2=[[15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10],[3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5],[0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15],[13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9]]
s3=[[10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8],[13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1],[13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7],[1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12]]
s4=[[7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15],[13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9],[10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4],[3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14]]
s5=[[2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9],[14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6],[4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14],[11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3]]
s6=[[12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11],[10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8],[9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6],[4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13]]
s7=[[4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1],[13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6],[1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2],[6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12]]
s8=[[13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7],[1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2],[7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8],[2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11]]
#get 48bit key for each round
def permute_key(k, n):
	key = ['0' for i in range(48)]
	key[0]=k[13]
	key[1]=k[16]
	key[2]=k[10]
	key[3]=k[23]
	key[4]=k[0]
	key[5]=k[4]
	key[6]=k[2]
	key[7]=k[27]
	key[8]=k[14]
	key[9]=k[5]
	key[10]=k[20]
	key[11]=k[9]
	key[12]=k[22]
	key[13]=k[18]
	key[14]=k[11]
	key[15]=k[3]
	key[16]=k[25]
	key[17]=k[7]
	key[18]=k[15]
	key[19]=k[6]
	key[20]=k[26]
	key[21]=k[19]
	key[22]=k[12]
	key[23]=k[1]
	key[24]=k[40]
	key[25]=k[51]
	key[26]=k[30]
	key[27]=k[36]
	key[28]=k[46]
	key[29]=k[54]
	key[30]=k[29]
	key[31]=k[39]
	key[32]=k[50]
	key[33]=k[44]
	key[34]=k[32]
	key[35]=k[47]
	key[36]=k[43]
	key[37]=k[48]
	key[38]=k[38]
	key[39]=k[55]
	key[40]=k[33]
	key[41]=k[52]
	key[42]=k[45]
	key[43]=k[41]
	key[44]=k[49]
	key[45]=k[35]
	key[46]=k[28]
	key[47]=k[31]
	print "final 48 bit key for round",n,''.join(key)
	return key
#drop 8bits from64 bit key
def parity_drop(k):
	key = ['0' for i in range(56)]
	key[0]=k[56]
	key[1]=k[48]
	key[2]=k[40]
	key[3]=k[32]
	key[4]=k[24]
	key[5]=k[16]
	key[6]=k[8]
	key[7]=k[0]
	key[8]=k[57]
	key[9]=k[49]
	key[10]=k[41]
	key[11]=k[33]
	key[12]=k[25]
	key[13]=k[17]
	key[14]=k[9]
	key[15]=k[1]
	key[16]=k[58]
	key[17]=k[50]
	key[18]=k[42]
	key[19]=k[34]
	key[20]=k[26]
	key[21]=k[18]
	key[22]=k[10]
	key[23]=k[2]
	key[24]=k[59]
	key[25]=k[51]
	key[26]=k[43]
	key[27]=k[35]
	key[28]=k[62]
	key[29]=k[54]
	key[30]=k[46]
	key[31]=k[38]
	key[32]=k[30]
	key[33]=k[22]
	key[34]=k[14]
	key[35]=k[6]
	key[36]=k[61]
	key[37]=k[53]
	key[38]=k[45]
	key[39]=k[37]
	key[40]=k[29]
	key[41]=k[21]
	key[42]=k[13]
	key[43]=k[5]
	key[44]=k[60]
	key[45]=k[52]
	key[46]=k[44]
	key[47]=k[36]
	key[48]=k[28]
	key[49]=k[20]
	key[50]=k[12]
	key[51]=k[4]
	key[52]=k[27]
	key[53]=k[19]
	key[54]=k[11]
	key[55]=k[3]
	print "\nKey after dropping 8 bits:", ''.join(key)
	return key

#perform left rotation on left and right halves according to count value
def cleft(c,d,count,i):			
	t1=c[0]
	t2=d[0]
	if(count==1):
		c[:26]=c[1:]
		d[:26]=d[1:]
		c[27]=t1
		d[27]=t2

	else:
		t3=c[1]
		t4=d[1]
		c[:25]=c[2:]
		d[:25]=d[2:]
		c[26]=t1
		d[26]=t2
		c[27]=t3
		d[27]=t4

	c[28:56]=d
	print "\nkey for round",i,"after left rotation on left and right halves:",''.join(c)
	return c

def generate_key(key):
	print "\n*******Generating 48 bit keys for each round********"
	print "\nKey in Hex:",key
	key = list(bin(int(key,16))[2:].rjust(64,'0'))		#converting key into a list of binary bits
	print "Corresponding key in Binary:",''.join(key)
	key_array=[[] for i in range(17)]
	key_final=[[] for i in range(17)]
	hex_key=['a' for i in range(17)]
	key_array[0]=parity_drop(key)						#permute key while dropping 8 bits from the key
	#generate keys for each of 16rounds
	for i in range (1,17):
		if(i==1 or i==2 or i==9 or i==16):
			count=1
		else:
			count=2
		key_array[i]=cleft(key_array[i-1][:28], key_array[i-1][28:56], count,i)	#perform left rotation on left and right halves according to count value
		key_final[i]=permute_key(key_array[i], i)									#permute key for each round to get 48bit key
	print "\n*************KEY GENERATION ENDED*********************"
	return key_final
#perform initial permutation on plaintext
def initial_perm(p):												
	c=['0' for i in range(64)]
	c[0]=p[57]
	c[1]=p[49]
	c[2]=p[41]
	c[3]=p[33]
	c[4]=p[25]
	c[5]=p[17]
	c[6]=p[9]
	c[7]=p[1]
	c[8]=p[59]
	c[9]=p[51]
	c[10]=p[43]
	c[11]=p[35]
	c[12]=p[27]
	c[13]=p[19]
	c[14]=p[11]
	c[15]=p[3]
	c[16]=p[61]
	c[17]=p[53]
	c[18]=p[45]
	c[19]=p[37]
	c[20]=p[29]
	c[21]=p[21]
	c[22]=p[13]
	c[23]=p[5]
	c[24]=p[63]
	c[25]=p[55]
	c[26]=p[47]
	c[27]=p[39]
	c[28]=p[31]
	c[29]=p[23]
	c[30]=p[15]
	c[31]=p[7]
	c[32]=p[56]
	c[33]=p[48]
	c[34]=p[40]
	c[35]=p[32]
	c[36]=p[24]
	c[37]=p[16]
	c[38]=p[8]
	c[39]=p[0]
	c[40]=p[58]
	c[41]=p[50]
	c[42]=p[42]
	c[43]=p[34]
	c[44]=p[26]
	c[45]=p[18]
	c[46]=p[10]
	c[47]=p[2]
	c[48]=p[60]
	c[49]=p[52]
	c[50]=p[44]
	c[51]=p[36]
	c[52]=p[28]
	c[53]=p[20]
	c[54]=p[12]
	c[55]=p[4]
	c[56]=p[62]
	c[57]=p[54]
	c[58]=p[46]
	c[59]=p[38]
	c[60]=p[30]
	c[61]=p[22]
	c[62]=p[14]
	c[63]=p[6]
	print "\nText after initial permutation:",''.join(c)
	return c	
def inv_perm(p):
	c=['0' for i in range(64)]
	c[0]=p[39]
	c[1]=p[7]
	c[2]=p[47]
	c[3]=p[15]
	c[4]=p[55]
	c[5]=p[23]
	c[6]=p[63]
	c[7]=p[31]
	c[8]=p[38]
	c[9]=p[6]
	c[10]=p[46]
	c[11]=p[14]
	c[12]=p[54]
	c[13]=p[22]
	c[14]=p[62]
	c[15]=p[30]
	c[16]=p[37]
	c[17]=p[5]
	c[18]=p[45]
	c[19]=p[13]
	c[20]=p[53]
	c[21]=p[21]
	c[22]=p[61]
	c[23]=p[29]
	c[24]=p[36]
	c[25]=p[4]
	c[26]=p[44]
	c[27]=p[12]
	c[28]=p[52]
	c[29]=p[20]
	c[30]=p[60]
	c[31]=p[28]
	c[32]=p[37]
	c[33]=p[3]
	c[34]=p[43]
	c[35]=p[11]
	c[36]=p[51]
	c[37]=p[19]
	c[38]=p[59]
	c[39]=p[27]
	c[40]=p[34]
	c[41]=p[2]
	c[42]=p[42]
	c[43]=p[10]
	c[44]=p[50]
	c[45]=p[18]
	c[46]=p[58]
	c[47]=p[26]
	c[48]=p[33]
	c[49]=p[1]
	c[50]=p[41]
	c[51]=p[9]
	c[52]=p[49]
	c[53]=p[17]
	c[54]=p[57]
	c[55]=p[25]
	c[56]=p[32]
	c[57]=p[0]
	c[58]=p[40]
	c[59]=p[8]
	c[60]=p[48]
	c[61]=p[16]
	c[62]=p[56]
	c[63]=p[24]
	print "\nText after final permutation:",''.join(c)
	return c
def s_box(s,k):
	#print("KKKKK",k)
	r=int(int(k[0],2)*2+int(k[5],2))
	c=int(''.join(k[1:5]),2)
	#print("r,c", r, c)
	return list(bin(s[r][c])[2:].rjust(4,'0'))

def f_func(r,k,n):
	nr=['0' for i in range(48)]
	for i in range(32):
		j=((i/4)*6 + 1 + (i % 4))%48
		nr[j] = r[i]
		if (i%4 == 0):
			nr[((i/4)*6 -1)%48] = r[i]
		elif (i%4 == 3):
			nr[((i/4)*6 + 6)%48] = r[i]
	out=list(bin((int(''.join(nr),2)) ^ (int(''.join(k),2)))[2:].rjust(48,'0'))			#perform xor with key
	final=['0' for i in range(32)]
	ff=['0' for i in range(32)]
	#print("ouuuut", out[0])
	final[0:4]=s_box(s1,out[0:6])
	final[4:8]=s_box(s2,out[6:12])
	final[8:12]=s_box(s3,out[12:18])
	final[12:16]=s_box(s4,out[18:24])
	final[16:20]=s_box(s5,out[24:30])
	final[20:24]=s_box(s6,out[30:36])
	final[24:28]=s_box(s7,out[36:42])
	final[28:32]=s_box(s8,out[42:48])
	print "\nOutput of SBOX for round",n, ''.join(final)
	ff[0]=final[15]
	ff[1]=final[6]
	ff[2]=final[19]
	ff[3]=final[20]
	ff[4]=final[28]
	ff[5]=final[11]
	ff[6]=final[27]
	ff[7]=final[16]
	ff[8]=final[0]
	ff[9]=final[14]
	ff[10]=final[22]
	ff[11]=final[25]
	ff[12]=final[4]
	ff[13]=final[17]
	ff[14]=final[30]
	ff[15]=final[9]
	ff[16]=final[1]
	ff[17]=final[7]
	ff[18]=final[23]
	ff[19]=final[13]
	ff[20]=final[31]
	ff[21]=final[26]
	ff[22]=final[2]
	ff[23]=final[8]
	ff[24]=final[18]
	ff[25]=final[12]
	ff[26]=final[29]
	ff[27]=final[5]
	ff[28]=final[21]
	ff[29]=final[10]
	ff[30]=final[3]
	ff[31]=final[24]
	print "Final output of Fbox after round",n, ''.join(ff)
	return ff

	#print(nr)
def des_encrypt(plaintext,key):
	key_array = generate_key(key)										#generate 48bit key from 64bit key
	cipher_text = ['0' for i  in range(64)]
	plaintext= list(bin(int(plaintext,16))[2:].rjust(64,'0'))			#convert plaintext to list of binary bits
	print "\n******Encryting plaintext using key generated********"
	print "plaintext in binary:",''.join(plaintext)
	plaintext=initial_perm(plaintext)									#perform initial permutation on plaintext
	plain_array=[['a' for i in range(64)] for j in range(17)]
	plain_array[0]=plaintext
	#operations in each round
	for i in range(1,17):
		plain_array[i][0:32]=plain_array[i-1][32:64]
		plain_array[i][32:64]=list(bin(int(''.join(plain_array[i-1][0:32]),2)^(int(''.join(f_func(plain_array[i-1][32:64],key_array[i], i)),2)))[2:].rjust(32,'0'))	#perform xor with L and output of fbox
		print "Output after round",i ,hex(int(''.join(plain_array[i]),2))
	cipher_text[0:32]=plain_array[16][32:64]
	cipher_text[32:64]=plain_array[16][0:32]
	cipher_text=inv_perm(cipher_text)									#perform inverse permutation on data
	cipher_text = hex(int(''.join(cipher_text),2))
	print "\nFinal Ciphertext is:-",cipher_text
	print "\n*********ENCRYPTION ENDS**********"
	return cipher_text

def des_decrypt(ciphertext,key):
	key_array = generate_key(key)										#generate 48bit key from 64bit key
	plaintext = ['0' for i  in range(64)]
	print "\nCipherText input",ciphertext
	ciphertext = ciphertext[2:]
	ciphertext = ciphertext[:-1]
	ciphertext= list(bin(int(ciphertext,16))[2:].rjust(64,'0'))			#convert ciphertext to list of binary bits
	print "\n*******Decryting ciphertext using key generated*********"
	print "ciphertext in binary:",''.join(ciphertext)
	ciphertext=initial_perm(ciphertext)									#perform initial permutation on plaintext
	plain_array=[['a' for i in range(64)] for j in range(17)]
	plain_array[0]=ciphertext

	for i in range(1,17):
		plain_array[i][0:32]=plain_array[i-1][32:64]
		plain_array[i][32:64]=list(bin(int(''.join(plain_array[i-1][0:32]),2)^(int(''.join(f_func(plain_array[i-1][32:64],key_array[17-i], i)),2)))[2:].rjust(32,'0'))
		print "Output after round",i ,hex(int(''.join(plain_array[i]),2))
	plaintext[0:32]=plain_array[16][32:64]
	plaintext[32:64]=plain_array[16][0:32]
	plaintext=(inv_perm(plaintext))											#perform inverse permutation
	plaintext="{0:#0{1}x}".format((int(''.join(plaintext),2)),18)
	print "\nFinal Plaintext is:-",plaintext	
	print "\n*********DECRYPTION ENDS**********"				
	return plaintext
flag=1
# while flag:
# 	data = raw_input("Enter 64 bit data to be encrypted in hexadecimal:")			#input data from user
# 	if(len(data)>16):
# 		print "Data should be max 64bits long"
# 	else:
# 		flag=0

data='02468ACEECA86420'
key = '0F1571C947D9E859'
# key = raw_input("Enter 64 bit key to be used for encryption in hexadecimal:")	#input key from user
start = timeit.default_timer()
print "\n****************ENCRYPTION STARTS*******************"
#encryption algorithm starts
cipher = des_encrypt(data,key)
print "\n*******************DECRYPTION STARTS******************"
des_decrypt(cipher,key)
stop = timeit.default_timer()

print "Time taken for execution:",(stop - start) 
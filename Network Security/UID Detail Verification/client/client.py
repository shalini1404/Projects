import json
import rsa
import tkinter
from tkinter import Tk, messagebox
from tkinter.filedialog import askopenfilename
from tkinter import *
import tkinter.font as tkFont
from PIL import Image, ImageTk

def helloCallBack():
	path = askopenfilename()
	file = open(path,'r')
	data = json.loads(file.read())
	file.close
	msg_str=data["msg"]
	msg = json.loads(msg_str)
	sig = bytes([int(x) for x in data["sig"].split(",")])
	
	public_key = rsa.key.PublicKey._load_pkcs1_pem(open('public_key.pem').read())
	try:
		
		messagebox.showinfo( "Result", "Name: "+msg["name"]+"\nDoB: "+msg["dob"]+"\nFName: "+msg["fname"]+"\nVerified: "+str(rsa.verify(msg_str.encode(),sig,public_key)))
		#messagebox.geometry("100x100")
	except:
		messagebox.showinfo( "Result", "Not verified")

top = Tk()
top.wm_title("Server Response Verification")
top.configure(background='black')
top.geometry('{}x{}'.format(500, 300))
im = Image.open('11.png')
tkimage = ImageTk.PhotoImage(im)

myvar=tkinter.Label(top,image = tkimage)
myvar.place(x=0, y=0, relwidth=1, relheight=1)
#T = Text(top, relief="flat")
#T.insert(INSERT, "Select the downloaded file\nto check result from Server.")
#T.grid(padx=150, pady=50)
#T.config(font=("arial", 18), height=2, width=23, background="black", foreground="white")
#T.tag_configure("center", justify='center')
helv36 = tkFont.Font(family='arial', size=20, weight='bold')
B = tkinter.Button(top, text ="Browse", command = helloCallBack, width = 8, font=helv36, bg="black", fg="white")
#B.attribute("-alpha", .30)
B.grid(padx=160, pady=150)
top.mainloop()


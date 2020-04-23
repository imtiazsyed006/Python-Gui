from matplotlib.backends.backend_tkagg import (FigureCanvasTkAgg, NavigationToolbar2Tk)
from matplotlib.figure import Figure
import matplotlib.pyplot as plt
from matplotlib.pyplot import plot, ion, show
#import serial
import time
from drawnow import*
from tkinter import*
#=============================================================================================================================
#ser=serial.Serial('COM3',baudrate=9600)
#=============================================================================================================================
root=Tk()
root.title("CONTROL SYSTEM                               FINAL YEAR PROJECT                                Dr. Massab Junaid")
root.geometry("1350x670+0+0")
f0=Frame(root)
f0.grid(row=0,column=0)
commandframe=Frame(root)
commandframe.grid(row=1,column=0)
f1=Frame(root)
f1.grid(row=2,column=0)
f2=Frame(root,width=100)
f2.grid(row=0,column=1,rowspan=2)
fc=Frame(root)
fc.grid(row=0,column=2,rowspan=3)
toolbar_frame = Frame(root)
toolbar_frame.grid(row=3,column=2)
#=============================================================================================================================
option=StringVar()
option.set("All")
def selected_thermocouple (self):
  selected_option=option.get()
  a.clear()
  if selected_option=="All":
    a.clear()
    plot_graph(0)
  if selected_option=="Thermocouple 1":
    a.clear()
    plot_graph(1)
  if selected_option=="Thermocouple 2":
    a.clear()
    plot_graph(2)
  if selected_option=="Thermocouple 3":
    a.clear()
    plot_graph(3)
  if selected_option=="Thermocouple 4":
    a.clear()
    plot_graph(4)
  if selected_option=="Thermocouple 5":
    a.clear()
    plot_graph(5)
  if selected_option=="Thermocouple 6":
    a.clear()
    plot_graph(6)
#-----------------------------------------------------------------------------------------------------------------------------
check_plot=IntVar()
optionList = ["All","Thermocouple 1","Thermocouple 2","Thermocouple 3","Thermocouple 4","Thermocouple 5","Thermocouple 6"]
optionlabel=Label(fc,text="PLOT : ",width=10,font=('arial',12,'bold'),anchor='w')
optionlabel.grid(row=0,column=0)
thermocouples=OptionMenu(fc,option,*optionList,command=selected_thermocouple)
thermocouples.config(width=20,font=('arial',12,'bold'),relief="solid")
thermocouples.grid(row=0,column=1)
plot=Checkbutton(fc,variable=check_plot,onvalue=1,offvalue=0,text="Stop Plotting",font=('arial',12,'bold'))
plot.grid(row=0,column=2)
c=Canvas(fc,height=400,width=600)
c.grid(row=1,column=0,columnspan=3)
#=============================================================================================================================
speed=StringVar()
distance=StringVar()
off_set=StringVar()
massflowrate=StringVar()
t1=StringVar()
t2=StringVar()
t3=StringVar()
t4=StringVar()
t5=StringVar()
t6=StringVar()
message=StringVar()
massflowrate.set('')
t1.set('')
t2.set('')
t3.set('')
t4.set('')
t5.set('')
t6.set('')
message.set('')
#=============================================================================================================================
time_array=[]
temperature1=[]
temperature2=[]
temperature3=[]
temperature4=[]
temperature5=[]
temperature6=[]
#-----------------------------------------------------------------------------------------------------------------------------
f = Figure(figsize=(8,6), dpi=100)
a = f.add_subplot(111)
#-----------------------------------------------------------------------------------------------------------------------------
dataPlot = FigureCanvasTkAgg(f,c)
dataPlot.get_tk_widget().pack(side=TOP, fill=BOTH, expand=1)
#-----------------------------------------------------------------------------------------------------------------------------
toolbar = NavigationToolbar2Tk(dataPlot,toolbar_frame) 
toolbar.update()
#-----------------------------------------------------------------------------------------------------------------------------
def plot_graph(n):
  a.set_xlabel("Time")
  a.set_ylabel("Temperature")
  if n==0:
    a.scatter(time_array,temperature1,label="Thermocouple 1")
    a.scatter(time_array,temperature2,label="Thermocouple 2")
    a.scatter(time_array,temperature3,label="Thermocouple 3")
    a.scatter(time_array,temperature4,label="Thermocouple 4")
    a.scatter(time_array,temperature5,label="Thermocouple 5")
    a.scatter(time_array,temperature6,label="Thermocouple 6")
    a.legend(bbox_to_anchor=(0,0.93,1,0.2),loc="upper right",mode="expand",borderaxespad=0,ncol=3)
    dataPlot.draw()
  if n==1:
    a.scatter(time_array,temperature1,label="Thermocouple 1")
    dataPlot.draw()
  if n==2:
    a.scatter(time_array,temperature2,label="Thermocouple 2")
    dataPlot.draw()
  if n==3:
    a.scatter(time_array,temperature3,label="Thermocouple 3")
    dataPlot.draw()
  if n==4:
    a.scatter(time_array,temperature4,label="Thermocouple 4")
    dataPlot.draw()
  if n==5:
    a.scatter(time_array,temperature5,label="Thermocouple 4")
    dataPlot.draw()
  if n==6:
    a.scatter(time_array,temperature6,label="Thermocouple 4")
    dataPlot.draw()
#=============================================================================================================================
def reSet ():
  a.clear()
  speed.set('')
  distance.set('')
  massflowrate.set('')
  t1.set('')
  t2.set('')
  t3.set('')
  t4.set('')
  t5.set('')
  t6.set('')
  message.set('')
  del time_array[:]
  del temperature1[:]
  del temperature2[:]
  del temperature3[:]
  del temperature4[:]
  del temperature5[:]
  del temperature6[:]
  option.set("All")
  global file_name
  year=time.localtime().tm_year
  month=time.localtime().tm_mon
  day=time.localtime().tm_mday
  hours=time.localtime().tm_hour
  minutes=time.localtime().tm_min
  seconds=time.localtime().tm_sec
  file_name=str(year)+'_'+str(month)+'_'+str(day)+'_'+str(hours)+'_'+str(minutes)+'_'+str(seconds)
#=============================================================================================================================
def forward_motion ():
  if speedEntry.get().isdigit() and distanceEntry.get().isdigit():
    message.set('')
    v=int(speedEntry.get())
    d=int(distanceEntry.get())
    o=int(offsetEntry.get())
    data=str(v)+";"+str(d)+";"+str(o)+";"+"2"+";"
    ser.write(str(data).encode())
    set_state="disable"
    speedEntry.config(state=set_state)
    distanceEntry.config(state=set_state)
    offsetEntry.config(state=set_state)
    forward.config(state=set_state)
    backward.config(state=set_state)
    reset.config(state=set_state)
  else:
    message.set('Enter Speed And Distance')
def backward_motion ():
  if speedEntry.get().isdigit() and distanceEntry.get().isdigit():
    message.set('')
    v=int(speedEntry.get())
    d=int(distanceEntry.get())
    o=int(offsetEntry.get())
    data=str(v)+";"+str(d)+";"+str(o)+";"+"1"+";"
    ser.write(str(data).encode())
    set_state="disable"
    speedEntry.config(state=set_state)
    distanceEntry.config(state=set_state)
    offsetEntry.config(state=set_state)
    forward.config(state=set_state)
    backward.config(state=set_state)
    reset.config(state=set_state)
  else:
    message.set('Enter Speed And Distance')
def enable_interface():
  set_state="normal"
  speedEntry.config(state=set_state)
  distanceEntry.config(state=set_state)
  offsetEntry.config(state=set_state)
  forward.config(state=set_state)
  backward.config(state=set_state)
  reset.config(state=set_state)
#=============================================================================================================================
blankLabel0=Label(f0,height=1)
blankLabel0.grid(column=0,row=0,columnspan=2)
#-----------------------------------------------------------------------------------------------------------------------------
speedLabel=Label(f0,font=('arial',20,'bold'),width=15,text="SPEED (mm/min)",fg="green",relief=FLAT,anchor='center')
speedLabel.grid(column=0,row=1)
speedEntry=Entry(f0,textvariable=speed,font=('arial',20,'bold'),width=8,relief="solid")
speedEntry.grid(column=1,row=1)
#-----------------------------------------------------------------------------------------------------------------------------
#-----------------------------------------------------------------------------------------------------------------------------
distanceLabel=Label(f0,font=('arial',20,'bold'),width=15,text="DISTANCE (mm)",fg="green",relief=FLAT,anchor='center')
distanceLabel.grid(column=0,row=2)
distanceEntry=Entry(f0,textvariable=distance,font=('arial',20,'bold'),width=8,relief="solid")
distanceEntry.grid(column=1,row=2)
offsetLabel=Label(f0,font=('arial',20,'bold'),width=15,text="OFFSET (mm)",fg="green",relief=FLAT,anchor='center')
offsetLabel.grid(column=0,row=3)
offsetEntry=Entry(f0,textvariable=off_set,font=('arial',20,'bold'),width=8,relief="solid")
offsetEntry.grid(column=1,row=3)
#-----------------------------------------------------------------------------------------------------------------------------
blankLabel2=Label(f0,height=1)
blankLabel2.grid(column=0,row=4,columnspan=3)
#-----------------------------------------------------------------------------------------------------------------------------
flowrateLabel=Label(f0,text="FLOW RATE (L/hr)",fg='blue',width=15,font=('arial',20,'bold'),relief=FLAT,anchor='center')
flowrateLabel.grid(column=0,row=5)
flowrate=Label(f0,textvariable=massflowrate,font=('arial',20,'bold'),width=7,fg="blue",relief="groove")
flowrate.grid(column=1,row=5)
#-----------------------------------------------------------------------------------------------------------------------------
messageLabel3=Label(f0,textvariable = message,font=('arial',16,'bold'),fg="red")
messageLabel3.grid(column=0,row=6,columnspan=2)
#-----------------------------------------------------------------------------------------------------------------------------
forward=Button(commandframe, text = "FORWARD",fg="purple",bg="skyblue",font=('arial',16,'bold'),bd=5,relief=RAISED,command=forward_motion)
forward.grid(row=0,column=0)
backward=Button(commandframe, text = "BACKWARD",fg="purple",bg="skyblue",font=('arial',16,'bold'),bd=5,relief=RAISED,command=backward_motion)
backward.grid(row=0,column=1)
reset=Button(commandframe, text = "RESET",fg="purple",bg="skyblue",font=('arial',16,'bold'),bd=5,relief=RAISED,command=reSet)
reset.grid(row=0,column=2)
#=============================================================================================================================
tc1label=Label(f1,text="Thermocouple 1 : ",font=('arial',18,'bold'))
tc1label.grid(row=0,column=0)
tc1=Label(f1,textvariable=t1,width=8,font=('arial',18,'bold'),fg="red")
tc1.grid(row=0,column=1)
#-----------------------------------------------------------------------------------------------------------------------------
tc2label=Label(f1,text="Thermocouple 2 : ",font=('arial',18,'bold'))
tc2label.grid(row=1,column=0)
tc2=Label(f1,textvariable=t2,width=8,font=('arial',18,'bold'),fg="red")
tc2.grid(row=1,column=1)
#-----------------------------------------------------------------------------------------------------------------------------
tc3label=Label(f1,text="Thermocouple 3 : ",font=('arial',18,'bold'))
tc3label.grid(row=2,column=0)
tc3=Label(f1,textvariable=t3,width=8,font=('arial',18,'bold'),fg="red")
tc3.grid(row=2,column=1)
#-----------------------------------------------------------------------------------------------------------------------------
tc4label=Label(f1,text="Thermocouple 4 : ",font=('arial',18,'bold'))
tc4label.grid(row=3,column=0)
tc4=Label(f1,textvariable=t4,width=8,font=('arial',18,'bold'),fg="red")
tc4.grid(row=3,column=1)
#-----------------------------------------------------------------------------------------------------------------------------
tc5label=Label(f1,text="Thermocouple 5 : ",font=('arial',18,'bold'))
tc5label.grid(row=4,column=0)
tc5=Label(f1,textvariable=t5,width=8,font=('arial',18,'bold'),fg="red")
tc5.grid(row=4,column=1)
#-----------------------------------------------------------------------------------------------------------------------------
tc6label=Label(f1,text="Thermocouple 6 : ",font=('arial',18,'bold'))
tc6label.grid(row=5,column=0)
tc6=Label(f1,textvariable=t6,width=8,font=('arial',18,'bold'),fg="red")
tc6.grid(row=5,column=1)
#=============================================================================================================================
global file_name
year=time.localtime().tm_year
month=time.localtime().tm_mon
day=time.localtime().tm_mday
hours=time.localtime().tm_hour
minutes=time.localtime().tm_min
seconds=time.localtime().tm_sec
file_name=str(year)+'_'+str(month)+'_'+str(day)+'_'+str(hours)+'_'+str(minutes)+'_'+str(seconds)
#=============================================================================================================================
def update_values():
  arduinoData = (ser.readline().strip())
  a_data=str(arduinoData.decode('utf-8'))
  if a_data!='s':
    data_array=a_data.split(',')
    Time=float(data_array[0])
    flow_rate=float(data_array[1])
    temp1=float(data_array[2])
    temp2=float(data_array[3])
    temp3=float(data_array[4])
    temp4=float(data_array[5])
    temp5=float(data_array[6])
    temp6=float(data_array[7])
    #----------------------------------------------------------------------------------------
    time_array.append(Time)
    temperature1.append(temp1)
    temperature2.append(temp2)
    temperature3.append(temp3)
    temperature4.append(temp4)
    temperature5.append(temp5)
    temperature6.append(temp6)
    #----------------------------------------------------------------------------------------
    massflowrate.set(flow_rate)
    #----------------------------------------------------------------------------------------
    t1.set(temp1)
    t2.set(temp2)
    t3.set(temp3)
    t4.set(temp4)
    t5.set(temp5)
    t6.set(temp6)
    with open(file_name+'.txt','a') as file:
      file.write(str(Time)+','+str(temp1)+','+str(temp2)+','+str(temp3)+','+str(temp4)+
                 ','+str(temp5)+','+str(temp6)+'\n')
    #----------------------------------------------------------------------------------------
    if check_plot.get()==0:
      selected_thermocouple(0)
  if a_data=='s':
    enable_interface()
  root.after(50,update_values)
update_values()
root.mainloop()

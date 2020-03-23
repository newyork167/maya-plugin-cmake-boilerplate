import socket
import sys
#HOST = '192.168.1.122' # The remote host

HOST = '127.0.0.1' # the local host
PORT = 4434 # The same port as used by the server

# Run the following if you do not already have an MEL connection
#    import maya.cmds as cmds
#    if not cmds.commandPort(':4434', q=True):
#        cmds.commandPort(n=':4434')

def SendCommand(command, host=HOST, port=PORT):
    ADDR=(HOST,PORT)
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect(ADDR)
    #command = 'import maya.cmds as mc mc.polyCube()' # the command from external editor to maya

    print("TO_MAYA: {command}".format(command=command))

    client.send(command)
    data = client.recv(1024) #receive the result info
    client.close()

    print("FROM_MAYA: {data}".format(data=data))
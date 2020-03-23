import maya_socket
import argparse
import datetime

now = datetime.datetime.now()

parser = argparse.ArgumentParser(description='Load/Unload Maya Plugins.')
parser.add_argument("-p", "--plugin_name", help="Plugin Name", required=True)
parser.add_argument("-l", "--load", help="Load plugin", action="store_true", dest="plugin_load")
parser.add_argument("-u", "--unload", help="Unload plugin", action="store_true", dest="plugin_unload")
arguments = parser.parse_args()

plugin_name = arguments.plugin_name.strip()
print('{action} {plugin_name} @ {now_time}'.format(action="Loading" if arguments.plugin_load else "Unloading", plugin_name=plugin_name, now_time=now.strftime("%m/%d/%Y, %H:%M:%S")))

action = "loadPlugin" if arguments.plugin_load else "unloadPlugin"
maya_socket.SendCommand('print("{action} plugin: {plugin_name} @ {now_time}\\n")'.format(action="Loading" if arguments.plugin_load else "Unloading", plugin_name=plugin_name, now_time=now.strftime("%m/%d/%Y, %H:%M:%S")))
maya_socket.SendCommand('{action} "{plugin_name}"'.format(action=action, plugin_name=plugin_name))


import maya_socket
import argparse

parser = argparse.ArgumentParser(description='Load/Unload Maya Plugins.')
parser.add_argument("-p", "--plugin_name", help="Plugin Name", required=True)
parser.add_argument("-l", "--load", help="Load plugin", action="store_true", dest="plugin_load")
parser.add_argument("-u", "--unload", help="Unload plugin", action="store_true", dest="plugin_unload")
arguments = parser.parse_args()

action = "loadPlugin" if arguments.plugin_load else "unloadPlugin"
maya_socket.SendCommand('print("{action} plugin\\n")'.format(action="Loading" if arguments.plugin_load else "Unloading"))
maya_socket.SendCommand('{action} "{plugin_name}"'.format(action=action, plugin_name=arguments.plugin_name))


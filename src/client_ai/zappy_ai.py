#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys

from Zappy.ZappyData import *
from Zappy.ZappyClient import *

flags = ['-n', '-p', '-h']

def usage():
    print("USAGE")
    print("./client [-n team-name] [-p port] [-h machine-name]")

def readArgs(av):
    data = ZappyData()
    i = 1

    while (i < len(av)):
        if (av[i] == '--help'):
            usage()
            sys.exit(0)
        elif (av[i] in flags):
            if (av[i] == '-n'):
                data.team = av[i + 1]
            elif (av[i] == '-p'):
                data.port = int(av[i + 1])
            elif (av[i] == '-h'):
                data.machine = av[i + 1]
            i += 1
        else:
            raise ValueError
        i += 1
    if (data.machine == "localhost"):
        data.machine = '127.0.0.1'
    if (data.team == None or data.port == None or data.machine == None):
        usage()
        sys.exit(1)
    return data
    
def main(av):
    try:
        data = readArgs(av)
        client = ZappyClient(data)
    except (IndexError, ValueError):
        print("Invalid Argument", file=sys.stderr)
        return 1
    return client.run()

if (__name__ == "__main__"):
    sys.exit(main(sys.argv))

#!/usr/bin/env python3

class ZappyData:
    def __init__(self, team = None, port = None, machine = "localhost"):
        self.team = team
        self.port = port
        self.machine = machine
        self.xSize = 0
        self.ySize = 0
        self.clientNb = 0

    def __str__(self):
        return ("<ZappyData [team=" + str(self.team) +
                "; port=" + str(self.port) +
                "; machine=" + str(self.machine) + "]>")

#!/usr/bin/env python3

import sys
from random import randint
from collections import deque
from Zappy.CSocket import CSocket
from Zappy.ZappyRequest import ZappyRequest

elevationReq = {
    'ressources':['player',
                  'linemate', 'deraumere', 'sibur', 'mendiane', 'phiras', 'thystame'],
    1:[1,1,0,0,0,0,0],
    2:[2,1,1,1,0,0,0],
    3:[2,2,0,1,0,2,0],
    4:[4,1,1,2,0,1,0],
    5:[4,1,2,1,3,0,0],
    6:[6,1,2,3,0,1,0],
    7:[6,2,2,2,2,2,1],
}

class ZappyClient:
    commands = [
        ["avance", 7],
        ["droite", 7],
        ["gauche", 7],
        ["voir", 7],
        ["inventaire", 1],
        ["prend", 7],
        ["pose", 7],
        ["expulse", 7],
        ["broadcast", 7],
        ["incantation", 300],
        ["fork", 42],
        ["connect_nbr", 0]
    ]

    def __init__(self, data):
        self.log("Initializing client...")
        if (data.port == None or data.machine == None or data.team == None):
            raise ValueError
        self.data = data
        self.level = 1
        self.timeout = 100
        self.respBuffer = ""
        self.reqQueue = deque([], 10)
        self.inventory = {}
        self.view = []
        self.forked = False
        self.lastAction = None
        self.incanting = False
        self.lastResp = ""
        self.moved = True
        self.needed = [0,0,0,0,0,0]
        self.target = None
        self.log("\t" + str(data))
        self.log("Initializing socket...")
        self.socket = CSocket(data.port, data.machine)
        self.log("Connecting to server...")
        self.socket.connect()
        try:
            resp = self.read_response(self.timeout * 2000)
            if (len(resp) == 0):
                raise RuntimeError
            if (resp != "BIENVENUE"):
                raise ValueError
            self.send_cmd(self.data.team)
            resp = self.read_response(self.timeout * 2000)
            if (len(resp) == 0):
                raise RuntimeError
            self.data.clientNb = int(resp)
            resp = self.read_response(self.timeout * 2000)
            if (len(resp) == 0):
                raise RuntimeError
            s = resp.split()
            self.data.xSize = int(s[0])
            self.data.ySize = int(s[1])
        except RuntimeError:
            self.log("No response from server (timeout=" + str(self.timeout * 2000) + "ms)")
            sys.exit(1)
        except (TypeError, ValueError):
            self.log("Invalid response from server (\"" + resp + "\")")
            sys.exit(1)
        self.log("Connection to server established (clientNb="
                 + str(self.data.clientNb) + "; map=[" + str(self.data.xSize) + ";"
                 + str(self.data.ySize) + "]).")
        
    def run(self):
        self.log("Running client...")
        loop = True
        self.inventaire()
        while (loop):
            if (self.check_response()):
                loop = False
            if (len(self.reqQueue) < 10):
                self.decideAction()
        self.log("Client finished running...")
        
    def send_cmd(self, cmd):
        self.log("Sending command \"" + cmd + "\"...")
        self.socket.send(cmd + '\n')

    def commandIsPending(self, cmd):
        for i in self.reqQueue:
            if (i.cmd == cmd):
                return True
        return False
        
    def handleServerMessage(self, msg):
        s = msg.split()
        try:
            if (s[0] == "message"):
                s = msg.split(' ', 1)
                cont = s[1].split(',', 1)
                self.log("Received message \"" + cont[1] + "\" from " + cont[0] + ".")
            elif (s[0] == "deplacement:"):
                self.log("Expulsed to " + s[1] + ".")
            elif (s[0] == "mort"):
                self.log("Player has died.")
                return -1
            else:
                return 0
            return 1
        except IndexError:
            pass
        return 0
                
    def check_response(self):
        resp = self.read_response(self.timeout)
        if (resp != ""):
            ret = self.handleServerMessage(resp)
            if (ret == 0):
                req = self.reqQueue.pop()
                if (req.cb != None and req.isExpected(resp)):
                    req.cb(resp)
            elif (ret == -1):
                return 1
        return 0
        
    def read_response(self, timeout=0):
        resp = ""
        while (self.respBuffer.find('\n') == -1):
            resp = self.socket.receive(timeout)
            if (resp == ""):
                return resp
            self.respBuffer += resp
        ret = self.respBuffer[:self.respBuffer.find('\n')]
        self.respBuffer = self.respBuffer[self.respBuffer.find('\n') + 1:]
        #self.log("Received response: \"" + ret + "\"")
        self.lastResp = ret
        return ret

    def itemCount(self, item):
        try:
            return self.inventory[item]
        except:
            return 0
    
    def getObjective(self):
        ob = []
        try:
            if (self.itemCount('nourriture') < 7):
                ob.append('nourriture')
            for i in range(1, 7):
                c = self.itemCount(elevationReq['ressources'][i])
                if (c < elevationReq[self.level][i]):
                    ob.append(elevationReq['ressources'][i])
        except:
            pass
        return ob if (len(ob) != 0) else None

    def canElevate(self):
        need = elevationReq[self.level]
        if (self.view == None or len(self.view) < 1):
            return 0
        for i in range(len(need)):
            if (need[i]):
                item = elevationReq['ressources'][i]
                if (item == 'player'):
                    if (self.view[0].count('player') + 1 < need[i]):
                        return 0
                    continue
                elif (self.view[0].count(item) + self.inventory[item] < need[i]):
                    return 0
                elif (self.view[0].count(item) < need[i]):
                    return 2
        return 1

    def prepareIncantation(self):
        need = elevationReq[self.level]
        for i in range(len(need)):
            item = elevationReq['ressources'][i]
            if (item != 'player'):
                if (self.view[0].count(item) < need[i] and self.commandIsPending("pose") == False):
                    self.pose(item)
    
    def decideAction(self):
        if (self.lastAction != "inventaire" and not self.commandIsPending("inventaire")):
            return self.inventaire()
        if (self.incanting == False):
            el = self.canElevate()
            if (el == 1 and self.inventory['nourriture'] >= 7):
                return self.incantation()
            elif (el == 2):
                return self.prepareIncantation()
        if (randint(0, 60) == 42 and self.lastAction != "fork" and not self.commandIsPending('fork') and self.data.clientNb != 0 and self.forked == False):
            return self.fork()        
        if (self.lastAction != "voir" and (self.moved or self.lastAction in ['prend', 'pose'])):
            return self.voir()
        else:
            ob = self.getObjective()
            if (ob != None and self.view != None and len(self.view) >= 1):
                for i in ob:
                    if i in self.view[0] and not self.commandIsPending("prend") and not self.commandIsPending("incantation"):
                        return self.prend(i)
            r = randint(0, 5)
            f = self.avance
            if (r == 5):
                f = self.gauche
            elif (r == 4):
                f = self.droite
            return f() if (not self.commandIsPending("avance") and not self.commandIsPending("gauche") and not self.commandIsPending("droite")) else None
                    
    def avance(self):
        self.send_cmd("avance")
        self.reqQueue.appendleft(ZappyRequest("avance", ["ok"]))
        self.moved = True
        self.lastAction = "avance"

    def droite(self):
        self.send_cmd("droite")
        self.reqQueue.appendleft(ZappyRequest("droite", ["ok"]))
        self.moved = True
        self.lastAction = "droite"

    def gauche(self):
        self.send_cmd("gauche")
        self.reqQueue.appendleft(ZappyRequest("gauche", ["ok"]))
        self.moved = True
        self.lastAction = "gauche"

    def voir(self):
        self.send_cmd("voir")
        self.reqQueue.appendleft(ZappyRequest("avance", None, self.voir_cb))
        self.moved = False
        self.lastAction = "voir"

    def voir_cb(self, resp):
        #self.log("voir_cb")
        try:
            if (len(resp) > 2 and resp[0] == '{' and resp[-1] == '}'):
                tmp = []
                resp = resp.lstrip('{').rstrip('}')
                s = resp.split(',')
                for i in s:
                    tmp.append(i.split())
                self.view = tmp
                #self.log(str(self.view))
        except:
            self.log("voir: Invalid response from server.")
        return 1

    def inventaire(self):
        self.send_cmd("inventaire")
        self.reqQueue.appendleft(ZappyRequest("inventaire", None, self.inventaire_cb))
        self.lastAction = "inventaire"

    def inventaire_cb(self, resp):
        #self.log("inventaire_cb")
        try:
            if (len(resp) > 2 and resp[0] == "{" and resp[-1] == "}"):
                tmp = {}
                resp = resp.lstrip('{').rstrip('}')
                s = resp.split(',')
                for i in s:
                    sp = i.split()
                    tmp[sp[0]] = int(sp[1])
                    self.inventory = tmp
                return 0
        except (IndexError, ValueError):
            self.log("inventaire: Invalid response from server.")
        return 1

    def prend(self, arg):
        self.send_cmd("prend " + arg)
        self.reqQueue.appendleft(ZappyRequest("prend", ["ok", "ko"]))
        self.lastAction = "prend"

    def pose(self, arg):
        self.send_cmd("pose " + arg)
        self.reqQueue.appendleft(ZappyRequest("pose", ["ok", "ko"]))
        self.lastAction = "pose"

    def expulse(self):
        self.send_cmd("expulse")
        self.reqQueue.appendleft(ZappyRequest("expluse", ["ok", "ko"]))
        self.lastAction = "expulse"

    def broadcast(self, arg):
        self.send_cmd("broadcast " + arg)
        self.reqQueue.appendleft(ZappyRequest("broadcast", ["ok", "ko"]))

    def incantation(self):
        self.send_cmd("incantation")
        self.reqQueue.appendleft(ZappyRequest("incantation", None, self.incantation_cb))
        self.reqQueue.appendleft(ZappyRequest("incantation", None, self.incantation_cb))
        self.lastAction = "incantation"
        self.incanting = True

    def incantation_cb(self, resp):
        if (resp == "elevation en cours"):
            return
        if (resp == "ko"):
            self.reqQueue.pop()
        if (resp[0] == 'n'):
            self.level += 1
        self.incanting = False
        
    def fork(self):
        self.send_cmd("fork")
        self.reqQueue.appendleft(ZappyRequest("fork", ["ok"]))
        self.lastAction = "fork"
        self.forked = True

    def connect_nbr(self):
        self.send_cmd("connect_nbr")
        self.reqQueue.appendleft(ZappyRequest("connect_nbr", None, self.connect_nbr_cb))

    def connect_nbr_cb(self, resp):
        #self.log("connect_nbr_cb")
        try:
            self.data.clientNb = int(resp)
        except:
            self.log("Invalid response from sever.")
        
    def log(self, msg):
        print("ZappyClient: " + msg, file=sys.stderr)

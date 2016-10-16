#!/usr/bin/env python3

class ZappyRequest:
    def __init__(self, cmd, expected = None, cb = None):
        self.cmd = cmd
        self.expected = expected
        self.cb = cb
        self.resp = None

    def isExpected(self, resp):
        return 1 if (self.expected == None) else (resp in self.expected)

    def cb(self, resp = None):
        print("calling cb")
        if (resp != None):
            self.resp = resp
        return self.cb(self)

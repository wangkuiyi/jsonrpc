import json, socket

s = socket.create_connection(("localhost", 1234))

s.sendall(
    json.dumps({"id": 1, "method": "RPCFunc.Echo", "params": ["Cupid's Arrow"]}).encode())
print((s.recv(4096)).decode())

s.sendall(
    json.dumps({"id": 1, "method": "RPCFunc.Echo", "params": ["apple"]}).encode())
print((s.recv(4096)).decode())
